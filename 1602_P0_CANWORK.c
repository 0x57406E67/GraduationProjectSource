/*
 * RS P0.5
 * RW P0.6
 * EN P0.7
 * OUTPUT P1.0-P1.7
 * DONE
 */
#include <ioCC2530.h>

typedef unsigned char uchar;
typedef unsigned int  uint;
uchar tab[] = "Wang Wei Jun";
uchar tab2[]= "Zhang jian zao";

#define RS P0_5
#define RW P0_6
#define EN P0_7


void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void initIO1()
{
	//P1SEL &= 0x00;
	//P2SEL &= 0xf0;
	P0DIR |= 0xff;
	P1DIR |= 0xff;
	// P2INP &= 0xf0;
	//P2INP = 0xf0;
}
void LCD_wcom(uchar com)
{
	RS = 0;
	RW = 0;
	P1 = com;
	delayms(1000);
	EN = 1;
	EN = 0;
}
void LCD_wdate(uchar date)
{
	RS = 1;
	RW = 0;
	P1 = date;
	delayms(1000);
	EN = 1;
	EN = 0;
}
void LCD_init()
{
	// LCD_wcom(0x01); 
	// delayms(1000);
	LCD_wcom(0x38); 
	// delayms(1000);
    LCD_wcom(0x0c); 
    //LCD_wcom(0x0e); 
    // LCD_wcom(0x0f); 
    // delayms(1000);
    LCD_wcom(0x06); 
    // LCD_wcom(0x07); 
    // delayms(1000);
    LCD_wcom(0x01);
    delayms(1000);
}

void main()
{
	uchar n,m;
	initIO1();
	LCD_init();
	LCD_wcom(0x80);
	for (n = 0; n < 12; n++)
	{
		LCD_wdate(tab[n]);
		delayms(1000);
	}
	LCD_wcom(0x80+0x40);
	for (m = 0; m < 14; m++)
	{
		LCD_wdate(tab2[m]);
		delayms(1000);
	}
	while(1);
}

/*void main()
{
	initIO1();
	LCD_init();
	LCD_wcom(0x80);
	LCD_wcom(0x41);
	while(1);
}*/