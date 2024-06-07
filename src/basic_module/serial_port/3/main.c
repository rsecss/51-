#include <REGX52.H>
unsigned char x=0;

unsigned char code NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
0x77,0x7F,0x39,0x3F,0x79,0x71};//0~F


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


//数码管显示
void Display()
{
	//位选第一个数码管
	P2_4=1;
	P2_3=1;
	P2_2=1;
	P0=NixieTable[x];
	Delayms(1000);
	P0=0x00;
}
	
//初始化，串口选择方式1（8位异步收发）
void Uart1_Init()	//9600bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD=1，其余为0
	SCON = 0x50;		//8位数据,可变波特率,高四位SM0=0,SM1=1,SM2=0,REN=1
	TMOD &= 0x0F;		//把TMOD的高四位清零，低四位保持不变
	TMOD |= 0x20;		//把TMOD的高四位置0010，低四位保持不变
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	
	EA = 1;				//总中断开关
	ES = 1;				//控制串口中断打开
}

//串口发送一个字节数据
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;			//SBUF串口数据缓存寄存器，写入操作
	while(TI == 0);		//TI发送中断请求标志位
	TI  = 0;					//复位
	
}

void main()
{
	Uart1_Init();
	
	while(1)
	{
		
	}
}

//串口中断函数
void UART_Routine()		interrupt 4		//串口中断号为4
{
	if(RI == 1)
	{
		x=SBUF;							//接受
		Display();					//显示
		UART_SendByte(x);		//发送
		RI=0;								//复位
	}
}
