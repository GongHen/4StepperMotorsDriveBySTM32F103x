/*
 * @ Author: luolichq
 * @ Description: ��������˲�������ṹ��MOTOR���ͳ�ʼ��
 * @ More:
 * 		motor_camera	PULSE-		ENA-	DIR-		
 *						PI5			PD3		PD7
 *		motor_rail		PULSE-		ENA-	DIR-
 *						PI6			PD11	PF11
 */
#include "motor.h"

#undef NULL
#define NULL 0

/*******************************************************************************
* �� �� ��         : Init_Motor_Struct
* ��������         : �������������MOTOR���ͽṹ�����������ʼ��
* ��    ��         : motorId
* ��    ��         : ��
*******************************************************************************/
void MOTOR_Struct_Init(MotorID motorId)
{
	volatile MOTOR* pmotor = NULL;
	switch(motorId) 
	{
		case MOTOR_RAIL:
			pmotor = &motor_rail;
			pmotor->_mtId = MOTOR_RAIL;
			pmotor->_mtDir = FORWARD;
			pmotor->_mtTIMState = STARTTIM;
			break;
		case MOTOR_CAMERA:
			pmotor = &motor_camera;
			pmotor->_mtId = MOTOR_CAMERA;
			pmotor->_mtDir = FORWARD;
			pmotor->_mtTIMState = STARTTIM;
			break;
	}
	pmotor->_mtTimer = TIM8;
	pmotor->_mtEnable = DISABLE;
	pmotor->_mtState = STOPPING;
	pmotor->_mtSpeed = 956;
} 

