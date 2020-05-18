#include "usart4_wifi.h"
#include "SqQueue.h"


/****************************************************************************
* 名    称:uart4_init
* 功    能：LTE_uart4初始化
* 入口参数：bound：波特率   
* 返回参数：无
* 说    明： 
****************************************************************************/
void uart4_init(void)
{   
/****************************** 串口4初始化*********************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能USART4时钟 
	USART_DeInit(UART4);  //复位串口4
	//串口4对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4); 
	//USART4端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;      
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);        
	//USART4 初始化设置
	USART_InitStructure.USART_BaudRate = UART4BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART4, &USART_InitStructure); 
	USART_Cmd(UART4, ENABLE);  //使能串口4 

	USART_ClearFlag(UART4, USART_FLAG_TC);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);         //开启相关中断
	//Usart4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  
	NVIC_Init(&NVIC_InitStructure);	  
/****************************** 串口4初始化**********************************/  
}

//使能ESP8266 就是置CH_PD为高
void ESP8266_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);          // 
	GPIO_SetBits(GPIOC, GPIO_Pin_1); 
}

//串口1发送一个字符
void uart4SendChar(u8 ch)
{      
	while((UART4->SR&0x40)==0)
		;  
    UART4->DR = (u8) ch;      
}
/****************************************************************************
* 名    称: void uart1SendChars(u8 *str, u16 strlen)
* 功    能：串口1发送一字符串
* 入口参数：*str：发送的字符串
            strlen：字符串长度
* 返回参数：无
* 说    明：
****************************************************************************/
void uart4SendChars(u8 *str, u16 strlen)
{ 
	u16 k= 0 ; 
	do {
		uart4SendChar(*(str + k));
		k++;   //循环发送,直到发送完毕   
	}while (k < strlen); 
}




