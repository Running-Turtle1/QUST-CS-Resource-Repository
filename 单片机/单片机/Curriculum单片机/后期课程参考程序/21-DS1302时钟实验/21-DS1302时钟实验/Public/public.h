#ifndef _public_H
#define _public_H

#include "reg52.h"

typedef unsigned int u16;	//��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;


void delay_10us(u16 ten_us);
void delay_ms(u16 ms);

#endif


/*
// ds1302_write_byte(0x80,0X50); wjf
	// ��Ĵ���addr=0x80, dat=0x50
	// 8421BCD��?
								 ��     ��    ʱ   ��    ��    ����   ��
extern u8 g_WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};

24 ��, ����һ, 5��20��,16ʱ41��50��
extern u8 g_SET_RTC_TIME[7] = {0x50, 0x41, 0x16, 0x20, 0x05, 0x01, 0x24};

void ds1302_init(void){
	// DS1302 ����ʱ��Ϊ 16ʱ41��50��
	
	// �Ĵ��ַ�� 0x8E, 
	ds1302_write_byte(0x8E, 0x00); // �ر�д�����Ĵ���,д����λ, �ر�֮�� MCU �ſ���д�� RTC
	u8 i = 0;
	for(i = 0 ; i < 7; i ++){
		ds1302_write_byte(g_WRITE_RTC_ADDR[i], g_SET_RTC_TIME[i]);
	}
}
*/
