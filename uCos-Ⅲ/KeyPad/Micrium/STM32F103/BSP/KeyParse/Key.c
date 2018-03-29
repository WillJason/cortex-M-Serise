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

#include 		<includes.h>
#include    "hw_config.h"

#define TIMER_DEV            	( TIM2 )

#define PULSE_TIME						(5)
#define WR_RESP_TIME					(5000)
#define RD_RESP_TIME					(100)
#define BTW_TIME							(200)

/*  Disp SPI Interface pins  */  
#define sKEY_SPI                           SPI3
#define sKEY_SPI_CLK                       RCC_APB1Periph_SPI3
#define sKEY_SPI_CLK_INIT                  RCC_APB1PeriphClockCmd

#define sKEY_SPI_SCK_PIN                   GPIO_Pin_3
#define sKEY_SPI_SCK_GPIO_PORT             GPIOB
#define sKEY_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOB
#define sKEY_SPI_SCK_SOURCE                GPIO_PinSource3
#define sKEY_SPI_SCK_AF                    GPIO_AF_SPI3

#define sKEY_SPI_MISO_PIN                  GPIO_Pin_4
#define sKEY_SPI_MISO_GPIO_PORT            GPIOB
#define sKEY_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sKEY_SPI_MISO_SOURCE               GPIO_PinSource4
#define sKEY_SPI_MISO_AF                   GPIO_AF_SPI3

#define sKEY_SPI_MOSI_PIN                  GPIO_Pin_5
#define sKEY_SPI_MOSI_GPIO_PORT            GPIOB
#define sKEY_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOB
#define sKEY_SPI_MOSI_SOURCE               GPIO_PinSource5
#define sKEY_SPI_MOSI_AF                   GPIO_AF_SPI3

#define sKEY_CS1_PIN                        GPIO_Pin_6
#define sKEY_CS1_GPIO_PORT                  GPIOB
#define sKEY_CS1_GPIO_CLK                   RCC_APB2Periph_GPIOB

#define sKEY_CS2_PIN                        GPIO_Pin_7
#define sKEY_CS2_GPIO_PORT                  GPIOB
#define sKEY_CS2_GPIO_CLK                   RCC_APB2Periph_GPIOB
/* ÒÆÖ²±¾Èí¼þ°üÊ±ÐèÒªÐÞ¸ÄÒÔÏÂµÄº¯Êý»òºê */
#define			CS1_Low()		(GPIO_ResetBits(sKEY_CS1_GPIO_PORT, sKEY_CS1_PIN))
#define     CS1_High()		(GPIO_SetBits(sKEY_CS1_GPIO_PORT, sKEY_CS1_PIN))
#define			CS2_Low()		(GPIO_ResetBits(sKEY_CS2_GPIO_PORT, sKEY_CS2_PIN))
#define     CS2_High()		(GPIO_SetBits(sKEY_CS2_GPIO_PORT, sKEY_CS2_PIN))

#define			CLK_Low()		(GPIO_ResetBits(sKEY_SPI_SCK_GPIO_PORT, sKEY_SPI_SCK_PIN))
#define     CLK_High()		(GPIO_SetBits(sKEY_SPI_SCK_GPIO_PORT, sKEY_SPI_SCK_PIN))
#define			SDA_Low()		(GPIO_ResetBits(sKEY_SPI_MOSI_GPIO_PORT,sKEY_SPI_MOSI_PIN))
#define     SDA_High()		(GPIO_SetBits(sKEY_SPI_MOSI_GPIO_PORT,sKEY_SPI_MOSI_PIN))
#define			SDA_IN()		(GPIO_ReadInputDataBit(sKEY_SPI_MISO_GPIO_PORT, sKEY_SPI_MISO_PIN))

//#define USE_KEY_SPI


__inline static void delay_in_us(unsigned us)													   

{
	for(;us!=0;us--) 
	{
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;__NOP;
		__NOP;__NOP;
	}
}

/**
  * @brief  Initializes the peripherals used by the SPI KEY driver.
  * @param  None
  * @retval None
  */
static void sKey_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

