#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef unsigned char u8;
typedef unsigned int u16;

// ����ϵͳͷ�ļ�
#include "reg52.h"

// �����Լ�д��ͷ�ļ�, ע��Ҫ���ͷ�ļ���Ŀ¼
#include "LCD.h"
#include "DS.h"
#include "DS18.h"
#include "intrins.h" /////// _nop_();
#include "timer.h"

// LCD.h
sbit LCD1602_RS=P2^6;//��������ѡ��
sbit LCD1602_RW=P2^5;//��дѡ��
sbit LCD1602_E=P2^7; //ʹ���ź�
#define LCD1602_DATAPORT P0	//�궨��LCD1602���ݶ˿�


// DS.h
//�ܽŶ���
sbit DS1302_RST=P3^5;//��λ�ܽ�
sbit DS1302_CLK=P3^6;//ʱ�ӹܽ�
sbit DS1302_IO=P3^4;//���ݹܽ�

//��������
extern u8 gDS1302_TIME[7];//�洢ʱ��

// DS18.h
//�ܽŶ���
sbit DS18B20_PORT=P3^7;	//DS18B20���ݿڶ���

// ��������
void delay_10us(u16 ten_us);

#endif