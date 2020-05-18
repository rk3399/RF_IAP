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
#define  OS_CFG_MSG_POOL_SIZE            100u               /*支持的最大消息数量 Maximum number of messages           */
#define  OS_CFG_ISR_STK_SIZE             128u               /*ISR 堆栈的大小 Stack size of ISR stack (number of CPU_STK elements)   */
#define  OS_CFG_TASK_STK_LIMIT_PCT_EMPTY  10u               /*检查堆栈的剩余大小（百分百形式，此处是10%）Stack limit position in percentage to empty            */


                                                            /* ---------------------- IDLE TASK --------------------- */
#define  OS_CFG_IDLE_TASK_STK_SIZE       128u               /*空闲任务堆栈大小 Stack size (number of CPU_STK elements)                */


                                                            /* ------------------ ISR HANDLER TASK ------------------ */
#define  OS_CFG_INT_Q_SIZE                10u               /*中断处理任务队列大小 Size of ISR handler task queue                         */
#define  OS_CFG_INT_Q_TASK_STK_SIZE      128u               /*中断处理任务的堆栈大小 Stack size (number of CPU_STK elements)                */


                                                            /* -------------------统计任务 STATISTIC TASK ------------------- */
#define  OS_CFG_STAT_TASK_PRIO            10u               /*统计任务的优先级 Priority                                               */
#define  OS_CFG_STAT_TASK_RATE_HZ         10u               /*统计任务的指向频率（1 - 10HZ） Rate of execution (1 to 10 Hz)                         */
#define  OS_CFG_STAT_TASK_STK_SIZE       128u               /*统计任务的堆栈大小 Stack size (number of CPU_STK elements)                */


                                                            /* ------------------------时钟节拍任务 TICKS ----------------------- */
#define  OS_CFG_TICK_RATE_HZ            1000u               /*系统的时钟节拍(一般为10 到 1000 Hz) Tick rate in Hertz (10 to 1000 Hz)                     */
#define  OS_CFG_TICK_TASK_PRIO             1u               /*时钟节拍任务的优先级 Priority                                               */
#define  OS_CFG_TICK_TASK_STK_SIZE       128u               /*时钟节拍任务的堆栈大小 Stack size (number of CPU_STK elements)                */
#define  OS_CFG_TICK_WHEEL_SIZE           17u               /*时钟节拍任务的列表大小 Number of 'spokes' in tick  wheel; SHOULD be prime     */


                                                            /* -----------------------定时器任务 TIMERS ----------------------- */
#define  OS_CFG_TMR_TASK_PRIO             11u               /*定时器任务的优先级 Priority of 'Timer Task'                               */
#define  OS_CFG_TMR_TASK_RATE_HZ         OS_CFG_TICK_RATE_HZ               /*定时器频率（100 Hz 是典型值） Rate for timers (100 Hz Typ.)                          */
#define  OS_CFG_TMR_TASK_STK_SIZE        128u               /*定时器任务的堆栈大小 Stack size (number of CPU_STK elements)                */
#define  OS_CFG_TMR_WHEEL_SIZE            17u               /*定时器任务的列表大小 Number of 'spokes' in timer wheel; SHOULD be prime     */

#endif
