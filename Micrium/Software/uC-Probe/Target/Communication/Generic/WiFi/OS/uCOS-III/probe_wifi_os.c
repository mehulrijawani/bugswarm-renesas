/*
*********************************************************************************************************
*                                       uC/Probe Communication
*
*                         (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        COMMUNICATION: Wi-Fi
*                                        Micrium uC/OS-III PORT
*
* Filename      : probe_wifi_os.c
* Version       : V2.30
* Programmer(s) : FT
*********************************************************************************************************
* Note(s)       : (1) This file is the uC/OS-III layer for the uC/Probe Wi-Fi Communication Module.
*
*                 (2) Assumes uC/OS-II V3.00 is included in the project build.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_wifi.h>
#include  <os.h>


/*
*********************************************************************************************************
*                                               ENABLE
*
* Note(s) : (1) See 'probe_wifi.h  ENABLE'.
*********************************************************************************************************
*/

#if (PROBE_COM_CFG_WIFI_EN == DEF_ENABLED)                     /* See Note #1.                                         */


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_TCB   ProbeWiFi_OS_TaskTCB;
static  CPU_STK  ProbeWiFi_OS_TaskStk[PROBE_WIFI_CFG_TASK_STK_SIZE];  /* Stack for Wi-Fi server task.                 */


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  ProbeWiFi_OS_Task  (void *p_arg);                        /* Wi-Fi server task.                           */


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        ProbeWiFi_OS_Init()
*
* Description : Initialize the UDP server task for Probe communication.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeWiFi_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeWiFi_OS_Init (void)
{
    OS_ERR  err;


    OSTaskCreate((OS_TCB     *)&ProbeWiFi_OS_TaskTCB,
                 (CPU_CHAR   *)"Probe Wi-Fi",
                 (OS_TASK_PTR ) ProbeWiFi_OS_Task,
                 (void       *) 0,
                 (OS_PRIO     ) PROBE_WIFI_CFG_TASK_PRIO,
                 (CPU_STK    *)&ProbeWiFi_OS_TaskStk[0],
                 (CPU_STK_SIZE)(PROBE_WIFI_CFG_TASK_STK_SIZE / 10u),
                 (CPU_STK_SIZE) PROBE_WIFI_CFG_TASK_STK_SIZE,
                 (OS_MSG_QTY  ) 0u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
    
    (void)&err;
}


/*
*********************************************************************************************************
*                                         ProbeWiFi_OS_Dly()
*
* Description : Delay the UDP server task.
*
* Argument(s) : ms          Number of milliseconds for which the UDP task should be delayed.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeWiFi_Task().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeWiFi_OS_Dly (CPU_INT16U  ms)
{
    OS_ERR      err;

    
    OSTimeDlyHMSM((CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT32U) ms,
                  (OS_OPT    ) OS_OPT_TIME_HMSM_NON_STRICT,
                  (OS_ERR   *)&err);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        ProbeWiFi_OS_Task()
*
* Description : Receives and transmits packets.
*
* Argument(s) : p_arg       Argument passed to ProbeWiFi_OS_Task() by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  ProbeWiFi_OS_Task (void *p_arg)
{
   (void)&p_arg;
    ProbeWiFi_Task();
}


/*
*********************************************************************************************************
*                                              ENABLE END
*
* Note(s) : See 'ENABLE  Note #1'.
*********************************************************************************************************
*/

#endif
