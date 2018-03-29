/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
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
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT


/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

//#define  APP_CFG_USBD_EN                                DEF_ENABLED
#define  APP_CFG_SERIAL_EN                              DEF_DISABLE

#define  APP_NAME   "                   ¼üÅÌ¿ØÖÆÆ÷            \n"
#define USER_CONFIG_AREA   (uint32_t)0x08003000

extern int Image$$ER_IROM1$$Base; //?????
#define USER_APP_BEGIN  (unsigned)(&Image$$ER_IROM1$$Base)
/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                        6u
#define  APP_CFG_TASK_TERM_PRIO                     		5u
#define  APP_CFG_TASK_DISPLAY_PRIO											4u
#define  APP_CFG_TASK_COMM_PRIO                         3u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE                    256u
#define  APP_CFG_TASK_TERM_STK_SIZE											600u
#define  APP_CFG_TASK_DISPLAY_STK_SIZE									600u
#define  APP_CFG_TASK_COMM_STK_SIZE									    600u

/*
*********************************************************************************************************
*                                       BSP CONFIGURATION
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL                           BSP_SER_COMM_UART_02
#define  KEY_CAP_TIMEOUT								10


/*
*********************************************************************************************************
*                               uC/USB-DEVICE APPLICATION CONFIGURATION
*********************************************************************************************************
*/

//#define  APP_CFG_USBD_CDC_EN                            DEF_DISABLED
//#define  APP_CFG_USBD_HID_EN                            DEF_ENABLED
//#define  APP_CFG_USBD_MSC_EN                            DEF_DISABLED
//#define  APP_CFG_USBD_VENDOR_EN                         DEF_DISABLED
//#define  APP_CFG_USBD_PHDC_EN                           DEF_DISABLED

//#define  APP_CFG_USBD_VENDOR_ECHO_SYNC_EN               DEF_ENABLED
//#define  APP_CFG_USBD_VENDOR_ECHO_ASYNC_EN              DEF_ENABLED

//#define  APP_CFG_USBD_HID_TEST_MOUSE_EN                 DEF_ENABLED

//#define  APP_CFG_USBD_CDC_SERIAL_TEST_EN                DEF_ENABLED


//#define  USBD_RAMDISK_CFG_NBR_UNITS                     1
//#define  USBD_RAMDISK_CFG_BLK_SIZE                      512
//#define  USBD_RAMDISK_CFG_NBR_BLKS                      44
//#define  USBD_RAMDISK_CFG_BASE_ADDR                     0

//#define  APP_CFG_USBD_PHDC_ITEM_DATA_LEN_MAX            8u
//#define  APP_CFG_USBD_PHDC_ITEM_NBR_MAX                 2u


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/
#if 0
#define  TRACE_LEVEL_OFF                                0
#define  TRACE_LEVEL_INFO                               1
#define  TRACE_LEVEL_DBG                                2
#endif

#include  <cpu.h>
void  BSP_Ser_Printf   (CPU_CHAR *format, ...);

#define  APP_TRACE_LEVEL                                TRACE_LEVEL_OFF
#define  APP_TRACE                                      printk


#define  FS_TRACE_LEVEL                                 TRACE_LEVEL_OFF
#define  FS_TRACE                                       printk

#define  APP_TRACE_INFO(x)                      ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO) ? (void)(APP_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                       ((APP_TRACE_LEVEL >= TRACE_LEVEL_DBG ) ? (void)(APP_TRACE x) : (void)0)


#endif
