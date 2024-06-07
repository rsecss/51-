#include <REGX52.H>

//延时函数
void Delayms(unsigned int xms)
{
	unsigned char data i,j;
	while(xms--)
	{
		i=2;
		j=199;
		do
		{
			while(j--);
		}while(i--);
	}
}

unsigned int MatrixKey()
{
	//KeyValue 按下按键的键码值
	//如果按键按下不放，程序会停留在此函数，
	//松手的一瞬间，返回按键键码，没有按键按下时，返回0
	unsigned char KeyValue=0;
	
	P1=0xff;
	P1_3=0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyValue = 1;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyValue =5;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyValue =9;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyValue =13;}

	P1=0xff;
	P1_2=0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyValue =2;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyValue =6;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyValue =10;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyValue =14;}

	P1=0xff;
	P1_1=0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyValue =3;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyValue =7;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyValue =11;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyValue =15;}

	P1=0xff;
	P1_0=0;
	if(P1_7==0){Delayms(20);while(P1_7==0);Delayms(20);KeyValue =4;}
	if(P1_6==0){Delayms(20);while(P1_6==0);Delayms(20);KeyValue =8;}
	if(P1_5==0){Delayms(20);while(P1_5==0);Delayms(20);KeyValue =12;}
	if(P1_4==0){Delayms(20);while(P1_4==0);Delayms(20);KeyValue =16;}
	
	return KeyValue*KeyValue;
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

void main()
{	
	unsigned int KeyNum=0;    //按键的键码值
	unsigned int x=0;					//定义一个变量x接收按键扫描
	
	while(1)
	{
		KeyNum = MatrixKey();
		
		if(KeyNum)
		{
			x=KeyNum;
		}
		NixieTube(1,x/100);
		NixieTube(2,x/10%10);
		NixieTube(3,x%10);
		
	}
}
