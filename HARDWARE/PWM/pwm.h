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
 
// ��ʼ������pwm�����A4988�������������STEP����
// ����TIMx_CH2����PWM�����źţ���������STEP������Ĭ������˿���
//*ʹ�õ�IO��  	�����GPIOC��

//				(MotorX)A4988--> GPIOC0-GPIO1
//						GPIOA1 	--> STEP(TIM2)
//				
//				(MotorY)A4988--> GPIOC2-GPIO3
//						GPIOA7 	--> STEP(TM3)
//				
//				(MotorZ)A4988--> GPIOC4-GPIO5
//						GPIOB7 	--> STEP(TIM4)

#ifndef __PWM_H
#define __PWM_H


#include "sys.h"
#include "GPIO_Motor.h"


#define OC1_ENR	((uint16_t)0)		// ѡ��Ƚ����ʹ��ͨ��
#define OC2_ENR	((uint16_t)4)
#define OC3_ENR	((uint16_t)8)
#define OC4_ENR	((uint16_t)12)



void TIM2_PWM_Config_Init(uint16_t arr, uint16_t psc);
void TIM3_PWM_Config_Init(uint16_t arr, uint16_t psc);
void TIM4_PWM_Config_Init(uint16_t arr, uint16_t psc);


#endif


