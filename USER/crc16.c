#include "crc16.h"

unsigned short getCRC16(volatile unsigned char *ptr,unsigned int len) 
{ 
    unsigned char i; 
    unsigned short crc = 0xFFFF; 
    if(len==0) 										  
    {
        len = 1;									 
    } 
    while(len--)  									 
    {   																	
        crc ^= *ptr; 								  
        for(i=0; i<8; i++)  						  
    	{ 											  						  
            if(crc&1) 								  
        	{ 										 
                crc >>= 1;  												   
                crc ^= 0xA001;   
        	}
        	else
    		{										  
                crc >>= 1;							 
        	}
        }         									 
        ptr++; 										  
    } 
    return(crc); 
}
