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

#include "IronHand.h"
#include "delay.h"


// ��е�֣�������
// �򿪻�е��
void OpenHand(void)
{
	HAND_OPEN = 1;
	HAND_CLOSE = 0;
	delay_ms(50);	
	HAND_OPEN = 0;
	HAND_CLOSE = 0;
}
// �رջ�е��
void CloseHand(void)
{
	HAND_OPEN = 0;
	HAND_CLOSE = 1;
	delay_ms(50);
	HAND_OPEN = 0;
	HAND_CLOSE = 0;
}
// ���ֻ�е�ֵ�ǰ״̬
void HoldHand(void)
{
	HAND_OPEN = 0;
	HAND_CLOSE = 0;
}


