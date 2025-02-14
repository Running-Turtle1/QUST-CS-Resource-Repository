#include "reg52.h"

/* data, RCLK ��Ԥ�������*/

int i, j, k = 0;
sbit SER = P3^4; // ����������������
sbit SRCLK = P3^6; // ��λʱ����������
sbit RCLK_ = P3^5; // �洢ʱ����������

void delay_ten_us(int x){
	while(x --);
}

// ������ʱ���ݼĴ�����������λ��Q0->Q1->Q2-->Q3-->...-->Q7;�½�����λ�Ĵ������ݲ��䡣
void SRCLK_down(){
	SRCLK = 0;
	delay_ten_us(1);
	SRCLK = 1;
	delay_ten_us(1);
}

// 12 �� : ������ʱ��λ�Ĵ��������ݽ������ݴ洢�Ĵ������½���ʱ�洢�Ĵ������ݲ��䡣
void RCLK_down(){
	RCLK_ = 0;
	delay_ten_us(1);
	RCLK_ = 1;
	delay_ten_us(1);
}

// д������
void hc595_write_data(int data_){
	int i;
	for(i = 7; i >= 0; i --){
		SER = data_ >> i & 1;
		SRCLK_down();
	}		
	RCLK_down();
}
/*
01111111
10111111
11011111
11101111
11110111
11111011
11111101
11111110
*/
unsigned char code col[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

// ��ʮ��ÿ�д���
unsigned char code led_matrix_row_codes[8] = {
	0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18
};
void main(){
	P0 = 0xff;
	hc595_write_data(0x00);
	while(1){
		for(i = 0; i < 8; i ++){
			hc595_write_data(led_matrix_row_codes[i]);
			P0 = col[i];
			delay_ten_us(100);
			P0 = 0xff;
		}
	}
	
}