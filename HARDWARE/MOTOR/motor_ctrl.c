/*
 * @ Author: luolichq
 * @ Description: ��������˲�������ṹ��MOTOR���ͳ�ʼ��
 * @ More:
 * 		motor_camera	PULSE-		ENA-	DIR-		
 *						PI5			PD3		PD7
 *		motor_rail		PULSE-		ENA-	DIR-
 *						PI6			PD11	PF11
 */
#include "motor_ctrl.h"

/*******************************************************************************
* �� �� ��         : MOTOR_SetENA
* ��������         : �����������ʹ������
* ��    ��         : motor, motorEna
* ��    ��         : ��
*******************************************************************************/
void MOTOR_SetENA(MOTOR motor, FunctionalState motorEna)
{
	/* ����״̬�����ı䣬�޸��µ����ǰ״̬���ṹ����������ԣ� */
	motor._mtEnable = motorEna;
	
	switch(motorEna) 
	{
		case ENABLE:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET); // PD11��0
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET); // PD3��0(ʵ�ʹ���ȡ���Ϊ1)
				
			}
			break;
		case DISABLE:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET); // PD11��1
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET); // PD3��1		
			}			
			break;
	}
}

/*******************************************************************************
* �� �� ��         : MOTOR_SetTIMENA
* ��������         : ���������Ӧ��TIM����ʹ������
* ��    ��         : motor, motorTIMState
* ��    ��         : ��
*******************************************************************************/
void MOTOR_SetTIMENA(MOTOR motor, MotorTIMStatus motorTIMState)
{
	motor._mtTIMState = motorTIMState;
	switch(motorTIMState) 
	{
		case STARTTIM:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_TIM_PWM_Start(&tim8_handler, TIM_CHANNEL_2);
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_TIM_PWM_Start(&tim8_handler, TIM_CHANNEL_1);
				
			}
			break;
		case STOPTIM:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_TIM_PWM_Stop(&tim8_handler, TIM_CHANNEL_2);
				
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_TIM_PWM_Stop(&tim8_handler, TIM_CHANNEL_1);
			}				
			break;
	}		
}


/*******************************************************************************
* �� �� ��         : MOTOR_SetDIR
* ��������         : ����������з�������
* ��    ��         : motor, motorDir
* ��    ��         : ��
*******************************************************************************/
void MOTOR_SetDIR(MOTOR motor, MotorDirection motorDir) 
{
	motor._mtDir = motorDir;
	
	switch(motorDir) 
	{
		case FORWARD:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_RESET); // PF11��0
				
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET); // PD7��0
			}
			HAL_Delay(1); // ��ʱ10us����������
			break;
		case BACKWARD:
			if(motor._mtId == MOTOR_RAIL)
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_11, GPIO_PIN_SET); // PF11��1
			}
			if(motor._mtId == MOTOR_CAMERA) 
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET); // PD7��1
				
			}		
			HAL_Delay(1);			
			break;
	}	
}

/*******************************************************************************
* �� �� ��         : MOTOR_SetSpeed
* ��������         : ���������������ٶ�����
* ��    ��         : motorSpeed
* ��    ��         : ��
*******************************************************************************/
void MOTOR_SetSpeed(uint32_t motorSpeed)
{
	tim8_handler.Instance->PSC = motorSpeed;
	motor_rail._mtSpeed = motorSpeed;        // TIM8_CH1��TIM8_CH2ʵ����һ����ʱ�����ٶ�һ��
	motor_camera._mtSpeed = motorSpeed;
}







