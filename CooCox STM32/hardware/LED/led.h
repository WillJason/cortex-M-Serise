#ifndef __LED_H
#define __LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//////////////////////////////////////////////////////////////////////////////////
#define LED0 PBout(3)// PE3
#define LED1 PBout(4)// PE4
#define LED2 PBout(5)// PE5
#define LED3 PEout(6)// PE6

#define LED_On(x) x=0
#define LED_Off(x) x=1

void LED_Init(void);//��ʼ��


#endif

