/*
 * FreeModbus Libary: STM32F103 Port
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
 * File: $Id: porttimer.c,v 1.6 2006/05/14 21:54:16 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "assert.h"

/* ----------------------- FreeRTOS includes --------------------------------*/
#include "includes.h"

/* ----------------------- STM32F103 includes ----------------------------------*/


/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_TIMER_DEV            ( TIM2 )
#define MB_TIMER_PRESCALER      ( 255UL )
#define MB_TIMER_IRQ_CH         ( T0TIMI_IRQChannel )
#define MB_IRQ_PRIORITY         ( 1 )

/* Timer ticks are counted in multiples of 50us. Therefore 20000 ticks are
 * one second.
 */
#define MB_TIMER_TICKS          ( 20000UL )

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usTimerDeltaOCRA;

/* ----------------------- Static functions ---------------------------------*/
void            prvvMBTimerIRQHandler( void );

void
prvvMBTimerIRQHandler( void )
{
	if( TIM_GetITStatus( MB_TIMER_DEV, TIM_IT_Update ) == SET){
		
			 TIM_ClearITPendingBit(MB_TIMER_DEV,TIM_IT_Update);	
			 pxMBPortCBTimerExpired();
	}
}
/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{		
		
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_Cmd(MB_TIMER_DEV,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  TIM_TimeBaseStructure.TIM_Period = usTim1Timerout50us-1;   //dly/50  us
  TIM_TimeBaseStructure.TIM_Prescaler = 3599;//APB1 71?? 50us
  TIM_TimeBaseStructure.TIM_ClockDivision=0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//?????
	
  TIM_TimeBaseInit(MB_TIMER_DEV,&TIM_TimeBaseStructure);
	TIM_UpdateRequestConfig(MB_TIMER_DEV,TIM_UpdateSource_Global);
	
  TIM_ClearFlag(MB_TIMER_DEV,TIM_FLAG_Update);
  TIM_ITConfig(MB_TIMER_DEV,TIM_IT_Update,ENABLE);
	TIM_Cmd(MB_TIMER_DEV,ENABLE);
	BSP_IntVectSet(BSP_INT_ID_TIM2, prvvMBTimerIRQHandler);
  BSP_IntEn(BSP_INT_ID_TIM2);

  return TRUE;
}

void
vMBPortTimersEnable(void)
{
	TIM_ClearITPendingBit(MB_TIMER_DEV,TIM_FLAG_Update);
	TIM_ITConfig(MB_TIMER_DEV,TIM_IT_Update,DISABLE);
	TIM_GenerateEvent(MB_TIMER_DEV,TIM_EventSource_Update);
	TIM_ClearFlag(MB_TIMER_DEV,TIM_FLAG_Update);
  TIM_ITConfig(MB_TIMER_DEV,TIM_IT_Update,ENABLE);
	TIM_Cmd(MB_TIMER_DEV,ENABLE);	
}

void
vMBPortTimersDisable(void)
{
  /* We can always clear both flags. This improves performance. */
  TIM_ITConfig(MB_TIMER_DEV,TIM_IT_Update,DISABLE);
	TIM_GenerateEvent(MB_TIMER_DEV,TIM_EventSource_Update);
	TIM_ClearFlag(MB_TIMER_DEV,TIM_FLAG_Update);
	TIM_Cmd(MB_TIMER_DEV,DISABLE);
}
