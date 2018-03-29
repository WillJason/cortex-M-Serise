/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

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
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : EHS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_INT_MODULE
#include <bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_SRC_NBR                                 68


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

static  CPU_FNCT_VOID  BSP_IntVectTbl[BSP_INT_SRC_NBR];


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_IntHandler     (CPU_DATA  int_id);
static  void  BSP_IntHandlerDummy(void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              BSP_IntClr()
*
* Description : Clear interrupt.
*
* Argument(s) : int_id      Interrupt to clear.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) An interrupt does not need to be cleared within the interrupt controller.
*********************************************************************************************************
*/

void  BSP_IntClr (CPU_DATA  int_id)
{

}


/*
*********************************************************************************************************
*                                              BSP_IntDis()
*
* Description : Disable interrupt.
*
* Argument(s) : int_id      Interrupt to disable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDis (CPU_DATA  int_id)
{
    if (int_id < BSP_INT_SRC_NBR) {
        CPU_IntSrcDis(int_id + 16);
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntDisAll()
*
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    CPU_IntDis();
}


/*
*********************************************************************************************************
*                                               BSP_IntEn()
*
* Description : Enable interrupt.
*
* Argument(s) : int_id      Interrupt to enable.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntEn (CPU_DATA  int_id)
{
    if (int_id < BSP_INT_SRC_NBR) {
        CPU_IntSrcEn(int_id + 16);
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntVectSet()
*
* Description : Assign ISR handler.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               isr         Handler to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntVectSet (CPU_DATA       int_id,
                      CPU_FNCT_VOID  isr)
{
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {
        CPU_CRITICAL_ENTER();
        BSP_IntVectTbl[int_id] = isr;
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntPrioSet()
*
* Description : Assign ISR priority.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*               prio        Priority to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntPrioSet (CPU_DATA    int_id,
                      CPU_INT08U  prio)
{
    CPU_SR_ALLOC();


    if (int_id < BSP_INT_SRC_NBR) {
        CPU_CRITICAL_ENTER();
        CPU_IntSrcPrioSet(int_id + 16, prio);
        CPU_CRITICAL_EXIT();
    }
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           INTERNAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              BSP_IntInit()
*
* Description : Initialize interrupts:
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntInit (void)
{
    CPU_DATA  int_id;


    for (int_id = 0; int_id < BSP_INT_SRC_NBR; int_id++) {
        BSP_IntVectSet(int_id, BSP_IntHandlerDummy);
    }
}


/*
*********************************************************************************************************
*                                        BSP_IntHandler####()
*
* Description : Handle an interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntHandlerWWDG          (void)  { BSP_IntHandler(BSP_INT_ID_WWDG);            }
void  BSP_IntHandlerPVD           (void)  { BSP_IntHandler(BSP_INT_ID_PVD);             }
void  BSP_IntHandlerTAMPER        (void)  { BSP_IntHandler(BSP_INT_ID_TAMPER);          }
void  BSP_IntHandlerRTC           (void)  { BSP_IntHandler(BSP_INT_ID_RTC);             }
void  BSP_IntHandlerFLASH         (void)  { BSP_IntHandler(BSP_INT_ID_FLASH);           }
void  BSP_IntHandlerRCC           (void)  { BSP_IntHandler(BSP_INT_ID_RCC);             }
void  BSP_IntHandlerEXTI0         (void)  { BSP_IntHandler(BSP_INT_ID_EXTI0);           }
void  BSP_IntHandlerEXTI1         (void)  { BSP_IntHandler(BSP_INT_ID_EXTI1);           }
void  BSP_IntHandlerEXTI2         (void)  { BSP_IntHandler(BSP_INT_ID_EXTI2);           }
void  BSP_IntHandlerEXTI3         (void)  { BSP_IntHandler(BSP_INT_ID_EXTI3);           }
void  BSP_IntHandlerEXTI4         (void)  { BSP_IntHandler(BSP_INT_ID_EXTI4);           }
void  BSP_IntHandlerDMA1_CH1      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH1);        }
void  BSP_IntHandlerDMA1_CH2      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH2);        }
void  BSP_IntHandlerDMA1_CH3      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH3);        }
void  BSP_IntHandlerDMA1_CH4      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH4);        }
void  BSP_IntHandlerDMA1_CH5      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH5);        }
void  BSP_IntHandlerDMA1_CH6      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH6);        }
void  BSP_IntHandlerDMA1_CH7      (void)  { BSP_IntHandler(BSP_INT_ID_DMA1_CH7);        }
void  BSP_IntHandlerADC1_2        (void)  { BSP_IntHandler(BSP_INT_ID_ADC1_2);          }
void  BSP_IntHandlerCAN1_TX       (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_TX);         }
void  BSP_IntHandlerCAN1_RX0      (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_RX0);        }
void  BSP_IntHandlerCAN1_RX1      (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_RX1);        }
void  BSP_IntHandlerCAN1_SCE      (void)  { BSP_IntHandler(BSP_INT_ID_CAN1_SCE);        }
void  BSP_IntHandlerEXTI9_5       (void)  { BSP_IntHandler(BSP_INT_ID_EXTI9_5);         }
void  BSP_IntHandlerTIM1_BRK      (void)  { BSP_IntHandler(BSP_INT_ID_TIM1_BRK);        }
void  BSP_IntHandlerTIM1_UP       (void)  { BSP_IntHandler(BSP_INT_ID_TIM1_UP);         }
void  BSP_IntHandlerTIM1_TRG_COM  (void)  { BSP_IntHandler(BSP_INT_ID_TIM1_TRG_COM);    }
void  BSP_IntHandlerTIM1_CC       (void)  { BSP_IntHandler(BSP_INT_ID_TIM1_CC);         }
void  BSP_IntHandlerTIM2          (void)  { BSP_IntHandler(BSP_INT_ID_TIM2);            }
void  BSP_IntHandlerTIM3          (void)  { BSP_IntHandler(BSP_INT_ID_TIM3);            }
void  BSP_IntHandlerTIM4          (void)  { BSP_IntHandler(BSP_INT_ID_TIM4);            }
void  BSP_IntHandlerI2C1_EV       (void)  { BSP_IntHandler(BSP_INT_ID_I2C1_EV);         }
void  BSP_IntHandlerI2C1_ER       (void)  { BSP_IntHandler(BSP_INT_ID_I2C1_ER);         }
void  BSP_IntHandlerI2C2_EV       (void)  { BSP_IntHandler(BSP_INT_ID_I2C2_EV);         }
void  BSP_IntHandlerI2C2_ER       (void)  { BSP_IntHandler(BSP_INT_ID_I2C2_ER);         }
void  BSP_IntHandlerSPI1          (void)  { BSP_IntHandler(BSP_INT_ID_SPI1);            }
void  BSP_IntHandlerSPI2          (void)  { BSP_IntHandler(BSP_INT_ID_SPI2);            }
void  BSP_IntHandlerUSART1        (void)  { BSP_IntHandler(BSP_INT_ID_USART1);          }
void  BSP_IntHandlerUSART2        (void)  { BSP_IntHandler(BSP_INT_ID_USART2);          }
void  BSP_IntHandlerUSART3        (void)  { BSP_IntHandler(BSP_INT_ID_USART3);          }
void  BSP_IntHandlerEXTI15_10     (void)  { BSP_IntHandler(BSP_INT_ID_EXTI15_10);       }
void  BSP_IntHandlerRTCAlarm      (void)  { BSP_IntHandler(BSP_INT_ID_RTC_ALARM);       }
void  BSP_IntHandlerUSBWakeUp     (void)  { BSP_IntHandler(BSP_INT_ID_OTG_FS_WKUP);     }
void  BSP_IntHandlerTIM5          (void)  { BSP_IntHandler(BSP_INT_ID_TIM5);            }
void  BSP_IntHandlerSPI3          (void)  { BSP_IntHandler(BSP_INT_ID_SPI3);            }
void  BSP_IntHandlerUSART4        (void)  { BSP_IntHandler(BSP_INT_ID_USART4);          }
void  BSP_IntHandlerUSART5        (void)  { BSP_IntHandler(BSP_INT_ID_USART5);          }
void  BSP_IntHandlerTIM6          (void)  { BSP_IntHandler(BSP_INT_ID_TIM6);            }
void  BSP_IntHandlerTIM7          (void)  { BSP_IntHandler(BSP_INT_ID_TIM7);            }
void  BSP_IntHandlerDMA2_CH1      (void)  { BSP_IntHandler(BSP_INT_ID_DMA2_CH1);        }
void  BSP_IntHandlerDMA2_CH2      (void)  { BSP_IntHandler(BSP_INT_ID_DMA2_CH2);        }
void  BSP_IntHandlerDMA2_CH3      (void)  { BSP_IntHandler(BSP_INT_ID_DMA2_CH3);        }
void  BSP_IntHandlerDMA2_CH4      (void)  { BSP_IntHandler(BSP_INT_ID_DMA2_CH4);        }
void  BSP_IntHandlerDMA2_CH5      (void)  { BSP_IntHandler(BSP_INT_ID_DMA2_CH5);        }
void  BSP_IntHandlerETH           (void)  { BSP_IntHandler(BSP_INT_ID_ETH);             }
void  BSP_IntHandlerETHWakeup     (void)  { BSP_IntHandler(BSP_INT_ID_ETH_WKUP);        }
void  BSP_IntHandlerCAN2_TX       (void)  { BSP_IntHandler(BSP_INT_ID_CAN2_TX);         }
void  BSP_IntHandlerCAN2_RX0      (void)  { BSP_IntHandler(BSP_INT_ID_CAN2_RX0);        }
void  BSP_IntHandlerCAN2_RX1      (void)  { BSP_IntHandler(BSP_INT_ID_CAN2_RX1);        }
void  BSP_IntHandlerCAN2_SCE      (void)  { BSP_IntHandler(BSP_INT_ID_CAN2_SCE);        }
void  BSP_IntHandlerOTG           (void)  { BSP_IntHandler(BSP_INT_ID_OTG_FS);          }


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_IntHandler()
*
* Description : Central interrupt handler.
*
* Argument(s) : int_id          Interrupt that will be handled.
*
* Return(s)   : none.
*
* Caller(s)   : ISR handlers.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_IntHandler (CPU_DATA  int_id)
{
    CPU_FNCT_VOID  isr;
    CPU_SR_ALLOC();


    CPU_CRITICAL_ENTER();                                       /* Tell the OS that we are starting an ISR            */

    OSIntEnter();

    CPU_CRITICAL_EXIT();

    if (int_id < BSP_INT_SRC_NBR) {
        isr = BSP_IntVectTbl[int_id];
        if (isr != (CPU_FNCT_VOID)0) {
            isr();
        }
    }

    OSIntExit();                                                /* Tell the OS that we are leaving the ISR            */
}


