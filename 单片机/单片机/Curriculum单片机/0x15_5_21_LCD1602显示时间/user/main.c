#include "public.h"

u8 time_buf[8]; // ���� LCD ��ʾ

char date_str[17]; // �����ַ���������Ϊ16�ַ�+1��������
char time_str[17]; // ʱ���ַ���������Ϊ16�ַ�+1��������

u16 x;

void main(){
	lcd1602_init();//LCD1602��ʼ��
	ds1302_init();//��ʼ��DS1302
	
	while(1){
		ds1302_read_time(); // ��ȡ DS1302 ��ʱ��
		LcdDisplay(); // LCD1602 ��ʾʱ��
	}
}