#include <REGX52.H>

sbit Key=P3^1;
unsigned char NixieTube[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x6f};

//延时函数
void Delayms(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

unsigned char Number=0;
//数码管显示
void Display()
{
	//位选第一个数码管
	P2_4=1;
	P2_3=1;
	P2_2=1;
	P0=NixieTube[Number];
	Delayms(1);
	P0=0x00;
}

void main()
{
	
	while(1)
	{
		Display();
		if(Key == 0)
		{
			//消抖
			Delayms(20);
			while(Key == 0);
			Delayms(20);
			
			Number++;
			if(Number == 9)
			{
				Number =0;
			}
		}
	}
}
