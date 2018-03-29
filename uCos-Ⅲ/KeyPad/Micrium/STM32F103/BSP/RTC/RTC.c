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
* Filename      : RTC.c
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
#include "includes.h"


 #define SecsPerComYear  3153600 //(365*3600*24)
 #define SecsPerLeapYear 31622400//(366*3600*24)
 #define SecsPerFourYear 126230400//((365*3600*24)*3+(366*3600*24))
 #define SecsPerDay      (3600*24)
 
const unsigned  Year_Secs_Accu[5]={0,31622400,63158400,94694400,126230400};
const unsigned  Month_Secs_Accu_C[13] = { 0,2678400,5097600,7776000,10368000,13046400,15638400,18316800,20995200,23587200,26265600,28857600,31536000};
const unsigned  Month_Secs_Accu_L[13] = {0, 2678400,5184000,7862400,10454400,13132800,15724800,18403200,21081600,23673600,26352000,28944000,31622400};

static tDate CurrentTime; 

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
void RTC_Init(void){
	
   if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
   {
				/* Backup data register value is not correct or not yet programmed (when
						the first time the program is executed) */
				/* Enable PWR and BKP clocks */
			 RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
				/* Allow access to BKP Domain */
			 PWR_BackupAccessCmd(ENABLE);
			/* Reset Backup Domain */
			//BKP_DeInit(); //??0XA5A5 ?????????
			/* Enable LSE */
			 RCC_LSEConfig(RCC_LSE_ON);
			 /* Wait till LSE is ready */
			 while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
			 {}
			/* Select LSE as RTC Clock Source */
			 RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
			/* Enable RTC Clock */
			 RCC_RTCCLKCmd(ENABLE);
			/* Wait for RTC registers synchronization */
			 RTC_WaitForSynchro();
			/* Wait until last write operation on RTC registers has finished */
			 RTC_WaitForLastTask();
			/* Enable the RTC Second */
		//   RTC_ITConfig(RTC_IT_SEC, ENABLE);
			/* Wait until last write operation on RTC registers has finished */
			 RTC_WaitForLastTask();
			/* Set RTC prescaler: set RTC period to 1sec */
			 RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
			/* Wait until last write operation on RTC registers has finished */
			 RTC_WaitForLastTask();
       RTC_SetTime(0);				 
			 BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
   }
   else
   {
     /* Check if the Power On Reset flag is set */
     if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
     {
			 BKP_WriteBackupRegister(BKP_DR2, BKP_ReadBackupRegister(BKP_DR2)|0x0001);
			 BKP_WriteBackupRegister(BKP_DR3, RTC_GetCounter());
     }
     /* Check if the Pin Reset flag is set */
     else if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
     {
			 BKP_WriteBackupRegister(BKP_DR2, BKP_ReadBackupRegister(BKP_DR2)|0x0002);
			 BKP_WriteBackupRegister(BKP_DR4, RTC_GetCounter());
     }
		 else
		 {
			 BKP_WriteBackupRegister(BKP_DR2, BKP_ReadBackupRegister(BKP_DR2)|0x0004);
			 BKP_WriteBackupRegister(BKP_DR5, RTC_GetCounter());
		 }	
     /* Wait for RTC registers synchronization */
     RTC_WaitForSynchro();
    /* Enable the RTC Second */
//     RTC_ITConfig(RTC_IT_SEC, ENABLE);
     /* Wait until last write operation on RTC registers has finished */
     RTC_WaitForLastTask(); 
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
void RTC_SetTime(unsigned TimeVar){
	
   unsigned Num4Y,NumY, OffSec, Off4Y = 0;
   unsigned i;
   unsigned NumDay;  //OffDay;
	
	 Num4Y = TimeVar/SecsPerFourYear;
	 OffSec = TimeVar%SecsPerFourYear;

	 i=1;
	 while(OffSec > Year_Secs_Accu[i++])
		 Off4Y++;
 
		/* Numer of Complete Year */
	 NumY = Num4Y*4 + Off4Y;
		/* 2000,2001,...~2000+NumY-1 complete year before, so this year is 2000+NumY*/
	 CurrentTime.Year = 2000+NumY;
	 
	 OffSec = OffSec - Year_Secs_Accu[i-2];
	 
		/* Month (TBD with OffSec)*/
	 i=0;
	 if(CurrentTime.Year%4)
	 {// common year
		 while(OffSec > Month_Secs_Accu_C[i++]);
		 CurrentTime.Month = i-1;
		 OffSec = OffSec - Month_Secs_Accu_C[i-2];
	 }
	 else
	 {
		 // leap year
		 while(OffSec > Month_Secs_Accu_L[i++]);
		 CurrentTime.Month = i-1;
		 OffSec = OffSec - Month_Secs_Accu_L[i-2];
	 }
	 
		/* Date (TBD with OffSec) */
	 NumDay = OffSec/SecsPerDay;
	 OffSec = OffSec%SecsPerDay;
	 CurrentTime.Day = NumDay+1;
 
    /* Compute  hours */
   CurrentTime.Hour = OffSec/3600;
   /* Compute minutes */
   CurrentTime.Minute = (OffSec % 3600)/60;
   /* Compute seconds */
   CurrentTime.Second = (OffSec % 3600)% 60;
	 /* Wait until last write operation on RTC registers has finished */
   RTC_WaitForLastTask();
   /* Change the current time */
   RTC_SetCounter(TimeVar);
   /* Wait until last write operation on RTC registers has finished */
   RTC_WaitForLastTask();
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
void RTC_GetTime(tDate *pDate){
   pDate = &CurrentTime;
}




