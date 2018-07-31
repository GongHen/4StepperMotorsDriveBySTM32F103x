/*
 *
 *  Copyright 2018���̺�������������ҵ��ѧ�����ڣ�
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

// ��ʼ��8x1���̶�ӦIO���ã����ð���ɨ�����

//*���̣�
//*				GPIOB5	(K1)
//*				GPIOB6	(K2)
//*				GPIOB13 (K3)	//GPIOB7  (K3)
//*				GPIOB14	(K4)	//GPIOB8  (K4)
//*				GPIOB9	(K5)
//*				GPIOB10	(K6)
//*				GPIOB11	(K7)
//*				GPIOB12	(K8)

//*     Ч���� 		����K1��˳ʱ��ת;
//*			   		����K2����ʱ��ת;
//* 		   		����K3������;
//*			   		����K4������ ;
//*			   		����K5����ͣ;
//*			   		����K6������;
//*			   		����K7����ʱ�ӳ�;
//*			   		����K8����ʱ���٣�

#include "key8.h"
#include "delay.h"




void GPIO_Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// ��ӦIO�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	

	// KEY1~KEY8��ӦIO�˿ڳ�ʼ������ 
	GPIO_InitStructure.GPIO_Pin = KEY1_Pin|KEY2_Pin|KEY3_Pin|KEY4_Pin|KEY5_Pin|KEY6_Pin|KEY7_Pin|KEY8_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	// 	��������
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//	GPIOB
}


/*******************************************************************************
* �� �� ��         : Key8_scan
* ��������         : ��������*8ɨ����򣬰������¶�ӦIO��ֵΪ0
* ��    ��         : ��
* ��    ��         : 0(�޼�����)/������Ӧ��־ֵ
*******************************************************************************/
uint16_t Key8_scan() 
{
		// ��֧����������
		if(KEY1 == 0 ||KEY2 == 0 ||KEY3 == 0 ||KEY4 == 0 ||KEY5 == 0 ||KEY6 == 0 ||KEY7 == 0 ||KEY8 == 0) 
		{
			delay_ms(15);
			if(KEY1 == 0)	{while(KEY1 == 0){;} 	return KEY_CC;}
			if(KEY2 == 0) 	{while(KEY2 == 0){;} 	return KEY_CCW;}
			if(KEY3 == 0) 	{while(KEY3 == 0){;} 	return KEY_INC;}
			if(KEY4 == 0) 	{while(KEY4 == 0){;} 	return KEY_DEC;}
			if(KEY5 == 0) 	{while(KEY5 == 0){;} 	return KEY_STOP;}
			if(KEY6 == 0) 	{while(KEY6 == 0){;} 	return KEY_START;}
			if(KEY7 == 0) 	{while(KEY7 == 0){;} 	return KEY_TIMEUP;}
			if(KEY8 == 0) 	{while(KEY8 == 0){;} 	return KEY_TIMEDOWN;}
		}		
		return  0;				// �ް������� Key8_ret ���� 0
}



	

