#include "AT_ESP8266.h"
#include "common.h"

#include "SqQueue.h"
#include "bsp.h"

#include "IAP.h"
#define ESP8266CCMDCount		4

const ESP8266CMDTypeDef ESP8266InitCMDList[ESP8266CCMDCount] = {
	"AT\r\n",4,
	//"AT+CWMODE_DEF=2\r\n",17,
	//"AT+CWSAP_DEF=\"RF_IAP\",\"IAP_ESP8266\",1,3\r\n",41,
	"AT+CIPMODE=0\r\n",14,
	"AT+CIPMUX=1\r\n",13,
	"AT+CIPSERVER=1,52617\r\n",22
};
OS_TCB ESP8266TaskTCB;
CPU_STK ESP8266TaskStack[ESP8266TaskStackSize];


ArraySqQueueTypeDef ESP8266RxSqQueue = {0};
#define ESP8266LoopArraySize	2048
u8 ESP8266LoopArray[ESP8266LoopArraySize];


#define ESP8266_CMD_BufSize	128
u8 ESP8266_CMD_Buf[ESP8266_CMD_BufSize] = {0};

#define ESP8266_DATA_BufSize	0x100000
u8 ESP8266_DATA_Buf[ESP8266_DATA_BufSize] __attribute__((at(0X68000000)));

