#include "public.h"

void main(){
	test();
	light_the_x_th_led(1);
	lcd1602_init();//LCD1602��ʼ��
	lcd1602_show_string(0,0,"DATE:24-05-21 #23");//��һ����ʾ
	lcd1602_show_string(0,1,"TIME:19:03:12");//�ڶ�����ʾ
	while(1){
		
	}
}