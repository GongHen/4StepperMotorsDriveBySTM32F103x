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

//				��е�֣��ŷ��������ź�ʹ��GPIOB��
//				GPIOB8	--> IRONHAND(TIM4 CH3)

#ifndef __IRONHAND_H
#define __IRONHAND_H

#include "sys.h"

#define HAND_OPEN 	PCout(6)
#define HAND_CLOSE 	PCout(7)

void OpenHand(void);
void CloseHand(void);
void HoldHand(void);

#endif



