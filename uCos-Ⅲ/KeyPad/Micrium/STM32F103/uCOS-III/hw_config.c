/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V1.0
* Date               : 10/08/2007
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "includes.h"
#include "usb_istr.h"

//#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_flash.h"
//#include "misc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define JOY_UP       GPIO_Pin_2  /* PD.08 */
//#define JOY_DOWN     GPIO_Pin_3 /* PD.14 */
//#define JOY_LEFT     GPIO_Pin_4  /* PE.01 */
//#define JOY_RIGHT    GPIO_Pin_5  /* PE.00 */
//#define JOY_LEFT_BUTTON    GPIO_Pin_13  /* PC.13 */
//#define JOY_RIGHT_BUTTON    GPIO_Pin_12  /* PC.12 */
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
//ErrorStatus HSEStartUpStatus;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USB_GPIO_Config
* Description    : Configures Main system clocks & power.
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIOD and GPIOE clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
  
  /* PD.09 used as USB pull-up */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//  GPIO_ResetBits(GPIOC, GPIO_Pin_5);

}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USBClock_config(void)
{
  /* Select USBCLK source */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

  /* Enable USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : Configures the USB interrupts.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	BSP_IntVectSet(BSP_INT_ID_CAN1_RX0, USB_Istr); //
	BSP_IntEn(BSP_INT_ID_CAN1_RX0);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{ 
  if (NewState != DISABLE)
  {
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
  }
  else
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
  }
}

/*******************************************************************************
* Function Name : Joystick_Send.
* Description   : prepares buffer to be sent containing Joystick event infos.
* Input         : Keys: keys received from terminal.
* Output        : None.
* Return value  : None.
*******************************************************************************/
void Joystick_Send(u8 Keys)
{
  u8 Mouse_Buffer[4] = {0, 0, 0, 0};
  s8 X = 0, Y = 0,BUTTON=0;

  switch (Keys)
  {
    case LEFT:
      X += CURSOR_STEP;
      break;
    case RIGHT:

      X -= CURSOR_STEP;
      break;
    case UP:
      Y -= CURSOR_STEP;
      break;
    case DOWN:
      Y += CURSOR_STEP;
      break;
	 case LEFT_BUTTON:
      BUTTON = BUTTON|0x01;
      break;
 	 case RIGHT_BUTTON:
      BUTTON = BUTTON|0x02;
      break;
    
    default:
      return;
  }

  /* prepare buffer to send */
  Mouse_Buffer[0] = BUTTON;
  Mouse_Buffer[1] = X;
  Mouse_Buffer[2] = Y;

  /*copy mouse position info in ENDP1 Tx Packet Memory Area*/
  UserToPMABufferCopy(Mouse_Buffer, GetEPTxAddr(ENDP1), 4);
  if(Mouse_Buffer[0]!= 0)
  {
    Mouse_Buffer[0] = 0;
    UserToPMABufferCopy(Mouse_Buffer, GetEPTxAddr(ENDP1), 4);
  } 
  /* enable endpoint for transmission */
  SetEPTxValid(ENDP1);
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
