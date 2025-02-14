#include "public.h"

/******************************************************
�������ƣ�void step_motor_4_beat_send_pulse(u8 dir,u8 step)
�������ܣ��������-��������-���Ƴ���
����	: 	u8 dir
			dir=1:��ʱ����ת
			dir=0:˳ʱ����ת
			u8 step
���	��void
******************************************************/
void step_motor_4_beat_send_pulse(u8 dir,u8 step)
{
	u8 temp=step;
	
	if(dir==0)	//���Ϊ��ʱ����ת
		temp=3-step;//���������ź�
	switch(temp)//8�����Ŀ��ƣ�
	{
		//->D
		case 0: STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//->C
		case 1: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//B
		case 2: 
			   	STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//CB
		case 3: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		 //ֹͣ����
		default:
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;	
	}			
}
/******************************************************
�������ƣ�void step_motor_8_beat_send_pulse(u8 dir,u8 step)
�������ܣ��������-��������-���Ƴ���
����	: 	u8 dir
			dir=1:��ʱ����ת
			dir=0:˳ʱ����ת
			u8 step
���	��void
******************************************************/
void step_motor_8_beat_send_pulse(u8 dir,u8 step)
{
	u8 step_temp=step;
	if(dir=0)
	{
	   step_temp=7-step;
	}
	switch(step_temp)
	{
		//->D
		case 0: STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//->DC
		case 1: 
				STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//C
		case 2: 
			   	STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//CB
		case 3: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//B
		case 4: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//BA
		case 5: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=1;
				break;
		//A
		case 6: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		//AD
		case 7: 
				STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		 //ֹͣ����
		default:
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;				
	}	
}
