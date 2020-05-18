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


                                             /* ---------------------------- MISCELLANEOUS <��>-------------------------- */
#define OS_CFG_APP_HOOKS_EN             1u   /*�Ƿ�ʹ�ù��Ӻ��� Enable (1) or Disable (0) application specific hooks                  */
#define OS_CFG_ARG_CHK_EN               1u   /*�Ƿ�ʹ�ò������ Enable (1) or Disable (0) argument checking                           */
#define OS_CFG_CALLED_FROM_ISR_CHK_EN   1u   /*�Ƿ�ʹ���жϵ��ü�� Enable (1) or Disable (0) check for called from ISR                   */
#define OS_CFG_DBG_EN                   1u   /*�Ƿ�ʹ��debug Enable (1) debug code/variables                                       */
#define OS_CFG_ISR_POST_DEFERRED_EN     1u   /*�Ƿ�ʹ���ж��ӳ�post ���� Enable (1) or Disable (0) Deferred ISR posts                          */
#define OS_CFG_OBJ_TYPE_CHK_EN          1u   /*�Ƿ�ʹ�ö������ͼ�� Enable (1) or Disable (0) object type checking                        */
#define OS_CFG_TS_EN                    1u   /*�Ƿ�ʹ��ʱ��� Enable (1) or Disable (0) time stamping                               */

#define OS_CFG_PEND_MULTI_EN            0u   /*�Ƿ�ʹ��֧�ֶ������pend ���� Enable (1) or Disable (0) code generation for multi-pend feature      */

#define OS_CFG_PRIO_MAX                32u   /*���������������ȼ� Defines the maximum number of task priorities (see OS_PRIO data type) */

#define OS_CFG_SCHED_LOCK_TIME_MEAS_EN  1u   /*�Ƿ�ʹ��֧�ֲ�������������ʱ�� Include code to measure scheduler lock time                           */
#define OS_CFG_SCHED_ROUND_ROBIN_EN     1u   /*�Ƿ�֧��ѭ������ Include code for Round-Robin scheduling                               */
#define OS_CFG_STK_SIZE_MIN            64u   /*��С�������ջ��С Minimum allowable task stack size                                     */


                                             /* ----------------------------- EVENT FLAGS --------------------------- */
#define OS_CFG_FLAG_EN                  1u   /*�Ƿ�ʹ���¼���־λ Enable (1) or Disable (0) code generation for EVENT FLAGS             */
#define OS_CFG_FLAG_DEL_EN              1u   /*�Ƿ����OSFlagDel()�Ĵ���     Include code for OSFlagDel()                                      */
#define OS_CFG_FLAG_MODE_CLR_EN         1u   /*�Ƿ��������¼���־λ�Ĵ���     Include code for Wait on Clear EVENT FLAGS                        */
#define OS_CFG_FLAG_PEND_ABORT_EN       1u   /*�Ƿ����OSFlagPendAbort()�Ĵ��� PendAbort��ȡ������     Include code for OSFlagPendAbort()                                */


                                             /* -------------------------- MEMORY MANAGEMENT ------------------------ */
#define OS_CFG_MEM_EN                   1u   /*�Ƿ�ʹ���ڴ���� Enable (1) or Disable (0) code generation for MEMORY MANAGER          */


                                             /* --------------------- MUTUAL EXCLUSION SEMAPHORES ------------------- */
#define OS_CFG_MUTEX_EN                 1u   /*�Ƿ�ʹ�û����� Enable (1) or Disable (0) code generation for MUTEX                   */
#define OS_CFG_MUTEX_DEL_EN             1u   /*�Ƿ����OSMutexDel()�Ĵ���     Include code for OSMutexDel()                                     */
#define OS_CFG_MUTEX_PEND_ABORT_EN      1u   /*�Ƿ����OSMutexPendAbort()�Ĵ���     Include code for OSMutexPendAbort()                               */


                                             /* --------------------------- MESSAGE QUEUES -------------------------- */
