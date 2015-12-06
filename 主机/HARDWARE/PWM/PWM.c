#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include  "PWM.h"

void GPIO_TIM2_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructuer;
    
    //����TIM2ʱ��Ϊ72MHZ
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    //����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructuer.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructuer.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
    GPIO_InitStructuer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructuer);
    
}

void TIM2_Mode_Config(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    TIM_TimeBaseStructure.TIM_Period = arr;//�Զ���װ������ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc;//����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//���÷�Ƶϵ��������Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    /***********************************************************************************
     *PWMģʽ1��ģʽ2������Ϊ�������ϼ���ʱ���� TIMx_CNT<TIMx_CCRn ���ȽϼĴ���������ֵ�� *
     *��TIM_Pulse ��Ա�����ݣ�ʱ��ͨ��n���Ϊ��Ч��ƽ������Ϊ��Ч��ƽ �������¼���ʱ,��    *  
     *TIMx_CNT>TIMx_CCRn ʱͨ�� n Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��PWM2 ģʽ�� PWM1ģʽ�෴��  *
     ************************************************************************************/
    
    /*PWM����*/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����Ϊģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ֵС��CRR_Valʱ������Ϊ�ߵ�ƽ
    
//    /*PWM1-CH1*/
//    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�������ģʽ״̬
////    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//����ռ�ձ�
//    TIM_OC1Init(TIM2, &TIM_OCInitStructure);//ʹ��ͨ��1
//    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//�ȽϼĴ���TIM_CCRԤװ��ʹ��

//    /*PWM����*/
//    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����Ϊģʽ1
//    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//����ֵС��CRR_Valʱ������Ϊ�ߵ�ƽ    
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
    
    /*ʹ��TIM2�����ؼĴ���ARR*/
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    
    /*ʹ��TIM3*/
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_Init(uint16_t arr, uint16_t psc)
{
    GPIO_TIM2_Config();
    TIM2_Mode_Config(arr, psc);
}


