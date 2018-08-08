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

//				��е�֣����˲�������������ź�ʹ��GPIOC��
//				GPIOC6	--> MotorH_A
//				GPIOC7	--> MotorH_B	
//				GPIOC8	--> MotorH_C
//				GPIOC9	--> MotorH_D

#ifndef __IRONHAND_H
#define __IRONHAND_H

#include "sys.h"

#define MotorH_BitA PCout(6)
#define MotorH_BitB PCout(7)
#define MotorH_BitC PCout(8)
#define MotorH_BitD PCout(9)

void Get_Seal_By(u16 Dir,u16 Speed,u16 Steps);
void Set_Motor_CWPort(int k);
void Set_Motor_CCWPort(int k);

#endif



