#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init();
void LCD_ShowChar(unsigned char row,unsigned char col,unsigned char ch);
void LCD_ShowString(unsigned char row,unsigned char col,unsigned char* str);
void LCD_ShowNum(unsigned char row,unsigned char col,unsigned int num,unsigned char len);
void LCD_ShowSignedNum(unsigned char row,unsigned char col,int num,unsigned char len);
void LCD_ShowHexNum(unsigned char row,unsigned char col,unsigned int num,unsigned char len);
void LCD_ShowBinNum(unsigned char row,unsigned char col,unsigned int num,unsigned char len);
#endif