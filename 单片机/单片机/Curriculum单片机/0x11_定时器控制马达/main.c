#include "reg52.h"

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

void T0_1ms_init(){
	// �趨T0��ʱ��ģʽ : �����ڷ�ʽ1, 16λ��ʱ�� 
	TMOD = 0x01;
	
	/*
		�趨��ʱ����ֵ, ʹ�� 1ms �ж�һ��
		���� 8 λ�������� 2^16 = 65536 �����
		��������Ϊ 1us,
		��ʼֵ�趨Ϊ 64536 = 0xFC18 ���� 1ms �ж�һ��
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

void T1_50ms_init(){
	// �趨T0��ʱ��ģʽ : �����ڷ�ʽ1, 16λ��ʱ�� 
	TMOD |= 0x10;
	
	// 50ms �ж�һ��
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	// ������ʱ��0 �ж�
	ET1 = 1;
	// �������ж�
	EA = 1;
	
	// ������ʱ������ TR0 
	TR1 = 1;
}
/***********************************************************/
// ��ڿε����� : 
/*
	51 ��Ƭ����������, ���ǿ���
	����Ԫ�� : 
	ULN2003 ��߲����� 50V
	in : 1, out : 0
	in : 0, out : ?
*/

sbit dc_motor_pin = P1 ^ 0; // ���� dc2003 ����
void delay_ten_us(int x){
	while(x --);
}
void DC_MOTOR_INIT(){
	// �رյ��
	dc_motor_pin = 0;
}
void main(){
	DC_MOTOR_INIT();
	delay_ten_us(1000 * 100);
	delay_ten_us(1000 * 100);
	delay_ten_us(1000 * 100);
	T0_1ms_init();
	T1_50ms_init();
	while(1){
		
	}
}
/***********************************************************/
void T0_isr() interrupt 1{
	// 1s ʹ��С��1 ��תһ��
	// 1s ʹ�õ���ı�һ��״̬
	static unsigned int counter = 0;
	counter ++;
	if(counter == 1000){ // 1000 ms
		counter = 0; 
		LED0 = !LED0;
		dc_motor_pin = !dc_motor_pin;
	}
	// ��֤ 1ms �ļ�ʱ���ж�����
	TH0 = 0xFC;
	TL0 = 0x18;
}

void T1_isr() interrupt 3{
	// 1s ʹ��С��2 ��תһ��
	static unsigned int counter = 0;
	counter ++;
	if(counter == 20){ // 1000 ms
		counter = 0; 
		LED1 = !LED1;
	}
	// ��֤ 50ms �ļ�ʱ���ж�����
	TH1 = 0x3C;
	TL1 = 0xB0;
}