
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

#include "uart.h"

static OS_SEM UartRecSem;
static CPU_INT08U 	 UartRecDat=0;
__align(4)
static tUartRingBuf  Uart3Buf[UART_RING_BUF_SIZE];// __attribute__((at(0x20010000-sizeof(tUartRingBuf)*UART_RING_BUF_SIZE)));
static tUartInfo 		 pUartInfo[UART_MSG_SIZE];


void Uart_RCC_Init(void){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

void Uart_Keypad_RCC_Init(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
}

void Uart_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	//GPIOA初始化，USART1 Tx (PA9) 复用开漏输出
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	  
	//Configure USART1 Rx (PA10) as input floating 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Uart_Keypad_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	//GPIOA初始化，USART3 Tx (PB10) 复用开漏输出
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	  
	//Configure USART3 Rx (PB11) as input floating 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void USART_IRQHandler(void){

	OS_ERR err;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		 UartRecDat =USART_ReceiveData(USART1);
		 OSSemPost(&UartRecSem,OS_OPT_POST_1,&err);
		/* clear interrupt */
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{
		/* clear interrupt */
		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}
}


static void Keypad_EnvInit(void){
 unsigned i=0;
 for(i=0;i<(UART_RING_BUF_SIZE-1);i++)
	Uart3Buf[i].pnext = &Uart3Buf[i+1];
 Uart3Buf[i].pnext = &Uart3Buf[0];
// for(tUartRingBuf *p=&Uart3Buf[0];p!=&Uart3Buf[UART_RING_BUF_SIZE-1];p=p->pnext){
//	USART3->DR = p->dat;
//	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
// }
}

void Keypad_IRQHandler(void){
	OS_ERR err;
	extern OS_TCB		AppTaskCommTCB;
	static unsigned Usart3_Msg_Index = 0;
	static unsigned count=0;
	static volatile tUartRingBuf  *pNext=&Uart3Buf[0]; 
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{		/* clear interrupt */
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
			char dat =USART_ReceiveData(USART3);
		  if(pNext == NULL) {pNext = &Uart3Buf[0];};
		  if(pNext == NULL) return;
		  pNext->dat=dat;
			pNext->count=count++;
			if(pNext->dat == 0xFE){
				pUartInfo[Usart3_Msg_Index].pStart = pNext;
				pNext->count = count =0;
			}else if(pNext->dat == 0xFF){
				pUartInfo[Usart3_Msg_Index].pStop = pNext;			
				OSTaskQPost(&AppTaskCommTCB,&pUartInfo[Usart3_Msg_Index],sizeof(tUartInfo),OS_OPT_POST_FIFO,&err);
				Usart3_Msg_Index = (Usart3_Msg_Index+1)%UART_MSG_SIZE;
			}
			pNext=pNext->pnext;
	}
//	if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
//	{
//		/* clear interrupt */
//		USART_ClearITPendingBit(USART3, USART_IT_TC);
//	}
}

void Uart_cfg(void){
	
	USART_InitTypeDef USART_InitStructure;
	OS_ERR err;
	
	Uart_RCC_Init();
  USART_DeInit(USART1);
	Uart_GPIO_Init();
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);		 //使能UART
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	OSSemCreate(&UartRecSem,"Uart RecSem",0,&err);
	
	BSP_IntVectSet(BSP_INT_ID_USART1, USART_IRQHandler); //
	BSP_IntEn(BSP_INT_ID_USART1);
}

void Uart_Keypad_Send(uint8_t *buf,uint8_t len){
	  for(unsigned i=0;i<len;i++){
			USART3->DR = (CPU_INT08U)buf[i];
			while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
		}
}

void Uart_Keypad_Init(void){
	USART_InitTypeDef USART_InitStructure;
	Uart_Keypad_RCC_Init();
  USART_DeInit(USART3);
	Uart_Keypad_GPIO_Init();
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART3, &USART_InitStructure);
  USART_Cmd(USART3, ENABLE);		 //使能UART	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	Keypad_EnvInit();
	BSP_IntVectSet(BSP_INT_ID_USART3, Keypad_IRQHandler); //
	BSP_IntEn(BSP_INT_ID_USART3);
}

void LCD_IRQHandler(void){
    static uint8_t xyplot[10]; 
	static uint32_t xydata[10];
	static uint8_t index=0;
	OS_ERR p_err;
	extern OS_TCB	AppTaskDisplayTCB;
  uint8_t i;
	USART_GetITStatus(USART2, USART_IT_RXNE);
	for(i=0;i<9;i++)
		xyplot[i]=xyplot[i+1];
	xyplot[9] =USART_ReceiveData(USART2);
	if(xyplot[0]==0xfd && xyplot[6]==0xdd&&xyplot[7]==0xcc&&xyplot[8]==0xbb&&xyplot[9]==0xaa){
//		printk("X:%03d,Y:%03d\n",(xyplot[2]<<8)+xyplot[3],(xyplot[4]<<8)+xyplot[5]);
		xydata[index]=(xyplot[2]<<24)+(xyplot[3]<<16)+(xyplot[4]<<8)+xyplot[5];
		OSTaskQPost(&AppTaskDisplayTCB,&xydata[index],1,OS_OPT_POST_FIFO,&p_err);
		index=(index+1)%10;
		for(i=0;i<10;i++)
			xyplot[i]=0;
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}
void LCD_Init(void){
//	OS_ERR err;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//GPIOA初始化，USART2 Tx (PA2) 复用开漏输出
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	  
	//Configure USART2 Rx (PA3) as input floating 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_DeInit(USART2);

  USART_InitStructure.USART_BaudRate = 460800;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
//	OSSemCreate(&UartRecSem,"Uart RecSem",0,&err);
	
	BSP_IntVectSet(BSP_INT_ID_USART2, LCD_IRQHandler); //
	BSP_IntEn(BSP_INT_ID_USART2);
	USART_Cmd(USART2, ENABLE);		 //使能UART
}

int fputc(int ch ,FILE *f){
	  
//	  if(ch=='\n'){
//			USART1->DR = '\r';
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//		}
		USART1->DR = (CPU_INT08U)ch;
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		return ch;
}

int fgetc(FILE *stream){
	OS_ERR err;
	CPU_TS ts;
	OSSemPend(&UartRecSem,0,OS_OPT_PEND_BLOCKING,&ts,&err);
	return UartRecDat;
}
