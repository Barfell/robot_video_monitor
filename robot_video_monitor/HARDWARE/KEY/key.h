#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "stm32f10x.h"


#define Key1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)//��ȡKey1ֵ
#define Key2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)//��ȡKey2ֵ
#define Key3 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)//��ȡKey3ֵ
#define Key4 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7)//��ȡKey4ֵ

#define Key1_Press 1
#define Key2_Press 2
#define Key3_Press 3
#define Key4_Press 4

void Key_init(void);
uint8_t Key_Scan(uint8_t mode);



#endif
/********************************************************END OF FILE************/
