/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2012; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*                                                  CONFIGURATION FILE
*
* File    : OS_CFG.H
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

#ifndef OS_CFG_H
#define OS_CFG_H


                                             /* ---------------------------- MISCELLANEOUS <杂>-------------------------- */
#define OS_CFG_APP_HOOKS_EN             1u   /*是否使用钩子函数 Enable (1) or Disable (0) application specific hooks                  */
#define OS_CFG_ARG_CHK_EN               1u   /*是否使用参数检查 Enable (1) or Disable (0) argument checking                           */
#define OS_CFG_CALLED_FROM_ISR_CHK_EN   1u   /*是否使用中断调用检查 Enable (1) or Disable (0) check for called from ISR                   */
#define OS_CFG_DBG_EN                   1u   /*是否使用debug Enable (1) debug code/variables                                       */
#define OS_CFG_ISR_POST_DEFERRED_EN     1u   /*是否使用中断延迟post 操作 Enable (1) or Disable (0) Deferred ISR posts                          */
#define OS_CFG_OBJ_TYPE_CHK_EN          1u   /*是否使用对象类型检查 Enable (1) or Disable (0) object type checking                        */
#define OS_CFG_TS_EN                    1u   /*是否使用时间戳 Enable (1) or Disable (0) time stamping                               */

#define OS_CFG_PEND_MULTI_EN            0u   /*是否使用支持多个任务pend 操作 Enable (1) or Disable (0) code generation for multi-pend feature      */

#define OS_CFG_PRIO_MAX                32u   /*定义任务的最大优先级 Defines the maximum number of task priorities (see OS_PRIO data type) */

#define OS_CFG_SCHED_LOCK_TIME_MEAS_EN  1u   /*是否使用支持测量调度器锁定时间 Include code to measure scheduler lock time                           */
#define OS_CFG_SCHED_ROUND_ROBIN_EN     1u   /*是否支持循环调度 Include code for Round-Robin scheduling                               */
#define OS_CFG_STK_SIZE_MIN            64u   /*最小的任务堆栈大小 Minimum allowable task stack size                                     */


                                             /* ----------------------------- EVENT FLAGS --------------------------- */
#define OS_CFG_FLAG_EN                  1u   /*是否使用事件标志位 Enable (1) or Disable (0) code generation for EVENT FLAGS             */
#define OS_CFG_FLAG_DEL_EN              1u   /*是否包含OSFlagDel()的代码     Include code for OSFlagDel()                                      */
#define OS_CFG_FLAG_MODE_CLR_EN         1u   /*是否包含清除事件标志位的代码     Include code for Wait on Clear EVENT FLAGS                        */
#define OS_CFG_FLAG_PEND_ABORT_EN       1u   /*是否包含OSFlagPendAbort()的代码 PendAbort：取消挂起     Include code for OSFlagPendAbort()                                */


                                             /* -------------------------- MEMORY MANAGEMENT ------------------------ */
#define OS_CFG_MEM_EN                   1u   /*是否使用内存管理 Enable (1) or Disable (0) code generation for MEMORY MANAGER          */


                                             /* --------------------- MUTUAL EXCLUSION SEMAPHORES ------------------- */
#define OS_CFG_MUTEX_EN                 1u   /*是否使用互斥量 Enable (1) or Disable (0) code generation for MUTEX                   */
#define OS_CFG_MUTEX_DEL_EN             1u   /*是否包含OSMutexDel()的代码     Include code for OSMutexDel()                                     */
#define OS_CFG_MUTEX_PEND_ABORT_EN      1u   /*是否包含OSMutexPendAbort()的代码     Include code for OSMutexPendAbort()                               */


                                             /* --------------------------- MESSAGE QUEUES -------------------------- */
