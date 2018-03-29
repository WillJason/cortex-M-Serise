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
//  232 Ïß  2ÂÌ  3À¶  5ºÚ
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include    <includes.h>
#include    "hw_config.h"
#include    "keycode.h"
/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/
static volatile unsigned time_delay = 0;

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/ 
static  OS_TCB                  AppTaskStartTCB;
static  OS_TCB                  AppTaskTermTCB;
        OS_TCB					AppTaskCommTCB;
        OS_TCB					AppTaskDisplayTCB;
__align(8)
static  CPU_STK         AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];
__align(8)
static  CPU_STK         AppTaskTermStk[APP_CFG_TASK_TERM_STK_SIZE];
__align(8)
static  CPU_STK					AppTaskDisplayStk[APP_CFG_TASK_DISPLAY_STK_SIZE];
__align(8)
static  CPU_STK         AppTaskCommStk[APP_CFG_TASK_COMM_STK_SIZE];
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart              (void *p_arg);
static  void  AppTaskTerm               (void *p_arg);
static  void  AppTaskDisplay			(void *p_arg);
static  void  AppTaskComm				(void *p_arg);
static  void  AppTaskCreate             (void);
static  void  AppObjCreate              (void);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR  err;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, (USER_APP_BEGIN - NVIC_VectTab_FLASH));
    BSP_IntDisAll();                                            /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */
														    
    OSTaskCreate((OS_TCB    *)&AppTaskStartTCB,                 /* Create the start task                                */
                 (CPU_CHAR  *)"App Task Start",
                 (OS_TASK_PTR)AppTaskStart,
                 (void      *)0,
                 (OS_PRIO    )APP_CFG_TASK_START_PRIO,
                 (CPU_STK   *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE)AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE / 10],
                 (CPU_STK_SIZE)APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY )0,
                 (OS_TICK    )0,
                 (void      *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR    *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

    (void)&err;

    return (0);
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

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts         = cpu_clk_freq                                 /* Determine nbr SysTick increments                     */
                 / (CPU_INT32U)OSCfg_TickRate_Hz;

    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize memory managment module                   */
    Math_Init();                                                /* Initialize mathematical module                       */
	  
		App_OS_SetAllHooks();

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    BSP_LED_Off(0);

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
    BSP_Ser_Init(115200);                                       /* Initialize Serial communication for application ...  */
#endif                                                          /* ... tracing                                          */
    
    
    APP_TRACE_DBG(("Creating Application kernel objects\n\r"));
    AppObjCreate();                                             /* Create Applicaiton kernel objects                    */

    APP_TRACE_DBG(("Creating Application Tasks\n\r"));
    AppTaskCreate();                                            /* Create Application tasks                             */
    cnts=0;
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
//				uint8_t i=0;
				BSP_LED_Toggle(1);
			  OSTimeDly(100,OS_OPT_TIME_DLY,&err);
//        printk("Key:%08x\n",cnts++);
			
    }
}


/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
	OS_ERR      err;
	
	OSTaskCreate((OS_TCB    *)&AppTaskTermTCB,                 /* Create the Term task                                */
                 (CPU_CHAR  *)"App Task Term",
                 (OS_TASK_PTR)AppTaskTerm,
                 (void      *)0,
                 (OS_PRIO    )APP_CFG_TASK_TERM_PRIO,
                 (CPU_STK   *)&AppTaskTermStk[0],
                 (CPU_STK_SIZE)AppTaskTermStk[APP_CFG_TASK_TERM_STK_SIZE / 10],
                 (CPU_STK_SIZE)APP_CFG_TASK_TERM_STK_SIZE,
                 (OS_MSG_QTY )0,
                 (OS_TICK    )0,
                 (void      *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR    *)&err);
	OSTaskCreate((OS_TCB    *)&AppTaskDisplayTCB,                 /* Create the Term task                                */
                 (CPU_CHAR  *)"App Task Display",
                 (OS_TASK_PTR)AppTaskDisplay,
                 (void      *)0,
                 (OS_PRIO    )APP_CFG_TASK_DISPLAY_PRIO,
                 (CPU_STK   *)&AppTaskDisplayStk[0],
                 (CPU_STK_SIZE)AppTaskDisplayStk[APP_CFG_TASK_DISPLAY_STK_SIZE / 10],
                 (CPU_STK_SIZE)APP_CFG_TASK_DISPLAY_STK_SIZE,
                 (OS_MSG_QTY )10,
                 (OS_TICK    )0,
                 (void      *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR    *)&err);
	OSTaskCreate((OS_TCB    *)&AppTaskCommTCB,                 /* Create the Term task                                */
                 (CPU_CHAR  *)"App Task Comm",
                 (OS_TASK_PTR)AppTaskComm,
                 (void      *)0,
                 (OS_PRIO    )APP_CFG_TASK_COMM_PRIO,
                 (CPU_STK   *)&AppTaskCommStk[0],
                 (CPU_STK_SIZE)AppTaskCommStk[APP_CFG_TASK_COMM_STK_SIZE / 10],
                 (CPU_STK_SIZE)APP_CFG_TASK_COMM_STK_SIZE,
                 (OS_MSG_QTY )10,
                 (OS_TICK    )0,
                 (void      *)0,
                 (OS_OPT     )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR    *)&err);
}