#ifdef USE_KEY_SPI	
  /*!< Enable the SPI clock */
  sKEY_SPI_CLK_INIT(sKEY_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_APB2PeriphClockCmd(sKEY_SPI_SCK_GPIO_CLK | sKEY_SPI_MISO_GPIO_CLK | 
                         sKEY_SPI_MOSI_GPIO_CLK | sKEY_CS1_GPIO_CLK |
												 sKEY_CS2_GPIO_CLK, ENABLE);
  
  /*!< SPI pins configuration *************************************************/

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sKEY_SPI_SCK_PIN;
  GPIO_Init(sKEY_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sKEY_SPI_MOSI_PIN;
  GPIO_Init(sKEY_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sKEY_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(sKEY_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
#else
 /*!< Enable GPIO clocks */
  RCC_APB2PeriphClockCmd(sKEY_SPI_SCK_GPIO_CLK | sKEY_SPI_MISO_GPIO_CLK | 
                         sKEY_SPI_MOSI_GPIO_CLK | sKEY_CS1_GPIO_CLK |
												 sKEY_CS2_GPIO_CLK, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB , ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sKEY_SPI_SCK_PIN;
  GPIO_Init(sKEY_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sKEY_SPI_MOSI_PIN;
  GPIO_Init(sKEY_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin =  sKEY_SPI_MISO_PIN;
  GPIO_Init(sKEY_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
	
#endif

  /*!< Configure sKEY Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = sKEY_CS1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(sKEY_CS1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = sKEY_CS2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(sKEY_CS2_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes the peripherals used by the SPI KEY driver.
  * @param  None
  * @retval None
  */
static void sKey_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable the sKEY_SPI  ************************************************/
  SPI_Cmd(sKEY_SPI, DISABLE);
  
  /*!< DeInitializes the sKEY_SPI *******************************************/
  SPI_I2S_DeInit(sKEY_SPI);
  
  /*!< sKEY_SPI Periph clock disable ****************************************/
  sKEY_SPI_CLK_INIT(sKEY_SPI_CLK, DISABLE);
      
  /*!< Configure all pins used by the SPI as input floating *******************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

  GPIO_InitStructure.GPIO_Pin = sKEY_SPI_SCK_PIN;
  GPIO_Init(sKEY_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sKEY_SPI_MISO_PIN;
  GPIO_Init(sKEY_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sKEY_SPI_MOSI_PIN;
  GPIO_Init(sKEY_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sKEY_CS1_PIN;
  GPIO_Init(sKEY_CS1_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = sKEY_CS2_PIN;
  GPIO_Init(sKEY_CS2_GPIO_PORT, &GPIO_InitStructure);
}
/* SPI³õÊ¼»¯ */
/*******************************************************************************************
** º¯ÊýÃû³Æ£ºSPIInit															
** ¹¦ÄÜËµÃ÷£º³õÊ¼»¯SPI¡£				
** Èë¿Ú²ÎÊý£ºÎÞ																
** ³ö¿Ú²ÎÊý£ºÎÞ																
*******************************************************************************************/
static void  KeyInit(void)
{  
  SPI_InitTypeDef  SPI_InitStructure;

  sKey_LowLevel_Init();
    
  /*!< Deselect the KEY: Chip Select high */
  CS1_High();
	CS2_High();
#ifdef USE_KEY_SPI
	/*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sKEY_SPI, &SPI_InitStructure);

  /*!< Enable the sKEY_SPI  */
  SPI_Cmd(sKEY_SPI, ENABLE);
#else
	CLK_High();
	SDA_Low();
#endif
}

/************************************************************************
** º¯ÊýÃû³Æ: Send_Byte													
** º¯Êý¹¦ÄÜ£ºÍ¨¹ýÓ²¼þSPI·¢ËÍÒ»¸ö×Ö½Úµ½SST25VF016B					
** Èë¿Ú²ÎÊý:data															
** ³ö¿Ú²ÎÊý:ÎÞ																
************************************************************************/
static void KSend_Byte(unsigned  short data)
{
#ifdef USE_KEY_SPI
    /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sKEY_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sKEY_SPI, data);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sKEY_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  SPI_I2S_ReceiveData(sKEY_SPI);
#else
	for(unsigned i=0;i<16;i++){
		CLK_Low();
		if(data & 0x8000) 
			SDA_High();
		else
			SDA_Low();
		data<<=1;
		delay_in_us(20);
		CLK_High();
		delay_in_us(20);
	}
#endif
}

/************************************************************************
** º¯ÊýÃû³Æ:Get_Byte														
** º¯Êý¹¦ÄÜ:Í¨¹ýÓ²¼þSPI½Ó¿Ú½ÓÊÕÒ»¸ö×Ö½Úµ½´¦ÀíÆ÷						
** Èë¿Ú²ÎÊý:ÎÞ																
** ³ö¿Ú²ÎÊý:ÎÞ																
************************************************************************/
static unsigned  short KGet_Byte(void)
{
#ifdef USE_KEY_SPI
	/*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sKEY_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sKEY_SPI, 0x55);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sKEY_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(sKEY_SPI);
#else
		unsigned short data=0;
		for(unsigned i=0;i<16;i++){
			data = data <<1;
			CLK_Low();
			delay_in_us(100);
			CLK_High();
			delay_in_us(40);
			if(SDA_IN())
				data |=1;
			delay_in_us(40);
		}
		return data;
#endif
}
/*
*********************************************************************************************************
*                                          read7281()
*
* Description : 读7281
*
* Argument(s) :  addr
*
* Return(s)   : data
*
* Caller(s)   : App()
*
* Note(s)     : 读出 BC728X 内部寄存器的值, 调用参数为寄存器地址
*********************************************************************************************************
*/
static void BC7277_ISR(void){
	extern OS_TCB					AppTaskDisplayTCB;
	OS_ERR err;
	tKeyFun  key;
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
		key.fun = FUN_READ_KEY;
		key.code[0]=0x01;
		OSTaskQPost(&AppTaskDisplayTCB,&key,1,OS_OPT_POST_FIFO,&err);
    /* Clear the  EXTI line 6 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
		key.fun = FUN_READ_KEY;
		key.code[0]=0x02;
		OSTaskQPost(&AppTaskDisplayTCB,&key,1,OS_OPT_POST_FIFO,&err);
    /* Clear the  EXTI line 6 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line12);
  }
}
/*
*********************************************************************************************************
*                                          read7281()
*
* Description : 读7281
*
* Argument(s) :  addr
*
* Return(s)   : data
*
* Caller(s)   : App()
*
* Note(s)     : 读出 BC728X 内部寄存器的值, 调用参数为寄存器地址
*********************************************************************************************************
*/
static void BC7277_hw_Init(void){
	
	GPIO_InitTypeDef  gpio_init;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	
  KeyInit();
	
	gpio_init.GPIO_Pin   = GPIO_Pin_2;
	gpio_init.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &gpio_init);
	gpio_init.GPIO_Pin   = GPIO_Pin_12;
	gpio_init.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &gpio_init);
	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);
//	/* Configure EXTI2 line */
//  EXTI_InitStructure.EXTI_Line = EXTI_Line2|EXTI_Line12;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
//	
//	BSP_IntVectSet(BSP_INT_ID_EXTI15_10, BC7277_ISR);
//  BSP_IntEn(BSP_INT_ID_EXTI15_10);
//	BSP_IntVectSet(BSP_INT_ID_EXTI2, BC7277_ISR);
//  BSP_IntEn(BSP_INT_ID_EXTI2);
}
/*
*********************************************************************************************************
*                                          debug_bc7281()
*
* Description : 
*
* Argument(s) :  none
*
* Return(s)   : none
*
* Caller(s)   : App()
*
* Note(s)     : 
*********************************************************************************************************
*/
void BC7277_Init(void)
{
	BC7277_hw_Init();
//	write7281(0x12,0x87); // initialize BC7281. 采用74HC595,开启扫描,反向.
}
///*
//*********************************************************************************************************
//*                                          debug_bc7281()
//*
//* Description : 
//*
//* Argument(s) :  none
//*
//* Return(s)   : none
//*
//* Caller(s)   : App()
//*
//* Note(s)     : 
//*********************************************************************************************************
//*/
//void BC7281B_Write(uint8_t addr,uint8_t dat)
//{
//	write7281(addr,dat); // display '0' at postion 0.
//}
/*
*********************************************************************************************************
*                                          debug_bc7281()
*
* Description : 
*
* Argument(s) :  none
*
* Return(s)   : none
*
* Caller(s)   : App()
*
* Note(s)     : 
*********************************************************************************************************
*/
uint16_t BC7277_Read(uint8_t addr)
{
	uint16_t dat=0;
	addr == 1?CS1_Low():CS2_Low();
	delay_in_us(400);
	dat  =  KGet_Byte();
	delay_in_us(200);
	addr == 1?CS1_High():CS2_High();
	return dat;
}
