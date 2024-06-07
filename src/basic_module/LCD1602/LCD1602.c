#include <REGX52.H>
#include <INTRINS.H>

#define uint unsigned int
#define uchar unsigned char

//引脚定义
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;
sbit LCD_EN = P2^7;

#define LCD_DataPort P0

/**
  * @brief  LCD1602延时函数，11.0592MHz调用可延时1ms
  * @param  无
  * @retval 无
  */
void LCD_Delay()	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void LCD_WriteCommand(uchar command)
{
	LCD_RS = 0;
	LCD_WR = 0;
	LCD_DataPort = command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
  * @brief  LCD1602写数据
  * @param  datas 要写入的数据
  * @retval 无
  */

void LCD_WriteData(uchar datas)
{
	LCD_RS = 1;
	LCD_WR = 0;
	LCD_DataPort = datas;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
  * @brief  LCD1602初始化函数
  * @param  无
  * @retval 无
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}

/**
  * @brief  LCD1602设置光标位置
  * @param  row 行位置，范围：1~2
  * @param  col 列位置，范围：1~16
  * @retval 无
  */
void LCD_SetCursor(uchar row,uchar col)
{
	if(row == 1)
	{
		LCD_WriteCommand(0x80|(col-1));
	}
	else if(row == 2)
	{
		LCD_WriteCommand(0x80|(col-1)+0x40);
	}
}
	
/**
  * @brief  在LCD1602指定位置上显示一个字符
  * @param  row 行位置，范围：1~2
  * @param  col 列位置，范围：1~16
  * @param  ch 要显示的字符
  * @retval 无
  */
void LCD_ShowChar(uchar row,uchar col,uchar ch)
{
	LCD_SetCursor(row,col);
	LCD_WriteData(ch);
}

/**
  * @brief  在LCD1602指定位置开始显示所给字符串
  * @param  row 起始行位置，范围：1~2
  * @param  col 起始列位置，范围：1~16
  * @param  str 要显示的字符串
  * @retval 无
  */
void LCD_ShowString(uchar row,uchar col,uchar* str)
{
	uchar i = 0;
	
	LCD_SetCursor(row,col);
	
	for(i=0; str[i] != '\0'; i++)
	{
		LCD_WriteData(str[i]);
	}
}

/**
  * @brief  返回值等于x的y次方
  */
int LCD_Pow(int x,int y)
{
	uchar i =0;
	int result=1;
	for(i=0; i<y; i++)
	{
		result*=x;
	}
	
	return result;
}


/**
  * @brief  在LCD1602指定位置开始显示所给数字
  * @param  row 起始行位置，范围：1~2
  * @param  col 起始列位置，范围：1~16
  * @param  num 要显示的数字，范围：0~65535
  * @param  len 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowNum(uchar row,uchar col,uint num,uchar len)
{
	uchar i = 0;
	LCD_SetCursor(row,col);
	for(i=len; i>0; i--)
	{
		LCD_WriteData(num/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
  * @param  row 起始行位置，范围：1~2
  * @param  col 起始列位置，范围：1~16
  * @param  num 要显示的数字，范围：-32768~32767
  * @param  len 要显示数字的长度，范围：1~5
  * @retval 无
  */
void LCD_ShowSignedNum(uchar row,uchar col,int num,uchar len)
{
	uchar i = 0;
	int num1 = 0;
	
	LCD_SetCursor(row,col);
	if(num >= 0)
	{
		LCD_WriteData('+');
		num1=num;
	}
	else
	{
		LCD_WriteData('-');
		num1=-num;
	}
	for(i=len; i>0; i--)
	{
		LCD_WriteData(num1/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  在LCD1602指定位置开始以十六进制显示所给数字
  * @param  row 起始行位置，范围：1~2
  * @param  col 起始列位置，范围：1~16
  * @param  num 要显示的数字，范围：0~0xFFFF
  * @param  len 要显示数字的长度，范围：1~4
  * @retval 无
  */
void LCD_ShowHexNum(uchar row,uchar col,uint num,uchar len)
{
	uchar i=0;
	uchar SingleNumber=0;
	LCD_SetCursor(row,col);
	for(i=len;i>0;i--)
	{
		SingleNumber=num/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

/**
  * @brief  在LCD1602指定位置开始以二进制显示所给数字
  * @param  row 起始行位置，范围：1~2
  * @param  col 起始列位置，范围：1~16
  * @param  num 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  len 要显示数字的长度，范围：1~16
  * @retval 无
  */
void LCD_ShowBinNum(uchar row,uchar col,uint num,uchar len)
{
	uchar i=0;
	LCD_SetCursor(row,col);
	for(i=len;i>0;i--)
	{
		LCD_WriteData(num/LCD_Pow(2,i-1)%2+'0');
	}
}

