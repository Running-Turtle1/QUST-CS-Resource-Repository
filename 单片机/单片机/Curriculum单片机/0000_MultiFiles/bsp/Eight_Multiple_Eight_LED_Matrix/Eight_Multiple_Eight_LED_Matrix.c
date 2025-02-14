#include "public.h"

// ������Ƭ���ĵ� x ����
void light_the_x_th_led(u16 x){
	P2 = 0xff; // ȫ��Ϩ��
	P2 &= ~(1 << x); // ���� x λ��Ϊ 0
}

void waterfall_light(){
	u16 i, t;
	for(i = 0; i < 8; i ++){
		light_the_x_th_led(i); 
		delay_10us(500 * 100); // ��ʱ 500 ms
	}
}