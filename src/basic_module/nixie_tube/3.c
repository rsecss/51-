#include <REGX52.H>
#include <intrins.h>


//定时器T0初始化函数
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	
	ET0=1;					//打开中断定时器0的开关	
	EA=1;					//打开中断总开关
	PT0=0;					//低优先级（相对于外部中断，这里可以不写）
}


//控制数码管显示的数值
unsigned char NixieTable[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void NixieTube(unsigned char Location,unsigned char Number)
{
	switch(Location)
	{
		case 1:
			P2_4=1;
		    P2_3=1;
		    P2_2=1;
		    break;
		case 2:
			P2_4=1;
		    P2_3=1;
		    P2_2=0;
		    break;
		case 3:
			P2_4=1;
		    P2_3=0;
		    P2_2=1;
		    break;
		case 4:
			P2_4=1;
		    P2_3=0;
		    P2_2=0;
		    break;
		case 5:
			P2_4=0;
		    P2_3=1;
		    P2_2=1;
		    break;
		case 6:
			P2_4=0;
		    P2_3=1;
		    P2_2=0;
		    break;
		case 7:
			P2_4=0;
		    P2_3=0;
		    P2_2=1;
		    break;
		case 8:
			P2_4=0;
		    P2_3=0;
		    P2_2=0;
		    break;	
	}
		P0=NixieTable[Number];	
} 


void main()
{
	Timer0_Init();//中断初始化
	
	while(1)
	{
		
	}
}

//当前显示的数字
unsigned int count = 0;

//中断定时函数
void Timer0_Routine()	interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;
	TH0 = 0xFC;
	T0Count++;
	if(T0Count>=1000)	//1s
	{
		T0Count = 0;
		
		NixieTube(1, count%10);//显示当前数字
		count++;
	}
}