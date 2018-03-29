/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#ifndef __KEY_H__
#define __KEY_H__

#include "stdint.h"

#define KEY_HIGH_SPEED    	(1)
#define KEY_LOW_SPEED     	(2)
#define KEY_DEV_SEL_PLUS  	(3)
#define KEY_DEV_SEL_MINUS		(4)
#define KEY_CTRL_REMOTE			(5)
#define KEY_CTRL_AUTOPILOT  (6)
#define KEY_CTRL_START      (7)
#define KEY_CTRL_STOP       (8)
#define KEY_CTRL_FORWARD    (9)
#define KEY_CTRL_BACKWARD   (10)
#define KEY_CTRL_SUPPLY     (11)
#define KEY_CTRL_DESUPPLY   (12)
#define KEY_CTRL_BEEP				(13)
#define KEY_CTRL_HALT       (14)
#define KEY_CTRL_WRIGGLE    (15)
#define KEY_CTRL_BREAK      (16)
#define KEY_CTRL_ACCEL      (17)
#define KEY_CTRL_DECEL			(18)
#define KEY_CTRL_UNLOCK     (19)
#define KEY_CTRL_EBREAK     (20)
#define KEY_CTRL_F					(21)
#define KEY_CTRL_B  				(22)
#define KEY_CTRL_L					(23)
#define KEY_CTRL_R					(24)
#define KEY_CTRL_LEAK				(25)
#define KEY_CTRL_LEAKING    (26)
#define KEY_CTRL_STOP_LEAK  (27)
#define KEY_CTRL_CONTRL     (28)
#define KEY_CTRL_UNCTRL     (29)

#define FUN_READ_KEY				(1)
#define FUN_CTRL_LED				(2)
#define FUN_CTRL_LED_F			    (3)

typedef struct{
	unsigned fun;
	unsigned char code[8];
}tKeyFun;

typedef struct{
	unsigned char code;
	unsigned char row;
	unsigned char col;
}tKeyList;

typedef struct{
	unsigned char lcol;
	unsigned char lrow;
	unsigned char row;
	unsigned char col;
}tLEDList;

void BC7277_Init(void);
//void BC7281B_Write(uint8_t addr,uint8_t dat);
uint16_t BC7277_Read(uint8_t addr);


#endif
