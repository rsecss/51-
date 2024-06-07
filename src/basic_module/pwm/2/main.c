#include <REGX52.H>
#include "Delayms.h"
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

sbit Motor = P1^0;

unsigned char T0Count = 0;
unsigned char Compare = 0;
unsigned char KeyNum = 0;
unsigned char Speed = 0;

void main()
{
	
	Timer0_Init();
	Compare = 5;
	while(1)
	{
		KeyNum = Key();
		if(KeyNum ==1)
		{
			Speed++;
			Speed%=4;
			switch(Speed)
			{
				case 0:
					Compare = 0;
					break;
				case 1:
					Compare = 50;
					break;
				case 2:
					Compare = 75;
					break;
				case 3:
					Compare = 100;
					break;
				default:
					break;
			}
		}
		NixieTube(1,Speed);
	}
}

void Timer0_Routine()	interrupt 1
{
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	T0Count++;
	T0Count%=100;
	if(T0Count<Compare)
	{
		Motor = 1;
	}
	else
	{
		Motor = 0;
	}
}