#ifndef __WDG_H
#define __WDG_H
//#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//
//////////////////////////////////////////////////////////////////////////////////


void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);

#define WdogFeed() IWDG_Feed();
#endif