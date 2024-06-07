#include <REGX52.H>
#include <intrins.h>

 int count=60;

//延时函数
void Delayms(unsigned int xms)
{
	unsigned char data i,j;
	while(xms--)
	{
		_nop_();
		i=2;
		j=199;
		do
		{
			while(--j);
		}while(--i);
	}
}

//控制数码管显示相应的数值(0~9)
unsigned char code NixieTable[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void NixieTube(unsigned char Position,unsigned char Number)
{
	switch(Position)
	{
		case 1: P2_4=1;P2_3=1;P2_2=1;break;
		case 2: P2_4=1;P2_3=1;P2_2=0;break;
		case 3: P2_4=1;P2_3=0;P2_2=1;break;
		case 4: P2_4=1;P2_3=0;P2_2=0;break;
		case 5: P2_4=0;P2_3=1;P2_2=1;break;
		case 6: P2_4=0;P2_3=1;P2_2=0;break;
		case 7: P2_4=0;P2_3=0;P2_2=1;break;
        case 8: P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];
	Delayms(1);//消隐
	P0=0x00;//清零
}

//定时器0初始化函数
void Timer0_Init()		//50毫秒@11.0592MHz
{
	TMOD = 0x01;		//由于选择的是定时器0，故是控制低四位，GATE位控制开关，C/T位为0选择定时，M1、M0控制工作方式
	TL0=0x00;			//(6500536-500000/(12/11.0592))%256	
	TH0=0x4C;			//(6500536-500000/(12/11.0592))/256	
	TR0=1;				//定时器0开始计时开关
	TF0=0;				//清除TF0标志
	
	EA=1;				//打开中断总开关
	ET0=1;				//打开中断定时器0的开关
}

int main()
{
	Timer0_Init();
	
	while(1)
	{
		NixieTube(1,count/10);
		NixieTube(2,count%10);
	}
}

//中断定时T0函数
void Timer0_Routine()	interrupt 1
{
	static unsigned int T0Count=0;
	TL0=0x00;
	TH0=0x4C;
	
	T0Count++;
	if(T0Count >= 20)
	{
		T0Count=0;
		count--;
		if(count<0)
		{
			count=0;
		}
	}
}
		

	