/*
*********************************************************************************************************
*                                          AppObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
  
}
/*
*********************************************************************************************************
*                                          AppTaskLOC()
*
* Description : Location tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : os
*
* Note(s)     : none.
*********************************************************************************************************
*/
static void AppTaskTerm(void* arg)
{
	Uart_cfg();
	init_builtin_cmds();
   while(1)
	 {
		 serial_terminal();
   }
}
/*
*********************************************************************************************************
*                                          AppTaskDisplay()
*
* Description : Location tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : os
*
* Note(s)     : none.
*********************************************************************************************************
*/
#define KEY_BUF_SIZE 10
static tUartRingBuf  KeyBuf[KEY_BUF_SIZE];
static CPU_INT08U KeyFrame[KEY_BUF_SIZE]={0xFD,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF};
const char FillStr[1000]="hello world";
static void Keypad_EnvInit(void){
 unsigned i=0;
 for(i=0;i<(KEY_BUF_SIZE-1);i++){
	KeyBuf[i].pnext = &KeyBuf[i+1];
	KeyBuf[i].dat = KeyFrame[i];
	KeyBuf[i].count=i+1;
 }
 KeyBuf[i].pnext = &KeyBuf[0];
 KeyBuf[i].dat=KeyFrame[i];
 KeyBuf[i].count = i+1;
}

