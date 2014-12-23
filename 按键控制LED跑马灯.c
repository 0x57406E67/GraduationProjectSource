/****************************************************************************
* 文 件 名: main.c
* 作    者: Andy
* 修    订: 2013-01-08
* 版    本: 1.0
* 描    述: 按下按键S1控制LED1.LED2.LED3实现跑马灯效果
****************************************************************************/
#include <ioCC2530.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

#define LED1 P1_0        // 定义P1.0口为LED1控制端
#define LED2 P1_1        // 定义P1.1口为LED2控制端
#define LED3 P1_4        // 定义P1.4口为LED3控制端
#define KEY1 P0_1        // 定义P0.1口为S1控制端
#define ON      0
#define OFF     1

/****************************************************************************
* 名    称: DelayMS()
* 功    能: 以毫秒为单位延时，系统时钟不配置时默认为16M(用示波器测量相当精确)
* 入口参数: msec 延时参数，值越大，延时越久
* 出口参数: 无
****************************************************************************/
void DelayMS(uint msec)
{ 
    uint i,j;
    
    for (i=0; i<msec; i++)
        for (j=0; j<535; j++);
}

/****************************************************************************
* 名    称: LedOnOrOff()
* 功    能: 点亮或熄灭所有LED灯    
* 入口参数: mode为0时LED灯亮  mode为1时LED灯灭
* 出口参数: 无
****************************************************************************/
void LedOnOrOff(uchar mode)
{
    LED1 = mode;
    LED2 = mode;
    LED3 = mode; //由于P1.4与仿真器共用,必须拔掉仿真器的插头才能看到LED3的变化
}

/****************************************************************************
* 名    称: InitLed()
* 功    能: 设置LED相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitLed(void)
{
    P1DIR |= 0x13;  // P1.0、P1.1、P1.4定义为输出
    LedOnOrOff(1);  // 使所有LED灯默认为熄灭状态  
}

/****************************************************************************
* 名    称: InitKey()
* 功    能: 设置按键相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void InitKey(void)
{
    P0SEL &= ~0x02;     //设置P0.1为普通IO口  
    P0DIR &= ~0x02;     //按键接在P0.1口上，设P0.1为输入模式 
    P0INP &= ~0x02;     //打开P0.1上拉电阻
}

/****************************************************************************
* 名    称: KeyScan()
* 功    能: 读取按键状态
* 入口参数: 无
* 出口参数: 0为抬起   1为按键按下
****************************************************************************/
uchar KeyScan(void)
{
    if (KEY1 == 0)
    {
        DelayMS(10);      //延时10MS去抖
        if (KEY1 == 0)
        {
            while(!KEY1); //松手检测
            return 1;     //有按键按下
        }
    }
    
    return 0;             //无按键按下
}

/****************************************************************************
* 程序入口函数
****************************************************************************/
void main(void)
{
    InitLed();		      //设置LED灯相应的IO口
    InitKey();            //设置按键S1相应的IO口
    
    while(1)
    {
        DelayMS(2);
        if (KeyScan())    //扫描按键当前状态,按下时执行跑马灯效果
        {
            LED1 = ON;    //点亮LED1      
            DelayMS(500); 
            LED1 = OFF;   //熄灭LED1 
            LED2 = ON;                
            DelayMS(500); 
            LED2 = OFF;            
            LED3 = ON;           
            DelayMS(500); 
            LED3 = OFF; 
        }
    }
}
