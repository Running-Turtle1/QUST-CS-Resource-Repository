#include "reg52.h"

/*
	IIC Э��, ���� 
*/

// https://blog.csdn.net/as480133937/article/details/105366932

// ����I2C���ߵ�������źͿ��ƼĴ���
sbit SCL = P1^0; // ����ʱ���� : Serial Clock Line
sbit SDA = P1^1; // ���������� : Serial Data Line
 
void delay_10us(unsigned int x){
	while(x --);
}	

void i2c_start() {
	/**** ����״̬ / ��ʼ״̬  ***/
	/*
		��ΪIIC�� SCL ��SDA ����Ҫ���������裬��֤����״̬���ȶ���
		����IIC�����ڿ���״̬��SCL ��SDA�����ָߵ�ƽ
	*/
	SCL = 1;
    SDA = 1;
	delay_10us(1);
	
    // ������ʼ�ź� : SCL ����, SDA �ɸߵ�ƽ��Ϊ�͵�ƽ
    SDA = 0;
	delay_10us(1);
	
    // SCL�ɸߵ�ƽ��Ϊ�͵�ƽ�������½���
	// ��I2Cͨ���У�ʱ���ߣ�SCL�����½���ͨ���������������ݵĴ������ա�
	// �����ʼ�źŵ��γ� 
    SCL = 0;
	delay_10us(1);
}

void i2c_stop() {
	// ��ʼ״̬
    SDA = 0;
    SCL = 1;
	delay_10us(1);
	
    // ����ֹͣ�ź� : SCL���ָߵ�ƽ, SDA�ɵ͵�ƽ��Ϊ�ߵ�ƽ��
    SDA = 1;
	delay_10us(1);
}

/****  IIC����һ���ֽ�����  ****/
/*
	�ܽ� : 
	1. �� SCL Ϊ�ߵ�ƽ�ڼ䣬�������ݣ�����8�����ݣ�
	   ����Ϊ 1 ,SDA������ ; ����Ϊ 0��SDA�����͡�  
	2. �����ڼ䱣�ִ����ȶ������������߽�������ʱ�� SCL Ϊ�͵�ƽʱ�ı䡣
*/
void i2c_send_byte(unsigned char byte) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        // ����ÿһλ����
        SDA = (byte & 0x80) ? 1 : 0; // �ȷ��͸�λ
        byte <<= 1;
		delay_10us(1);
		
		// ���� SDA �ϵ����ݲ��䣬 ���ڷ���
        SCL = 1;
		delay_10us(1);
		
        // SCL�ɸߵ�ƽ��Ϊ�͵�ƽ�������½���
		// ���Կ�ʼ������һ�η���
        SCL = 0;
		delay_10us(1);
    }
}


// C51 ��Ƭ����ȡһ���ֽڵ����� 
/*
	�ܽ� : 
	1. �� SCL Ϊ�ߵ�ƽ�ڼ䣬�������ݣ�����8�����ݣ�
	   ����Ϊ 1 ,SDA������ ; ����Ϊ 0��SDA�����͡�  
	2. �����ڼ䱣�ִ����ȶ������������߽�������ʱ�� SCL Ϊ�͵�ƽʱ�ı䡣
*/
unsigned char i2c_read_byte() {
    unsigned char i, byte = 0;
    SDA = 1; // ������豸����������
    for (i = 0; i < 8; i++) {
        SCL = 1;
        byte = (byte << 1) | SDA; // ��������
        SCL = 0;
    }
    return byte;
}

//void i2c_init() {
//    // ��ʼ��I2C����
//    SDA = 1;
//    SCL = 1;
//}

void main() {
    unsigned char dat;
    i2c_init(); // ��ʼ��I2C����
    
    i2c_start(); // ������ʼ�ź�
    i2c_send_byte(0xA0); // �����豸��ַ��дģʽ��
    i2c_send_byte(0x00); // �������ݵ�ַ
    i2c_send_byte(0x55); // ��������
    i2c_stop(); // ����ֹͣ�ź�
    
    i2c_start(); // ������ʼ�ź�
    i2c_send_byte(0xA0); // �����豸��ַ��дģʽ��
    i2c_send_byte(0x00); // �������ݵ�ַ
    i2c_start(); // �����ظ���ʼ�ź�
    i2c_send_byte(0xA1); // �����豸��ַ����ģʽ��
    dat = i2c_receive_byte(); // ��������
    i2c_stop(); // ����ֹͣ�ź�
    
    while (1);
}
