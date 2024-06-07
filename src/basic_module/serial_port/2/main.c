 #include <REGX52.H>

#include "UART.h"
#include "Delayms.h"

unsigned char sec = 0;

void main()
{
	Uart1_Init();
	while(1)
	{
		
	}
}

void UART_Routine() interrupt 4
{
	if(RI == 1)
	{
		P2 = SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}
