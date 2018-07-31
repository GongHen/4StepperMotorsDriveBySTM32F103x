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
 
 
#include "timer1.h"
#include "GPIO_Motor.h"
#include "motor.h"
#include "motor_ctrl.h"



void TIM1Nvic_Config_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;     // TIM1�����ж�ͨ��,���������stm32f10x.h��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   // ��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      // �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     // IQRͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);
}

void TIM1_Config_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* 1. ��ʱ�������ϵͳʱ��ʹ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);		// ע��TIM1�ǹ�����APB2Ԥ��Ƶ������������
    /* 2. ��ʱ��TIM1��ʼ�� */
	
    TIM_TimeBaseStructure.TIM_Period = arr-1;     // �Զ���װ����ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc-1;  // Ԥ��Ƶϵ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // CKD[1:0]�� ʱ�ӷ�Ƶ���� (Clock division)����CK_INT�й�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     // ���ϼ���ģʽ
	//�߼���ʱ��TIM1����ͨ��ʱ��TIM3�Ȳ�ͬ���ǣ�����Ҫ��ʼ�����ظ���������
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;		// �ظ���������
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);

	/* ʹ��ǰ����������жϱ�־λ */
    TIM_ClearFlag(TIM1,TIM_FLAG_Update);		//ʹ��ǰ����жϱ�־λ������һ�����жϺ����������ж�
	
	/* 4. ��������ж�ʹ�� */
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);

    /* 5. �ж����ȼ����� */
    TIM1Nvic_Config_Init();

    /* 6. ��/ʹ��TIM3 */
    TIM_Cmd(TIM1,ENABLE);
}

// �жϷ����ӳ��������ο������ļ�startup_stm32f10x_md.s
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);	
		if(count_time == motor1.totalTime * 1000)
		{
			Stop_Motor_withS(MOTOX);
			if(motor1.nextMove == 0)		// �����������̣�����Ŀ�ĵ�ֹͣ
			{
				motor1.isDestn = 1;
			}
			if(motor1.nextMove == 1)		// ����Ƿ�����̣����︴λ��ֹͣ
			{
				motor1.isResetPoint = 1;
				motor1.nextMove = 0;
				if(motor1.totalTime > motor2.totalTime)
				{
					TIM_Cmd(TIM1,DISABLE);	// ���1�õ�ʱ�䳤�����λֹͣʱ�رն�ʱ��
				}
			}
		}
		
		if(count_time == motor2.totalTime * 1000)
		{
			Stop_Motor_withS(MOTOY);
			if(motor2.nextMove == 0)
			{
				motor2.isDestn = 1;
			}
			if(motor2.nextMove == 1)
			{
				motor2.isResetPoint = 1;
				motor2.nextMove = 0;
				if(motor2.totalTime > motor1.totalTime)
				{
					TIM_Cmd(TIM1,DISABLE);
				}
			}
			
		}

		count_time ++;
	}
}
