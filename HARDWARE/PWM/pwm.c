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

#include "pwm.h"
#include "GPIO_Motor.h"

// Ĭ�Ϲر������ʹ��
// ռ�ձ�50%
/*****************************************************************************
						PWM   By   TIM2
******************************************************************************/

void TIM2_PWM_Config_Init(uint16_t arr, uint16_t psc)
{
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* 1. ����TIM2����ʱ�ӹ��ܣ�����MotorX_STEPΪ����������� */
	TIM2_GPIO_PWM_Init();
	
	/* 2. �������Ҫ������TIMx_CHx����ӳ�䵽PXx��---->����δ���ã�����Ĭ������˿� */
	
	/* 3. ��ʼ��TIMx������TIMx��ARR��PSC(�ο���ʱ���ж�) */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	//ʹ��TIM2ʱ��
	
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��	
	// ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1),������һ����������
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָTDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* 4. ����TIMx_CHx��PWMģʽ��ʹ��TIMx��CHx������ѡ��ͨ��2����� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܣ�����ʱ�ر����ʹ�ܣ���ֹ���һ����������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	//TIM_OCInitStructure.TIM_Pulse =1800;               //���ô�װ�벶��ȽϼĴ���������ֵ,ȡֵ������0x0000~0xFFFF֮�䣬ռ�ձ�1800/3600
	TIM_OCInitStructure.TIM_Pulse =arr/2;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);          //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	// ����������TIM_Pulseֵ�����ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	/* 5. ʹ��TIMx��ʱ�� */
	
	TIM_Cmd(TIM2,ENABLE);
	
}

/*****************************************************************************
						PWM   By   TIM3
******************************************************************************/




void TIM3_PWM_Config_Init(uint16_t arr, uint16_t psc)
{
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* 1. ����TIM3����ʱ�ӹ��ܣ�����MotorX_STEPΪ����������� */
	TIM3_GPIO_PWM_Init();
	
	/* 2. �������Ҫ������TIMx_CHx����ӳ�䵽PXx��---->����δ���ã�����Ĭ������˿� */
	
	/* 3. ��ʼ��TIMx������TIMx��ARR��PSC(�ο���ʱ���ж�) */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	//ʹ��TIM3ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��		
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָTDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* 4. ����TIMx_CHx��PWMģʽ��ʹ��TIMx��CHx������ѡ��ͨ��2����� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�

	TIM_OCInitStructure.TIM_Pulse = arr/2;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);          //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	// ����������TIM_Pulseֵ�����ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	/* 5. ʹ��TIMx��ʱ�� */
	
	TIM_Cmd(TIM3,ENABLE);
	
}


/*****************************************************************************
						PWM   By   TIM4
******************************************************************************/

void TIM4_PWM_Config_Init(uint16_t arr, uint16_t psc)
{
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	/* 1. ����TIM4����ʱ�ӹ��ܣ�����MotorX_STEPΪ����������� */
	TIM4_GPIO_PWM_Init();
	
	/* 2. �������Ҫ������TIMx_CHx����ӳ�䵽PXx��---->����δ���ã�����Ĭ������˿� */
	
	/* 3. ��ʼ��TIMx������TIMx��ARR��PSC(�ο���ʱ���ж�) */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	//ʹ��TIM4ʱ��
	
	TIM_TimeBaseStructure.TIM_Period = arr-1;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָTDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	/* 4. ����TIMx_CHx��PWMģʽ��ʹ��TIMx��CHx������ѡ��ͨ��2����� */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ��
	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	

	TIM_OCInitStructure.TIM_Pulse = arr/2;
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);          //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	
	
	// ����������TIM_Pulseֵ�����ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	/* 5. ʹ��TIMx��ʱ�� */
	
	TIM_Cmd(TIM4,ENABLE);
	
}

