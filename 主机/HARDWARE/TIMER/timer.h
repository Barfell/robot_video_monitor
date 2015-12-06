#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"


void TIM4_Mode_Config(void );

void TIM4_PWM_Init(void);

void TIM3_Int_Init(u16 arr,u16 psc);
#endif
