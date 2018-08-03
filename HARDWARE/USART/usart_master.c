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
 
#include "usart_master.h"

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

// ��ʼ��USART1���ջ������ṹ�����
void Init_USART1_Buffer()
{
	volatile REC_BUFFER* pbuffer = &rec_buffer;
	int i;
	pbuffer->buf_id = 1;
	pbuffer->sbuf_id = 2;
	pbuffer->isnc_id = 3;
	pbuffer->buf_index = 0;
	pbuffer->sbuf_index = 0;
	pbuffer->isnc_index = 0;
	
	for(i=0;i<BUF_MAXSIZE;i++)								// ��ʼ����ջ���������һ���ڴ������
	{
		pbuffer->buf[i] = 0;
		pbuffer->sbuf[i] = 0;
		pbuffer->isNeedChange[i] = 0;
	}
	
	for(i=0;i<SBUF_MAXSIZE;i++)	
	{
		pbuffer->sbuf[i] = 0;
		pbuffer->isNeedChange[i] = 0;
	}
	
	for(i=0;i<ISNC_MAXSIZE;i++)	
	{
		pbuffer->isNeedChange[i] = 0;
	}
	
	pbuffer->isbufNull = 1;
	pbuffer->issbufNull = 1;
	pbuffer->isisncNull = 1;
	
}

// ��黺�����Ƿ�Ϊ��
unsigned char Check_Null_Buffer(unsigned char BUF_ID)
{
	int i;
	switch(BUF_ID)
	{
		case 1:
			for(i=0;i<BUF_MAXSIZE;i++)
			{
				if(rec_buffer.buf[i] != 0) return 0;
			}
			break;
		case 2:
			for(i=0;i<SBUF_MAXSIZE;i++)	
			{
				if(rec_buffer.sbuf[i] != 0) return 0;
			}
			break;
		case 3:
			for(i=0;i<ISNC_MAXSIZE;i++)	
			{
				if(rec_buffer.isNeedChange[i] != 0) return 0;
			}
			break;
	}
	return 1;
}

// �����жϷ����ӳ���
void USART1_IRQHandler(void)
{
	u8 Rec;
	// �����ж����ͣ������ж�����
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Rec = USART_ReceiveData(USART1);					//(USART1->DR);	//��ȡ���յ�������  // USARTx_DR���������Խ���־λ RXNE ��0
		
		if(Rec == 0xEE)										// �� sbuf ���������ֵ��0
		{
			rec_buffer.buf_index = 0;
		}
		if(Rec == 0xEF)										// �� isNeedChange ���������ֵ��0
		{
			rec_buffer.isnc_index = 0;
		}
		if(Rec == 0xFF)										// �� buf ���������ֵ��0
		{
			rec_buffer.sbuf_index = 0;
		}
		
		
		if((Rec & 0xF0) == 0xF0 && (Rec != 0xFF))			// ��ȡӡ�µ� id ֵ�� sbuf ����
		{
			rec_buffer.sbuf[rec_buffer.sbuf_index] = Rec;
			rec_buffer.sbuf_index ++;		
			if(rec_buffer.sbuf_index > SBUF_MAXSIZE-1) rec_buffer.sbuf_index = 0;
		}
		if(Rec == 0xED)										// �յ� 0xED(don't change) ��ʾ��һ�β������ø���ӡ��
		{
			rec_buffer.isNeedChange[rec_buffer.isnc_index] = 0;
			rec_buffer.isnc_index ++;						
			if(rec_buffer.isnc_index > ISNC_MAXSIZE-1) rec_buffer.isnc_index = 0;
		}
		if(Rec == 0xEC)										// �յ� 0xEC(change) ��ʾ��һ�β�����Ҫ����ӡ��
		{
			rec_buffer.isNeedChange[rec_buffer.isnc_index] = 1;
			rec_buffer.isnc_index ++;						
			if(rec_buffer.isnc_index > ISNC_MAXSIZE-1) rec_buffer.isnc_index = 0;
		}
		if(Rec == 0xEB)										// �յ� 0xEB(be obliged to) ��ʾ�ʼ��һ�β���һ����Ҫ����ӡ��
		{
			rec_buffer.isNeedChange[rec_buffer.isnc_index] = 11;
			rec_buffer.isnc_index ++;				
			if(rec_buffer.isnc_index > ISNC_MAXSIZE-1) rec_buffer.isnc_index = 0;
		}
		if(Rec <= 0xE9)										// ��ȡĿ�������ֵ�� buf ����
		{
			rec_buffer.buf[rec_buffer.buf_index] = Rec;
			rec_buffer.buf_index ++;
			if(rec_buffer.buf_index > BUF_MAXSIZE-1) rec_buffer.buf_index = 0;	
		}
		if(Rec == 0xEA)
		{
			rec_buffer.isbufNull = 0;						// buf �����յ����ݣ���Ϊ��
			rec_buffer.isbufNull = 0;						// sbuf �����յ����ݣ���Ϊ��
			rec_buffer.isisncNull = 0;						// isNeedChange �����յ����ݲ�Ϊ��
		}
		
	}
}



