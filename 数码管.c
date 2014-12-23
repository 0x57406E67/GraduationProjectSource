// DONE
#include <ioCC2530.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

uchar led[8] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8};//显示1-8
// uchar table[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x00};
// uchar table[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe}; 
uchar table[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//点亮1-8
void DelayMS(uint msec) // 延迟
{ 
    uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

void InitLed(void)  // 初始化
{
    P0DIR |= 0xff;         
    P1DIR |= 0xff;
    // LedOnOrOff(0);      
}

void Delay(uint i)
{
	uchar x,j;
	for(j=0;j<i;j++)
	for(x=0;x<=148;x++);	
}

void main(void)
{
	uint i = 0, j = 0;
	InitLed();
	//P0 = 0xff;
	//P1 = 0x00;
	while(1)
	{
		P0 = table[i];
                P1 = 0xff;
		P1 = led[j];                
		Delay(1);
		i++;
		j++;
		if (j == 8)
		{
			i = 0;
			j = 0;
		}
	}
}
/*void main(void)
{
	InitLed();
	while(1)
	{
		P1 = 0x06;
		P0 = 0x00;
	}
}*/