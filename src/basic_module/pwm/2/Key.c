#include <REGX52.H>
#include "Delayms.h"


/**
  *@brief 独立按键
  *@param 无	
  *@retval 按下按键的键码，范围：0~4，无按键按下时返回0
  */


unsigned char Key()
{
	unsigned char KeyNumber=0;
	
	//第一个独立按键
	if(P3_1==0){Delayms(20);while(P3_1==0);Delayms(20);KeyNumber=1;}
	
	//第二个独立按键
	if(P3_0==0){Delayms(20);while(P3_0==0);Delayms(20);KeyNumber=2;}
	
	//第三个独立按键
	if(P3_2==0){Delayms(20);while(P3_2==0);Delayms(20);KeyNumber=3;}
	
	//第四个独立按键
	if(P3_3==0){Delayms(20);while(P3_3==0);Delayms(20);KeyNumber=4;}
	
	return KeyNumber;
}