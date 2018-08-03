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
 
#ifndef __KEY8_H
#define __KEY8_H
#include "sys.h"

//*���̣�
//*				GPIOB5	(K1)
//*				GPIOB6	(K2)
//*				GPIOB13 (K3)	//GPIOB7  (K3)
//*				GPIOB14	(K4)	//GPIOB8  (K4)
//*				GPIOB9	(K5)
//*				GPIOB10	(K6)
//*				GPIOB11	(K7)
//*				GPIOB12	(K8)

//*Ч���� 			����K1��˳ʱ��ת;
//*			   		����K2����ʱ��ת;
//* 		   		����K3������;
//*			   		����K4������ ;
//*			   		����K5����ͣ;
//*			   		����K6������;
//*			   		����K7����ʱ�ӳ�;
//*			   		����K8����ʱ���٣�


#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
//#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
//#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define KEY5 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define KEY6 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define KEY7 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define KEY8 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)

#define KEY1_Pin GPIO_Pin_5
#define KEY2_Pin GPIO_Pin_6
//#define KEY3_Pin GPIO_Pin_7
#define KEY3_Pin GPIO_Pin_13
//#define KEY4_Pin GPIO_Pin_8
#define KEY4_Pin GPIO_Pin_14
#define KEY5_Pin GPIO_Pin_9
#define KEY6_Pin GPIO_Pin_10
#define KEY7_Pin GPIO_Pin_11
#define KEY8_Pin GPIO_Pin_12


#define KEY_CC			1
#define KEY_CCW			2
#define KEY_INC			3
#define KEY_DEC			4
#define KEY_STOP 		5
#define KEY_START		6
#define KEY_TIMEUP		7
#define KEY_TIMEDOWN	8

// �����ⲿ��������
void GPIO_Key_Init(void);
uint16_t Key8_scan(void);
#endif


