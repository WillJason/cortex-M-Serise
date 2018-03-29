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

#ifndef __UART_H__
#define __UART_H__

#include 		<includes.h>

#define UART_RING_BUF_SIZE  (500)
#define UART_MSG_SIZE       (10)

typedef struct _tUartRingBuf{
	struct _tUartRingBuf	*pnext;
	unsigned short count;
	unsigned char  dat;
	unsigned char  rsv;
}tUartRingBuf;



typedef struct{
	tUartRingBuf *pStart;
	tUartRingBuf *pStop;
}tUartInfo;

void Uart_cfg(void);
void Uart_Keypad_Init(void);
void Uart_Keypad_Send(uint8_t *buf,uint8_t len);
void LCD_Init(void);

#endif
