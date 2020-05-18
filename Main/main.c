#include  <includes.h>

OS_TCB StastTaskTCB;
extern void StastTaskPtr(void *p_arg);
#define StastTaskStackSize     10240
CPU_STK StastTaskStack[StastTaskStackSize];
#define StastTaskPrio    25

#include "usart.h"	

int main(void)
{
	OS_ERR  p_err;	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	
	uart_init(115200);
	
	OSInit(&p_err);	
	
	OSTaskCreate(
	(OS_TCB*)&StastTaskTCB,
	(CPU_CHAR *)"StastTask",
	(OS_TASK_PTR)StastTaskPtr,
	(void *)0,
	(OS_PRIO)StastTaskPrio,
	(CPU_STK*)StastTaskStack,
	(CPU_STK_SIZE)StastTaskStackSize / 10,
	(CPU_STK_SIZE)StastTaskStackSize,
	(OS_MSG_QTY)0,
	(OS_TICK)0,
	(void *)0,
	(OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP,
	&p_err
	);
	OSStart(&p_err);
	while(1)
	{
		
	}
}

			
