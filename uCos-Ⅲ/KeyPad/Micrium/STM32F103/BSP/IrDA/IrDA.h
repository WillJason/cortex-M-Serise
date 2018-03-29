/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
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
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                        Evaluation Board
*
* Filename      : IrDA.h
* Version       : V1.00
* Programmer(s) : EHS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  __IRDA_H__
#define  __IRDA_H__

typedef struct _tIrData{
// unsigned short 	Polarity;
// unsigned short 	TimeOut;
 unsigned 				TimeStamp;
 struct _tIrData  *pFwd;
}tIrData;

typedef struct{
	tIrData * pDStart;
	tIrData * pDStop;
}tIrDataQ;

//extern void IrDA_Init(void);
extern void IrControler_Init(void);
#endif
