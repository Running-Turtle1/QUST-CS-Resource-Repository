#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef unsigned char u8;
typedef unsigned int u16;

// ����ϵͳͷ�ļ�
#include "reg52.h"

// �����Լ�д��ͷ�ļ�, ע��Ҫ���ͷ�ļ���Ŀ¼
#include "Eight_Multiple_Eight_LED_Matrix.h"
#include "timer.h"
//#include "LCD1602.h"
//#include "DS1302.h"

sbit LCD1602_RS=P2^6;//��������ѡ��
sbit LCD1602_RW=P2^5;//��дѡ��
sbit LCD1602_E=P2^7; //ʹ���ź�
#define LCD1602_DATAPORT P0	//�궨��LCD1602���ݶ˿�

// ��������
void delay_10us(u16 ten_us);

#endif