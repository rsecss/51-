#include <REGX52.H>
#include <INTRINS.H>
#define unint unsigned int
#define unchar unsigned char

void Delay(unint xms)	//@11.0592MHz
{
	unchar data i, j;
	while(xms--)
	{
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	}
}

void main()
{
	
		unchar i = 0,j=0;
	while(1)
	{
		//间隔300ms先奇数亮后偶数亮
		for(i=0;i<3;i++)
		{
			P2=0XAA;//1010 1010
			Delay(300);
			P2=0X55;//0101 0101
			Delay(300);
		}
		
		//一个灯左右循环三次
		for(i=0;i<3;i++)
		{
			P2=0XFE;
			Delay(200);
			for(j=0;j<7;j++)
			{
				//从左往右移动
				P2=_crol_(P2,1);//1111 1110	
				Delay(200);
			}
			
			for(j=0;j<7;j++)
			{
				//从右往左移动
				P2=_cror_(P2,1);
				Delay(200);
			}
		}
		
		//两个灯从两边往中间移动,后从中间往两边移动
		for(i=0;i<3;i++)
			{
				P2=0X7E;//0111 1110
				Delay(200);
				P2=0XBD;//1011 1101
				Delay(200);
				P2=0XDB;//1101 1011
				Delay(200);
				P2=0XE7;//1110 0111
				Delay(500);
				P2=0XE7;//1110 0111
				Delay(200);
				P2=0XDB;//1101 1011
				Delay(200);
				P2=0XBD;//1011 1101
				Delay(200);
				P2=0X7E;//0111 1110
				Delay(200);
			}
		
		//8个灯闪烁3次
		P2=0x00;
		for(i=0;i<3;i++)
			{
				P2=0xff;
				Delay(500);
				P2=0x00;
				Delay(500);
			}
	
	//关闭发光管
	P2=0XFF;
	while(1){}	
	}		
}