static void Tcp_sever_init(void )
{
	u8 i = 0;
	
	OS_ERR  p_err;
	OSTimeDlyHMSM(0,0,5,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
	while(i < ESP8266CCMDCount){
		uart4SendChars(ESP8266InitCMDList[i].CMD,ESP8266InitCMDList[i].len);
		
		OSTimeDlyHMSM(0,0,2,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
		i++;
	}
}

u8 *databuf	= "EX SRAN INFO\r\nTotal size:1024KB; Remaining size:1024KB";

static void ESP8266CMDHendler(u8 *cmdbuf,u16 cmdlen)
{
	 OS_ERR       p_err;
//	if(cmdbuf[cmdlen-1] != '\n' || cmdbuf[cmdlen - 2] != '\r')//���������������������
//		return ;
	
//	cmdbuf[cmdlen] = 0;//�����ַ���������
//	printf("%s",cmdbuf);
	if(strcmp(ESP8266_CMD_Buf,"0,CONNECT") == 0)
	{		
		LED0 = 0;
		//���͵���Ϣ����
		
		OSTaskQPost(&ESP8266SendTaskTCB,(void *)databuf,strlen(databuf),OS_OPT_POST_FIFO,&p_err);	
		
	}
	else if(strcmp(ESP8266_CMD_Buf,"0,CLOSED") == 0)
	{										
		LED0 = 1;
		//���͵���Ϣ����
			
			
	}			
}
void ESP8266SendNetData(u8 *buf,u16 len)
{
	OS_ERR  p_err;	
	u8 str[16],i;
	ESP8266CMDTypeDef ESP8266SendNetDataCmd = {"AT+CIPSENDEX=0,",15};
	i = IntTooString(str,len);
	str[i++] = '\r';
	str[i++] = '\n';
	uart4SendChars(ESP8266SendNetDataCmd.CMD,ESP8266SendNetDataCmd.len);
	uart4SendChars(str,i);
	
	OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&p_err);
	uart4SendChars(buf,len);	
}
void ESP8266TaskPtr(void *p_arg)
{
	OS_ERR  p_err;
	
	u16 ESP8266DataBufIndex = 0,ESP8266CmdBufIndex = 0;
	u8 tem = 0, Flag = 0;//�������ݱ�־λ
	u16 NetMsgLen = 0;
	ESP8266_init();       //��ʹ��ESP8266 ������CH_PDΪ��	
	uart4_init();	    //���ڳ�ʼ��
	
	Tcp_sever_init();
	
	
	/*��ʼ�����ڽ���ѭ������*/
	ArraySqQueueInit(&ESP8266RxSqQueue,ESP8266LoopArray,ESP8266LoopArraySize);
	
	while(1)
	{
		OSTaskSemPend(0, OS_OPT_PEND_BLOCKING, 0, &p_err);
		/*���ڽ��յ����ݿ�ʼ����*/
		
		NetMsgLen = ESP8266DataBufIndex = ESP8266CmdBufIndex = Flag = 0;//��ʼ��
//		memset(ESP8266_DATA_Buf,0,ESP8266_DATA_BufSize);
		memset(ESP8266_CMD_Buf,0,ESP8266_CMD_BufSize);
		
		while(1)
		{
			OutputQueueElement(&ESP8266RxSqQueue,&tem);
			if(p_err == OS_ERR_NONE)//�жϵȴ���������յ�����
			{				
				if(!Flag && ESP8266CmdBufIndex < ESP8266_CMD_BufSize)
				{
					/*����ǿɼ��ֽ�ֱ�ӱ��浽CMD buf��������Ӧ���ǿɼ��ֽڣ�*/
					if(ISVISIBLECHAR(tem))
						ESP8266_CMD_Buf[ESP8266CmdBufIndex++] = tem;
					
					/*�ж��ǲ��ǽ��յ���������*/
					if(ESP8266CmdBufIndex == 7 && memcmp(ESP8266_CMD_Buf,"+IPD,0,",ESP8266CmdBufIndex) == 0)
					{
						/*����ǣ��������ݱ�־λ��λΪ������������*/						
						Flag = 1;
						ESP8266CmdBufIndex = 0;
					}
				}
				else if(Flag == 1 && ESP8266CmdBufIndex < ESP8266_CMD_BufSize)			
				{		
					ESP8266_CMD_Buf[ESP8266CmdBufIndex++] = tem;
					/*���յ�':',�����������ݳ��Ȳ���λ�������ݱ�־λΪ��ʼ����ʵ����������*/
					if(tem == ':')
					{
						NetMsgLen += StringTooInt(ESP8266_CMD_Buf,ESP8266CmdBufIndex - 1);	
						Flag = 2;
					}
				}else if(Flag == 2){
					ESP8266_DATA_Buf[ESP8266DataBufIndex++] = tem;
					
					/*�ȴ��������*/
					if(ESP8266DataBufIndex == NetMsgLen)
					{
						/*����������ݱ�־λ��ʼ��һ���ڴ���*/
						Flag = 0;
						ESP8266CmdBufIndex = 0;
						printf("%d\r\n",ESP8266DataBufIndex);
					}
				}
			}else if(p_err == OS_ERR_TIMEOUT)//��ʱ�˳����������
			{
				if(ESP8266DataBufIndex){					
					//���յ������ݷ��͸�IAP����
					OSTaskQPost(&IAPTaskTCB,(void *)ESP8266_DATA_Buf,ESP8266DataBufIndex,OS_OPT_POST_FIFO,&p_err);																				
				}
				else{
					ESP8266CMDHendler(ESP8266_CMD_Buf,ESP8266CmdBufIndex); //����֡����			
				}
				break;
			}
			
			OSTaskSemPend(ESP8266READTIME, OS_OPT_PEND_BLOCKING, 0, &p_err);//�ȴ���һ���ֽ�
		}
	}
}


OS_TCB ESP8266SendTaskTCB;
CPU_STK ESP8266SendTaskStack[ESP8266SendTaskStackSize];


void ESP8266SendTaskPtr(void *p_arg)
{
	
	OS_ERR  p_err;
	u8 *SendBuf = 0;
	OS_MSG_SIZE size;
	while(1)
	{
		SendBuf = (u8 *)OSTaskQPend(0,OS_OPT_PEND_BLOCKING,&size,0,&p_err);
		
		ESP8266SendNetData(SendBuf,size);	
	}
}

//����4�жϷ������

void UART4_IRQHandler(void)
{
	OSIntEnter();    
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж� 
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		if(ESP8266RxSqQueue.ArrayZeroAddr){		
			OS_ERR  p_err;
			InputQueueElement(&ESP8266RxSqQueue,(u8)UART4->DR);
			OSTaskSemPost(&ESP8266TaskTCB,OS_OPT_POST_NONE,&p_err);		
		}			
	} 
	OSIntExit();  	
}

















