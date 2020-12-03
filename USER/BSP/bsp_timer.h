#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_it.h"
#include "misc.h"

extern __IO uint32_t TimingDelay;
void Init_NVIC(void);
void Systick_Init(void);
void TimingDelay_Decrement(void);
void delay_ms(__IO uint32_t nTime);//ÑÓ³Ùº¯Êý£¬ÉèÖÃÎª US
void Init_Timer(u8 num, FunctionalState IsEnable);
void Enc_Init(u16 zEncLine, u16 yEncLine);
void Timer3_Init(void);

#endif