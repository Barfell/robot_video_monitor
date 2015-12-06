#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include  "PWM.h"

void GPIO_TIM2_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructuer;
    
    //设置TIM2时钟为72MHZ
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    //设置GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructuer.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructuer.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_InitStructuer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructuer);
    
}

void TIM2_Mode_Config(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    TIM_TimeBaseStructure.TIM_Period = arr;//自动重装载周期值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;//不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置分频系数：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    /***********************************************************************************
     *PWM模式1和模式2的区别为：在向上计数时，当 TIMx_CNT<TIMx_CCRn （比较寄存器，其数值等 *
     *于TIM_Pulse 成员的内容）时，通道n输出为有效电平，否则为无效电平 ；在向下计数时,当    *  
     *TIMx_CNT>TIMx_CCRn 时通道 n 为无效电平，否则为有效电平。PWM2 模式与 PWM1模式相反。  *
     ************************************************************************************/
    
    /*PWM设置*/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置为模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//计数值小于CRR_Val时，跳变为高电平
    
//    /*PWM1-CH1*/
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//配置输出模式状态
////    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//设置占空比
//    TIM_OC1Init(TIM2, &TIM_OCInitStructure);//使能通道1
//    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//比较寄存器TIM_CCR预装载使能

//    /*PWM设置*/
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置为模式1
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//计数值小于CRR_Val时，跳变为高电平    
//    /*PWM1-CH2*/
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
//    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
//    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
    /*PWM1-CH3*/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
    /*PWM1-CH4*/
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
    /*使能TIM2的重载寄存器ARR*/
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    
    /*使能TIM3*/
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_Init(uint16_t arr, uint16_t psc)
{
    GPIO_TIM2_Config();
    TIM2_Mode_Config(arr, psc);
}


