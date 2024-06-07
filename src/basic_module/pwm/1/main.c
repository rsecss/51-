#include <REGX52.H>

sbit LED=P2^0;

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time=0;
	unsigned char i=0;
	
	while(1)
	{
		//亮度由低到高
		for(Time=0; Time<100; Time++)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				Delay(Time);
				LED=1;
				Delay(100-Time);
			}
		}
		
		//亮度由高到低
		for(Time=100; Time>0; Time--)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				Delay(Time);
				LED=1;
				Delay(100-Time);
			}
		}
	}
}
