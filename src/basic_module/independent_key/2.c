#include <REGX52.H>

void Delay(unsigned int xms)	//@12.000MHz
{
	unsigned char data i, j;
	while (xms--)
	{
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	}
}


void main()
{
	unsigned char LEDNum=0;
	while(1)
	{
	if(P3_1==0)
	 {
        Delay(20);
        while(P3_1==0);
	    Delay(20);
		 
		 LEDNum++;
		 P2=~LEDNum;
	 /* //1111 1111
		 P2++;//0000 0000
		 P2=~P2;//1111 1111
		 */
	 }	
	}
}