/*
*********************************************************************************************************
*                                        BSP_IntHandlerDummy()
*
* Description : Dummy interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_IntHandlerDummy (void)
{

}
/*
*********************************************************************************************************
*                                        App_NMI_ISR()
*
* Description : NMI interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  App_NMI_ISR_c (unsigned int * p_args)
{
			APP_TRACE_INFO(("R0  : 0x%08x\n", p_args[0]));
			APP_TRACE_INFO(("R1  : 0x%08x\n", p_args[1]));
			APP_TRACE_INFO(("R2  : 0x%08x\n", p_args[2]));
			APP_TRACE_INFO(("R3  : 0x%08x\n", p_args[3]));
			APP_TRACE_INFO(("R12 : 0x%08x\n", p_args[4]));
			APP_TRACE_INFO(("LR  : 0x%08x\n", p_args[5]));
			APP_TRACE_INFO(("PC  : 0x%08x\n", p_args[6]));
			APP_TRACE_INFO(("CPSR: 0x%08x\n", p_args[7]));
	    APP_TRACE_INFO(("NMI ISR\n"));
	while(1);
}
/*
*********************************************************************************************************
*                                        App_Fault_OverFlow_c()
*
* Description : App_Fault_OverFlow interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void App_Fault_OverFlow_c(void)
{
		APP_TRACE_INFO(("Main Stack OverFlow\n"));
}
/*
*********************************************************************************************************
*                                        App_Fault_ISR()
*
* Description : App_Fault_ISR interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  App_Fault_ISR_c (unsigned int * p_args)
{
		unsigned int CFSR;
    unsigned int HFSR;
	
		APP_TRACE_INFO(("R0  : 0x%08x\n", p_args[0]));
		APP_TRACE_INFO(("R1  : 0x%08x\n", p_args[1]));
		APP_TRACE_INFO(("R2  : 0x%08x\n", p_args[2]));
		APP_TRACE_INFO(("R3  : 0x%08x\n", p_args[3]));
		APP_TRACE_INFO(("R12 : 0x%08x\n", p_args[4]));
		APP_TRACE_INFO(("LR  : 0x%08x\n", p_args[5]));
		APP_TRACE_INFO(("PC  : 0x%08x\n", p_args[6]));
		APP_TRACE_INFO(("PSR : 0x%08x\n", p_args[7]));
		CFSR = *((volatile unsigned long *)(0xE000ED28));
    APP_TRACE_INFO ((" CFSR = 0x%08x\r\n", CFSR)); 
    APP_TRACE_INFO ((" BFARVALID   :%d\r\n",CFSR&(1<<15)?1:0));
    APP_TRACE_INFO ((" STKERR      :%d\r\n",CFSR&(1<<12)?1:0));
    APP_TRACE_INFO ((" UNSTKERR    :%d\r\n",CFSR&(1<<11)?1:0));
    APP_TRACE_INFO ((" IMPRECISERR :%d\r\n",CFSR&(1<<10)?1:0));
    APP_TRACE_INFO ((" PRECISERR   :%d\r\n",CFSR&(1<<9)?1:0));
    APP_TRACE_INFO ((" IBUSERR     :%d\r\n",CFSR&(1<<8)?1:0));
    APP_TRACE_INFO ((" MMARVALID   :%d\r\n",CFSR&(1<<7)?1:0));
    APP_TRACE_INFO ((" MSTKERR     :%d\r\n",CFSR&(1<<4)?1:0));
    APP_TRACE_INFO ((" MUNSTKERR   :%d\r\n",CFSR&(1<<3)?1:0));
    APP_TRACE_INFO ((" DACCVIOL    :%d\r\n",CFSR&(1<<1)?1:0));
    APP_TRACE_INFO ((" IACCVIOL    :%d\r\n",CFSR&(1<<0)?1:0));
    APP_TRACE_INFO ((" DIVBYZERO   :%d\r\n",CFSR&(1<<25)?1:0));
    APP_TRACE_INFO ((" UNALIGNED   :%d\r\n",CFSR&(1<<24)?1:0));
    APP_TRACE_INFO ((" NOCP        :%d\r\n",CFSR&(1<<19)?1:0));
    APP_TRACE_INFO ((" INVPC       :%d\r\n",CFSR&(1<<18)?1:0));
    APP_TRACE_INFO ((" INVSTATE    :%d\r\n",CFSR&(1<<17)?1:0));
    APP_TRACE_INFO ((" UNDEFINSTR  :%d\r\n",CFSR&(1<<16)?1:0));
    HFSR = *((volatile unsigned long *)(0xE000ED2C));
    APP_TRACE_INFO (("HFSR = 0x%08x\r\n", HFSR)); 
    APP_TRACE_INFO ((" DEBUGEVT    :%d\r\n",HFSR&((u32)1<<31)?1:0));
    APP_TRACE_INFO ((" FORCED      :%d\r\n",HFSR&(1<<30)?1:0));
    APP_TRACE_INFO ((" VECTBL      :%d\r\n",HFSR&(1<<1)?1:0));
    APP_TRACE_INFO (("DFSR = 0x%08x\r\n", (*((volatile unsigned long *)(0xE000ED30))))); 
    APP_TRACE_INFO (("AFSR = 0x%08x\r\n", (*((volatile unsigned long *)(0xE000ED3C))))); 
    APP_TRACE_INFO (("BFAR = 0x%08x\r\n", (*((volatile unsigned long *)(0xE000ED38))))); 
    APP_TRACE_INFO (("MMAR = 0x%08x\r\n", (*((volatile unsigned long *)(0xE000ED34))))); 
	  APP_TRACE_INFO (("Hardware Fault ISR\n"));
	while(1);
}
/*
*********************************************************************************************************
*                                        BSP_IntHandlerDummy()
*
* Description : App_MemFault_ISR interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  App_MemFault_ISR_c (unsigned int * p_args)
{
			APP_TRACE_INFO(("R0  : 0x%08x\n", p_args[0]));
			APP_TRACE_INFO(("R1  : 0x%08x\n", p_args[1]));
			APP_TRACE_INFO(("R2  : 0x%08x\n", p_args[2]));
			APP_TRACE_INFO(("R3  : 0x%08x\n", p_args[3]));
			APP_TRACE_INFO(("R12 : 0x%08x\n", p_args[4]));
			APP_TRACE_INFO(("LR  : 0x%08x\n", p_args[5]));
			APP_TRACE_INFO(("PC  : 0x%08x\n", p_args[6]));
			APP_TRACE_INFO(("CPSR: 0x%08x\n", p_args[7]));
	    APP_TRACE_INFO(("MemFault ISR\n"));
	while(1);	
}
/*
*********************************************************************************************************
*                                        App_BusFault_ISR()
*
* Description : App_BusFault_ISR interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  App_BusFault_ISR_c (unsigned int * p_args)
{
			APP_TRACE_INFO(("R0  : 0x%08x\n", p_args[0]));
			APP_TRACE_INFO(("R1  : 0x%08x\n", p_args[1]));
			APP_TRACE_INFO(("R2  : 0x%08x\n", p_args[2]));
			APP_TRACE_INFO(("R3  : 0x%08x\n", p_args[3]));
			APP_TRACE_INFO(("R12 : 0x%08x\n", p_args[4]));
			APP_TRACE_INFO(("LR  : 0x%08x\n", p_args[5]));
			APP_TRACE_INFO(("PC  : 0x%08x\n", p_args[6]));
			APP_TRACE_INFO(("CPSR: 0x%08x\n", p_args[7]));
	    APP_TRACE_INFO(("BusFault ISR\n"));
	while(1);	
}
/*
*********************************************************************************************************
*                                        App_UsageFault_ISR()
*
* Description : App_UsageFault_ISR interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  App_UsageFault_ISR_c (unsigned int * p_args)
{
			APP_TRACE_INFO(("R0  : 0x%08x\n", p_args[0]));
			APP_TRACE_INFO(("R1  : 0x%08x\n", p_args[1]));
			APP_TRACE_INFO(("R2  : 0x%08x\n", p_args[2]));
			APP_TRACE_INFO(("R3  : 0x%08x\n", p_args[3]));
			APP_TRACE_INFO(("R12 : 0x%08x\n", p_args[4]));
			APP_TRACE_INFO(("LR  : 0x%08x\n", p_args[5]));
			APP_TRACE_INFO(("PC  : 0x%08x\n", p_args[6]));
			APP_TRACE_INFO(("CPSR: 0x%08x\n", p_args[7]));
	    APP_TRACE_INFO(("UsageFault ISR\n"));
	while(1);
}