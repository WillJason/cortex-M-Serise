#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#ifdef  SYS_GLOBLE
#define SYS_EXT
#else
#define SYS_EXT extern
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

#define globle

// IAR、gcc，ARM的数据定义
typedef unsigned char   uint8;
typedef signed   char   int8;
typedef unsigned short    uint16;
typedef signed   short    int16;
typedef unsigned long   uint32;
typedef signed   long   int32;
typedef float           fp32;
typedef double          fp64;
typedef unsigned char   BOOL;

#define GPIO(x)  ((x)?0xFF:0x00)

#include  <math.h>
#include  <stdlib.h>
#include  <stdio.h>
#include  <ctype.h>
#include  <stdarg.h>
#include  <string.h>
//  包含必要的头文件

#include  "misc.h"
#include  "stm32f10x_exti.h"
#include  "stm32f10x_flash.h"
#include  "stm32f10x_gpio.h"
#include  "stm32f10x_rcc.h"
#include  "stm32f10x_usart.h"
#include  "stm32f10x_iwdg.h"
#include  "stm32f10x_tim.h"
#include  "stm32f10x_rtc.h"
#include  "stm32f10x_bkp.h"
#include  "stm32f10x_pwr.h"
#include  "stm32f10x_adc.h"
#include  "stm32f10x_spi.h"

//包含用户的头文件

#include  "sys.h"
#include  "usart.h"
#include  "delay.h"
#include  "led.h"
#include  "AD974.h"
#include  "CAT9555.h"
#include	"detect.h"
#include  "wdg.h"
#include  "timer.h"
#include "exti.h"
#include "KGOUT.h"
#include "CMD.h"

#define MCU_FIRMWARE_VER 		10   								//软件版本


extern void Delay(uint32 t);

#endif   //  __CONFIG_H__

