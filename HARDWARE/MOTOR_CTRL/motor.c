/*
 *
 *  Copyright 2018���̺�������������ҵ��ѧ
 *  All Rights Reserved.
 */
/*
 * *******************************֣������****************************************
 
 * �ó���Ϊ������д�������˴����ľ������ֽ��乫����������Ҳο�ѧϰ��
 * �κθ��˺���֯����δ����Ȩ���˳���ת�أ���������ҵ��Ϊ��
 * 
 * ���ڱ���ˮƽ���ޣ�����������ִ��󣬿���ͨ���������ϵ��ʽ��ϵ����
 * лл���ָ����
 *
 * ���䣺18s153717@stu.hit.edu.cn
 * github��https://github.com/clearcumt
 * ���ͣ�https://www.cnblogs.com/loveclear/
 * 
 * ******************************************************************************
 */
 
#include "motor.h"

#undef NULL
#define NULL 0


/*******************************************************************************
* �� �� ��         : Init_Motor_Struct
* ��������         : XYZ�ᣬ������������Ľṹ�����������ʼ��
* ��    ��         : motor.id�������id�ţ�1->x, 2->y, 3->z�� 
* ��    ��         : ��
*******************************************************************************/
void Init_Motor_Struct(unsigned char MOTOID)
{
	volatile MOTOR_CONTROL* pmotor = NULL;
	switch(MOTOID)
	{
		case 1:
			pmotor = &motor1;
			pmotor->id = 1;
			pmotor->MOTOx = MOTOX;
			break;
		case 2:
			pmotor = &motor2;
			pmotor->id = 2;
			pmotor->MOTOx = MOTOY;
			break;
		case 3:
			pmotor = &motor3;
			pmotor->id = 3;
			pmotor->MOTOx = MOTOZ;

			break;
	}
	pmotor->direction = REVERSE;
	pmotor->speed = 956;
	pmotor->running = STOPPING;
	pmotor->enable = ENABLE;
	pmotor->destn = 0;
	pmotor->totalTime = 0;
	pmotor->isResetPoint = 1;
	pmotor->isDestn = 0;
	pmotor->nextMove = 0;

}



