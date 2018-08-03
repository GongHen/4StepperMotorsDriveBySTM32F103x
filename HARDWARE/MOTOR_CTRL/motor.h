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

#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"


// ��ôд����̫���ˣ���������ŵ��ṹ����
// ��Ϊ�ⲿ�ɱ����������ɱ�������Ͳ��ɱ����

// 1. �ⲿ�ɱ����������Ҫʵʱ�޸ģ����ڽṹ���ⲿ�������޸ģ��������ⲿ��ֵ�ı�����ǰ״̬

// 2. ����ɱ������Ҳ������Ҫͨ����ȡ�����Ӧ�Ĵ�����ǰ��ֵ��ʵʱ�޸ģ����ⲿ�����޸ģ������ڳ����ȡ��ǰ״̬

// 3. ���ɱ�������ڳ�ʼ����Ͳ��ٸı���
typedef __packed struct {
	
	/* �ⲿ�ɱ���� */
	unsigned char direction;		// �������
	uint16_t speed;					// ����ٶȣ��ı�psc,����pwm����Ƶ�ʣ����ı��ٶ�
	float destn;					// ��������ƶ�Ŀ�ĵ����꣨mm��
	int totalTime;					// ����ƶ�������Ŀ�ĵ��ܹ�����ʱ��(ms)
	unsigned char nextMove;
	
	
	/* ����ɱ���� */
	uint16_t running;				// �����ǰ����״̬������/ֹͣ���ʱ���ֵ�ᱻʵʱ�޸�
									// Ϊ�˲����ҳ�����Щ��ȡ��״̬������ʾ���������޸�״̬
	unsigned char isResetPoint;		// ����Ƿ��ڸ�λ�㣬1/�ڣ�0/����
	unsigned char isDestn;			// ����Ƿ񵽴�ָ������λ��
	
	/* ���ɱ���� */
	unsigned char id;				// ���id
	TIM_TypeDef* MOTOx;				// ���pwm����������ʱ��
	FunctionalState enable;			// ���ʹ��,Ĭ�ϴ�

} MOTOR_CONTROL;

// �����Ӧ�Ķ�ʱ���궨��
#define MOTOX	TIM2
#define MOTOY	TIM3
#define MOTOZ	TIM4

// �������궨��
#define FORWARD 	1
#define	REVERSE 	0

// �������״̬�궨��
#define RUNNING 	((uint16_t)1)
#define	STOPPING 	((uint16_t)0)

// ����ṹ���������������
extern volatile MOTOR_CONTROL motor1;
extern volatile MOTOR_CONTROL motor2;
extern volatile MOTOR_CONTROL motor3;

void Init_Motor_Struct(unsigned char MOTOID);

#endif

