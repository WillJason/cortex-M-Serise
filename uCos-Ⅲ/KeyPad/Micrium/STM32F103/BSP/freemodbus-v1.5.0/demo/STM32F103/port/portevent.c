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
 * File: $Id: portevent.c,v 1.6 2006/05/14 21:54:16 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "assert.h"

/* ----------------------- RTOS -----------------------------------------*/
#include "includes.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Variables ----------------------------------------*/
//static xQueueHandle xMBPortQueueHdl;
static OS_Q         xMBPortQueueHdl;

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortEventInit( void )
{
	OS_ERR err;
//    xMBPortQueueHdl = xQueueCreate( 1, sizeof( eMBEventType ) );
	OSQCreate(&xMBPortQueueHdl,NULL,10,&err);
//    return xMBPortQueueHdl != NULL ? TRUE : FALSE;
	return err == OS_ERR_NONE ? TRUE : FALSE;
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
//    portBASE_TYPE   xEventSent = pdFALSE;
		OS_ERR err;
    static eMBEventType eEventBuf[10];
	  static unsigned eEventIndex = 0;
	  eEventBuf[eEventIndex] = eEvent;
//    xEventSent = xQueueSendFromISR( xMBPortQueueHdl, &eEvent, xEventSent );
	  OSQPost(&xMBPortQueueHdl,&eEventBuf[eEventIndex],sizeof(eMBEventType),OS_OPT_POST_ALL,&err);
	  eEventIndex = (eEventIndex+1)%10;
//    return xEventSent == pdTRUE ? TRUE : FALSE;
		return err == OS_ERR_NONE ? TRUE : FALSE;
}

BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
//    BOOL            xEventHappened = FALSE;
		OS_MSG_SIZE size;
	  OS_ERR err;
	  eMBEventType *pdat;

//    if( xQueueReceive( xMBPortQueueHdl, eEvent, portMAX_DELAY ) == pdTRUE )
//    {
//        xEventHappened = TRUE;
//    }
		pdat = OSQPend(&xMBPortQueueHdl,portMAX_DELAY,OS_OPT_PEND_BLOCKING,&size,NULL,&err);
	  if(err == OS_ERR_NONE){
			*eEvent = *pdat;
			return TRUE;
		}else
			return FALSE;
}
