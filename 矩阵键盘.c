/********************************************************************
* �ļ���  �� �������.c
* ����    :  ���ļ�ʵ���� 4 * 4 ���̵����顣ͨ������ܵ������λ����ʾ��ǰ�İ���ֵ��		 
* ������  �� ������2009��4��9��
* �汾��  �� 2.0
* ����֧����̳��www.zidh.com/bbs������롰�����̰�顱�еġ��������ӹ����ҡ���
* ��л���й��Զ�����Ѷ�����Ա������ҵĴ���֧�֡�
* LED 0 �� 1 ��
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
* ���� : Delay_1ms()
* ���� : ��ʱ�ӳ�����ʱʱ��Ϊ 1ms * x
* ���� : x (��ʱһ����ĸ���)
* ��� : ��
***********************************************************************/
void Delay_1ms(uint i)
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

/********************************************************************
* ���� : InitKey()
* ���� : ��ʼ������
***********************************************************************/
void InitKey(void)//��ʼ��Key
{
	P0DIR &= 0x0f;
	P0SEL &= 0x00;
	P2INP &= 0x00;//ffffff
	P0INP &= 0xff;
}

/********************************************************************
* ���� : InitLed()
* ���� : ��ʼ��LED
***********************************************************************/
void InitLed(void)//��ʼ��led
{
	P1DIR |= 0xff;
                P0DIR |= 0xff;
}

/********************************************************************
* ���� : Keyscan()
* ���� : ʵ�ְ����Ķ�ȡ��
***********************************************************************/
uchar Keyscan(void)
{
	uchar  temp,key;
	P0 = 0xfe;                                                       // 1111 1110 ��һ���͵͵�ƽ
	temp = P0;
	temp &= 0xfe;                                              // temp & 0xfe = xxxx 1110 & 1111 0000 
	if (temp != 0xf0)                                          // ���temp������0xf0(1111 0000) ˵���а�������
	{
		Delay_1ms(10);                            // ��������
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
			while(temp != 0xf0) //�ȴ������ͷ�
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
* ���� : Main()
* ���� : ������
* ���� : ��
* ��� : ��
***********************************************************************/
void main(void)
{
	uchar Key_Value; 	
	InitLed();      // ��ʼ��LED
	InitKey();      // ��ʼ������
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
