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
* Filename      : RTC.h
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/
#ifndef  __RTC_H__
#define  __RTC_H__

typedef struct{
  unsigned Year;
	unsigned Month;
	unsigned Day;
	unsigned Hour;
	unsigned Minute;
	unsigned Second;
}tDate;

extern void RTC_Init(void);
extern void RTC_SetTime(unsigned TimeVar);
extern void RTC_GetTime(tDate *pDate);
#endif
