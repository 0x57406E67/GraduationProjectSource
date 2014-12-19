/********************************************************************
* 文件名  ： 矩阵键盘.c
* 描述    :  该文件实现了 4 * 4 键盘的试验。通过数码管的最后两位来显示当前的按键值。		 
* 创建人  ： 东流，2009年4月9日
* 版本号  ： 2.0
* 技术支持论坛：www.zidh.com/bbs（请进入“赞助商板块”中的“东流电子工作室”）
* 感谢“中国自动化资讯网”对本工作室的大力支持。
* LED 0 亮 1 灭
*********************************************************************/
#include<ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define h1 P0_0
#define h2 P0_1
#define h3 P0_2
#define h4 P0_3

#define l1 P0_7
#define l2 P0_6
#define l3 P0_5
#define l4 P0_4

/********************************************************************
* 名称 : Delay_1ms()
* 功能 : 延时子程序，延时时间为 1ms * x
* 输入 : x (延时一毫秒的个数)
* 输出 : 无
***********************************************************************/
void Delay_1ms(uint i)
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

/********************************************************************
* 名称 : InitKey()
* 功能 : 初始化按键
***********************************************************************/
void InitKey(void)//初始化Key
{
	P0DIR &= 0x0f;
	P0SEL &= 0x00;
	P2INP &= 0x00;//ffffff
	P0INP &= 0xff;
}

/********************************************************************
* 名称 : InitLed()
* 功能 : 初始化LED
***********************************************************************/
void InitLed(void)//初始化led
{
	P1DIR |= 0xff;
                P0DIR |= 0xff;
}

/********************************************************************
* 名称 : Keyscan()
* 功能 : 实现按键的读取。
***********************************************************************/
uchar Keyscan(void)
{
	uchar  temp,key;
	P0 = 0xfe;                                                       // 1111 1110 第一行送低电平
	temp = P0;
	temp &= 0xfe;                                              // temp & 0xfe = xxxx 1110 & 1111 0000 
	if (temp != 0xf0)                                          // 如果temp不等于0xf0(1111 0000) 说明有按键按下
	{
		Delay_1ms(10);                            // 按键消抖
		temp = P0;
		temp &= 0xf0;
		if (temp != 0xf0)
		{
			temp = P0;
			switch(temp)
			{
				case 0x7e: key = 0xfe; // 0111 1110, 1111 1110
				break;
				case 0xbe: key = 0xfc; // 1011 1110, 1111 1100
				break;
				case 0xde: key = 0xf8; // 1101 1110, 1111 1000
				break;
				case 0xee: key = 0xf0; // 1110 1110, 1111 0000
				break;
			}
			while(temp != 0xf0) //等待按键释放
			{
				temp = P0;
				temp &= 0xf0;
			}
			return key;
		}
	}
	P0 = 0xfd; // 1111 1101
	temp = P0;
	temp &= 0xfd; // 0xfd & 0xf0 = 1111 1101 & 1111 0000
	if (temp != 0xf0)
	{
		Delay_1ms(10);
		temp = P0;
		temp &= 0xf0;
		if (temp != 0xf0)
		{
			temp = P0;
			switch(temp)
			{
				case 0x7d: key = 0xe0; // 0111 1101, 1110 0000
                                                                break;
                                                                case 0xbd: key = 0xc0; // 1011 1101, 1100 0000
                                                                break;
                                                                case 0xdd: key = 0x80; // 1101 1101, 1000 0000
                                                                break;
                                                                case 0xed: key = 0x00; // 1110 1101, 0000 0000
                                                                break;
			}
			while(temp != 0xf0)
			{
				temp = P0;
				temp &= 0xf0;
			}
			return key;
		}
	}
	P0 = 0xfb;
	temp = P0;
	temp &= 0xfb;
	if(temp != 0xf0)
	{
		Delay_1ms(10);
		temp = P0;
		temp &= 0xf0;
		if (temp != 0xf0)
		{
			temp = P0;
			switch(temp)
			{
				case 0x7b: key = 0x01;
                                                                break;
                                                                case 0xbb: key = 0x03;
                                                                break;
                                                                case 0xdb: key = 0x07;
                                                                break;
                                                                case 0xeb: key = 0x0f;
                                                                break;
			}
			while(temp != 0xf0)
			{
				temp = P0;
				temp &= 0xf0;
			}
			return key;
		}
	}
	P0 = 0xf7;
	temp = P0;
	temp &= 0xf7;
	if(temp != 0xf0)
	{
		Delay_1ms(10);
		temp = P0;
		temp &= 0xf0;
		if (temp != 0xf0)
		{
			temp = P0;
			switch(temp)
			{
				case 0x77: key = 0x1f;
                                                                break;
                                                                case 0xb7: key = 0x3f;
                                                                break;
                                                                case 0xd7: key = 0x7f;
                                                                break;
                                                                case 0xe7: key = 0xff;
                                                                break;
			}
			while(temp != 0xf0)
			{
				temp = P0;
				temp &= 0xf0;
			}
			return key;
		}
	}
}
/********************************************************************
* 名称 : Main()
* 功能 : 主函数
* 输入 : 无
* 输出 : 无
***********************************************************************/
void main(void)
{
	uchar Key_Value; 	
	InitLed();      // 初始化LED
	InitKey();      // 初始化按键
	while(1)
	{
		P0 = 0xf0;
		if (P0 != 0xf0) 
		{
			Delay_1ms(15);
			if (P0 != 0xf0)
			{
				Key_Value = Keyscan();
			}
		}
		P1 = Key_Value;
		Delay_1ms(50);
	}
        
}
