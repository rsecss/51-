#include <REGX52.H>

/**
  *@brief  串口初始化，9600bps@11.0592MHz
  *@param  无
  *@retval 无
  */


void Uart1_Init(void)	//9600bps@11.0592MHz
{
	PCON |= 0x80;		//电源控制寄存器，使能波特率倍速位SMOD
	SCON = 0x50;		//串行口控制寄存器，8位数据,可变波特率
	TMOD &= 0x0F;		//把TMOD的高四位清零，低四位保持不变
	TMOD |= 0x20;		//把TMOD的高四位置0010，低四位保持不变
	TL1 = 0xFA;			//设置定时初始值
	TH1 = 0xFA;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
}


/**
  *@brief 	串口发送一个字节数据
  *@param   Byte要发送一个字节数据
  *@retval  无
  */

void Uart1_SendByte(unsigned char Byte)
{
	SBUF = Byte;		//SBUF串口数据缓存寄存器，写入操作
	while(TI == 0);		//TI标志位
	TI  = 0;			//复位
	
}