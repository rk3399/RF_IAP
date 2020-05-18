#ifndef __USART4_WIFI_H
#define __USART4_WIFI_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 


#define UART4BAUDRATE 115200


void ESP8266_init(void);
void uart4_init(void);


void uart4SendChars(u8 *str, u16 strlen);

#endif


