#ifndef __OLED_H
#define __OLED_H
//#include "include.h"
#include "stdlib.h"
#include "sys.h"    
#include "delay.h"

#define LCD_SCL PDout(14)    //时钟 D0（SCLK）  
#define LCD_SDA PDout(0)    //D1（SDA） 数据
#define LCD_RST PEout(7)    //复位RST 
#define LCD_DC  PEout(9)    //DC数据/命令控制

extern void LCD_Fill(unsigned char bmp_dat);
extern void LCD_DLY_ms(unsigned int ms);
extern void LCD_WrDat(unsigned char dat);
extern void LCD_Set_Pos(unsigned char x, unsigned char y);
extern void LCD_CLS(void);
extern void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char str[]);
extern void LCD_P6X8Char(unsigned char x,unsigned char  y,unsigned char ch);
extern void LCD_P6X8Num(unsigned char x, unsigned char  y, int num);
extern void LCD_P8x16Str(unsigned char x,unsigned char  y,unsigned char ch[]);
extern void LCD_P16x16Ch(unsigned char x,unsigned char  y,unsigned char  N);
extern void Draw_BMP(unsigned char x0,unsigned char  y0,unsigned char x1,unsigned char  y1,unsigned char BMP[]);
extern void OLED_Init(void);

#endif
