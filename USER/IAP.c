#include "IAP.h"
#include "AT_ESP8266.h"
#include "crc16.h"

OS_TCB IAPTaskTCB;
CPU_STK IAPTaskStack[IAPTaskStackSize];
OS_TCB  *IAPSendTaskTCB;
//IAP命令回调函数
static void IAPCmdCallbackFun_GETINFO(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_READ(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_ADD(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_RENAME(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_DEL(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_GO(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_READPRO(u8 *arg0,u16 arg1);
static void IAPCmdCallbackFun_WRITEPRO(u8 *arg0,u16 arg1);

static IAPCMDStructDef IAPCMDList[IAPCMD_COUNT] = {
	{IAPCMD_GETINFO,"GETINFO",0,sizeof("GETINFO") - 1,IAPCmdCallbackFun_GETINFO},
	{IAPCMD_READ,"READ",1,sizeof("READ") - 1,IAPCmdCallbackFun_READ},
	{IAPCMD_ADD,"ADD",2,sizeof("ADD") - 1,IAPCmdCallbackFun_ADD},
	{IAPCMD_RENAME,"RENAME",2,sizeof("RENAME") - 1,IAPCmdCallbackFun_RENAME},
	{IAPCMD_DEL,"DEL",2,sizeof("DEL") - 1,IAPCmdCallbackFun_DEL},
	{IAPCMD_GO,"GO",0,sizeof("GO") - 1,IAPCmdCallbackFun_GO},
	{IAPCMD_READPRO,"RPRO",0,sizeof("RPRO") - 1,IAPCmdCallbackFun_READPRO},
	{IAPCMD_WRITEPRO,"WPRO",0,sizeof("WPRO") - 1,IAPCmdCallbackFun_WRITEPRO}
	
};

//IAP回显消息
#define IAPECHO_OK ToString(\r\nRES  OK\r\n)
#define IAPECHO_ERROR ToString(\r\nRES  ERROE\r\n)
#define IAPECHO_Readpro ToString(Read protection)
#define IAPECHO_Writepro  ToString(Write protection)
#define IAPECHO_UNReadpro ToString(Un Read protection)
#define IAPECHO_UNWritepro ToString(Un Write protection)
#define IAPECHO_WAIT ToString(WAIT...)
#define IAPECHO_READY ToString(READY)
#define IAPECHO_CRCERR ToString(CRCERR)
#define IAPECHO_SADDRERR ToString(SADDRERR)
//读写保护位
static u8 ReadProtectionFlag = 1,WriteProtectionFlag = 2;

OS_MSG_SIZE MSG_Size;
u8 *PendingBuf;


//u16 MsgLength = 0;

void IAPErrorHendler(IAPERROR err)
{
	OS_ERR p_err;
	switch(err)
	{	
		
		case ERROR_NOIAPCMD:
		case ERROR_NOFOUNDCMD:			
		case ERROR_DATA:
			OSTaskQPost(IAPSendTaskTCB,(void *)PendingBuf,MSG_Size,OS_OPT_POST_FIFO,&p_err);
			break;
		case ERROR_READPRO:
		{			
			OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_Readpro,strlen(IAPECHO_Readpro),OS_OPT_POST_FIFO,&p_err);	
		}
			break;
		case ERROR_WRITEPRO:
		{			
			OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_Writepro,strlen(IAPECHO_Writepro),OS_OPT_POST_FIFO,&p_err);	
		}
			break;
		case ERROR_CRC:
		{			
			OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_CRCERR,strlen(IAPECHO_CRCERR),OS_OPT_POST_FIFO,&p_err);	
		}
			break;
		case ERROR_SADDR:
		{			
			OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_SADDRERR,strlen(IAPECHO_SADDRERR),OS_OPT_POST_FIFO,&p_err);	
		}
			break;
		default:
			break;
	}
	
	
	OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
	OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_ERROR,strlen(IAPECHO_ERROR),OS_OPT_POST_FIFO,&p_err);		
}
void IAPTaskPtr(void *p_arg)
{
	OS_ERR p_err;
	u16 PendingBufIndex = 0;
	while(1)
	{		
		u8 i = 0;
		PendingBufIndex = 0 ;
		PendingBuf = (u8 *)OSTaskQPend(0,OS_OPT_PEND_BLOCKING,&MSG_Size,0,&p_err);
		
		if(memcmp(&PendingBuf[PendingBufIndex],"IAP",3) != 0 || PendingBuf[MSG_Size - 1] != ';')//不是IAP命令		
		{
			IAPErrorHendler(ERROR_NOIAPCMD);
			continue;
		}
		
		PendingBufIndex += 3;
		do{
			if(memcmp(&PendingBuf[PendingBufIndex],IAPCMDList[i].CmdStr,IAPCMDList[i].CmdStrLen) == 0)
			{
				if(IAPCMDList[i].Attribute & ReadProtectionFlag)
				{				
					IAPErrorHendler(ERROR_READPRO);
					break;
				}
				if(IAPCMDList[i].Attribute & WriteProtectionFlag)
				{
					
					IAPErrorHendler(ERROR_WRITEPRO);
					break;
				}
				if(IAPCMDList[i].CallbackFun){
					IAPCMDList[i].CallbackFun(&PendingBuf[PendingBufIndex + IAPCMDList[i].CmdStrLen],MSG_Size - PendingBufIndex);								
				}
				break;
			}
		}while(++i < IAPCMD_COUNT);
		if(i == IAPCMD_COUNT){
			//不存在的命令

			IAPErrorHendler(ERROR_NOFOUNDCMD);			
		}
	}
}




static void IAPCmdCallbackFun_GETINFO(u8 *arg0,u16 arg1)
{
	u8 FileList[6][10];
	 u8 i = 0;
	i = IAPGetBinFileList(FileList);
	while(i--)
		printf("%s\r\n",FileList[i]);
	
	
	LED0 = 0;
	LED1 = 0;
	LED2 = 1;
}

static void IAPCmdCallbackFun_READ(u8 *arg0,u16 arg1)
{
	
	LED0 = 0;
	LED1 = 1;
	LED2 = 0;
}
u8 IAPSaveBinFile(u8 *DataMsg,u32 DataMsgSize,u16 CRC16RES,u32 StartAddr)
{
	//获取文件列表 得到下一个是P？支持p0 - pe
	
	//新建一个二进制文件，已存在的文件将内容清空，只允许写（w）
	
	u8 FileList[6][10];
	u8 i = 0;
	UINT PW;
	
	u8 STRing[8];
	
	
	
	u8 FileName[9] = "0:P0.BIN";
	
		FATFS *ffp = &SPINORFatFS;
	
	i = IAPGetBinFileList(FileList);
	
	FileName[3] += i;
	
	f_mount(ffp,"0:",1);
	f_open(&SPINORFile,FileName,FA_CREATE_ALWAYS | FA_WRITE);
	
	sprintf(STRing,"%x",CRC16RES);
	f_write(&SPINORFile,STRing,4,&PW);
	sprintf(STRing,"%x",StartAddr);

	f_write(&SPINORFile,STRing,6,&PW);
	f_write(&SPINORFile,DataMsg,DataMsgSize,&PW);
	f_close(&SPINORFile);
	return 0;
}
static void IAPCmdCallbackFun_ADD(u8 *buf,u16 size)
{
	//ADD->"CRC"->CRCRES->rvsbyte1(保留一个字节位)->"SADDR"->ADDR->rvsbyte2(保留一个字节位)
	
	__IO u16 CRC16RES = 0;
	u32 StartAddr = 0;
	u32 *IAP_Msg = 0;
	 OS_ERR       p_err;
	const u8 rvsbyte1index = 7;
	OS_MSG_SIZE DataMsgSize;
	u8 *DataMsg;
	LED0 = 1;
	LED1 = 0;
	LED2 = 0;
	/*Start*///CRC1234RSADDR12345678
	OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_WAIT,strlen(IAPECHO_WAIT),OS_OPT_POST_FIFO,&p_err);
	if(memcmp(buf,"CRC",3) == 0 && StringToHex(&buf[3],4,(u32 *)&CRC16RES))
	{
//		buf[rvsbyte1index] = 0;
//		sscanf(&buf[3],"%x",&CRC16RES);
	}
	else{
		
		IAPErrorHendler(ERROR_CRC);
		return ;
	}
	if(memcmp(&buf[rvsbyte1index + 1],"SADDR",5) == 0 && StringToHex(&buf[rvsbyte1index + 6],8,(u32 *)&StartAddr)){
//		buf[rvsbyte2index] = 0;
//		sscanf(&buf[rvsbyte1index + 6],"%x",&StartAddr);
		/*检查地址合法性*/
		
		
		
	}
	else{			
		IAPErrorHendler(ERROR_SADDR);
		return ;
	}	
	
	OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
	OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_READY,strlen(IAPECHO_READY),OS_OPT_POST_FIFO,&p_err);	
	//准备就绪等待数据
	DataMsg = (u8 *)OSTaskQPend(0,OS_OPT_PEND_BLOCKING,&DataMsgSize,0,&p_err);
	if(CRC16RES != getCRC16(DataMsg,DataMsgSize))//获取到要下载的数据，开始校验
	{
		
		printf("%X\r\n%d\r\n",CRC16RES,DataMsgSize);
		IAPErrorHendler(ERROR_CRC);
		return ;
	}
	/*校验通过，开始保存*/
	/*获取文件系统互斥信号量*/
	OSMutexPend(&FATFS_MUTEX,0,OS_OPT_PEND_BLOCKING,0,&p_err);
	IAPSaveBinFile(DataMsg,DataMsgSize,CRC16RES,StartAddr);
	OSMutexPost(&FATFS_MUTEX,OS_OPT_POST_NONE,&p_err);
}
static void IAPCmdCallbackFun_RENAME(u8 *arg0,u16 arg1)
{
	LED0 = 0;
	LED1 = 1;
	LED2 = 1;
	
}
static void IAPCmdCallbackFun_DEL(u8 *arg0,u16 arg1)
{
	LED0 = 1;
	LED1 = 0;
	LED2 = 1;
}
static void IAPCmdCallbackFun_GO(u8 *arg0,u16 arg1)
{
	LED0 = 1;
	LED1 = 1;
	LED2 = 0;
}
static void IAPCmdCallbackFun_READPRO(u8 *arg0,u16 arg1)
{
	 OS_ERR p_err;
	if(memcmp(arg0,"=1",2) == 0){//读保护
		
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_Readpro,strlen(IAPECHO_Readpro),OS_OPT_POST_FIFO,&p_err);	
	
		ReadProtectionFlag = 1;
		
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_OK,strlen(IAPECHO_OK),OS_OPT_POST_FIFO,&p_err);	
	
	}
	else if(memcmp(arg0,"=0",2) == 0){//解除读保护
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_UNReadpro,strlen(IAPECHO_UNReadpro),OS_OPT_POST_FIFO,&p_err);	
	
		ReadProtectionFlag = 0;
		
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_OK,strlen(IAPECHO_OK),OS_OPT_POST_FIFO,&p_err);	
	}
}
static void IAPCmdCallbackFun_WRITEPRO(u8 *arg0,u16 arg1)
{
	 OS_ERR p_err;
	
	if(memcmp(arg0,"=1",2) == 0){//写保护
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_Writepro,strlen(IAPECHO_Writepro),OS_OPT_POST_FIFO,&p_err);	
	
		WriteProtectionFlag = 2;
		
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_OK,strlen(IAPECHO_OK),OS_OPT_POST_FIFO,&p_err);	
	}
	else if(memcmp(arg0,"=0",2) == 0){//解除写保护
		
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_UNWritepro,strlen(IAPECHO_UNWritepro),OS_OPT_POST_FIFO,&p_err);	
	
		WriteProtectionFlag = 0;
		
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&p_err);
		OSTaskQPost(IAPSendTaskTCB,(void *)IAPECHO_OK,strlen(IAPECHO_OK),OS_OPT_POST_FIFO,&p_err);	
	}
}

