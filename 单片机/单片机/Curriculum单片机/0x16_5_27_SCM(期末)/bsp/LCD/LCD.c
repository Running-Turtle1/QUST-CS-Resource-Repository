#include "public.h"

/*******************************************************************************
* �� �� ��       : lcd1602_write_cmd
* ��������		 : LCD1602д����
* ��    ��       : cmd��ָ��
* ��    ��    	 : ��

*******************************************************************************/
void lcd1602_write_cmd(u8 cmd)
{
	// ���Բ�ѯ lcd1602 ʱ��ͼ�� дʱ�������б���
	LCD1602_RS=0;//ѡ������
	LCD1602_RW=0;//ѡ��д
	LCD1602_E=0;
	LCD1602_DATAPORT=cmd;//׼������
	delay_10us(100);
	LCD1602_E=1;//ʹ�ܽ�E��������д��
	delay_10us(100);
	LCD1602_E=0;//ʹ�ܽ�E���������д��	
}

/*******************************************************************************
* �� �� ��       : lcd1602_write_data
* ��������		 : LCD1602д����
* ��    ��       : dat������
* ��    ��    	 : ��
*******************************************************************************/

void lcd1602_write_data(u8 dat) 
{
	LCD1602_RS=1;//ѡ������
	LCD1602_RW=0;//ѡ��д
	LCD1602_E=0;
	LCD1602_DATAPORT=dat;//׼������
	delay_10us(100);
	LCD1602_E=1;//ʹ�ܽ�E��������д��
	delay_10us(100);
	LCD1602_E=0;//ʹ�ܽ�E���������д��		
}

/*******************************************************************************
* �� �� ��       : lcd1602_init
* ��������		 : LCD1602��ʼ��
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void lcd1602_init()
{
	lcd1602_write_cmd(0x38);//��������8λ����ʾ2�У�5*7����/�ַ�
	lcd1602_write_cmd(0x0c);//��ʾ���ܿ����޹�꣬�����˸
	lcd1602_write_cmd(0x06);//д�������ݺ������ƣ���ʾ�����ƶ�
	lcd1602_write_cmd(0x01);//����	
}

/*******************************************************************************
* �� �� ��       : lcd1602_clear
* ��������		 : LCD1602����
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void lcd1602_clear()
{
	lcd1602_write_cmd(0x01);	
}

/*******************************************************************************
* �� �� ��       : lcd1602_show_string
* ��������		 : LCD1602��ʾ�ַ�
* ��    ��       : x,y����ʾ���꣬x=0~15��y=0~1;
				   str����ʾ�ַ���
* ��    ��    	 : ��
*******************************************************************************/
void lcd1602_show_string(u8 x,u8 y,u8 *str)
{
	u8 i=0;

	if(y>1||x>15)return;//���в���������ǿ���˳�

	if(y<1)	//��1����ʾ
	{	
		while(*str!='\0')//�ַ�������'\0'��β��ֻҪǰ�������ݾ���ʾ
		{
			if(i<16-x)//����ַ����ȳ�����һ����ʾ��Χ�����ڵڶ��м�����ʾ
			{
				lcd1602_write_cmd(0x80+i+x);//��һ����ʾ��ַ����	
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16);//�ڶ�����ʾ��ַ����	
			}
			lcd1602_write_data(*str);//��ʾ����
			str++;//ָ�����
			i++;	
		}	
	}
	else	//��2����ʾ
	{
		while(*str!='\0')
		{
			if(i<16-x) //����ַ����ȳ����ڶ�����ʾ��Χ�����ڵ�һ�м�����ʾ
			{
				lcd1602_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd1602_write_cmd(0x80+i+x-16);	
			}
			lcd1602_write_data(*str);
			str++;
			i++;	
		}	
	}				
}

