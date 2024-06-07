#include <REGX52.H>

//《起风了》以十六分音符为标准

//蜂鸣器端口定义
sbit Buzzer =P2^5;

//(60min/77)=780微秒,播放速度，值为四分音符的时长(ms)
#define SPEED  780		

//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线：升半音符号#
#define P	  0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

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

//定时器0初始化函数
void Timer0_Init()
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;	//由于选择的是定时器0，故是控制低四位，GATE位控制开关，C/T位为0选择定时，M1、M0控制工作方式
	TL0=0x00;			//(6500536-500000/(12/11.0592))%256	
	TH0=0x4C;			//(6500536-500000/(12/11.0592))/256
	TR0=1;				//定时器0开始计时开关
	TF0=0;				//清除TF0标志
	
	EA=1;					//打开中断总开关
	ET0=1;				//打开中断定时器0的开关	
}

//索引与频率对照表
unsigned int  PaceTable[]={
	0,
	63777,63872,63969,64054,64140,64216,
	64291,64360,64426,64489,64547,64607,
	64655,64704,64751,64795,64837,64876,
	64913,64948,64981,65012,65042,65070,
	65095,65120,65144,65166,65186,65206,
	65225,65242,65259,65274,65289,65303
	};

//乐谱
unsigned char code Music[]={
	//音符，时值
	
	//前奏
		L7,1,	M1,1,	M2,1,	M3,1,
		L3,2,	M5,1,	M3,1,
		L2,2,	L5,2,	M2,4,
	
		L7,1,	M1,1,	M2,1,	M3,1,
		L2,2,	M5,1,	M3,1,	
		M2,1,	M3,1,	M1,1,	M2,1,
		L7,1,	M1,1,	L5,2,
		
		L7,1,	M1,1,	M2,1,	M3,1,
		L3,2,	M5,1,	M3,1,
		L2,2,	L5,2,	M2,4,
		
		L7,1,	M1,1,	M2,1,	M3,1,	
		L2,2,	M5,1,	M3,1,
		M2,1,	M3,1,	M1,1,	M2,1,
		L7,1,	M1,1,	L5,2,
		
		L7,1,	M1,1,	M2,1,	M3,1,	
		L3,2,	M5,1,	M3,1,
		L2,2,	L5,2,	M2,4,
		
		L7,1,	M1,1,	M2,1,	M3,1,
		L2,2,	M5,1,	M3,1,	
		M2,1,	M3,1,	M1,1,	M2,1,
		L7,1,	M1,1,	L5,2,
		
		L7,1,	M1,1,	M2,1,	M3,1,
		L3,2,	M5,1,	M3,1,
		L2,2,	L5,2,	M2,4,
		
		M2,4+2,	M1_,4+2,
	
	//正曲
	M2,2+1,	M1,1,	M2,2+1,		M1,1,	M2,2,	M3,2,	M5,2,	M3,1+1,	M2,1+1,
	M2,2+1,	M1,1,	M2,2+1,		M1,1,	M2,1,	M3,1,	M2,1,	M1,1,	L5,4,
	M2,2+1,	M1,1,	M2,2+1,		M1,1,	M2,2,	M3,2,	M5,2,	M3,1,	M2,1,
	M2,2+1,	M3,1,	M2,2,		M1,1+1,	M2,1+1,	M2,4+2,
	M2,2+1,	M1,1,	M2,2+1,		M1,1,	M2,2,	M3,2,	M5,2,	M3,1+1,	M2,1+1,
	M2,2+1,	M3,1, 	M2,2,		M1,1+1,	L6,1+1, L6,4,	M3,1,	M2,1,	M1,1,	M2,1,
	M1,4,	M3,1,	M2,1,		M1,1,	M2,1,	M1,2+1,	M3,1,	M2,1,	M1,1,	M2,1,
	M1,4+2,	M1,2,	M2,2,		M3,2,	M1,2,
	M6,2,	M5,1,	M6,1+2+1, 	M1,1,	M7,2,	M6,1,	M7,1+4,	
	M7,2,	M6,1,	M7,1+2+1, 	M3,1,	H1,1,	H2,1,	H1,1,	M7,1,	M6,2,	M5,2,
	M6,2,	M5,1,	M6,1+1,		M5,1,	M6,1,	M5,1,	M6,2,	M5,2,	M2,1+2,	M5,1,	M3,1,
	M3,4+2,	M1,2,	M2,2,		M3,2,	M1,2,	
	M6,2,	M5,1,	M6,1+2+1, 	M1,1,	M7,2,	M6,1,	M7,1+4,
	M7,2,	M6,1,	M7,1+2+1, 	M3,1,	H1,1,	H2,1,	H1,1,	M7,1,	M6,2,	M5,2,
	M6,2,	H3,1,	H3,1+2,		M5,2,	M6,2,	H3,1,	H3,1+2,	M5,1,	M6,1,
	M6,4+2+2,		H1,2,		H2,2,
	H3,2,	H6,1,	H5,1+2,		H6,1,	H5,1+2,	H6,1,	H5,1+2,	H2,1,	H3,1+2,	H6,1,	H5,1+2,	H6,1,	H5,1+2,	H6,1,	H5,1+2,	H2,1,	H3,1,
	H2,2,	H1,1,	M6,1+2,		H1,1,	H1,1,	H2,1,	H1,1,	M6,2+1,	H1,2+1,
	H3,4+1,	H4,1,	H3,1,		H2,2+1,	H1,2,	H2,2,
	H3,2,	H6,1,	H5,1+2,		H6,1,	H5,1+2,	H6,1,	H5,1+2,	H3,2,
	H3,2,	H6,1,	H5,1+2,		H6,1,	H5,1+2,	H6,1,	H5,1+2,	H3,2+1,
	H2,2,	H1,1,	M6,1+1,		H3,2+1,	H2,1,	H1,1,	M6,2+1,	H1,2+1,
	H1,4+2+2,		M6,1,		H3,2+1,	
	H2,2,	H1,1,	M6,1+1,		H3,2+1,	H2,1,	H1,1,	M6,2+1,	H1,2+1,
	
	0xFF	//终止标志
};
	
//PaceSelect 选择的频率
//MusicSelect 选择的音符
unsigned char PaceSelect=0,MusicSelect=0;

void main()
{
	Timer0_Init();
	
	while(1)
	{
		if(Music[MusicSelect] != 0xFF)		//如果不是停止标志位
		{
			PaceSelect = Music[MusicSelect];//选择音符对应的频率
			MusicSelect++;
			Delayms((SPEED/4)*Music[MusicSelect]);//选择音符对应的值
			MusicSelect++;
			
			//音符间停顿5ms
			TR0=0;
			Delayms(5);
			TR0=1;
		}
		else
		{
			TR0=0;		//播放完停掉计时器
			while(1);
		}	
	}
}

//中断定时T0函数
void Timer0_Rountine()		interrupt 1
{
	if(PaceTable[PaceSelect])
	{
		//取相应频率值的重装载值到定时器
		TL0=PaceTable[PaceSelect]%256;		
		TH0=PaceTable[PaceSelect]/256;
		
		//翻转蜂鸣器IO口
		Buzzer=!Buzzer;
	}
}