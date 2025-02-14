#include "public.h"

//�������鱣�浽Flash��
//�������������ʾ0~F�Ķ�������
u8 code g_smg_duan_code[]={
   	//0 ,1	 ,2   ,3   ,4   ,5   ,6   ,7   ,8   ,9   
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	//A ,B   ,C   ,D   ,E   ,F
	0x77,0x7c,0x39,0x5e,0x79,0x71};

/*************************************************
* �� �� ��: void SMG_1_2_refresh()
* ��������: ��̬�������ʾ
* ��    ��: ��
* ��    ��: ��
*************************************************/
void smg_1_2_refresh()
{
	//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�					  
	//10ms=10*100*10us����10ms�𽥼��٣��۲�Ч��
	//�������ԣ�1ms=10*100usʱ��Ч��������
	delay_10us(100);
	//��Ӱ�ӣ���ֹ�ٶ�̫���ˣ�����Ӱ��
	//SMG_A_2_DP_PORT=0x00;
}
/*************************************************
* �� �� ��: SMG_1_2_display
* ��������: ��̬�������ʾ
* ��    ��: ��
* ��    ��: ��
*************************************************/
void smg_1_2_display(u8 pos,u8 dat)
{
	//u8 i=0;
	//for(i=0;i<8;i++)
	{
	   	switch(pos)//λѡ
		{
			case 0: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 1: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 2: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 3: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
			case 4: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 5: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 6: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 7: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
		 }
		//���Ͷ�ѡ����
		SMG_A_2_DP_PORT=g_smg_duan_code[dat];
		//�������ԣ�1ms=10*100usʱ��Ч��������
		//delay_10us(10);
		//��Ӱ�ӣ���ֹ�ٶ�̫���ˣ�����Ӱ��
		//SMG_A_2_DP_PORT=0x00;	
		}
}

/*******************************************************************************
* �� �� ��       : smg_display
* ��������		 : ��̬�������ʾ
* ��    ��       : dat��Ҫ��ʾ������
				   pos������ʼ�ڼ���λ�ÿ�ʼ��ʾ����Χ1-8
* ��    ��    	 : ��
*******************************************************************************/
void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	//pos_temp(0~7)
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<8;i++)
	{
	   	switch(i)//λѡ
		{
			case 0: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 1: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 2: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 3: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
			case 4: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 5: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 6: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 7: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
		}
		//���Ͷ�ѡ����
		SMG_A_2_DP_PORT=g_smg_duan_code[dat[i-pos_temp]];
		//��ʱ1msʱ�䣬�ȴ���ʾ�ȶ�
		delay_10us(100);
		//��Ӱ
		SMG_A_2_DP_PORT=0x00;
	}
}
