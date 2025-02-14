#include "reg52.h"

/******** ԭ���� : https://blog.csdn.net/m0_50562428/article/details/130895466 ********/

typedef unsigned char u8;
typedef unsigned int u16;

// ����ܶ�ѡ����
u8 code Array[] = { 
    // 0 - f
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

/*
	������� P1 ����
	<�� : P17 - P14>
	<�� : P13 - P10>
	1 �� -> P17		1 �� -> P13
	2 �� -> P16		2 �� -> P12
	3 �� -> P15		3 �� -> P11
	4 �� -> P14		4 �� -> P10
*/

void delay_10us(u16 x){
	while(x --);
}


void main(){
	while(1){
		// 0xf7 : 1111 0111, ��һ�н�ͨ�͵�ƽ
		P1 = 0xf7;
		if(P1 != 0xf7){ // ��ⰴ���Ƿ���
			delay_10us(1000); // ��ʱ����
			while(P1 == 0x77){ // ��ⰴ�� 1 : 0111 0111  
                // ��ʾ LED ���� 1
                P0 = Array[0];
            }
            while(P1 == 0xb7){ // ��ⰴ�� 2 : 1011 0111
                // ��ʾ LED ���� 2
                P0 = Array[1];
            }
            while(P1 == 0xd7){ // ��ⰴ�� 3 : 1101 0111
                // ��ʾ LED ���� 3
                P0 = Array[2];
            }
            while(P1 == 0xe7){ // ��ⰴ�� 4 : 1110 0111
                // ��ʾ LED ���� 4
                P0 = Array[3];
            }
		}
		
		/*********** ���ռ���һ�еķ�ʽ����ʣ���� ************/
		
		// 0xfb : 1111 1011, �ڶ��н�ͨ�͵�ƽ
		P1 = 0xfb;
		if(P1 != 0xfb){  
			delay_10us(1000); 
			while(P1 == 0x7b){  
                P0 = Array[4];
            }
            while(P1 == 0xbb){  
                P0 = Array[5];
            }
            while(P1 == 0xdb){  
                P0 = Array[6];
            }
            while(P1 == 0xeb){  
                P0 = Array[7];
            }
		}
		
		// 0xfd : 1111 1101, �����н�ͨ�͵�ƽ
		P1 = 0xfd;
		if(P1 != 0xfd){  
			delay_10us(1000);  
			while(P1 == 0x7d){   
                P0 = Array[8];
            }
            while(P1 == 0xbd){  
                P0 = Array[9];
            }
            while(P1 == 0xdd){  
                P0 = Array[10];
            }
            while(P1 == 0xed){  
                P0 = Array[11];
            }
		}
		
		// 0xfd : 1111 1110, �����н�ͨ�͵�ƽ
		P1 = 0xfe;
		if(P1 != 0xfe){  
			delay_10us(1000);  
			while(P1 == 0x7e){   
                P0 = Array[12];
            }
            while(P1 == 0xbe){  
                P0 = Array[13];
            }
            while(P1 == 0xde){  
                P0 = Array[14];
            }
            while(P1 == 0xee){  
                P0 = Array[15];
            }
		}
	}
    
}