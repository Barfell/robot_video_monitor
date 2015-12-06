#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "sys.h"



//电机按键控制
#define Dianji_GPIO   GPIOA
#define Dianji_Forward_Back_GPIO_Pin  GPIO_Pin_13  //前后
#define Dianji_Left_Right_GPIO_Pin    GPIO_Pin_14  //左右
#define Dianji_Center_Key             GPIO_Pin_15  //中间按键，缺省，可加功能

#define Dianji_RCC_CLK         RCC_APB2Periph_GPIOA  //时钟
#define Dianji_Forward_Back_Value  GPIO_ReadInputDataBit(Dianji_GPIO, Dianji_Forward_Back_GPIO_Pin)//读取Key值
#define Dianji_Left_Right_Value    GPIO_ReadInputDataBit(Dianji_GPIO, Dianji_Left_Right_GPIO_Pin )  //读取Key值
#define Dianji_Center_Key_Value    GPIO_ReadInputDataBit(Dianji_GPIO, Dianji_Center_Key ) 


//舵机按键控制
#define Duoji_GPIO   GPIOD
#define Motor_Right_Left_GPIO_Pin    GPIO_Pin_3 
#define Motor_Up_Down_GPIO_Pin       GPIO_Pin_4
#define Duoji_Center_Key             GPIO_Pin_5  //中间按键，缺省，可加功能

#define Duoji_RCC_CLK         RCC_APB2Periph_GPIOD  //时钟
#define Motor_Left_Right_Value     GPIO_ReadInputDataBit(Duoji_GPIO,Motor_Right_Left_GPIO_Pin)
#define Motor_Up_Down_Value        GPIO_ReadInputDataBit(Duoji_GPIO,Motor_Up_Down_GPIO_Pin)
#define Motor_Center_Key_Value    GPIO_ReadInputDataBit(Duoji_GPIO,Duoji_Center_Key ) 



void Dianji_Control_Key_Init(void);
void Motor_Contrl_Key_Init(void);

void Dianji_Action(void);
void Duoji_Action(void);
#endif