static void AppTaskDisplay(void* arg)
{
	OS_ERR err;
	CPU_TS ts;
	OS_MSG_SIZE msg_size;
	tKeyFun  *pkey;
	CPU_INT32U code=0,state =0xFFFFFFFF;
	tUartInfo pdat;
	BC7277_Init();
	DispInit();
	Disp_Flush();
  while(1){

	pkey = OSTaskQPend(KEY_CAP_TIMEOUT,OS_OPT_PEND_BLOCKING,&msg_size,&ts,&err);
		if(err == OS_ERR_NONE){
			switch(pkey->fun){
				case FUN_READ_KEY:
			      code  = BC7277_Read(2)<<16;
				    code |= BC7277_Read(1);
				  	code  = ~code;

					unsigned key_count=0;
					for(int i=0;i<KEY_NUM;i++){
						if(code&(1<<i))  key_count++;
					}
					if(key_count>3) code = 0;

            for(unsigned i=0;i<KEY_NUM;i++)
						KeyFrame[i]=(i==0||i==(KEY_NUM-1))?KeyFrame[i]:0;
				  	for(unsigned i=0;i<KEY_NUM;i++){
						if(code & (1<<i))
						{
							KeyFrame[KeyList[i].row+1]|=1<<KeyList[i].col;	   
						}
					}
					  Keypad_EnvInit();
					  pdat.pStart=&KeyBuf[0];
				    pdat.pStop =&KeyBuf[KEY_BUF_SIZE-1];				
					  OSTaskQPost(&AppTaskCommTCB,&pdat,1,OS_OPT_POST_FIFO,&err);										  
					break;
       case FUN_CTRL_LED:
					unsigned led_value=0;
//		    printk("%02x,%02x,%02x,%02x,%02x\n",pkey->code[0],pkey->code[1],pkey->code[2],pkey->code[3],pkey->code[4]);
					led_value = (pkey->code[3]<<24)+(pkey->code[2]<<16)+(pkey->code[1]<<8)+pkey->code[0];
					for(unsigned i=0;i<32;i++){
						Disp_WriteBits(LEDList[i].row,LEDList[i].col,led_value & (1<<i));
					}
					Disp_Flush();
					break;
				case FUN_CTRL_LED_F:
				
					Disp_Flashing(1);
				
				  
					break;
				default:
					break;
			}
		}else{
			code  = BC7277_Read(2)<<16;
			code |= BC7277_Read(1);
			code  = ~code;
     
		    unsigned key_count=0;
			for(int i=0;i<KEY_NUM;i++){
				if(code&(1<<i))  key_count++;
			}
			if(key_count>3) code = 0;
//			 printk("Key:%08x\n",code);
			
      for(unsigned i=0;i<KEY_NUM;i++)
				KeyFrame[i]=(i==0||i==(KEY_NUM-1))?KeyFrame[i]:0;
			for(unsigned i=0;i<KEY_NUM;i++){
				if(code & (1<<i)) KeyFrame[KeyList[i].row+1]|=1<<KeyList[i].col;
			}
			Keypad_EnvInit();
			pdat.pStart=&KeyBuf[0];
			pdat.pStop = &KeyBuf[KEY_BUF_SIZE-1];
			OSTaskQPost(&AppTaskCommTCB,&pdat,1,OS_OPT_POST_FIFO,&err);
		}
	}
}
/*
*********************************************************************************************************
*                                          AppTaskDisplay()
*
* Description : Location tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : os
*
* Note(s)     : none.
*********************************************************************************************************
*/
static CPU_INT08U inbuf[50],outbuf[50];
const  CPU_INT08U fillstr[156]="hello fill string";
static void AppTaskComm(void* arg)
{
	OS_ERR err;
	CPU_INT32U *pdat;
	CPU_TS ts;
	OS_MSG_SIZE msg_size;
	CPU_INT32U lost_counter=0;
	CPU_INT32U lost_time = 0;
	unsigned len,i=0;
	tUartInfo *p;
	tKeyFun info;
	Uart_Keypad_Init();
	lost_time = OSTimeGet(&err);
  while(1){
		p = OSTaskQPend(100,OS_OPT_PEND_BLOCKING,&msg_size,&ts,&err);
		if(err == OS_ERR_NONE){
			i=0;
			for(tUartRingBuf *pt = p->pStart->pnext;pt!=p->pStop&&i<50;pt=pt->pnext,i++){
				inbuf[i]=pt->dat;
			}
      	switch(p->pStart->dat){
				case 0xFE:
					lost_counter=0;
					unsigned sz = ConvertBytes7To8(p->pStop->count,inbuf,outbuf);
				  info.fun = FUN_CTRL_LED;
				  info.code[0]=outbuf[0];
					info.code[1]=outbuf[1];
					info.code[2]=outbuf[2];
					info.code[3]=outbuf[3];
					info.code[4]=outbuf[4];
					info.code[5]=outbuf[5];
					info.code[6]=outbuf[6];
					info.code[7]=outbuf[7];
				  OSTaskQPost(&AppTaskDisplayTCB,&info,1,OS_OPT_POST_FIFO,&err);
					break;
				case 0xFD:
				    lost_counter += (OSTimeGet(&err)-lost_time);
					  lost_time = OSTimeGet(&err);
					if((lost_counter > (KEY_CAP_TIMEOUT*100))){
						info.fun = FUN_CTRL_LED_F;
						info.code[0]=fillstr[0];
						OSTaskQPost(&AppTaskDisplayTCB,&info,1,OS_OPT_POST_FIFO,&err);
					}
//					if(lost_counter>(KEY_CAP_TIMEOUT*5)) info.code[3]=fillstr[3];//break;
					int len = ConvertBytes8To7(p->pStop->count-2,inbuf,outbuf);
					CPU_INT08U ch=0xFE;
					Uart_Keypad_Send(&ch,1);
					Uart_Keypad_Send(outbuf,len);
				  	ch=0xFF;
					Uart_Keypad_Send(&ch,1);
				
					break;
				default:
					break;			
			}						
		}else{
			lost_counter++;
			if(lost_counter == (KEY_CAP_TIMEOUT)){
				info.fun = FUN_CTRL_LED_F;
				OSTaskQPost(&AppTaskDisplayTCB,&info,1,OS_OPT_POST_FIFO,&err);
			}
		}
	}
}
