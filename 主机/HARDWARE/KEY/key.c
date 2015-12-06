#include "key.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x.h"
#include "led.h"
void Key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ��GPIOC������ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | 
                                     GPIO_Pin_6 |GPIO_Pin_7;//GPIOC4,5,6,7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//����ΪPC4��5��6��7Ϊ��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC4��5��6��7
	
}

/***********����ɨ�躯��************************************************
 *������   mode������ɨ�跽ʽ
 *         mode = 0 ��֧����������
 *         mode = 1 ֧��������
 *���ܣ�   ����ɨ��
************************************************************************/
uint8_t Key_Scan(uint8_t mode)//����mode���ð���ɨ�跽ʽ
{
    static uint8_t key_up = 1;//�����ɿ���־
    if(mode) key_up = 1;
    if(key_up && (Key1 == 0 || Key2 == 0 || Key3 == 0 || Key4 == 0))
    {
        delay_ms(10);//��ʱ����
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
    else if(Key1 == 1 && Key2 == 1 && Key3 == 1 && Key4 == 1)//û�а�������
        key_up = 1;
    return 0;
}
/******************************************************END OF FILE*********/
