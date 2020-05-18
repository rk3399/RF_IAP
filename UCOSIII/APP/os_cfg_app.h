/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2012; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*                                       OS CONFIGURATION (APPLICATION SPECIFICS)
*
* File    : OS_CFG_APP.H
* By      : JJL
* Version : V3.03.01
*
* LICENSING TERMS:
* ---------------
*           uC/OS-III is provided in source form for FREE short-term evaluation, for educational use or
*           for peaceful research.  If you plan or intend to use uC/OS-III in a commercial application/
*           product then, you need to contact Micrium to properly license uC/OS-III for its use in your
*           application/product.   We provide ALL the source code for your convenience and to help you
*           experience uC/OS-III.  The fact that the source is provided does NOT mean that you can use
*           it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*
*           Please help us continue to provide the embedded community with the finest software available.
*           Your honesty is greatly appreciated.
*
*           You can contact us at www.micrium.com, or by phone at +1 (954) 217-2036.
************************************************************************************************************************
*/

#ifndef OS_CFG_APP_H
#define OS_CFG_APP_H

/*
************************************************************************************************************************
*                                                      CONSTANTS
************************************************************************************************************************
*/

                                                            /* --------------------- MISCELLANEOUS ------------------ */
#define  OS_CFG_MSG_POOL_SIZE            100u               /*֧�ֵ������Ϣ���� Maximum number of messages           */
#define  OS_CFG_ISR_STK_SIZE             128u               /*ISR ��ջ�Ĵ�С Stack size of ISR stack (number of CPU_STK elements)   */
#define  OS_CFG_TASK_STK_LIMIT_PCT_EMPTY  10u               /*����ջ��ʣ���С���ٷְ���ʽ���˴���10%��Stack limit position in percentage to empty            */


                                                            /* ---------------------- IDLE TASK --------------------- */
#define  OS_CFG_IDLE_TASK_STK_SIZE       128u               /*���������ջ��С Stack size (number of CPU_STK elements)                */


                                                            /* ------------------ ISR HANDLER TASK ------------------ */
#define  OS_CFG_INT_Q_SIZE                10u               /*�жϴ���������д�С Size of ISR handler task queue                         */
#define  OS_CFG_INT_Q_TASK_STK_SIZE      128u               /*�жϴ�������Ķ�ջ��С Stack size (number of CPU_STK elements)                */


                                                            /* -------------------ͳ������ STATISTIC TASK ------------------- */
#define  OS_CFG_STAT_TASK_PRIO            10u               /*ͳ����������ȼ� Priority                                               */
#define  OS_CFG_STAT_TASK_RATE_HZ         10u               /*ͳ�������ָ��Ƶ�ʣ�1 - 10HZ�� Rate of execution (1 to 10 Hz)                         */
#define  OS_CFG_STAT_TASK_STK_SIZE       128u               /*ͳ������Ķ�ջ��С Stack size (number of CPU_STK elements)                */


                                                            /* ------------------------ʱ�ӽ������� TICKS ----------------------- */
#define  OS_CFG_TICK_RATE_HZ            1000u               /*ϵͳ��ʱ�ӽ���(һ��Ϊ10 �� 1000 Hz) Tick rate in Hertz (10 to 1000 Hz)                     */
#define  OS_CFG_TICK_TASK_PRIO             1u               /*ʱ�ӽ�����������ȼ� Priority                                               */
#define  OS_CFG_TICK_TASK_STK_SIZE       128u               /*ʱ�ӽ�������Ķ�ջ��С Stack size (number of CPU_STK elements)                */
#define  OS_CFG_TICK_WHEEL_SIZE           17u               /*ʱ�ӽ���������б��С Number of 'spokes' in tick  wheel; SHOULD be prime     */


                                                            /* -----------------------��ʱ������ TIMERS ----------------------- */
#define  OS_CFG_TMR_TASK_PRIO             11u               /*��ʱ����������ȼ� Priority of 'Timer Task'                               */
#define  OS_CFG_TMR_TASK_RATE_HZ         OS_CFG_TICK_RATE_HZ               /*��ʱ��Ƶ�ʣ�100 Hz �ǵ���ֵ�� Rate for timers (100 Hz Typ.)                          */
#define  OS_CFG_TMR_TASK_STK_SIZE        128u               /*��ʱ������Ķ�ջ��С Stack size (number of CPU_STK elements)                */
#define  OS_CFG_TMR_WHEEL_SIZE            17u               /*��ʱ��������б��С Number of 'spokes' in timer wheel; SHOULD be prime     */

#endif
