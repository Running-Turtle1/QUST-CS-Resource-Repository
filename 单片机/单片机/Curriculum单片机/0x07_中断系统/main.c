 // �ⲿ�ж� 0 1 ���� : https://blog.csdn.net/m0_56399733/article/details/133904885
#include "reg52.h"

typedef unsigned int u16;	 
typedef unsigned char u8;

// ͳ�� K3 ���µĴ��� , �� INT0 �����жϵĴ��� 
u16 press_button_k3_cnt = 0;

// ���� LED1 �� LED2 �ܽ�
sbit LED1=P2^0;
sbit LED2=P2^1;

// ����������� K3 �� K4 ���ƽ�
// ��������K3���ӵ����ⲿ�ж�0������
sbit KEY3=P3^2;
sbit KEY4=P3^3;

void delay_10us(u16 ten_us) {
	while(ten_us--);	
}

// �ⲿ�ж� 0 ���ú���
void exit0_init() {
	IT0 = 1; // �����ش�����ʽ���½��أ�
	EX0 = 1; //��INT0���ж�����
	EA = 1;  //�����ж�
}
// �ⲿ�ж� 1 ���ú���
void exit1_init() {
	IT1 = 1; //�����ش�����ʽ���½��أ�
	EX1 = 1; //��INT0���ж�����
	EA = 1;  //�����ж�
}

// ����ܶ�ѡ����
u8 code Array[] = { 
    // 0 - f
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

sbit pin0 = P2 ^ 2;
sbit pin1 = P2 ^ 3;
sbit pin2 = P2 ^ 4;

void main() {	
	exit0_init(); //�ⲿ�ж�0����
	exit1_init(); //�ⲿ�ж�1����
	pin0 = 1;
	pin1 = 1;
	pin2 = 1;
	while(1) {
		P0 = Array[press_button_k3_cnt]; // ��һ���������ʾ��������
		delay_10us(100); //��ֹ����������쵼����ʾ���������Ƚϵ�
		P0 = 0x00; //��Ӱ ��������
	}		 
}

void exit0() interrupt 0 //�ⲿ�ж� 0 �жϺ���
{
	delay_10us(1000); // ����
	if(KEY3 == 0){ // �ٴ��ж�K3���Ƿ���
		while(!KEY3); // �ȴ������ɿ�
		press_button_k3_cnt ++;
		if(press_button_k3_cnt == 10){
			press_button_k3_cnt = 0;	
		}
		LED1 =! LED1; //LED1״̬��ת
	}			
}
void exit1() interrupt 2 //�ⲿ�ж� 1 �жϺ���
{
	delay_10us(1000); //����
	if(KEY4 == 0){ //�ٴ��ж� K4 ���Ƿ���
		while(!KEY4);
		LED2 =! LED2; //LED2״̬��ת
	}			
}