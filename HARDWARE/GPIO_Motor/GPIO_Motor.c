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

//*ʹ�õ�IO��  	�����GPIOC��

//				(MotorX)A4988--> GPIOC0-GPIO1
//				GPIOC0 	--> ENABLE
//				GPIOA1 	--> STEP(TIM2)
//				GPIOC1	--> DIR
//				
//				(MotorY)A4988--> GPIOC2-GPIO3
//				GPIOC2 	--> ENABLE
//				GPIOA7 	--> STEP(TM3)
//				GPIOC3	--> DIR
//				
//				(MotorZ)A4988--> GPIOC4-GPIO5
//				GPIOC4 	--> ENABLE
//				GPIOB7 	--> STEP(TIM4)
//				GPIOC5	--> DIR

#include "GPIO_Motor.h"
#include "IronHand.h"

// ����ʹ�ܺͷ���ĵ������������
void GPIO_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// ��ӦIO�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	// ����A4988�����Ĳ����������ʼ��DIR������ENABLE����(ENABLE��DIR����GPIOC��)
	GPIO_InitStructure.GPIO_Pin = MotorX_ENABLE|MotorX_DIR;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);				
	GPIO_ResetBits(GPIOC,MotorX_ENABLE|MotorX_DIR);
	
	GPIO_InitStructure.GPIO_Pin = MotorY_ENABLE|MotorY_DIR;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,MotorY_ENABLE|MotorY_DIR);
	
	GPIO_InitStructure.GPIO_Pin = MotorZ_ENABLE|MotorZ_DIR;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,MotorZ_ENABLE|MotorZ_DIR);
}

// ���pwm�����źŵĵ������������
void TIM2_GPIO_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   	//ʹ��GPIOA��ʱ�� 
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    	//����ʱ�Ӳ���Ҫʹ��
	
	GPIO_InitStructure.GPIO_Pin = MotorX_STEP; //TIM2��ͨ��PWM��������˿�PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void TIM3_GPIO_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   	//ʹ��GPIOA��ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = MotorY_STEP; //TIM3��ͨ��PWM��������˿�PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void TIM4_GPIO_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   	//ʹ��GPIOB��ʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = MotorZ_STEP; //TIM4��ͨ��PWM��������˿�PB7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

void GPIO_IronHand_Init() 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// ��ӦIO�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	// ��е��GPIOC6(HAND_OPEN)����GPIOC7(HAND_CLOSE)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);				
	GPIO_ResetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7);
}

