#include "w25qxx.h" 

#include "hal_spi.h"

#include "ff_gen_drv.h"

#define W25QXX_TYPE  W25Q128	//Ĭ����W25Q64

#if W25QXX_TYPE == W25Q128

#define SPINOR_SECTOR_COUNT 	4096
#define SPINOR_SECTOR_SIZE		4096
#endif

//w25Qxx����spi2����
#define W25QXX_ReadWrite_byte(byte) SPI1_ReadWriteByte(byte)

#define W25QXX_SPI_Init()	 SPI1_Init()		   			//��ʼ��SPI

//4KbytesΪһ��Sector
//16������Ϊ1��Block
//W25Q128
//����Ϊ16M�ֽ�,����128��Block,4096��Sector 
													 
//��ʼ��SPI FLASH��IO��
u8 W25QXX_Init(void)
{  	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOGʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	
	W25QXX_CS=1;			//SPI FLASH��ѡ��
	
	W25QXX_SPI_Init();
	
	W25QXX_ReadWrite_byte(0xff);
	if(W25QXX_TYPE == W25QXX_ReadID())
		return 0;
	else if(W25QXX_TYPE == W25QXX_ReadID())
		return 0;
	else if(W25QXX_TYPE == W25QXX_ReadID())
		return 0;
	else 
		return 1;
}

//��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
static u8 W25QXX_ReadSR(void)   
{  
	u8 byte=0;   
	W25QXX_CS=0;                            //ʹ������   
	W25QXX_ReadWrite_byte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=W25QXX_ReadWrite_byte(0);             //��ȡһ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     
	return byte;   
} 
//дW25QXX״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
static void W25QXX_Write_SR(u8 sr)   
{   
	W25QXX_CS=0;                            //ʹ������   
	W25QXX_ReadWrite_byte(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	W25QXX_ReadWrite_byte(sr);               //д��һ���ֽ�  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
}   
//W25QXXдʹ��	
//��WEL��λ   
static void W25QXX_Write_Enable(void)   
{
	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_WriteEnable);      //����дʹ��  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 
//W25QXXд��ֹ	
//��WEL����  
static void W25QXX_Write_Disable(void)   
{  
	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_WriteDisable);     //����д��ָֹ��    
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
} 		
//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
static u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	W25QXX_CS=0;				    
	W25QXX_ReadWrite_byte(0x90);//���Ͷ�ȡID����	    
	W25QXX_ReadWrite_byte(0x00); 	    
	W25QXX_ReadWrite_byte(0x00); 	    
	W25QXX_ReadWrite_byte(0x00); 	 			   
	Temp|=W25QXX_ReadWrite_byte(0)<<8;  
	Temp|=W25QXX_ReadWrite_byte(0);	 
	W25QXX_CS=1;				    
	return Temp;
}   		    
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;   										    
	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_ReadData);         //���Ͷ�ȡ����   
    W25QXX_ReadWrite_byte((u8)((ReadAddr)>>16));  //����24bit��ַ    
    W25QXX_ReadWrite_byte((u8)((ReadAddr)>>8));   
    W25QXX_ReadWrite_byte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=W25QXX_ReadWrite_byte(0);   //ѭ������  
    }
	W25QXX_CS=1;  				    	      
}  
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
static void W25QXX_Write_Page(const u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    W25QXX_Write_Enable();                  //SET WEL 
	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_PageProgram);      //����дҳ����   
    W25QXX_ReadWrite_byte((u8)((WriteAddr)>>16)); //����24bit��ַ    
    W25QXX_ReadWrite_byte((u8)((WriteAddr)>>8));   
    W25QXX_ReadWrite_byte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
		W25QXX_ReadWrite_byte(pBuffer[i]);//ѭ��д��  
	W25QXX_CS=1;                            //ȡ��Ƭѡ 
	W25QXX_Wait_Busy();					   //�ȴ�д�����
} 
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
static void W25QXX_Write_NoCheck(const u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
}
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535) 

