#include "reg52.h"

// �ο����� : https://blog.csdn.net/qq_65980796/article/details/131996779

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

/*
	TMOD : 
	M0
	M1
	C/T_
	GATE
	M0
	M1
	C/T_
	GATE
*/

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

/* ��ʼ�� T1 ��ʱ����ʹ�� 50ms �ж�һ�� */
void T1_50ms_init(){
	// �趨T1��ʱ��ģʽ : �����ڷ�ʽ1, 16λ��ʱ�� 
	TMOD |= 0x10;
	
	// 50ms �ж�һ�� : 65536 - 50 * 1000 = 15536 = 0x3CB0
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	// ������ʱ��0 �ж�
	ET1 = 1;
	// �������ж�
	EA = 1;
	
	// ������ʱ������ TR0 
	TR1 = 1;
}

void main(){
	// ��ʼ����ʱ��
	T0_1ms_init();
	T1_50ms_init();
	while(1){
		
	}
}

void T0_isr() interrupt 1{
	// 1s ʹ��С��1 ��תһ��
	static unsigned int counter = 0;
	counter ++;
	if(counter == 1000){ // 1000 * 1 = 1000 ms
		counter = 0; 
		LED0 = !LED0;
	}
	// ��֤ 1ms �ļ�ʱ���ж�����
	TH0 = 0xFC;
	TL0 = 0x18;
}

void T1_isr() interrupt 3{
	// 1s ʹ��С��2 ��תһ��
	static unsigned int counter = 0;
	counter ++;
	if(counter == 20){ // 50 * 20 = 1000 ms
		counter = 0; 
		LED1 = !LED1;
	}
	// ��֤ 50ms �ļ�ʱ���ж�����
	TH1 = 0x3C;
	TL1 = 0xB0;
}