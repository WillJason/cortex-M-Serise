/*
 * FreeModbus Libary: STR71x Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.6 2006/06/15 15:41:20 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "assert.h"

/* ----------------------- RTOS includes --------------------------------*/
#include "includes.h"

/* ----------------------- STM32F103 includes ----------------------------------*/
//#include "gpio.h"
//#include "eic.h"
//#include "uart.h"
//#include "tim.h"

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_UART_DEV             ( UART4 )
#define MB_UART_RX_PORT         ( GPIOC )
#define MB_UART_RX_PIN          ( 11 )
#define MB_UART_TX_PORT         ( GPIOC )
#define MB_UART_TX_PIN          ( 10 )
#define MB_UART_IRQ_CH          ( UART4_IRQChannel )
#define MB_UART_TX_QUEUE_LEN    ( 8 )
#define MB_IRQ_PRIORITY         ( 1 )

/* ----------------------- Static functions ---------------------------------*/



/* ----------------------- Start implementation -----------------------------*/

static void
prvvMBSerialIRQHandler( void )
{

    if(USART_GetITStatus(MB_UART_DEV,USART_IT_TC) == SET)
    {
        pxMBFrameCBTransmitterEmpty();
				USART_ClearITPendingBit(MB_UART_DEV,USART_IT_TC);
    }
    if(USART_GetITStatus(MB_UART_DEV,USART_IT_RXNE) == SET)
    {
        pxMBFrameCBByteReceived(  );
				USART_ClearITPendingBit(MB_UART_DEV,USART_IT_RXNE);
    }
		if(USART_GetITStatus(MB_UART_DEV,USART_IT_TXE) == SET){
			  USART_ITConfig( MB_UART_DEV, USART_IT_TXE, DISABLE );
				pxMBFrameCBTransmitterEmpty();
				USART_ClearITPendingBit(MB_UART_DEV,USART_IT_TXE);
			  USART_ITConfig( MB_UART_DEV, USART_IT_TC, ENABLE );
		}
}

BOOL
xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
		USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
    (void)ucPort;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
		
		//GPIOA初始化，USART4 Tx (PC10) 复用开漏输出
		GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP; 
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
			
		//Configure USART4 Rx (PC11) as input floating 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	  
	  //Configure USART4 CTL (PA14) as input floating 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
		GPIO_SetBits(GPIOA,GPIO_Pin_14);

		USART_DeInit(MB_UART_DEV);
		USART_InitStructure.USART_BaudRate = ulBaudRate;
		USART_InitStructure.USART_WordLength = ucDataBits;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
		USART_Init(UART4, &USART_InitStructure);
		USART_Cmd(UART4, ENABLE);		 //使能UART
		
//		USART_ITConfig(MB_UART_DEV,USART_IT_RXNE,ENABLE);
		
		BSP_IntVectSet(BSP_INT_ID_USART4, prvvMBSerialIRQHandler); //
		BSP_IntEn(BSP_INT_ID_USART4);
		
		return TRUE;
}

void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    if( xRxEnable ){
			  USART_ClearFlag(MB_UART_DEV,USART_IT_RXNE);
        USART_ITConfig( MB_UART_DEV, USART_IT_RXNE, ENABLE );
			  GPIO_SetBits(GPIOA,GPIO_Pin_14);
		}
    else{
        USART_ITConfig( MB_UART_DEV, USART_IT_RXNE, DISABLE );
			  GPIO_ResetBits(GPIOA,GPIO_Pin_14);
		}

    if( xTxEnable ){
//			  USART_ClearFlag(MB_UART_DEV,USART_IT_TC);
        USART_ITConfig( MB_UART_DEV, USART_IT_TXE, ENABLE );
//			  GPIO_ResetBits(GPIOA,GPIO_Pin_14);
		}
    else{
        USART_ITConfig( MB_UART_DEV, USART_IT_TC, DISABLE );
//			  GPIO_SetBits(GPIOA,GPIO_Pin_14);
		}
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
	  MB_UART_DEV->DR = ucByte;
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
	  *pucByte = MB_UART_DEV->DR;
    return TRUE;
}