u8 W25QXX_BUF[4096];		 
void W25QXX_Write(const u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
//	u8  W25QXX_BUF[4096];	  
//   	W25QXX_BUF=W25QXX_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		W25QXX_Read(W25QXX_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25QXX_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			W25QXX_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				W25QXX_BUF[i+secoff]=pBuffer[i];	  
			}
			W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);//д����������  

		}else
			W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 

		   	pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		   	NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};
}
//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();                  //SET WEL 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_ChipErase);        //����Ƭ��������  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
	W25QXX_Wait_Busy();   				   //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ��ɽ��������ʱ��:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
	//����falsh�������,������   
// 	printf("fe:%x\r\n",Dst_Addr);	  
 	Dst_Addr*=4096;
    W25QXX_Write_Enable();                  //SET WEL 	 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_SectorErase);      //������������ָ�� 
    W25QXX_ReadWrite_byte((u8)((Dst_Addr)>>16));  //����24bit��ַ    
    W25QXX_ReadWrite_byte((u8)((Dst_Addr)>>8));   
    W25QXX_ReadWrite_byte((u8)Dst_Addr);  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
    W25QXX_Wait_Busy();   				   //�ȴ��������
}  
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
  	W25QXX_CS = 0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_PowerDown);        //���͵�������  
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
   // delay_us(3);                               //�ȴ�TPD  
}   
//����
void W25QXX_WAKEUP(void)   
{  
  	W25QXX_CS = 0;                            //ʹ������   
    W25QXX_ReadWrite_byte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	W25QXX_CS=1;                            //ȡ��Ƭѡ     	      
  //  delay_us(3);                               //�ȴ�TRES1
}   
#if _USE_IOCTL == 1
DRESULT SPINOR_ioctl(BYTE lun, BYTE cmd, void *buff)
{
  DRESULT res = RES_ERROR;


  switch (cmd)
  {
  /* Make sure that no pending write process */
  case CTRL_SYNC :
    res = RES_OK;
    break;

  /* Get number of sectors on the disk (DWORD) */
  case GET_SECTOR_COUNT :
    *(DWORD*)buff = SPINOR_SECTOR_COUNT;
    res = RES_OK;
    break;

  /* Get R/W sector size (WORD) */
  case GET_SECTOR_SIZE :
    *(WORD*)buff = SPINOR_SECTOR_SIZE;
    res = RES_OK;
    break;

  /* Get erase block size in unit of sector (DWORD) */
  case GET_BLOCK_SIZE :
   
    *(DWORD*)buff = 1;
    res = RES_OK;
    break;

  default:
    res = RES_PARERR;
  }

  return res;
}
#endif 
DSTATUS FAT_W25QXX_Init(BYTE lun)
{	
	return W25QXX_Init();
}
DSTATUS FAT_GetState(BYTE lun)
{
	W25QXX_Wait_Busy();
	return 0;
}
DRESULT FAT_W25QXX_Read(BYTE lun, BYTE* buf, DWORD sector, UINT Count)
{
	
	DRESULT res = RES_OK;
	W25QXX_Read(buf,sector * SPINOR_SECTOR_SIZE,Count * SPINOR_SECTOR_SIZE);
	return res;
}
DRESULT FAT_W25QXX_Write(BYTE lun, const BYTE* buf, DWORD sector, UINT Count)
{
	
	DRESULT res = RES_OK;
	W25QXX_Write(buf,sector * SPINOR_SECTOR_SIZE,Count * SPINOR_SECTOR_SIZE);
	return res;
}
Diskio_drvTypeDef SPINOR_Driver = {
	FAT_W25QXX_Init,
	FAT_GetState,
	FAT_W25QXX_Read,
	#if _USE_WRITE == 1
	FAT_W25QXX_Write,
	#endif
	#if _USE_IOCTL == 1
	SPINOR_ioctl
	#endif
};











