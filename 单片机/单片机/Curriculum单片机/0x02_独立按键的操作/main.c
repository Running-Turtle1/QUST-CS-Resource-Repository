#include "reg52.h"

void delay(unsigned int count) {
    while(count --);
}

// ���尴����LED���ӵ�����, ���ж���������Ӧ�����ŷֱ��� 1 0 2 3
sbit key1 = P3^1;
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;

sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led3 = P2^2;
sbit led4 = P2^3;

void main(){
	key1 = 1; // ����Ϊ����ģʽ
	key2 = 1;
	key3 = 1;
	key4 = 1;
	led1 = 0; // ����Ϊ���ģʽ
	led2 = 0;
	led3 = 0;
	led4 = 0;
	while(1) {
		// ��ȡ����״̬����������ʱΪ0������Ϊ 1
		if(!key1){
			delay(1000); // ��ʱ������������
			while(!key1); // �ȴ������ͷ�
			led1 = !led1; // ȡ����ʵ��LED�������л�
		}
		
		if(!key2){
			delay(1000); // ��ʱ������������
			while(!key2); // �ȴ������ͷ�
			led2 = !led2; // ȡ����ʵ��LED�������л�
		}
		
		if(!key3){
			delay(1000); // ��ʱ������������
			while(!key3); // �ȴ������ͷ�
			led3 = !led3; // ȡ����ʵ��LED�������л�
		}
		
		if(!key4){
			delay(1000); // ��ʱ������������
			while(!key4); // �ȴ������ͷ�
			led4 = !led4; // ȡ����ʵ��LED�������л�
		}
	}
}

