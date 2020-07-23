/*
 * @ Author: luolichq
 * @ Description: ��������˲�������ṹ��MOTOR���ͳ�ʼ��
 * @ More:
 * 		motor_camera	PULSE-		ENA-	DIR-		
 *						PI5			PD3		PD7
 *		motor_rail		PULSE-		ENA-	DIR-
 *						PI6			PD11	PF11
 */
#include "motor_ioinit.h"

TIM_HandleTypeDef tim8_handler;

/*
 * ���岽�����DIR��ENA�ڶ�Ӧ��GPIO�ڣ���ʼ���ṹ�����
 */
void MOTOR_CTRL_GPIO_Init(void)
{
	/* ���岽�����DIR��ENA�ڶ�Ӧ��GPIO�ڣ���ʼ���ṹ����� */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* ʹ��GPIO��Ӧ��IO�˿�ʱ�� */
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/* ����PD3��PD7��PD11��PF11���������ѹΪ�͵�ƽ */
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_7, GPIO_PIN_SET);

	/* PF11���ŵ�IOģʽ */
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* ����PD3��PD7��PD11���ŵ�IOģʽ */
	GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/*
 * ���岽�����PULSE�ڶ�Ӧ��GPIO�ڣ���ʼ���ṹ�����
 */
void MOTOR_PULSE_GPIO_Init(void) 
{
	/* ���岽�����PULSE�ڶ�Ӧ��GPIO�ڣ���ʼ���ṹ����� */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* ʹ��GPIO��Ӧ��IO�˿�ʱ�� */
	__HAL_RCC_GPIOI_CLK_ENABLE();

	/* ����PI5��PI6���ŵ�IOģʽ */
	GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
	
	HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);		
}


/*
 * ���岽�����PWM��Ӧ�Ķ�ʱ��TIM8�Ľṹ�����
 */
void MOTOR_TIM8PWM_Init(uint32_t arr, uint32_t psc)
{
	TIM_OC_InitTypeDef TIM_OCInitStructure = {0};
	
	/* ����TIM8���ù��ܣ�����PI5��PI6����Ϊ����������� */
	MOTOR_PULSE_GPIO_Init();
	
	/* ʹ��TIM8ʱ�� */
	__HAL_RCC_TIM8_CLK_ENABLE();

	/* 3. ��ʼ��TIM8������TIMx��ARR��PSC */
	tim8_handler.Instance = TIM8;
	tim8_handler.Init.Prescaler = psc-1; //Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��
	tim8_handler.Init.Period = arr - 1; //�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	tim8_handler.Init.CounterMode = TIM_COUNTERMODE_UP; //���ϼ���ģʽ
	tim8_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //ʱ�ӷָ����Ϊ0
	tim8_handler.Init.RepetitionCounter = 0;
	tim8_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; // �����Զ���װ��ģʽ
	HAL_TIM_PWM_Init(&tim8_handler);
	
	/* 4. ����TIM8_CHx��PWMģʽ��ʹ��TIM8_CHx��� */
	TIM_OCInitStructure.Pulse = arr/2; //���ô�װ�벶��ȽϼĴ���������ֵ��ռ�ձȣ�,ȡֵ������0x0000~0xFFFF֮��
	TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1; //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_HIGH; // �����������
	TIM_OCInitStructure.OCFastMode = TIM_OCFAST_DISABLE; 
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_RESET; //ѡ�����״̬�µ÷ǹ���״̬
	TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET; //ѡ�񻥲�����״̬�µ÷ǹ���״̬
	HAL_TIM_PWM_ConfigChannel(&tim8_handler, &TIM_OCInitStructure, TIM_CHANNEL_1); // ʹ��TIM_CHx��Ԥװ�ؼĴ���
	HAL_TIM_PWM_ConfigChannel(&tim8_handler, &TIM_OCInitStructure, TIM_CHANNEL_2);
	
	/* ʹ��TIM8_CHx�Ķ�ʱ�� */
	HAL_TIM_PWM_Start(&tim8_handler, TIM_CHANNEL_1); 
	HAL_TIM_PWM_Start(&tim8_handler, TIM_CHANNEL_2);
}
