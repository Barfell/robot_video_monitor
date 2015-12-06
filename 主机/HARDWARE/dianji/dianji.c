#include "PWM.h"
#include "dianji.h"
#include "sys.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "delay.h"

//电机初始化

void DC_Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
 /*初始化电机，*/
    INA1 = 1;
    INA2 = 0;
    INB1 = 0;
    INB2 = 1;
    STBY = 0;
    PWMA(TIM2, 0);
    PWMB(TIM2, 0);
 
	
}

/*---------前进-----------*/
void DC_Motor_forward(u16 Pwm_Val)
{
    /*初始化电机，前进,占空比50%*/
    INA1 = 1;
    INA2 = 0;
    INB1 = 0;
    INB2 = 1;
    STBY = 1;
    PWMA(TIM2, Pwm_Val);
    PWMB(TIM2, Pwm_Val);
	  delay_ms(5000);
	  STBY = 0;
}

/*---------后退-----------*/
void DC_Motor_back(u16 Pwm_Val)
{
	 
    INA1 = 0;
    INA2 = 1;
    INB1 = 1;
    INB2 = 0;
    STBY =1;
    PWMA(TIM2, Pwm_Val);
    PWMB(TIM2, Pwm_Val);
		delay_ms(5000);
	  STBY = 0;
}

/*---------左转-----------*/
void DC_Motor_Left(u16 Pwm_Val)
{
  
    INA1 = 1;
    INA2 = 0;
    INB1 = 0;
    INB2 = 1;
    STBY =1;
    PWMA(TIM2, 4000);
    PWMB(TIM2, Speed_10);
	  delay_ms(5000);
	  STBY = 0;
}

/*---------右转-----------*/
void DC_Motor_Right(u16 Pwm_Val)
{
	
    INA1 = 1;
    INA2 = 0;
    INB1 = 0;
    INB2 = 1;
    STBY =1;
    PWMA(TIM2,  Speed_10);
    PWMB(TIM2,  4000);
	  delay_ms(5000);
	  STBY = 0;
}



