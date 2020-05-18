#pragma once

#include  <includes.h>
//命令相关

typedef struct{
	char *CMD;
	unsigned short len;
}ESP8266CMDTypeDef;





//串口相关
#define ESP8266BAUDRATE UART4BAUDRATE 
#define ESP8266READTIME (OSCfg_TickRate_Hz / (20000000 / ESP8266BAUDRATE)) //20000 = 20 （假设一个字节的bit数）* 1000ms


//ESP8266任务相关
#define ESP8266TaskStackSize 512//*4等于字节数
#define ESP8266TaskPrio 15
extern OS_TCB ESP8266TaskTCB;
extern CPU_STK ESP8266TaskStack[ESP8266TaskStackSize];


//ESP8266任务相关
#define ESP8266SendTaskStackSize 512//*4等于字节数
#define ESP8266SendTaskPrio 16
extern OS_TCB ESP8266SendTaskTCB;
extern CPU_STK ESP8266SendTaskStack[ESP8266SendTaskStackSize];

void ESP8266TaskPtr(void *p_arg);
void ESP8266SendTaskPtr(void *p_arg);
