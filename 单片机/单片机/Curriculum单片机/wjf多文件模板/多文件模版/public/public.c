#include "public.h"
/***************************
�������ƣ�void delay_10us(u16 ten_us)
�������ܣ�������ʱ����10us
����	: u16 ten_us(���ʱ65536*10us)
���	��void
***************************/
void delay_10us(u16 ten_us)
{
 	while(ten_us--);
}