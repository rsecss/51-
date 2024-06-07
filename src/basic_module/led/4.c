#include <REGX52.H>


void Delay1ms(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;
while(xms)
{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
  xms--;
}
}

void main()
{
	while(1)
	{
		P2=0xFE;//1111 1110
		Delay1ms(1000);
		P2=0xFD;//1111 1101
		Delay1ms(900);
		P2=0xFB;//1111 1011
		Delay1ms(800);
		P2=0xF7;//1111 0111
		Delay1ms(700);
		P2=0xEF;//1110 1111
		Delay1ms(600);
		P2=0xDF;//1101 1111
		Delay1ms(500);
	    P2=0xBF;//1011 1111
		Delay1ms(400);
		P2=0x7F;//0111 1111
		Delay1ms(300);
	}
}