#define OS_CFG_Q_EN                     1u   /*是否使用消息队列 Enable (1) or Disable (0) code generation for QUEUES                  */
#define OS_CFG_Q_DEL_EN                 1u   /*是否包含OSQDel()的代码     Include code for OSQDel()                                         */
#define OS_CFG_Q_FLUSH_EN               1u   /*是否包含OSQFlush()的代码     Include code for OSQFlush()                                       */
#define OS_CFG_Q_PEND_ABORT_EN          1u   /*是否包含OSQPendAbort()的代码     Include code for OSQPendAbort()                                   */


                                             /* ----------------------------- SEMAPHORES ---------------------------- */
#define OS_CFG_SEM_EN                   1u   /*是否使用信号量 Enable (1) or Disable (0) code generation for SEMAPHORES              */
#define OS_CFG_SEM_DEL_EN               1u   /*是否包含OSSemDel()的代码    Include code for OSSemDel()                                        */
#define OS_CFG_SEM_PEND_ABORT_EN        1u   /*是否包含OSSemPendAbort()的代码    Include code for OSSemPendAbort()                                  */
#define OS_CFG_SEM_SET_EN               1u   /*是否包含OSSemSet()的代码    Include code for OSSemSet()                                        */


                                             /* -------------------------- TASK MANAGEMENT -------------------------- */
#define OS_CFG_STAT_TASK_EN             0u   /*是否使用任务统计功能 Enable (1) or Disable(0) the statistics task                          */
#define OS_CFG_STAT_TASK_STK_CHK_EN     0u   /*从统计任务中检查任务堆栈 Check task stacks from statistic task                                 */

#define OS_CFG_TASK_CHANGE_PRIO_EN      1u   /*是否包含OSTaskChangePrio()的代码 Include code for OSTaskChangePrio()                                   */
#define OS_CFG_TASK_DEL_EN              1u   /*是否包含OSTaskDel()的代码 Include code for OSTaskDel()                                          */
#define OS_CFG_TASK_Q_EN                1u   /*是否包含OSTaskQXXXX()的代码 Include code for OSTaskQXXXX()                                        */
#define OS_CFG_TASK_Q_PEND_ABORT_EN     1u   /*是否包含OSTaskQPendAbort()的代码 Include code for OSTaskQPendAbort()                                   */
#define OS_CFG_TASK_PROFILE_EN          1u   /*是否在OS_TCB 中包含变量以进行性能分析 Include variables in OS_TCB for profiling                             */
#define OS_CFG_TASK_REG_TBL_SIZE        1u   /*任务特定寄存器的数量 Number of task specific registers                                     */
#define OS_CFG_TASK_SEM_PEND_ABORT_EN   1u   /*是否包含OSTaskSemPendAbort()的代码 Include code for OSTaskSemPendAbort()                                 */
#define OS_CFG_TASK_SUSPEND_EN          1u   /*是否包含OSTaskSuspend() 暂停和 OSTaskResume()恢复的代码 Include code for OSTaskSuspend() and OSTaskResume()                   */


                                             /* -------------------------- TIME MANAGEMENT -------------------------- */
#define OS_CFG_TIME_DLY_HMSM_EN         1u   /*是否包含OSTimeDlyHMSM() 小时、分、秒、毫秒的代码     Include code for OSTimeDlyHMSM()                                  */
#define OS_CFG_TIME_DLY_RESUME_EN       1u   /*是否包含OSTimeDlyResume()的代码     Include code for OSTimeDlyResume()                                */


                                             /* -------------------任务本地存储管理 TASK LOCAL STORAGE MANAGEMENT ------------------- */
#define OS_CFG_TLS_TBL_SIZE             0u   /*引用本地任务存储寄存器 Include code for Task Local Storage (TLS) registers                   */


                                             /* ------------------------- TIMER MANAGEMENT -------------------------- */
#define OS_CFG_TMR_EN                   1u   /*是否使用定时器 Enable (1) or Disable (0) code generation for TIMERS                  */
#define OS_CFG_TMR_DEL_EN               1u   /*是否支持OSTmrDel() Enable (1) or Disable (0) code generation for OSTmrDel()              */

#endif