/*LCD1602 ��ʾDS1302���ں�ʱ�� ����*/
//---���ʱ�������� ���λ��дλ;-------//
//u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
// u8 gDS1302_TIME[7] = {0x01, 0x19, 0x20, 0x21, 0x05, 0x24, 0x20};
// //---DS1302ʱ�ӳ�ʼ��2021��05��20��������13��51��47�롣---//
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
// u8 gDS1302_TIME[7] = {0x47, 0x51, 0x13, 0x20, 0x04, 0x05, 0x21};
int temperture; // �¶�;
u8 i=0;
void LcdDisplay(){
	lcd1602_write_cmd(0x80+0X40); // ����ָ��������ǽ�LCD1602�Ĺ���ƶ����ڶ��еĵ�һ���ַ�λ�á�
	lcd1602_write_data('0'+gDS1302_TIME[2]/16);				//ʱ
	lcd1602_write_data('0'+(gDS1302_TIME[2]&0x0f));				 
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[1]/16);				//��
	lcd1602_write_data('0'+(gDS1302_TIME[1]&0x0f));	
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[0]/16);				//��
	lcd1602_write_data('0'+(gDS1302_TIME[0]&0x0f));

	lcd1602_write_cmd(0x80); // ������ƶ�����һ�еĵ�һ���ַ�λ��
	lcd1602_write_data('2');			//��
	lcd1602_write_data('0');
	lcd1602_write_data('0'+gDS1302_TIME[6]/16);			 
	lcd1602_write_data('0'+(gDS1302_TIME[6]&0x0f));
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[4]/16);			//��
	lcd1602_write_data('0'+(gDS1302_TIME[4]&0x0f));
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[3]/16);			//��
	lcd1602_write_data('0'+(gDS1302_TIME[3]&0x0f));
	
	lcd1602_write_data(' ');
	if((gDS1302_TIME[5]&0x07) == 1){
		lcd1602_write_data('M');
		lcd1602_write_data('o');
		lcd1602_write_data('n');
	}
	else if((gDS1302_TIME[5]&0x07) == 2){
		lcd1602_write_data('T');
		lcd1602_write_data('u');
		lcd1602_write_data('e');
		lcd1602_write_data('s');
	}
	else if((gDS1302_TIME[5]&0x07) == 3){
		lcd1602_write_data('W');
		lcd1602_write_data('e');
		lcd1602_write_data('d');
		lcd1602_write_data('n');
	}
	else if((gDS1302_TIME[5]&0x07) == 4){
		lcd1602_write_data('T');
		lcd1602_write_data('h');
		lcd1602_write_data('u');
		lcd1602_write_data('r');
	}
	else if((gDS1302_TIME[5]&0x07) == 5){
		lcd1602_write_data('F');
		lcd1602_write_data('r');
		lcd1602_write_data('i');
	}
	else if((gDS1302_TIME[5]&0x07) == 6){
		lcd1602_write_data('S');
		lcd1602_write_data('a');
		lcd1602_write_data('t');
	}
	else{
		lcd1602_write_data('S');
		lcd1602_write_data('u');
		lcd1602_write_data('n');
	}
	//lcd1602_write_cmd(0x8f); // 0x8? , ���� ? ����� ? ��λ����ʾʲô, ? = [0, f]
	//lcd1602_write_data('0'+(gDS1302_TIME[5]&0x07));	//����
	
		i++;
        if(i%50==0){
        //���һ��ʱ���ȡ�¶�ֵ�����ʱ��Ҫ�����¶ȴ�����ת���¶�ʱ��
            temperture=ds18b20_read_temperture()*10;//�����¶�ֵС����һλ
            
        }
		lcd1602_write_cmd(0x89 + 0x40); // �� 9 ����ʼд
        
        
    //  lcd1602_write_data('0' + (int)temp_value%10); //��λ
        
        if(temperture<0)//���¶�
        {
            temperture=-temperture;
            lcd1602_write_data('-'); //��λ
        }
        else{
             
        }
        
        
        lcd1602_write_data('0' + temperture/1000); //��λ
        lcd1602_write_data('0' + temperture%1000/100); //ʮλ
        lcd1602_write_data('0' + temperture%1000%100/10); //��λ+С����
        lcd1602_write_data('.');
        lcd1602_write_data('0' + temperture%1000%100%10); //С�����һλ
//      lcd1602_write_data('0' + temp_value%10); //С�������λ
}

