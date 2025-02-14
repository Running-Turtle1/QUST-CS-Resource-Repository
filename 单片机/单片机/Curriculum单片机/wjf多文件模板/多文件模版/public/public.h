//���й�������Դ
#ifndef __PUBLIC_H__
#define __PUBLIC_H__

//���������ض���,һ���ڰ��������ļ�ǰ��
typedef unsigned char 	u8;
typedef unsigned int 	u16;

//����ͷ�ļ�
#include <reg52.h>
#include "led.h"
#include "key.h"
#include "smg.h"
#include "step_motor.h"
#include "iic.h"
#include "24c02.h"
#include "lcd1602.h"

#include "timer.h"
/********************��ģ�飺LEDӦ�ã�********************/
//LED:D1~D7:�˿�
#define LEDS_PORT 	P2
//LED:D1~D7
sbit LED_D1=P2^0;
sbit LED_D2=P2^1;
sbit LED_D3=P2^2;
sbit LED_D4=P2^3;
sbit LED_D5=P2^4;
sbit LED_D6=P2^5;
sbit LED_D7=P2^6;
sbit LED_D8=P2^7;
/********************��ģ�飺KEYӦ�ã�********************/
//�������������λ��ͬʱҲ���ⲿ�����ж�INT0
sbit INT0_KEY_K3=P3^2;
sbit INT1_KEY_K4=P3^3;
//������KEY
sbit KEY_K1=P3^1;
sbit KEY_K2=P3^0;
sbit KEY_K3=P3^2;
sbit KEY_K4=P3^3;
/********************��ģ�飺SMGӦ�ã�********************/
//ʹ�ú궨�������"��ѡ"��˿�
#define SMG_A_2_DP_PORT	P0	
//��̬����ܡ�λѡ����˿�
sbit SMG_1_2_LS_A=P2^2;
sbit SMG_1_2_LS_B=P2^3;
sbit SMG_1_2_LS_C=P2^4;

extern u8 code g_smg_duan_code[];
/********************��STEP_MOTORӦ�ã�********************/
//����ULN2003���Ʋ�������ܽ�
//VCC������ɫ
//D������ɫ
sbit STEP_MOTOR_IN_D=P1^0;
//C������ɫ
sbit STEP_MOTOR_IN_C=P1^1;
//B������ɫ
sbit STEP_MOTOR_IN_B=P1^2;
//A������ɫ
sbit STEP_MOTOR_IN_A=P1^3;
/********************��ģ�飺IICӦ�ã�********************/
//����EEPROM���ƽ�
//SCLʱ����
sbit IIC_SCL=P2^1;
//SDA������
sbit IIC_SDA=P2^0;
/********************��ģ�飺EEPROMӦ�ã�********************/

//�������ݴ���EEPROM����ʼ��ַ
#define EEPROM_ADDRESS	0
/********************��ģ�飺LCD1602Ӧ�ã�********************/
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;
sbit LCD1602_E=P2^7;

#define LCD1602_DATA_PORT P0

extern u8 code lcd1602_table[];
	
/******************************
��������
******************************/
void delay_10us(u16 ten_us);
#endif