#include <REGX52.H>
#include "LCD1602.h"

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Bingo!");
	LCD_ShowNum(1,11,88,2);
	LCD_ShowSignedNum(2,1,-22,2);
	LCD_ShowHexNum(2,5,0xA5,2);
	LCD_ShowBinNum(2,8,0xA5,8);
	
	while(1)
	{
		
	}
}
