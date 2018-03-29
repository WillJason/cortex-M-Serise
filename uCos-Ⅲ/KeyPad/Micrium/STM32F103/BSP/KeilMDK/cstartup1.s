;/*
;********************************************************************************************************
;                                    EXCEPTION VECTORS & STARTUP CODE
;
; File      : cstartup.s
; For       : ARMv7M Cortex-M3
; Mode      : Thumb2
; Toolchain : RealView Development Suite
;             RealView Microcontroller Development Kit (MDK)
;             ARM Developer Suite (ADS)
;             Keil uVision
;********************************************************************************************************
;*/

;/*
;********************************************************************************************************
;*                           <<< Use Configuration Wizard in Context Menu >>>
;*
;* Note(s) : (1) The µVision4 Configuration Wizard enables menu driven configuration of assembler, 
;*               C/C++, or debugger initialization files. The Configuration Wizard uses control items 
;*               that are embedded into the comments of the configuration file.
;*
;********************************************************************************************************
;*/

;/*
;********************************************************************************************************
;*                                              STACK DEFINITIONS
;*
;* Configuration Wizard Menu:
;* // <h> Stack Configuration
;* //   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;* // </h>;
;*********************************************************************************************************
;*/

STACK_SIZE      EQU     0x00000200
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   STACK_SIZE
__initial_sp


;/*
;********************************************************************************************************
;*                                              STACK DEFINITIONS
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;*********************************************************************************************************
;*/

HEAP_SIZE       EQU     0x00000000
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   HEAP_SIZE
__heap_limit


                PRESERVE8
                THUMB


                                                      ; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                                IMPORT  BSP_IntHandlerWWDG                             
                                IMPORT  BSP_IntHandlerPVD                                           
                                IMPORT  BSP_IntHandlerTAMP_STAMP                                   
                                IMPORT  BSP_IntHandlerRTC_WKUP                                     
                                IMPORT  BSP_IntHandlerFLASH                                         
                                IMPORT  BSP_IntHandlerRCC                                           
                                IMPORT  BSP_IntHandlerEXTI0                                         
                                IMPORT  BSP_IntHandlerEXTI1                                        
                                IMPORT  BSP_IntHandlerEXTI2                                        
                                IMPORT  BSP_IntHandlerEXTI3                                         
                                IMPORT  BSP_IntHandlerEXTI4                                       
                                IMPORT  BSP_IntHandlerDMA1_CH1                                      
                                IMPORT  BSP_IntHandlerDMA1_CH2                                     
                                IMPORT  BSP_IntHandlerDMA1_CH3                                      
                                IMPORT  BSP_IntHandlerDMA1_CH4                                     
                                IMPORT  BSP_IntHandlerDMA1_CH5                                     
                                IMPORT  BSP_IntHandlerDMA1_CH6                                      
                                IMPORT  BSP_IntHandlerDMA1_CH7                                      
                                IMPORT  BSP_IntHandlerADC1                                          
                                IMPORT  BSP_IntHandlerUSB_HP                                        
                                IMPORT  BSP_IntHandlerUSB_LP                                        
                                IMPORT  BSP_IntHandlerDAC                                           
                                IMPORT  BSP_IntHandlerCOMP                                          
                                                                                            
                                IMPORT  BSP_IntHandlerEXTI9_5                                       
                                IMPORT  BSP_IntHandlerLCD                                           
                                IMPORT  BSP_IntHandlerTIM9                                          
                                IMPORT  BSP_IntHandlerTIM10                                         
                                IMPORT  BSP_IntHandlerTIM11                                         
                                IMPORT  BSP_IntHandlerTIM2                                          
                                IMPORT  BSP_IntHandlerTIM3                                          
                                IMPORT  BSP_IntHandlerTIM4                                          
                                IMPORT  BSP_IntHandlerI2C1_EV                                       
                                IMPORT  BSP_IntHandlerI2C1_ER                                       
                                IMPORT  BSP_IntHandlerI2C2_EV                                      
                                IMPORT  BSP_IntHandlerI2C2_ER                                       
                                IMPORT  BSP_IntHandlerSPI1                                          
                                IMPORT  BSP_IntHandlerSPI2                                          
                                IMPORT  BSP_IntHandlerUSART1                                        
                                IMPORT  BSP_IntHandlerUSART2                                        
                                IMPORT  BSP_IntHandlerUSART3                                        
                                IMPORT  BSP_IntHandlerEXTI15_10                                     
                                IMPORT  BSP_IntHandlerRTCAlarm                                      
                                IMPORT  BSP_IntHandlerUSB_FS_WKUP                                   
                                IMPORT  BSP_IntHandlerTIM6                                         
                                IMPORT  BSP_IntHandlerTIM7                                          
                                
                                IMPORT  BSP_IntHandlerSDIO                                          
                                IMPORT  BSP_IntHandlerTIM5                                          
                                IMPORT  BSP_IntHandlerSPI3                                          
                                IMPORT  BSP_IntHandlerUART4                                         
                                IMPORT  BSP_IntHandlerUART5                                         
                                IMPORT  BSP_IntHandlerDMA2_CH1                                      
                                IMPORT  BSP_IntHandlerDMA2_CH2                                      
                                IMPORT  BSP_IntHandlerDMA2_CH3                                      
                                IMPORT  BSP_IntHandlerDMA2_CH4                                      
                                IMPORT  BSP_IntHandlerDMA2_CH5                                      
                                IMPORT  BSP_IntHandlerAES                                          
                                IMPORT  BSP_IntHandlerCOMP_ACQ
                                
                IMPORT  OS_CPU_PendSVHandler                                        
                IMPORT  OS_CPU_SysTickHandler                                       
    
