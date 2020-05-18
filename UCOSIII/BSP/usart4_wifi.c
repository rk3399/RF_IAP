#include "usart4_wifi.h"
#include "SqQueue.h"


/****************************************************************************
* ��    ��:uart4_init
* ��    �ܣ�LTE_uart4��ʼ��
* ��ڲ�����bound��������   
* ���ز�������
* ˵    ���� 
****************************************************************************/
void uart4_init(void)
{   
/****************************** ����4��ʼ��*********************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��USART4ʱ�� 
	USART_DeInit(UART4);  //��λ����4
	//����4��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	//USART4�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);        
	//USART4 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART4BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART4, &USART_InitStructure); 
	USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���4 

	USART_ClearFlag(UART4, USART_FLAG_TC);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);         //��������ж�
	//Usart4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  
	NVIC_Init(&NVIC_InitStructure);	  
/****************************** ����4��ʼ��**********************************/  
}

//ʹ��ESP8266 ������CH_PDΪ��
void ESP8266_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);          // 
	GPIO_SetBits(GPIOC, GPIO_Pin_1); 
}

//����1����һ���ַ�
void uart4SendChar(u8 ch)
{      
	while((UART4->SR&0x40)==0)
		;  
    UART4->DR = (u8) ch;      
}
/****************************************************************************
* ��    ��: void uart1SendChars(u8 *str, u16 strlen)
* ��    �ܣ�����1����һ�ַ���
* ��ڲ�����*str�����͵��ַ���
            strlen���ַ�������
* ���ز�������
* ˵    ����
****************************************************************************/
void uart4SendChars(u8 *str, u16 strlen)
{ 
	u16 k= 0 ; 
	do {
		uart4SendChar(*(str + k));
		k++;   //ѭ������,ֱ���������   
	}while (k < strlen); 
}




