#include "usart_master.h"

unsigned char USART1_RX_COUNT = 0;

// ����USART1��GPIO�ڳ�ʼ��
void GPIO_USART1_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// USART1-TXD
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = MASTER_TXD;				// ��ʼ��GPIOA9(TXD)
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// �����������
	GPIO_Init(MASTER_CTRL, &GPIO_InitStructure);	

	// USART1-RXD
	GPIO_InitStructure.GPIO_Pin = MASTER_RXD;				// ��ʼ��GPIOA10(RXD)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ��������
	GPIO_Init(MASTER_CTRL, &GPIO_InitStructure);
}

// ��ʼ��NVIC�������ȼ�
void USART1Nvic_Config_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;     	// USART1ȫ���ж�ͨ��,��Ӧ���ִ����ж����Ϳ������жϷ����ӳ��������
	// ��ռ���ȼ�,�ض�ʱ��1Ҫ�ߣ���֤�������ݲ��ᶪʧ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;     	// �����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        	// IQRͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);
}

// ��ʼ�����ô���USART1
void USART1_Master_Init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	
	// ����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_USART1_Init();
	
	// ���ڸ�λ
	USART_DeInit(USART1);
	
	// ���ڲ�����ʼ��
	USART_InitStructure.USART_BaudRate = bound;				// ���ò�����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;		// ����żУ��λ��Ҳ����˵һ֡��������̤̤ʵʵ��8λ��
	// ��Ӳ������������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// �շ�ģʽ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
#if IS_MUTI_COMUNICATION
	//�ദ����ģʽ�£�һ֡�����ֳ�Ϊ9λ��MSBλ���������ݣ�0��/��ַ��1����־λ
	USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	USART_Init(USART1,&USART_InitStructure);				// ��ʼ������
	USART_SetAddress(USART1,MASTER_ADDR);					// �ദ����ģʽ�£�����������ַ
	
#else
	// ��ͨ�շ�ģʽ
	// �ֳ�Ϊ8λ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);				// ��ʼ������

#endif

	USART1Nvic_Config_Init();								// ����NVIC�ж����ȼ���ʼ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);			// ʹ�ܴ��ڽ����ж�

	// ����ʹ��
	USART_Cmd(USART1,ENABLE);
}

// �����жϷ����ӳ���
void USART1_IRQHandler(void)
{
	u8 Res;
	// �����ж����ͣ������ж�����
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART1);					//(USART1->DR);	//��ȡ���յ�������  // USARTx_DR���������Խ���־λ RXNE ��0
		if(Res == 0xEE)
		{
			USART1_RX_COUNT = 0;
		}
		else
		{
			buf[USART1_RX_COUNT] = Res;
			USART1_RX_COUNT ++;
			if(USART1_RX_COUNT > 200-1) USART1_RX_COUNT = 0;	
		}

	}
}



