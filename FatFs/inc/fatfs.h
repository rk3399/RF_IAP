/**
  ******************************************************************************
  * @file   fatfs.h
  * @brief  Header for fatfs applications
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __fatfs_H
#define __fatfs_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "ff.h"
#include "ff_gen_drv.h"
#include "w25qxx.h" 

#include  <includes.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern uint8_t retSPINOR;    /* Return value for SD */
extern char SPINORPath[4];   /* SD logical drive path */
extern FATFS SPINORFatFS;    /* File system object for SD logical drive */
extern FIL SPINORFile;       /* File object for SD */
void MX_FATFS_Init(void);
FRESULT scan_files (char* path );    
u8 IAPGetBinFileList(u8 FileList[6][10]);
void FATFS_MKF(void);
/* USER CODE BEGIN Prototypes */

extern OS_MUTEX FATFS_MUTEX;
/* USER CODE END Prototypes */
#ifdef __cplusplus
}
#endif
#endif /*__fatfs_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
