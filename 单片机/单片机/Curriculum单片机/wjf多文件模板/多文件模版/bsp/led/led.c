#include "public.h"

/***************************
函数名称：void leds_show_init(void)
函数功能：点亮LED
输入	: void
输出	：void
***************************/
void leds_show_init()
{
	LEDS_PORT=0xFF;
}
/***************************
函数名称：void leds_show_on(void)
函数功能：点亮LED
输入	: void
输出	：void
***************************/
void leds_show_on()
{
	LEDS_PORT=0x00;
}
/***************************
函数名称：void leds_show_off(void)
函数功能：点亮LED
输入	: void
输出	：void
***************************/
void leds_show_off()
{
	LEDS_PORT=0xFF;
}
/***************************
函数名称：void leds_show_run(void)
函数功能：点亮LED
输入	: void
输出	：void
***************************/
void leds_show_run()
{
	u8 i=0;
	for(i=0;i<8;i++)
	{
			/*
			方法1：使用(0xfe<<i)
			D8	|D7	|D6	|D5	|D4	|D3	|D2	|D1	|
			P27	|P26|P25|P24|P23|P22|P21|P20|
			i=0: (0xfe<<i)
			1	|1	|1	|1	|1	|1	|1	|0	|
			i=1:
			1	|1	|1	|1	|1	|1	|0	|0	|
			i=2:
			1	|1	|1	|1	|1	|0	|0	|0	|
			结论：该方法：不行
			********************************
			D8	|D7	|D6	|D5	|D4	|D3	|D2	|D1	|
			P27	|P26|P25|P24|P23|P22|P21|P20|
			i=0: (0x01<<i)
			0	|0	|0	|0	|0	|0	|0	|1	|
			i=0: ~(0x01<<i)
			1	|1	|1	|1	|1	|1	|1	|0	|
			---------------------------------
			i=1: (0x01<<i)
			0	|0	|0	|0	|0	|0	|1	|0	|
			i=1: ~(0x01<<i)
			1	|1	|1	|1	|1	|1	|0	|1	|
			---------------------------------
			i=2: (0x01<<i)
			0	|0	|0	|0	|0	|1	|0	|0	|
			i=2: ~(0x01<<i)
			1	|1	|1	|1	|1	|0	|1	|1	|
			---------------------------------
			i=3: (0x01<<i)
			0	|0	|0	|0	|1	|0	|0	|0	|
			i=3: ~(0x01<<i)
			1	|1	|1	|1	|0	|1	|1	|1	|
			---------------------------------
			i=4: (0x01<<i)
			0	|0	|0	|1	|0	|0	|0	|0	|
			i=4: ~(0x01<<i)
			1	|1	|1	|0	|1	|1	|1	|1	|
			---------------------------------
			i=5: (0x01<<i)
			0	|0	|1	|0	|0	|0	|0	|0	|
			i=5: ~(0x01<<i)
			1	|1	|0	|1	|1	|1	|1	|1	|
			---------------------------------
			---------------------------------
			i=6: (0x01<<i)
			0	|1	|0	|0	|0	|0	|0	|0	|
			i=6: ~(0x01<<i)
			1	|0	|1	|1	|1	|1	|1	|1	|
			---------------------------------
			i=7: (0x01<<i)
			1	|0	|0	|0	|0	|0	|0	|0	|
			i=7: ~(0x01<<i)
			0	|1	|1	|1	|1	|1	|1	|1	|
			---------------------------------
			*/
			LEDS_PORT=~(0x01<<i);
			delay_10us(50000);
	}		
}

