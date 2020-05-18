/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include "fatfs.h"
#include <stdio.h>
#include <string.h>
uint8_t retSPINOR;    /* Return value for SD */
char SPINORPath[4];   /* SD logical drive path */
FATFS SPINORFatFS;    /* File system object for SD logical drive */
FIL SPINORFile;       /* File object for SD */

extern Diskio_drvTypeDef SPINOR_Driver;
/* USER CODE BEGIN Variables */

OS_MUTEX FATFS_MUTEX;

/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
//  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
	retSPINOR = FATFS_LinkDriver(&SPINOR_Driver,SPINORPath);
  /* USER CODE BEGIN Init */
  /* additional user code for init */     
  /* USER CODE END Init */
}
FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("%s/%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}
void FATFS_MKF(void)
{
	u8 work[4096];
	f_mkfs("0:",FM_FAT,4096,work,4096);
	
}
u8 IAPGetBinFileList(u8 FileList[6][10])
{
	FRESULT res;
	
    DIR dir;
	
    static FILINFO fno;
	u8 i = 0;
    res = f_opendir(&dir, "");
    if (res == FR_OK) {
		while (1) {
			res = f_readdir(&dir, &fno);                  
			if (res != FR_OK || fno.fname[0] == 0) 
				break;
			if (!(fno.fattrib & AM_DIR) && (fno.fname[0] == 'P' || fno.fname[0] == 'p')
				&& (memcmp(&fno.fname[2],".BIN",4) == 0 || memcmp(&fno.fname[2],".bin",4) == 0)) 			
			{  //已存在的文件名
				memcpy(FileList[fno.fname[1] - '0'],fno.fname,6);	
				i++;			
			}			 
		}
	}
	return i;
}
/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
