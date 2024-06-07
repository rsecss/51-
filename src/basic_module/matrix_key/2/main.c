#include <REGX52.H>
#include "Matrix.h"
#include "Delayms.h"
#include "LCD1602.h"

unsigned char KeyNum;
unsigned int Password;
unsigned int count;

int main()
{
	LCD_Init();
	LCD_ShowString(1,1,"PassWord:");
	
	while(1)
	{
		KeyNum = MatrixKey();
		if(KeyNum)
		{
			if(KeyNum<=10)//如果s1~s10按键按下，输入密码
			{
				if(count<4)//输入次数小于4
				{
					Password *= 10;//密码左移一位
					Password += KeyNum%10;//获取一位密码
					count++;//计次加1	
				}	
				
				LCD_ShowNum(1,10,Password,4);//更新显示
			}
			if(KeyNum==11)	//如果s11按下，确认键
			{
				switch (Password) 
				{
				case 2345:
					LCD_ShowString(2, 1, "OK"); // 显示OK
					break;
				default:
					LCD_ShowString(2, 1, "ERR"); // 显示ERR
					break;
                }
			}
			if(KeyNum==12)
			{
				Password=0;	//密码清零
				count=0;	//计次清零
				LCD_ShowNum(1,10,Password,4);//更新显示
			}
		}
			
	}
}