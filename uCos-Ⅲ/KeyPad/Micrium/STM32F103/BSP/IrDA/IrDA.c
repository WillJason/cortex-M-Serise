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
* Filename      : IrDA.c
* Version       : V1.00
* Programmer(s) : HWC
*********************************************************************************************************
*/
#include "includes.h"

#define IR_TIMER_DEV    TIM3
#define IR_RX_BUF_SIZE  176

static tIrData  IrData[IR_RX_BUF_SIZE];
static unsigned bit_index=0;
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
static void IrDA_IRQHandler(void){
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{
			/* clear interrupt */
			USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
}
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
void IrDA_Init(void){

	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

  
	 /* Enable GPIOC and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
  /* Enable USART3 clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	
  /* Configure USART5 Rx PD.2 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx;
	 /* Configure the USART5 */
  USART_Init(UART5, &USART_InitStructure);
	
  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInit(UART5,&USART_ClockInitStructure);
  
  /* Configure the USART5 */
  USART_Init(UART5, &USART_InitStructure);
  /* Enable the USART5 */
  USART_Cmd(UART5, ENABLE);

  /* Set the USART3 prescaler */
  USART_SetPrescaler(UART5, 0x1);
  /* Configure the USART5 IrDA mode */
  USART_IrDAConfig(UART5, USART_IrDAMode_Normal);
  /* Enable the USART5 IrDA mode */
  USART_IrDACmd(UART5, ENABLE);
	
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	BSP_IntVectSet(BSP_INT_ID_USART5, IrDA_IRQHandler); //
	BSP_IntEn(BSP_INT_ID_USART5);
}


static void Ir_DataInit(void){
	unsigned i;
	for(i=1;i<IR_RX_BUF_SIZE;i++)
		IrData[i-1].pFwd = &IrData[i];
	IrData[IR_RX_BUF_SIZE-1].pFwd = &IrData[0];
}

static void Ir_IRQHandler(void){
	  
	  static unsigned IrStart = 0,IrFrameStartIndex=0;
	  static unsigned IrFrmIndex=0;
	  static tIrDataQ IrDataQ[2];
		OS_ERR p_err;
		extern OS_TCB	AppTaskIRTCB;
		
		EXTI_ClearFlag(EXTI_Line2); 
//		IrData[bit_index].Polarity = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2);
//		IrData[bit_index].TimeOut=0;
		IrData[bit_index].TimeStamp = TIM_GetCounter(IR_TIMER_DEV);
	
	  if(IrData[bit_index].TimeStamp >=440 && IrData[bit_index].TimeStamp <= 450){ //ÅÐ¶ÏÖ¡¿ªÊ¼
			IrStart = 0;
			IrFrameStartIndex=bit_index;
		}
		else
			IrStart++;
		
		if(IrStart == 64){
			IrStart = 0;
			IrDataQ[IrFrmIndex].pDStart = IrData[IrFrameStartIndex].pFwd;
			IrDataQ[IrFrmIndex].pDStop  = IrData[bit_index].pFwd;
			OSTaskQPost(&AppTaskIRTCB,&IrDataQ[IrFrmIndex],sizeof(tIrDataQ),OS_OPT_POST_FIFO,&p_err);
			IrFrmIndex=(IrFrmIndex+1)%2;
		}
		
	  bit_index = (bit_index+1)%IR_RX_BUF_SIZE;
	  TIM_ITConfig(IR_TIMER_DEV,TIM_IT_Update,DISABLE);
	  TIM_GenerateEvent(IR_TIMER_DEV,TIM_EventSource_Update);
	  TIM_ClearFlag(IR_TIMER_DEV,TIM_FLAG_Update);
	  TIM_ITConfig(IR_TIMER_DEV,TIM_IT_Update,ENABLE);
    BSP_LED_Toggle(2); 
}

static void IrGPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* GPIOA Configuration: PD.02 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	  /* Connect EXTI0 Line to PA.00 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource2);

	EXTI_ClearFlag(EXTI_Line2);
  EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd=ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  BSP_IntVectSet(BSP_INT_ID_EXTI2, Ir_IRQHandler);
  BSP_IntEn(BSP_INT_ID_EXTI2);
}

static void IrTimer_IRQHandler(void){
	if( TIM_GetITStatus( IR_TIMER_DEV, TIM_IT_Update ) == SET){
			TIM_ClearITPendingBit(IR_TIMER_DEV,TIM_IT_Update);
	}
}

void IrControler_Init(void){

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_Cmd(IR_TIMER_DEV,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
  TIM_TimeBaseStructure.TIM_Period = 10000;   //dly/50  us
  TIM_TimeBaseStructure.TIM_Prescaler = 719;//APB1 71?? 10us
  TIM_TimeBaseStructure.TIM_ClockDivision=0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//?????
	
  TIM_TimeBaseInit(IR_TIMER_DEV,&TIM_TimeBaseStructure);
	TIM_UpdateRequestConfig(IR_TIMER_DEV,TIM_UpdateSource_Global);
	
  TIM_ClearFlag(IR_TIMER_DEV,TIM_FLAG_Update);
  TIM_ITConfig(IR_TIMER_DEV,TIM_IT_Update,ENABLE);
	TIM_Cmd(IR_TIMER_DEV,ENABLE);
	BSP_IntVectSet(BSP_INT_ID_TIM3, IrTimer_IRQHandler);
  BSP_IntEn(BSP_INT_ID_TIM3);
	Ir_DataInit();
	IrGPIO_Init();
}
