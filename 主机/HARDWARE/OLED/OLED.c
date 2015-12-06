#include "OLED.H"
#include "codetab.h"

#define XLevelL  0x01
#define XLevelH  0x10
#define XLevel     ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column 132
#define Max_Row  64
#define Brightness 0xCF 
#define X_WIDTH 132
#define Y_WIDTH 64
/*********************LCD 延时1ms************************************/
void LCD_DLY_ms(unsigned int ms)
{                         
      unsigned int a;
      while(ms)
      {
            a=1800;
            while(a--);
                  ms--;
      }
}
/*********************LCD写数据************************************/ 
void LCD_WrDat(unsigned char dat)  
{
      unsigned char i=8;
      LCD_DC=1;  
      for(i=0;i<8;i++) //发送一个八位数据 
     { 
            LCD_SCL=0; 
            if(dat&0x80) LCD_SDA=1;
            else LCD_SDA=0;
             LCD_SCL=1;             
            dat<<=1;    
     }
}
/*********************LCD写命令************************************/          
void LCD_WrCmd(unsigned char cmd)
{
           unsigned char i=8;
           LCD_DC=0;
           for(i=0;i<8;i++) //发送一个八位数据 
          {  
                 LCD_SCL=0; 
                 if(cmd&0x80)LCD_SDA=1;
                 else LCD_SDA=0;
                 LCD_SCL=1;  
                 cmd<<=1;;   
          } 
          LCD_DC = 1; 
}
/*********************LCD 设置坐标************************************/
void LCD_Set_Pos(unsigned char x, unsigned char y) 
{ 
       LCD_WrCmd(0xb0+y);
       LCD_WrCmd(((x&0xf0)>>4)|0x10);
       LCD_WrCmd((x&0x0f)|0x00); 
} 
/*********************LCD全屏************************************/
void LCD_Fill(unsigned char bmp_dat) 
{
          unsigned char y,x;
          for(y=0;y<8;y++)
         {
                 LCD_WrCmd(0xb0+y);
                 LCD_WrCmd(0x01);
                 LCD_WrCmd(0x10);
                 for(x=0;x<X_WIDTH;x++)
                {
                         LCD_WrDat(bmp_dat);
                }
          }
}
/*********************LCD复位************************************/
void LCD_CLS(void)
{
          unsigned char y,x; 
          for(y=0;y<8;y++)
         {
                LCD_WrCmd(0xb0+y);
                LCD_WrCmd(0x01);
                LCD_WrCmd(0x10); 
                for(x=0;x<X_WIDTH;x++)
                     LCD_WrDat(0);
          }
}
/***************功能描述：显示6*8一组标准ASCII字符串 显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char str[])
{
    unsigned char c=0,i=0,j=0;      
    while (str[j]!='\0')
    {    
        c =str[j]-32;

        if(x>126){x=0;y++;}
            LCD_Set_Pos(x,y);    
        for(i=0;i<6;i++)     
            LCD_WrDat(F6x8[c][i]);  
        x+=6;
        j++;
    }
}
/***************功能描述：显示6*8一个标准ASCII字符 显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6X8Char(unsigned char x, unsigned char y, unsigned char ch)
{
    uint8_t i = 0;
    ch = ch - 32;
    if(x>126){x=0;y++;}
        LCD_Set_Pos(x,y);    
    for(i=0;i<6;i++)     
        LCD_WrDat(F6x8[ch][i]);
}
/***************功能描述：显示6*8字符的整数，显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6X8Num(unsigned char x, unsigned char  y, int num)
{
    uint8_t n = 0;
    if(num < 0)
    {
        LCD_P6X8Char(x,y,'-');
        x+=6;
        num = -num;
    }
    if(num >= 0 && num <= 9)
        n = 1;
    else if(num >= 10 && num <= 99)
        n = 2;
    else if(num >= 10 && num <= 999)
        n = 3;
    else if(num >= 100 && num <= 9999)
        n = 4;
    else if(num >= 1000 && num <= 99999)
        n = 5;
    else if(num >= 10000 && num <= 999999)
        n = 6;
    else if(num >= 100000 && num <= 9999999)
        n = 7;
    else if(num >= 1000000 && num <= 99999999)
        n = 8;
    switch(n)
    {
        case 8: LCD_P6X8Char(x,y,(num%100000000/10000000)+48);x+=6;
        case 7: LCD_P6X8Char(x,y,(num%10000000/1000000)+48);x+=6;
        case 6: LCD_P6X8Char(x,y,(num%1000000/100000)+48);x+=6;
        case 5: LCD_P6X8Char(x,y,(num%100000/10000)+48);x+=6;
        case 4: LCD_P6X8Char(x,y,(num%10000/1000)+48);x+=6;
        case 3: LCD_P6X8Char(x,y,(num%1000/100)+48);x+=6;
        case 2: LCD_P6X8Char(x,y,(num%100/10)+48);x+=6;
        case 1: LCD_P6X8Char(x,y,(num%10/1)+48);x+=6;
                 break;
        default: break;
    }
}
/*******************功能描述：显示8*16一组标准ASCII字符串  显示的坐标（x,y），y为页范围0～7****************/
void LCD_P8x16Str(unsigned char x, unsigned char  y, unsigned char ch[])
{
         unsigned char c=0,i=0,j=0;
         while (ch[j]!='\0')
         {    
                c =ch[j]-32;
                if(x>120){x=0;y++;}
                          LCD_Set_Pos(x,y);    
                for(i=0;i<8;i++)     
                          LCD_WrDat(F8X16[c*16+i]);
                LCD_Set_Pos(x,y+1);    
                for(i=0;i<8;i++)     
                           LCD_WrDat(F8X16[c*16+i+8]);  
                x+=8;
                j++;
           }
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void LCD_P16x16Ch(unsigned char x,unsigned char  y,unsigned char  N)
{
        unsigned char wm=0;
        unsigned int adder=32*N;  //   
        LCD_Set_Pos(x , y);
        for(wm = 0;wm < 16;wm++)  //             
       {
                 LCD_WrDat(F16x16[adder]);
                 adder += 1;
        }      
        LCD_Set_Pos(x,y + 1); 
        for(wm = 0;wm < 16;wm++) //         
       {
                 LCD_WrDat(F16x16[adder]);
                 adder += 1;
        }     
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(unsigned char x0,unsigned char  y0,unsigned char x1,unsigned char  y1,unsigned char BMP[])
{  
         unsigned int j=0;
         unsigned char x,y;
         if(y1%8==0) y=y1/8;      
         else y=y1/8+1;
         for(y=y0;y<y1;y++)
         {
                 LCD_Set_Pos(x0,y);    
                 for(x=x0;x<x1;x++)
                 {      
                            LCD_WrDat(BMP[j++]);      
                 }
           }
} 
    
//初始化SSD1306         
void OLED_Init(void)
{                   
            GPIO_InitTypeDef  GPIO_InitStructure;     
            RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE );
    
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //推挽输出   SCLK - PD14  SDIN - PD0
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //这个频率不能太高，10M我试过，OLED屏显示会有问题
            GPIO_Init(GPIOD, &GPIO_InitStructure);                    
                                                                                                 //               RST - PE7
             GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9;       //       DC - PE9 
             GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //推挽输出
             GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
             GPIO_Init(GPIOE, &GPIO_InitStructure);
             GPIO_SetBits(GPIOE, GPIO_Pin_7);

              LCD_SCL=1;
              LCD_RST=0;
              LCD_DLY_ms(50);
              LCD_RST=1;       //从上电到下面开始初始化要有足够的时间，即等待RC复位完毕   
              LCD_WrCmd(0xae);//--turn off oled panel
              LCD_WrCmd(0x00);//---set low column address
              LCD_WrCmd(0x10);//---set high column address
              LCD_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
              LCD_WrCmd(0x81);//--set contrast control register
              LCD_WrCmd(0xcf); // Set SEG Output Current Brightness
              LCD_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
              LCD_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
              LCD_WrCmd(0xa6);//--set normal display
              LCD_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
              LCD_WrCmd(0x3f);//--1/64 duty
              LCD_WrCmd(0xd3);//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
              LCD_WrCmd(0x00);//-not offset
              LCD_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
              LCD_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
              LCD_WrCmd(0xd9);//--set pre-charge period
              LCD_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
              LCD_WrCmd(0xda);//--set com pins hardware configuration
              LCD_WrCmd(0x12);
              LCD_WrCmd(0xdb);//--set vcomh
              LCD_WrCmd(0x40);//Set VCOM Deselect Level
              LCD_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
              LCD_WrCmd(0x02);//
              LCD_WrCmd(0x8d);//--set Charge Pump enable/disable
              LCD_WrCmd(0x14);//--set(0x10) disable
              LCD_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
              LCD_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
              LCD_WrCmd(0xaf);//--turn on oled panel
              LCD_Fill(0x00);  //初始清屏
              LCD_Set_Pos(0,0); 
}
