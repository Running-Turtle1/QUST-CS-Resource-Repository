#ifndef __TIMER_H__
#define __TIMER_H__


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
void T0_1ms_init();
void T0_50ms_init();
void T0_isr();
 
#endif