#define OS_CFG_Q_EN                     1u   /*�Ƿ�ʹ����Ϣ���� Enable (1) or Disable (0) code generation for QUEUES                  */
#define OS_CFG_Q_DEL_EN                 1u   /*�Ƿ����OSQDel()�Ĵ���     Include code for OSQDel()                                         */
#define OS_CFG_Q_FLUSH_EN               1u   /*�Ƿ����OSQFlush()�Ĵ���     Include code for OSQFlush()                                       */
#define OS_CFG_Q_PEND_ABORT_EN          1u   /*�Ƿ����OSQPendAbort()�Ĵ���     Include code for OSQPendAbort()                                   */


                                             /* ----------------------------- SEMAPHORES ---------------------------- */
#define OS_CFG_SEM_EN                   1u   /*�Ƿ�ʹ���ź��� Enable (1) or Disable (0) code generation for SEMAPHORES              */
#define OS_CFG_SEM_DEL_EN               1u   /*�Ƿ����OSSemDel()�Ĵ���    Include code for OSSemDel()                                        */
#define OS_CFG_SEM_PEND_ABORT_EN        1u   /*�Ƿ����OSSemPendAbort()�Ĵ���    Include code for OSSemPendAbort()                                  */
#define OS_CFG_SEM_SET_EN               1u   /*�Ƿ����OSSemSet()�Ĵ���    Include code for OSSemSet()                                        */


                                             /* -------------------------- TASK MANAGEMENT -------------------------- */
#define OS_CFG_STAT_TASK_EN             0u   /*�Ƿ�ʹ������ͳ�ƹ��� Enable (1) or Disable(0) the statistics task                          */
#define OS_CFG_STAT_TASK_STK_CHK_EN     0u   /*��ͳ�������м�������ջ Check task stacks from statistic task                                 */

#define OS_CFG_TASK_CHANGE_PRIO_EN      1u   /*�Ƿ����OSTaskChangePrio()�Ĵ��� Include code for OSTaskChangePrio()                                   */
#define OS_CFG_TASK_DEL_EN              1u   /*�Ƿ����OSTaskDel()�Ĵ��� Include code for OSTaskDel()                                          */
#define OS_CFG_TASK_Q_EN                1u   /*�Ƿ����OSTaskQXXXX()�Ĵ��� Include code for OSTaskQXXXX()                                        */
#define OS_CFG_TASK_Q_PEND_ABORT_EN     1u   /*�Ƿ����OSTaskQPendAbort()�Ĵ��� Include code for OSTaskQPendAbort()                                   */
#define OS_CFG_TASK_PROFILE_EN          1u   /*�Ƿ���OS_TCB �а��������Խ������ܷ��� Include variables in OS_TCB for profiling                             */
#define OS_CFG_TASK_REG_TBL_SIZE        1u   /*�����ض��Ĵ��������� Number of task specific registers                                     */
#define OS_CFG_TASK_SEM_PEND_ABORT_EN   1u   /*�Ƿ����OSTaskSemPendAbort()�Ĵ��� Include code for OSTaskSemPendAbort()                                 */
#define OS_CFG_TASK_SUSPEND_EN          1u   /*�Ƿ����OSTaskSuspend() ��ͣ�� OSTaskResume()�ָ��Ĵ��� Include code for OSTaskSuspend() and OSTaskResume()                   */


                                             /* -------------------------- TIME MANAGEMENT -------------------------- */
#define OS_CFG_TIME_DLY_HMSM_EN         1u   /*�Ƿ����OSTimeDlyHMSM() Сʱ���֡��롢����Ĵ���     Include code for OSTimeDlyHMSM()                                  */
#define OS_CFG_TIME_DLY_RESUME_EN       1u   /*�Ƿ����OSTimeDlyResume()�Ĵ���     Include code for OSTimeDlyResume()                                */


                                             /* -------------------���񱾵ش洢���� TASK LOCAL STORAGE MANAGEMENT ------------------- */
#define OS_CFG_TLS_TBL_SIZE             0u   /*���ñ�������洢�Ĵ��� Include code for Task Local Storage (TLS) registers                   */


                                             /* ------------------------- TIMER MANAGEMENT -------------------------- */
#define OS_CFG_TMR_EN                   1u   /*�Ƿ�ʹ�ö�ʱ�� Enable (1) or Disable (0) code generation for TIMERS                  */
#define OS_CFG_TMR_DEL_EN               1u   /*�Ƿ�֧��OSTmrDel() Enable (1) or Disable (0) code generation for OSTmrDel()              */

#endif
