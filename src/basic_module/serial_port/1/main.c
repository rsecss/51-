#include "UART.h"
#include "Delayms.h"

unsigned char sec = 0;

int main()
{
	Uart1_Init();
	
	while(1)
	{
		Uart1_SendByte(sec);
		sec++;
		Delayms(1000);
	}
}

