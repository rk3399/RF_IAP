#pragma once
#include "stm32f4xx.h"				    
#include "common.h" 								  
void SPI1_Init(void);			 
u8 SPI1_ReadWriteByte(u8 TxData);


void SPI2_Init(void);	
u8 SPI2_ReadWriteByte(u8 TxData);
		 

