
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
* Filename      : Sensor_Protocol.c
* Version       : V1.00
* Programmer(s) : HWC
*********************************************************************************************************
*/
#include "includes.h"
#include "stdio.h"
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
//ff d2 15 24 47 14 05 02 dd  d2代表传感器状态   d0 无火(不过阀值)  d1 d2 有火  d4 d5  传感器故障

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/
static const uint8_t normal0[]={0xff,0xF0,0xAA,0x03,0xdd};
static const uint8_t normal1[]={0xff,0x00,0x00,0x45,0x56,0x67,0x00,0x00,0xdd};
static const uint8_t normal2[]={0xff,0x10,0x00,0xC3,0xC5,0x51,0x24,0x61,0xdd};
static const uint8_t normal3[]={0xff,0x20,0x00,0x07,0x81,0x9D,0xA7,0x75,0xdd};
static const uint8_t normal4[]={0xff,0x30,0x00,0x52,0x55,0x9D,0x77,0x7E,0xdd};

static const uint8_t init0[]={0xff,0x00,0x00,0x14,0x05,0x02,0x00,0x04,0xdd};
static const uint8_t init1[]={0xff,0x10,0x00,0x57,0x30,0x07,0xa5,0xf7,0xdd};
static const uint8_t init2[]={0xff,0x20,0x00,0x02,0x33,0xdd,0xff,0x7d,0xdd};

