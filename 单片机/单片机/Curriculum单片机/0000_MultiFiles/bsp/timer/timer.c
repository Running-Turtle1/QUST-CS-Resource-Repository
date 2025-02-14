#include "public.h"

/* ��ʼ�� T0 ��ʱ����ʹ�� 1ms �ж�һ�� */
void T0_1ms_init(){
	/*
	�趨T0��ʱ��ģʽ 
	M1 = 0, M0 = 1, ������ʽ 1, 16 λ��ʱ��/������
	*/
	TMOD = 0x01;
	
	/*
		�趨��ʱ����ֵ, ʹ�� 1ms �ж�һ��
		���� 8 λ�������� 2^16 = 65536 �����
		�������ڴ�ԼΪ 1us,
		��ʼֵ�趨Ϊ 64536 = 0xFC18 ���� 1ms �ж�һ��(����ȷ)
	*/
	TH0 = 0xFC;
	TL0 = 0x18;
	
	// ������ʱ��0 �ж�
	ET0 = 1;
	
	// �������ж�
	EA = 1;
	
	// ������ʱ������ TR0 
	TR0 = 1;
}

void T0_isr() interrupt 1{
	// �жϷ����ܴ���
	static unsigned int counter = 0;
	// ��ǰ��Ҫ����С�Ƶı��
	static unsigned int ledNum = 0;
	counter ++;
	if(counter == 1000){ // 1000 * 1 = 1000 ms
		counter = 0; 
		light_the_x_th_led(ledNum);
		ledNum ++;
		if(ledNum == 8) ledNum = 0;
	}
	// ��֤ 1ms �ļ�ʱ���ж�����
	TH0 = 0xFC;
	TL0 = 0x18;
}