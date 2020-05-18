#include "led.h"
#include "beep.h"
#include "key.h"

//#include <os_app_hooks.h>
#include  <includes.h>

#include "AT_ESP8266.h"

#include "IAP.h"


void StastTaskPtr(void *p_arg)
{
	
	OS_ERR  p_err;	
		
	u8 StartFlag = 3;
	
	
	CPU_INT32U  cpu_clk_freq;
	CPU_INT32U  cnts;
	CPU_Init();

	cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
	cnts         = cpu_clk_freq                                 /* Determine nbr SysTick increments                     */
			 / (CPU_INT32U)OSCfg_TickRate_Hz;

	OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */


	Mem_Init();                                                 /* Initialize memory managment module                   */
	Math_Init();   

	
	KEY_Init();
	LED_Init();		  	  //初始化与LED 
	BEEP_Init();          //蜂鸣器初始化
	
	MX_FATFS_Init();
	
	OSSchedLock(&p_err);//创建任务前挂起任务调度器
	
	OSMutexCreate(&FATFS_MUTEX,"FS",&p_err);
	OSMutexPost(&FATFS_MUTEX,OS_OPT_POST_NONE,&p_err);
	
	if(StartFlag == 3)//IAP
	{				
		OSTaskCreate(
		(OS_TCB*)&ESP8266TaskTCB,
		(CPU_CHAR *)"ESP8266Task",
		(OS_TASK_PTR)ESP8266TaskPtr,
		(void *)0,
		(OS_PRIO)ESP8266TaskPrio,
		(CPU_STK*)ESP8266TaskStack,
		(CPU_STK_SIZE)ESP8266TaskStackSize / 10,
		(CPU_STK_SIZE)ESP8266TaskStackSize,
		(OS_MSG_QTY)0,
		(OS_TICK)0,
		(void *)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP,
		&p_err
		);
		
		OSTaskCreate(
		(OS_TCB*)&ESP8266SendTaskTCB,
		(CPU_CHAR *)"ESP8266SendTask",
		(OS_TASK_PTR)ESP8266SendTaskPtr,
		(void *)0,
		(OS_PRIO)ESP8266SendTaskPrio,
		(CPU_STK*)ESP8266SendTaskStack,
		(CPU_STK_SIZE)ESP8266SendTaskStackSize / 10,
		(CPU_STK_SIZE)ESP8266SendTaskStackSize,
		(OS_MSG_QTY)10,
		(OS_TICK)0,
		(void *)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP,
		&p_err
		);
					
		OSTaskCreate(
		(OS_TCB*)&IAPTaskTCB,
		(CPU_CHAR *)"IAPTask",
		(OS_TASK_PTR)IAPTaskPtr,
		(void *)0,
		(OS_PRIO)IAPTaskPrio,
		(CPU_STK*)IAPTaskStack,
		(CPU_STK_SIZE)IAPTaskStackSize / 10,
		(CPU_STK_SIZE)IAPTaskStackSize,
		(OS_MSG_QTY)10,
		(OS_TICK)0,
		(void *)0,
		(OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP,
		&p_err
		);
		IAPSendTaskTCB = &ESP8266SendTaskTCB;		
	}
	else{		
		FIL *fp = &SPINORFile;
		FATFS *ffp = &SPINORFatFS;
		FRESULT res;
		u8 FileHead[12] = {0};
		u32 Cnt = 0;
		u16 SAVECRC = 0;u32 Saddr = 0;
		u8 FileList[6][10];
		OSMutexPend(&FATFS_MUTEX,0,OS_OPT_PEND_BLOCKING,0,&p_err);
		FATFS_MKF();
		res = f_mount(ffp,"0:",1);
		
		IAPGetBinFileList(FileList);
		
		if(StartFlag == 0)
		{
			res = f_open(fp,"\\P0.bin",FA_READ);
			res = f_read(fp,FileHead,12,&Cnt);
			StringToHex(FileHead,4,(u32 *)&SAVECRC);
			StringToHex(&FileHead[4],8,(u32 *)&Saddr);
		}
		
		
		OSMutexPost(&FATFS_MUTEX,OS_OPT_POST_NONE,&p_err);
		
	}
	
	OSTaskDel((OS_TCB *)0,&p_err);
	OSSchedUnlock(&p_err);//解挂任务调度器
	while(1)
	{

	}
}
void assert_failed(uint8_t* file, uint32_t line)
{
	
	while(1);
}



