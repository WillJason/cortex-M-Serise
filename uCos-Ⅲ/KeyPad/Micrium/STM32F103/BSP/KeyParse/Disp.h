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
#ifndef __DISP_H__
#define __DISP_H__

#include "stdint.h"

void  DispInit(void);
void Disp_Write(uint8_t addr,uint8_t dat);
uint8_t Disp_Read(uint8_t addr);

#endif