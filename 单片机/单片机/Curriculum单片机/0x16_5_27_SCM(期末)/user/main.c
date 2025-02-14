#include "public.h"

int temp_value; // ȫ��������¼�¶�

void main(){	
	ds18b20_init();// ��ʼ��DS18B20�¶ȴ�����
	lcd1602_init(); // LCD 1602 ��ʼ��
	T0_50ms_init(); // T0 50 ms �ж�����
	
	while(1){
		lcd1602_write_cmd(0x80); // ��һ�п�ʼд
		
		if(temp_value<0)//�����¶�
		{
			temp_value=-temp_value; // ת��������
			lcd1602_write_data('-'); // ��� - ��
		
		}
		
		// �����ʾ�¶���Ϣ
		// �����ʾ Temperature ����д temp
		lcd1602_write_data('T');
		lcd1602_write_data('E');
		lcd1602_write_data('M');
		lcd1602_write_data('P');
		lcd1602_write_data(':');
		lcd1602_write_data('0' + temp_value/1000); // �¶ȵ�ʮλ
		lcd1602_write_data('0' + temp_value%1000/100); // �¶ȸ�λ
		lcd1602_write_data('.'); // С����
		lcd1602_write_data('0' + temp_value%100/10); // ����С����һλ
		lcd1602_write_data('0' + temp_value%10); // ����С������λ
		// \' ת���ַ�������ľ��ӽ�� ��� 'C ��ʾ���϶�
		lcd1602_write_data('\''); 
		lcd1602_write_data('C');
		// ��ʾ������Ϣ
		lcd1602_show_string(0, 1, "CREATED BY WPC"); // ��ʾ������Ϣ
	}
	
}

// ��ʱ������ :  1s ��ȡһ���¶�
void T0_isr() interrupt 1{
	static unsigned int counter = 0; // ��¼�жϴ���
	counter ++; // �жϴ��� + 1
	if(counter == 20){ // 50ms * 20 = 1000 ms = 1 s
		counter = 0; // ��ռ�¼����
		temp_value=ds18b20_read_temperture()*100;// ȫ�ֱ��� temp_value ��ȡ�¶�, �����¶�ֵС������λ
	}
	// ��֤ 50ms �ļ�ʱ���ж����� : 65536-50*1000 = 15536 = 0x3CB0
	TH0 = 0x3C;
	TL0 = 0xB0;
}