static const uint8_t sensor_threhold[]={0xff,0x08,0x01,0x14,0x05,0x02,0x00,0x04,0xdd};
static const uint8_t sensor_offset[]={0xff,0x28,0x02,0x02,0x33,0xdd,0xff,0x7d,0xdd};
static const uint8_t sensor_force[]={0xff,0x08,0x00,0x14,0x05,0x02,0x80,0x04,0xdd};
static const uint8_t sensor_adjust[]={0xff,0x08,0x20,0x14,0x05,0x02,0x40,0x00,0xdd};
static const uint8_t sensor_control[]={0xff,0x18,0x01,0x37,0x30,0x07,0xa5,0xf7,0xdd};
static const uint8_t sensor_output[]={0xff,0x28,0x01,0x00,0x33,0xdd,0xff,0x7d,0xdd};

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/
typedef struct{
	uint8_t *pbuf_in;
	uint8_t *pbuf_out;
	uint8_t len;
	void (*pfun)(void);
}tProtocol;

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
static uint8_t result[9]={0};//命令返回值
static uint8_t protocol_sbuf[9]={0xff,0x00,0x00,0x45,0x56,0x67,0x00,0x00,0xdd};//
static uint8_t protocol_nxtbuf[9]={0xff,0x00,0x00,0x45,0x56,0x67,0x00,0x00,0xdd};
static tProtocol protocol = {protocol_sbuf,result,9,NULL};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void Uart_WriteCh(uint8_t ch){
	USART3->DR = ch;
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
}
void PROTOCOL_proc_after_send(void){
	if(result[0]==0xFF && result[8]==0xDD){
			GUI_Env_Set(result[2],result[3],result[4]);
		  GUI_ThreholdTemp_Set(result[5],result[6]);
		  GUI_Fpu_State(DEF_TRUE);
		  GUI_Sensor_State(result[1]&0x04 ?DEF_FALSE:DEF_TRUE);
	}else{
		GUI_Fpu_State(DEF_FALSE);
	}
}
void PROTOCOL_Strength_Threhold_SetTriger(uint8_t strength,uint8_t freq){
//	uint8_t i;
	Mem_Copy(protocol.pbuf_in,sensor_threhold,sizeof(sensor_threhold));
	protocol.pbuf_in[2]=(strength&0x80)?1:2;
	protocol.pbuf_in[3]=(strength&0x80)?(strength&0x7F):strength;
	protocol.pbuf_in[4]=freq&0x7F;
	protocol.len = sizeof(sensor_threhold);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
	protocol.pbuf_in[2]=0x00;
//	protocol.pbuf_in[3]=protocol.pbuf_out[3];
//	protocol.pbuf_in[4]=protocol.pbuf_out[4];
//	for(i=0;i<sizeof(sensor_threhold);i++)
//		printk("%x ",protocol.pbuf_out[i]);
}
void PROTOCOL_Freq_Threhold_SetTriger(uint8_t strength,uint8_t freq){
  Uart_WriteCh(0xFF);
	Uart_WriteCh(0x08);
	Uart_WriteCh(0x02);
	Uart_WriteCh(strength);
	Uart_WriteCh(freq);
	Uart_WriteCh(0x02);
	Uart_WriteCh(0x00);
	Uart_WriteCh(0x04);
	Uart_WriteCh(0xdd);
}
void PROTOCOL_Offset_SetTriger(uint8_t strength,uint8_t freq){
//	uint8_t i;
	Mem_Copy(protocol.pbuf_in,sensor_offset,sizeof(sensor_offset));
	protocol.pbuf_in[4]=(strength<<4)|(freq&0x0F);
	protocol.len = sizeof(sensor_offset);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x20;
	protocol.pbuf_in[2]=0x00;
//	for(i=0;i<sizeof(sensor_offset);i++)
//		printk("%x ",protocol.pbuf_out[i]);
}
void PROTOCOL_Offset_SetNormal(uint8_t strength,uint8_t freq){
  Uart_WriteCh(0xFF);
	Uart_WriteCh(0x20);
	Uart_WriteCh(0x00);
	Uart_WriteCh(0x02);
	Uart_WriteCh((strength<<4)|(freq&0x0F));
	Uart_WriteCh(0xdd);
	Uart_WriteCh(0xff);
	Uart_WriteCh(0x7d);
	Uart_WriteCh(0xdd);
}
void PROTOCOL_Fireforce_SetTriger(uint8_t type,uint8_t dat){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[7]=0x44;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Fireforce_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_NoFireforce_SetTriger(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[7]=0x04;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_NoFireforce_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Errforce_SetTriger(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[7]=0x84;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Errforce_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_NoErrforce_SetTriger(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[7]=0x04;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_NoErrforce_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Selftest_SetTriger(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[6]=0x02;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Selftest_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Restore_SetTriger(uint8_t stength,uint8_t freq){
	Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.pbuf_in[6]=0x01;
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
	
	protocol_Init();
}
void PROTOCOL_Restore_SetNormal(uint8_t stength,uint8_t freq){
  Mem_Copy(protocol.pbuf_in,sensor_force,sizeof(sensor_force));
	protocol.len = sizeof(sensor_force);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
}
void PROTOCOL_Relay_SetTriger(uint8_t stength,uint8_t freq){
	Mem_Copy(protocol.pbuf_in,sensor_control,sizeof(sensor_control));
	protocol.pbuf_in[3]=stength;
	protocol.len = sizeof(sensor_control);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x10;
	protocol.pbuf_in[2]=0x00;
}
void PROTOCOL_Relay_SetNormal(uint8_t stength,uint8_t freq){

}
void PROTOCOL_NoFiredelay_SetTriger(uint8_t stength,uint8_t freq){

}
void PROTOCOL_NoFiredelay_SetNormal(uint8_t stength,uint8_t freq){

}
void PROTOCOL_OutputMode_SetTriger(uint8_t strength,uint8_t freq){
	
	Mem_Copy(protocol.pbuf_in,sensor_output,sizeof(sensor_output));
	switch(strength){
		case 1:
			protocol.pbuf_in[3]=1;
			break;
		case 2:
			protocol.pbuf_in[3]=0;
			break;
		case 4:
			protocol.pbuf_in[3]=2;
			break;
		case 8:
			protocol.pbuf_in[3]=3;
			break;
		default:
			protocol.pbuf_in[3]=0;
			break;
	}
	protocol.len = sizeof(sensor_output);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x20;
	protocol.pbuf_in[2]=0x00;
}
void PROTOCOL_OutputMode_SetNormal(uint8_t stength,uint8_t freq){

}
void PROTOCOL_Adjust_SetTriger(uint8_t stength,uint8_t freq){
	Mem_Copy(protocol.pbuf_in,sensor_adjust,sizeof(sensor_adjust));
	protocol.len = sizeof(sensor_adjust);
	protocol.pbuf_in[7]=stength==1?(0x00):(0x04);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x00;
	protocol.pbuf_in[2]=0x00;
}
void PROTOCOL_Adjust_SetNormal(uint8_t stength,uint8_t freq){
	Mem_Copy(protocol.pbuf_in,sensor_adjust,sizeof(sensor_adjust));
	protocol.len = sizeof(sensor_adjust);
	protocol.pbuf_in[1]=0x00;
	protocol.pbuf_in[2]=0x00;
	protocol.pbuf_in[7]=stength==1?(freq==1?0x02:0x01):(freq==1?0x06:0x05);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[7]=stength==1?0x00:0x04;
}
void PROTOCOL_Fmode_SetTriger(uint8_t fmode,uint8_t fgain){
	Mem_Copy(protocol.pbuf_in,sensor_control,sizeof(sensor_control));
	protocol.len = sizeof(sensor_control);
	protocol.pbuf_in[2]=0x02;
	protocol.pbuf_in[4]=fmode+(fgain<<4);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x10;
	protocol.pbuf_in[2]=0x00;
}
void PROTOCOL_Fmode_SetNormal(uint8_t fmode,uint8_t fgain){
	Mem_Copy(protocol.pbuf_in,sensor_control,sizeof(sensor_control));
	protocol.len = sizeof(sensor_control);
	protocol.pbuf_in[1]=0x10;
	protocol.pbuf_in[2]=0x00;
	protocol.pbuf_in[4]=fmode+(fgain<<4);
	protocol.pfun = NULL;
	protocol_send();
}
void PROTOCOL_ParamAB_SetTriger(uint8_t pA,uint8_t pB){
	Mem_Copy(protocol.pbuf_in,sensor_control,sizeof(sensor_control));
	protocol.len = sizeof(sensor_control);
	protocol.pbuf_in[2]=0x04;
	protocol.pbuf_in[5]=pA+(pB<<4);
	protocol.pfun = NULL;
	protocol_send();
	protocol.pbuf_in[1]=0x10;
	protocol.pbuf_in[2]=0x00;
}
void PROTOCOL_ParamAB_SetNormal(uint8_t pA,uint8_t pB){
	Mem_Copy(protocol.pbuf_in,sensor_control,sizeof(sensor_control));
	protocol.len = sizeof(sensor_control);
	protocol.pbuf_in[1]=0x10;
	protocol.pbuf_in[2]=0x00;
	protocol.pbuf_in[5]=pA+(pB<<4);
	protocol.pfun = NULL;
	protocol_send();
}


void (*protocol_fun[26])(uint8_t ,uint8_t)={
		PROTOCOL_Strength_Threhold_SetTriger,
		PROTOCOL_Freq_Threhold_SetTriger,
		PROTOCOL_Offset_SetTriger,
		PROTOCOL_Offset_SetNormal,
		PROTOCOL_Fireforce_SetTriger,
		PROTOCOL_Fireforce_SetNormal,
		PROTOCOL_NoFireforce_SetTriger,
		PROTOCOL_NoFireforce_SetNormal,
		PROTOCOL_Errforce_SetTriger,
		PROTOCOL_Errforce_SetNormal,
		PROTOCOL_NoErrforce_SetTriger,
		PROTOCOL_NoErrforce_SetNormal,
		PROTOCOL_Selftest_SetTriger,
		PROTOCOL_Selftest_SetNormal,
		PROTOCOL_Restore_SetTriger,
		PROTOCOL_Restore_SetNormal,
		PROTOCOL_Relay_SetTriger,
		PROTOCOL_Relay_SetNormal,
		PROTOCOL_OutputMode_SetTriger,
		PROTOCOL_OutputMode_SetNormal,
	  PROTOCOL_Adjust_SetTriger,
		PROTOCOL_Adjust_SetNormal,
		PROTOCOL_Fmode_SetTriger,
		PROTOCOL_Fmode_SetNormal,
		PROTOCOL_ParamAB_SetTriger,
		PROTOCOL_ParamAB_SetNormal
};


static void Conn_RCC_Init(void){

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO,ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
}

static void Conn_GPIO_Init(void){
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

static void Conn_IRQHandler(void){

//	OS_ERR err;
	static uint8_t buff[9];
	uint8_t i;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
			for(i=0;i<8;i++)
				buff[i]=buff[i+1];
			buff[8] =USART3->DR;
			if(buff[0]==0xff && buff[8]==0xdd){
				GUI_Env_Set(buff[2],buff[3],buff[4]);
//				printk("S:%d,F:%d,Q:%d\n",buff[2],buff[3],buff[4]);
//				printk("%x,%x,%x,%x,%x,%x,%x,%x,%x\n",buff[0],buff[1],buff[2],buff[3],buff[4],
//																							buff[5],buff[6],buff[7],buff[8]);
				for(i=0;i<9;i++)
					buff[i]=0;
			}
			/* clear interrupt */
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
	if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
	{
		/* clear interrupt */
		USART_ClearITPendingBit(USART3, USART_IT_TC);
	}
}

uint8_t Uart_Conn_Write(const uint8_t *psrc,uint8_t *pdst,uint8_t len){
	 uint8_t i;
	 uint32_t dly=100000;
	 USART_ClearFlag(USART3, USART_IT_RXNE);
	 for(i=0;i<len;i++){
		  USART3->DR = psrc[i];
			/* Loop until the end of transmission */
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET){
				if(0==dly--) return 1;
			}
			pdst[i]=USART3->DR;
      USART_ClearFlag(USART3, USART_IT_RXNE);
		}
	 return 0;
}	

void Uart_Conn_Init(void){
	
	USART_InitTypeDef USART_InitStructure;	
	Conn_RCC_Init();
  USART_DeInit(USART3);
	Conn_GPIO_Init();
  USART_InitStructure.USART_BaudRate = 172800;
  USART_InitStructure.USART_WordLength = USART_WordLength_9b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  USART_Init(USART3, &USART_InitStructure);
  USART_Cmd(USART3, ENABLE);		 //使能UART
	
//	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
//	
//	BSP_IntVectSet(BSP_INT_ID_USART3, Conn_IRQHandler); //
//	BSP_IntEn(BSP_INT_ID_USART3);
}
void protocol_send(void){
	Uart_Conn_Write(protocol.pbuf_in,protocol.pbuf_out,protocol.len);
	if(protocol.pfun !=NULL)
		protocol.pfun();
}
void protocol_normal(void){
	Mem_Copy(protocol.pbuf_in,normal1,sizeof(normal1));
	protocol.len = sizeof(normal1);
	protocol.pfun = PROTOCOL_proc_after_send;
}
//ff d0 37 30 07 08 06 27 dd
//ff d0 37 41 26 08 06 27 dd

void protocol_Init(void){
	OS_ERR err;
	Mem_Copy(protocol.pbuf_in,normal0,sizeof(normal0));
	protocol.len = sizeof(normal0);
	protocol.pfun = NULL;
	protocol_send();
	OSTimeDly(10,OS_OPT_TIME_DLY,&err);
	
	Mem_Copy(protocol.pbuf_in,normal1,sizeof(normal1));
	protocol.len = sizeof(normal1);
	protocol.pfun = NULL;
	protocol_send();
	GUI_Threhold_Set(protocol.pbuf_out[5],protocol.pbuf_out[6]);
	OSTimeDly(10,OS_OPT_TIME_DLY,&err);
	
	Mem_Copy(protocol.pbuf_in,normal2,sizeof(normal2));
	protocol.len = sizeof(normal2);
	protocol.pfun = NULL;
	protocol_send();
	GUI_Relay_Restore(protocol.pbuf_out[2]);
	GUI_FreqMode_Restore(protocol.pbuf_out[3]&0x0F,protocol.pbuf_out[3]>>4);
	GUI_ParamAB_Restore(protocol.pbuf_out[4]&0x0F,protocol.pbuf_out[4]>>4);
	OSTimeDly(10,OS_OPT_TIME_DLY,&err);
	
	Mem_Copy(protocol.pbuf_in,normal3,sizeof(normal3));
	protocol.len = sizeof(normal3);
	protocol.pfun = NULL;
	protocol_send();
	GUI_Offset_Set((protocol.pbuf_out[3]&0xF0)>>4,protocol.pbuf_out[3]&0x0F);
	GUI_OutputType_Set(protocol.pbuf_out[2]);
	OSTimeDly(10,OS_OPT_TIME_DLY,&err);
	
	Mem_Copy(protocol.pbuf_in,normal4,sizeof(normal4));
	protocol.len = sizeof(normal4);
	protocol.pfun = NULL;
	protocol_send();
	OSTimeDly(10,OS_OPT_TIME_DLY,&err);
	
	Mem_Copy(protocol.pbuf_in,normal1,sizeof(normal1));
	protocol.len = sizeof(normal1);
	protocol.pfun = PROTOCOL_proc_after_send;
}
