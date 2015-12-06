#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"



#define PWMA(TIMx, PWM_Val) TIM_SetCompare3(TIMx, PWM_Val)
#define PWMB(TIMx, PWM_Val) TIM_SetCompare4(TIMx, PWM_Val)

void GPIO_TIM2_Config(void);
void TIM2_Mode_Config(uint16_t arr, uint16_t psc);
void PWM_Init(uint16_t arr, uint16_t psc);


#endif