__Vectors       DCD     __initial_sp                      ; Top of Stack
                DCD     Reset_Handler                     ; Reset Handler
                DCD     App_NMI_ISR                       ;/*  2, NMI.                                               */
                DCD     App_Fault_ISR                     ;/*  3, Hard Fault.                                        */
                DCD     App_MemFault_ISR                  ;/*  4, Memory Management.                                 */
                DCD     App_BusFault_ISR                  ;/*  5, Bus Fault.                                         */
                DCD     App_UsageFault_ISR                ;/*  6, Usage Fault.                                       */
                DCD     App_Spurious_ISR                  ;/*  7, Reserved.                                          */
                DCD     App_Spurious_ISR                  ;/*  8, Reserved.                                          */
                DCD     App_Spurious_ISR                  ;/*  9, Reserved.                                          */
                DCD     App_Spurious_ISR                  ;/* 10, Reserved.                                          */
                DCD     App_Spurious_ISR                  ;/* 11, SVCall.                                            */
                DCD     App_Spurious_ISR                  ;/* 12, Debug Monitor.                                     */
                DCD     App_Spurious_ISR                  ;/* 13, Reserved.                                          */
                DCD     OS_CPU_PendSVHandler              ;/* 14, PendSV Handler.                                    */
                DCD     OS_CPU_SysTickHandler             ;/* 15, uC/OS-III Tick ISR Handler.                        */
    
                DCD     BSP_IntHandlerWWDG                ;/* 16, INTISR[  0]  Window Watchdog.                      */
                DCD     BSP_IntHandlerPVD                 ;/* 17, INTISR[  1]  PVD through EXTI Line Detection.      */
                DCD     BSP_IntHandlerTAMP_STAMP          ;/* 18, INTISR[  2]  Tamper and TimeStamp Interrupt.       */
                DCD     BSP_IntHandlerRTC_WKUP            ;/* 19, INTISR[  3]  RTC Wakeup Global Interrupt.          */
                DCD     BSP_IntHandlerFLASH               ;/* 20, INTISR[  4]  FLASH Global Interrupt.               */
                DCD     BSP_IntHandlerRCC                 ;/* 21, INTISR[  5]  RCC Global Interrupt.                 */
                DCD     BSP_IntHandlerEXTI0               ;/* 22, INTISR[  6]  EXTI Line0 Interrupt.                 */
                DCD     BSP_IntHandlerEXTI1               ;/* 23, INTISR[  7]  EXTI Line1 Interrupt.                 */
                DCD     BSP_IntHandlerEXTI2               ;/* 24, INTISR[  8]  EXTI Line2 Interrupt.                 */
                DCD     BSP_IntHandlerEXTI3               ;/* 25, INTISR[  9]  EXTI Line3 Interrupt.                 */
                DCD     BSP_IntHandlerEXTI4               ;/* 26, INTISR[ 10]  EXTI Line4 Interrupt.                 */
                DCD     BSP_IntHandlerDMA1_CH1            ;/* 27, INTISR[ 11]  DMA Channel1 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH2            ;/* 28, INTISR[ 12]  DMA Channel2 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH3            ;/* 29, INTISR[ 13]  DMA Channel3 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH4            ;/* 30, INTISR[ 14]  DMA Channel4 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH5            ;/* 31, INTISR[ 15]  DMA Channel5 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH6            ;/* 32, INTISR[ 16]  DMA Channel6 Global Interrupt.        */
                DCD     BSP_IntHandlerDMA1_CH7            ;/* 33, INTISR[ 17]  DMA Channel7 Global Interrupt.        */
                DCD     BSP_IntHandlerADC1                ;/* 34, INTISR[ 18]  ADC1 Global Interrupt.                */
                DCD     BSP_IntHandlerUSB_HP              ;/* 35, INTISR[ 19]  USB High priority interrupt           */
                DCD     BSP_IntHandlerUSB_LP              ;/* 36, INTISR[ 20]  USB Low priority interrupt            */
                DCD     BSP_IntHandlerDAC                 ;/* 37, INTISR[ 21]  DAC Interrupt                         */
                DCD     BSP_IntHandlerCOMP                ;/* 38, INTISR[ 22]  Comparator wakeup through ...         */
                                                          ;/* ...              EXTI line (21 & 22) int.              */
                DCD     BSP_IntHandlerEXTI9_5             ;/* 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.             */
                DCD     BSP_IntHandlerLCD                 ;/* 40, INTISR[ 24]  LCD global interrupt                  */
                DCD     BSP_IntHandlerTIM9                ;/* 41, INTISR[ 25]  TIM9 Global Interrupt.                */
                DCD     BSP_IntHandlerTIM10               ;/* 42, INTISR[ 26]  TIM10 Global Interrupt.               */
                DCD     BSP_IntHandlerTIM11               ;/* 43, INTISR[ 27]  TIM11 Global Interrupt.               */
                DCD     BSP_IntHandlerTIM2                ;/* 44, INTISR[ 28]  TIM2 Global Interrupt.                */
                DCD     BSP_IntHandlerTIM3                ;/* 45, INTISR[ 29]  TIM3 Global Interrupt.                */
                DCD     BSP_IntHandlerTIM4                ;/* 46, INTISR[ 30]  TIM4 Global Interrupt.                */
                DCD     BSP_IntHandlerI2C1_EV             ;/* 47, INTISR[ 31]  I2C1 Event  Interrupt.                */
                DCD     BSP_IntHandlerI2C1_ER             ;/* 48, INTISR[ 32]  I2C1 Error  Interrupt.                */
                DCD     BSP_IntHandlerI2C2_EV             ;/* 49, INTISR[ 33]  I2C2 Event  Interrupt.                */
                DCD     BSP_IntHandlerI2C2_ER             ;/* 50, INTISR[ 34]  I2C2 Error  Interrupt.                */
                DCD     BSP_IntHandlerSPI1                ;/* 51, INTISR[ 35]  SPI1 Global Interrupt.                */
                DCD     BSP_IntHandlerSPI2                ;/* 52, INTISR[ 36]  SPI2 Global Interrupt.                */
                DCD     BSP_IntHandlerUSART1              ;/* 53, INTISR[ 37]  USART1 Global Interrupt.              */
                DCD     BSP_IntHandlerUSART2              ;/* 54, INTISR[ 38]  USART2 Global Interrupt.              */
                DCD     BSP_IntHandlerUSART3              ;/* 55, INTISR[ 39]  USART3 Global Interrupt.              */
                DCD     BSP_IntHandlerEXTI15_10           ;/* 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.         */
                DCD     BSP_IntHandlerRTCAlarm            ;/* 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.         */
                DCD     BSP_IntHandlerUSB_FS_WKUP         ;/* 58, INTISR[ 42]  USBD FS Wakeup through EXTI line int. */
                DCD     BSP_IntHandlerTIM6                ;/* 59, INTISR[ 43]  TIM6 Global Interrupt.                */
                DCD     BSP_IntHandlerTIM7                ;/* 60, INTISR[ 44]  TIM7 Global Interrupt.                */
    
                DCD     BSP_IntHandlerSDIO                ;/* 61, INTISR[ 45]  SDIO Global Interrupt.                */
                DCD     BSP_IntHandlerTIM5                ;/* 62, INTISR[ 46]  TIM5 Global Interrupt.                */
                DCD     BSP_IntHandlerSPI3                ;/* 63, INTISR[ 47]  SPI3 Global Interrupt.                */
                DCD     BSP_IntHandlerUART4               ;/* 64, INTISR[ 48]  UART4 Global Interrupt.               */
                DCD     BSP_IntHandlerUART5               ;/* 65, INTISR[ 49]  UART5 Global Interrupt.               */
                DCD     BSP_IntHandlerDMA2_CH1            ;/* 66, INTISR[ 50]  DMA2 Channel 1 Interrupt.             */
                DCD     BSP_IntHandlerDMA2_CH2            ;/* 67, INTISR[ 51]  DMA2 Channel 2 Interrupt.             */
                DCD     BSP_IntHandlerDMA2_CH3            ;/* 68, INTISR[ 52]  DMA2 Channel 3 Interrupt.             */
                DCD     BSP_IntHandlerDMA2_CH4            ;/* 69, INTISR[ 53]  DMA2 Channel 4 Interrupt.             */
                DCD     BSP_IntHandlerDMA2_CH5            ;/* 70, INTISR[ 54]  DMA2 Channel 5 Interrupt.             */
                DCD     BSP_IntHandlerAES                 ;/* 71, INTISR[ 55]  AES Global Interrupt.                 */
                DCD     BSP_IntHandlerCOMP_ACQ            ;/* 72, INTISR[ 56]  Comparator Channel Aquisition Int.    */    

                AREA    |.text|, CODE, READONLY



; Reset Handler

Reset_Handler   PROC    
                EXPORT  Reset_Handler                 [WEAK]
                IMPORT  __main

                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)                

App_NMI_ISR      PROC
                EXPORT  App_NMI_ISR                   [WEAK]
                B       .
                ENDP
App_Fault_ISR\
                PROC
                EXPORT  App_Fault_ISR                 [WEAK]
                B       .
                ENDP
App_MemFault_ISR\
                PROC
                EXPORT  App_MemFault_ISR             [WEAK]
                B       .
                ENDP
App_BusFault_ISR\
                PROC
                EXPORT  App_BusFault_ISR             [WEAK]
                B       .
                ENDP
App_UsageFault_ISR\
                PROC
                EXPORT  App_UsageFault_ISR            [WEAK]
                B       .
                ENDP
App_Spurious_ISR\
                PROC
                EXPORT  App_Spurious_ISR                [WEAK]
                B       .
                ENDP
App_Reserved_ISR\
                PROC
                EXPORT  App_Reserved_ISR                [WEAK]
                B       .
                ENDP


                ALIGN


                                                                ; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + STACK_SIZE)
                LDR     R2, =(Heap_Mem  +  HEAP_SIZE)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
