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

/*  Disp SPI Interface pins  */  
#define sDISP_SPI                           SPI1
#define sDISP_SPI_CLK                       RCC_APB2Periph_SPI1
#define sDISP_SPI_CLK_INIT                  RCC_APB2PeriphClockCmd

#define sDISP_SPI_SCK_PIN                   GPIO_Pin_5
#define sDISP_SPI_SCK_GPIO_PORT             GPIOA
#define sDISP_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA
#define sDISP_SPI_SCK_SOURCE                GPIO_PinSource5
#define sDISP_SPI_SCK_AF                    GPIO_AF_SPI1

#define sDISP_SPI_MISO_PIN                  GPIO_Pin_6
#define sDISP_SPI_MISO_GPIO_PORT            GPIOA
#define sDISP_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA
#define sDISP_SPI_MISO_SOURCE               GPIO_PinSource6
#define sDISP_SPI_MISO_AF                   GPIO_AF_SPI1

#define sDISP_SPI_MOSI_PIN                  GPIO_Pin_7
#define sDISP_SPI_MOSI_GPIO_PORT            GPIOA
#define sDISP_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA
#define sDISP_SPI_MOSI_SOURCE               GPIO_PinSource7
#define sDISP_SPI_MOSI_AF                   GPIO_AF_SPI1

#define sDISP_CS_PIN                        GPIO_Pin_4
#define sDISP_CS_GPIO_PORT                  GPIOA
#define sDISP_CS_GPIO_CLK                   RCC_APB2Periph_GPIOA
/* 移植本软件包时需要修改以下的函数或宏 */
#define		CE_Low()		(GPIO_SetBits(sDISP_CS_GPIO_PORT, sDISP_CS_PIN))
#define     CE_High()		(GPIO_ResetBits(sDISP_CS_GPIO_PORT, sDISP_CS_PIN))
#define     WP_Low()    
#define     WP_High()		

static  uint8_t DisData[5]={0xFF,0xFF,0xFF,0xFF,0xFF};	


/**
  * @brief  Initializes the peripherals used by the SPI DISP driver.
  * @param  None
  * @retval None
  */
static void sDisp_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Enable the SPI clock */
  sDISP_SPI_CLK_INIT(sDISP_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_APB2PeriphClockCmd(sDISP_SPI_SCK_GPIO_CLK | sDISP_SPI_MISO_GPIO_CLK | 
                         sDISP_SPI_MOSI_GPIO_CLK | sDISP_CS_GPIO_CLK, ENABLE);
  
  /*!< SPI pins configuration *************************************************/

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sDISP_SPI_SCK_PIN;
  GPIO_Init(sDISP_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sDISP_SPI_MOSI_PIN;
  GPIO_Init(sDISP_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sDISP_SPI_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(sDISP_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sDISP Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = sDISP_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(sDISP_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes the peripherals used by the SPI DISP driver.
  * @param  None
  * @retval None
  */
static void sDisp_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable the sDISP_SPI  ************************************************/
  SPI_Cmd(sDISP_SPI, DISABLE);
  
  /*!< DeInitializes the sDISP_SPI *******************************************/
  SPI_I2S_DeInit(sDISP_SPI);
  
  /*!< sDISP_SPI Periph clock disable ****************************************/
  sDISP_SPI_CLK_INIT(sDISP_SPI_CLK, DISABLE);
      
  /*!< Configure all pins used by the SPI as input floating *******************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

  GPIO_InitStructure.GPIO_Pin = sDISP_SPI_SCK_PIN;
  GPIO_Init(sDISP_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sDISP_SPI_MISO_PIN;
  GPIO_Init(sDISP_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sDISP_SPI_MOSI_PIN;
  GPIO_Init(sDISP_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sDISP_CS_PIN;
  GPIO_Init(sDISP_CS_GPIO_PORT, &GPIO_InitStructure);
}
/* SPI初始化 */
/*******************************************************************************************
** 函数名称：SPIInit															
** 功能说明：初始化SPI。				
** 入口参数：无																
** 出口参数：无																
*******************************************************************************************/
void  DispInit(void)
{  
  SPI_InitTypeDef  SPI_InitStructure;

	sDisp_LowLevel_DeInit();
  sDisp_LowLevel_Init();
    
  /*!< Deselect the DISP: Chip Select high */
  CE_High();
	/*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sDISP_SPI, &SPI_InitStructure);

  /*!< Enable the sDISP_SPI  */
  SPI_Cmd(sDISP_SPI, ENABLE);
}

/************************************************************************
** 函数名称: Send_Byte													
** 函数功能：通过硬件SPI发送一个字节到SST25VF016B					
** 入口参数:data															
** 出口参数:无																
************************************************************************/
static void Send_Byte(unsigned  char data)
{
    /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sDISP_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sDISP_SPI, data);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sDISP_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  SPI_I2S_ReceiveData(sDISP_SPI);
}

/************************************************************************
** 函数名称:Get_Byte														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
static unsigned  char Get_Byte(void)
{
	/*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sDISP_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sDISP_SPI, 0xFF);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sDISP_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(sDISP_SPI);
}
/************************************************************************
** 函数名称:Get_Byte														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
void Disp_Write(uint8_t addr,uint8_t dat){
	
	DisData[addr%5]=dat;
	CE_Low();
	Send_Byte(DisData[4]);
	Send_Byte(DisData[3]);
	Send_Byte(DisData[2]);
	Send_Byte(DisData[1]);
	Send_Byte(DisData[0]);
	CE_High();
	
}
/************************************************************************
** 函数名称:Get_Byte														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
void Disp_WriteBits(uint8_t addr,uint8_t bit,uint8_t enable){
	
	if(enable)
    DisData[addr%5]&=~(1<<bit);
	else
		DisData[addr%5]|=1<<bit;	
}
/************************************************************************
** 函数名称:Get_Byte														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
void Disp_Flush(void){
	
	CE_Low();
	Send_Byte(DisData[4]);
	Send_Byte(DisData[3]);
	Send_Byte(DisData[2]);
	Send_Byte(DisData[1]);
	Send_Byte(DisData[0]);
	CE_High();
}
/************************************************************************
** 函数名称:Get_Byte														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
void Disp_Flashing(uint8_t en){
	static uint8_t dat =0;
  CE_Low();
  Send_Byte(dat);
  Send_Byte(dat);
  Send_Byte(dat);
  Send_Byte(dat);
  Send_Byte(dat);
  OSTimeDlyHMSM(0,0,0,2,OS_OPT_TIME_HMSM_STRICT,OS_ERR_NONE);
  CE_High();
	dat = dat^0xFF;
}
/************************************************************************
** 函数名称:uint8_t Disp_Read(uint8_t addr)														
** 函数功能:通过硬件SPI接口接收一个字节到处理器						
** 入口参数:无																
** 出口参数:无																
************************************************************************/
uint8_t Disp_Read(uint8_t addr){
	return DisData[addr%5];
}
