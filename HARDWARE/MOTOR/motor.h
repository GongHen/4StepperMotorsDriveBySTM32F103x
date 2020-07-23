/*
 * @ Author: luolichq
 * @ Description: ��������˲�������ṹ��MOTOR���ͳ�ʼ��
 * @ More:
 * 		motor_camera	PULSE-		ENA-	DIR-		
 *						PI5			PD3		PD7
 *		motor_rail		PULSE-		ENA-	DIR-
 *						PI6			PD11	PF11
 */
#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f4xx_hal.h"

// ö�ٱ��������ID��
typedef enum {
	MOTOR_RAIL = 0U,
	MOTOR_CAMERA
} MotorID;

// ö�ٱ������������
typedef enum {
	FORWARD = 0U,
	BACKWARD
} MotorDirection;

// ö�ٱ���������˶�״̬
typedef enum {
  RUNNING = 0U, 
  STOPPING = !RUNNING
} MotorStatus;

typedef enum {
	STOPTIM = 0U,
	STARTTIM = !STOPTIM
} MotorTIMStatus;

/*
 * ��������ṹ������ MOTOR ����
 */
typedef __packed struct
{
	MotorID _mtId;				// ���ID
	TIM_TypeDef* _mtTimer;		// ������õĶ�ʱ��
	MotorStatus _mtState; 		// �������״̬
	MotorDirection _mtDir;		// �������
	FunctionalState _mtEnable;	// ���ʹ��
	uint32_t _mtSpeed;			// ����ٶȣ��ı�psc,����pwm����Ƶ�ʣ����ı��ٶ�
	MotorTIMStatus _mtTIMState; // _mtTIMState = STOPTIM��������籣�֣�STARTTIM��������ת
}MOTOR;

// ����ṹ���������������
extern volatile MOTOR motor_rail;
extern volatile MOTOR motor_camera;

// �������������MOTOR���ͽṹ�����������ʼ��
void MOTOR_Struct_Init(MotorID motorId);

#endif


