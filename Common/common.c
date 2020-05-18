#include "common.h"

/*********************************************************************************
*************************MCU���� STM32F407���Ŀ�����******************************
**********************************************************************************
* �ļ�����: common.c                                                             *
* �ļ���������������������õĹ����ļ�                                           *
* �������ڣ�2015.03.03                                                           *
* ��    ����V1.0                                                                 *
* ��    �ߣ�Clever                                                               *
* ˵    ���������������Ͷ��塢IO��λ���塢λ�ζ�������ʱ��������                 * 
**********************************************************************************
*********************************************************************************/	  

/****************************************************************************
* ��    ��: void GPIO_group_OUT(_gpio_group *group,u16 outdata)
* ��    �ܣ�ʹ������16��IO�����һ��16λ���������
* ��ڲ�����*group�� ����16��IO��ΪԪ�صĽṹ��ָ��
            outdata: 16λ�����ֵ
* ���ز�������
* ˵    ����outdata�Ӹ�λ��ʼ��ֵ
****************************************************************************/
void GPIO_group_OUT(_gpio_group *group,u16 outdata)
{
	u8 t;
	for(t=0;t<16;t++)
    {               
        if((outdata&0x8000)>>15)  
				{
						switch(t)
						{
								case 0:	   group->data15=1; break;
								case 1:	   group->data14=1; break;
								case 2:	   group->data13=1; break;
								case 3:	   group->data12=1; break;
								case 4:	   group->data11=1; break;
								case 5:	   group->data10=1; break;
								case 6:	   group->data9=1;  break;
								case 7:	   group->data8=1;  break;
								case 8:	   group->data7=1;  break;
								case 9:	   group->data6=1;  break;
								case 10:	 group->data5=1;  break;
								case 11:	 group->data4=1;  break;
								case 12:	 group->data3=1;  break;
								case 13:	 group->data2=1;  break;
								case 14:	 group->data1=1;  break;
								case 15:	 group->data0=1;  break;
						}
				}
				else
				{
				  switch(t)
						{
								case 0:	   group->data15=0; break;
								case 1:	   group->data14=0; break;
								case 2:	   group->data13=0; break;
								case 3:	   group->data12=0; break;
								case 4:	   group->data11=0; break;
								case 5:	   group->data10=0; break;
								case 6:	   group->data9=0;  break;
								case 7:	   group->data8=0;  break;
								case 8:	   group->data7=0;  break;
								case 9:	   group->data6=0;  break;
								case 10:	 group->data5=0;  break;
								case 11:	 group->data4=0;  break;
								case 12:	 group->data3=0;  break;
								case 13:	 group->data2=0;  break;
								case 14:	 group->data1=0;  break;
								case 15:	 group->data0=0;  break;
						}
				}
     outdata<<=1; 	
	  }
}
/****************************************************************************
* ��    ��: void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
* ��    �ܣ�λ�β���ʵ�֣�ͬһIO�ڵļ�λ�����������
* ��ڲ�����* GPIOx��  ��Ӧ��IO��
*           start_bit: �����������ʼλ
*           bit_size:  Ҫ���������λ��
* ���ز�������
* ˵    ����start_bit: 0~14
            bit_size:  1~16 
            bit_size<=16-start_bit
****************************************************************************/
void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
{
  u8 i=0;
	u16 bu1=0;u16 middata=1;

	if( bit_size>(16-start_bit) ) 
     bit_size=16-start_bit;
	
	i=start_bit;
	if(i>0)
		 {
			 while(i--)
         { bu1+=middata; middata*=2;}
		 }
	
   assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
   
	 GPIOx->ODR&=(  ( (0xffff<<bit_size) <<start_bit ) |bu1   ); 
	 GPIOx->ODR|=(outdata<<start_bit);		 
}

/*****************************************************************************
*****************************���´���ο�����*********************************
*****************************************************************************/
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//���������ж�
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
unsigned char StringToHex(u8 *Str, u16 len,u32 *Res)
{
	unsigned char i = 0;
	if(len > 8)
		return 0;
	while(i < len)
	{			
		if(Str[i] <= '9' && Str[i] >= '0'){
			*Res <<= 4;
			*Res |= Str[i] - '0';
		}else if(Str[i] >= 'a' && Str[i] <= 'f'){
			*Res <<= 4;
			*Res |= Str[i] - 'a' + 10;
		}else if(Str[i] >= 'A' && Str[i] <= 'F'){
			*Res <<= 4;
			*Res |= Str[i] - 'A' + 10;
		}else{
			return 0;
		}
		i++;
	}
	return 1;
}

//������ת�ַ���
unsigned char IntTooString(unsigned char* String, unsigned int inttype)
{
	unsigned char i = 0;
	if (inttype < 10) {
		*String = inttype + '0';
		return 1;
	}else
	{
		i = IntTooString(String, inttype / 10) + 1;
		String[i - 1] = inttype % 10 + '0';
		return i;
	}
}
//�ַ���ת������
unsigned int StringTooInt(unsigned char* String, unsigned char strlen)
{
	unsigned int res = 0;
	while (--strlen && *String <= '9' && *String >= '0')
		res = (res + (*(String++) - '0')) * 10;

	return strlen ? 0 : res + ((*String) - '0');
}

