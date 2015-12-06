#include "key.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x.h"
#include "led.h"
void Key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOC的外设时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | 
                                     GPIO_Pin_6 |GPIO_Pin_7;//GPIOC4,5,6,7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置为PC4，5，6，7为上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC4，5，6，7
	
}

/***********按键扫描函数************************************************
 *参数：   mode，设置扫描方式
 *         mode = 0 不支持连续按，
 *         mode = 1 支持连续按
 *功能：   按键扫描
************************************************************************/
uint8_t Key_Scan(uint8_t mode)//参数mode设置按键扫描方式
{
    static uint8_t key_up = 1;//按键松开标志
    if(mode) key_up = 1;
    if(key_up && (Key1 == 0 || Key2 == 0 || Key3 == 0 || Key4 == 0))
    {
        delay_ms(10);//延时消抖
        key_up = 0;
        if(Key1 == 0)
            return Key1_Press;
        else if(Key2 == 0)
            return Key2_Press;
        else if(Key3 == 0)
           return Key3_Press;
        else if(Key4 == 0)
            return Key4_Press;
        else
            return 0;
    }
    else if(Key1 == 1 && Key2 == 1 && Key3 == 1 && Key4 == 1)//没有按键按下
        key_up = 1;
    return 0;
}
/******************************************************END OF FILE*********/
