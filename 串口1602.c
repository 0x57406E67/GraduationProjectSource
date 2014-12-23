/****************************************************************************
* 文 件 名: main.c
* 作    者: Andy
* 修    订: 2013-01-08
* 版    本: 1.0
* 描    述: 设置串口调试助手波特率：115200bps 8N1
*           串口调试助手给CC2530发字符串时，开发板会返回接收到的字符串
****************************************************************************/
#include <ioCC2530.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

#define UART0_RX    1
#define UART0_TX    2
#define SIZE       51

#define RS P0_5
#define RW P0_6
#define EN P0_7

char RxBuf;
char UartState;
uchar count;
char RxData[SIZE];        //存储发送字符串

void DelayMS(uint msec)
{ 
    uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<1070; j++);
}

void initIO1()
{
	//P0DIR |= 0xff;
	P0DIR |= 0xe0;
	P1DIR |= 0xff;
	P2INP &= 0xb7;
}

void LCD_wcom(uchar com)
{
	RS = 0;
	RW = 0;
	P1 = com;
	DelayMS(100);
	EN = 1;
	EN = 0;
}
void LCD_wdate(uchar date)
{
	RS = 1;
	RW = 0;
	P1 = date;
	DelayMS(100);
	EN = 1;
	EN = 0;
}
void LCD_init()
{
	LCD_wcom(0x38); 
                LCD_wcom(0x0c); 
                LCD_wcom(0x06); 
                LCD_wcom(0x01);
                DelayMS(100);
}


/****************************************************************************
* 名    称: InitUart()
* 功    能: 串口初始化函数
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitUart(void)
{ 
    PERCFG = 0x00;           //外设控制寄存器 USART 0的IO位置:0为P0口位置1 
    P0SEL = 0x0c;            //P0_2,P0_3用作串口（外设功能）
    P2DIR &= ~0xC0;          //P0优先作为UART0
    
    U0CSR |= 0x80;           //设置为UART方式
    U0GCR |= 11;				       
    U0BAUD |= 216;           //波特率设为115200
    UTX0IF = 0;              //UART0 TX中断标志初始置位0
    U0CSR |= 0x40;           //允许接收 
    IEN0 |= 0x84;            //开总中断允许接收中断  
}

/****************************************************************************
* 名    称: UartSendString()
* 功    能: 串口发送函数
* 入口参数: Data:发送缓冲区   len:发送长度
* 出口参数: 无
****************************************************************************/
void UartSendString(char *Data, int len)
{
    uint i;
    
    for(i=0; i<len; i++)
    {
        U0DBUF = *Data++;
        while(UTX0IF == 0);
        UTX0IF = 0;
    }
}

/****************************************************************************
* 名    称: UART0_ISR(void) 串口中断处理函数 
* 描    述: 当串口0产生接收中断，将收到的数据保存在RxBuf中
****************************************************************************/
#pragma vector = URX0_VECTOR 
__interrupt void UART0_ISR(void) 
{ 
    URX0IF = 0;       // 清中断标志 
    RxBuf = U0DBUF;                           
}


/****************************************************************************
* 程序入口函数
****************************************************************************/
void main(void)
{	
    uchar n;
    CLKCONCMD &= ~0x40;                        //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                   //等待晶振稳定为32M
    CLKCONCMD &= ~0x47;                        //设置系统主时钟频率为32MHZ   
   
    InitUart();                                //调用串口初始化函数   
    UartState = UART0_RX;                      //串口0默认处于接收模式
    memset(RxData, 0, SIZE);
    initIO1();
    LCD_init();
/*                 LCD_wcom(0x80);
             for (n = 0; n < 10; n++)
             {
             	          LCD_wdate(tab[n]);
             	          DelayMS(100);
             }*/
    while(1)
    {
        if(UartState == UART0_RX)              //接收状态 
        { 
            if(RxBuf != 0) 
            {                 
                if((RxBuf != '#')&&(count < 50))//以'＃'为结束符,一次最多接收50个字符            
                    RxData[count++] = RxBuf; 
                else
                {
                    if(count >= 50)             //判断数据合法性，防止溢出
                    {
                        count = 0;              //计数清0
                        memset(RxData, 0, SIZE);//清空接收缓冲区
                    }
                    else
                        UartState = UART0_TX;  //进入发送状态 
                }
                RxBuf  = 0;
            }
        }

        if(UartState == UART0_TX)       
        {                         
  /*          U0CSR &= ~0x40;                   
            UartSendString(RxData, count);   
            U0CSR |= 0x40;              
*/
             LCD_wcom(0x80);
             for (n = 0; n < count; n++)
             {
             	          LCD_wdate(RxData[n]);
             	          DelayMS(100);
             }
     
            UartState = UART0_RX;           
            count = 0;                       
            memset(RxData, 0, SIZE);           
        }    
    }
}