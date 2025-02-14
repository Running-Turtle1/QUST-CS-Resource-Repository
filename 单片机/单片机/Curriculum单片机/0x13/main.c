#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
/*
	IIC Э��, Ӧ���� EEPROM (AT24C02), IIC �����������Թ� 8 �� AT24C02(256 * 8bit), 000 - 111
	ÿһ�� EEPROM �ϴ洢�� (0x00 - OxFF)

	1. �ҵ���ַΪ 1010, (000) �� AT24C02
	2. �ҵ���� AT24C02 ��, �����ĵ�ַΪ 0x01 �Ĵ洢��
	3. ������洢����д������ 0x0F
*/
/*
	addr : AT24C02 �ϼĴ����ĵ�ַ
*/
void at24c02_write_byte(u8 addr, u8 dat){
	// 01 - ����IIC
	IIC_start();
	// 02 - ���� 7 λ��ַ�� (1010,000) + д�ź� : 0
	IIC_write_byte(0xA0); ?
	// 03 - �����ȴ����ܴӻ����͵���ЧASK�ź�
	IIC_wait_ask();
	// 04 - ���� 8 λ AT24C02 �ڲ��ļĴ�����ַ������ : 0x01)
	IIC_write_byte(addr);
	// 05 - �����ȴ����ܴӻ����͵���ЧASK�ź�
	IIC_wait_ask();
	// 06 - ���� 8 λ���� (���� : 0x0F)
	IIC_write_byte(0x0F);
	// 07 - �����ȴ����ܴӻ����͵���ЧASK�ź�
	IIC_wait_ask();
	// 08 - ֹͣ IIC
	IIC_stop();
}
u8 at24c02_read_byte(u8 addr){
	// 01 - ����IIC
	IIC_start();
	// 02 - ���� 7 λ��ַ�� (1010,000) + д�ź� : 0
	IIC_write_byte(0xA0); ?
	// 03 - �����ȴ����ܴӻ����͵���ЧASK�ź�
	IIC_wait_ask();
	// 04 - ���� 8 λ AT24C02 �ڲ��ļĴ�����ַ������ : 0x01)
	IIC_write_byte(addr);
	// 05 - �����ȴ����ܴӻ����͵���ЧASK�ź�
	IIC_wait_ask();
	
	// 06 - ���� IIC
	IIC_start();
	// 07 - ���� 7 λ��ַ�� (1010,000) + ���ź� : 1
	IIC_write_byte(0xA1); 
	//
	u8 Value = IIC_read_byte();
	
	//
	IIC_stop();
	
	return smg_show_data;
}

void delay_10us(u16 x){
	while(x --);
}

void main(){

}
