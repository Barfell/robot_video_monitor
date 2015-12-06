#ifndef __DUOJI_H
#define __DUOJI_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "timer.h"

#define   Motor_Pulse1    TIM4->CCR3 
#define   Motor_Pulse2    TIM4->CCR4

void Motor_Left(void);
void Motor_Right(void);
void Motor_Up(void);
void Motor_Down(void);
#endif
/********************************************************END OF FILE************/


