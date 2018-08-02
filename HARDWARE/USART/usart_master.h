#ifndef __USART_MASTER_H
#define __USART_MASTER_H

#include "sys.h"

// ����Ƕദ����ͨ�ŵĻ���ֵΪ1
// ��ͨ�շ�ģʽ��ֵΪ0
#define IS_MUTI_COMUNICATION	0

// ����ͨ�Ŷ�Ӧ���ź궨��
#define MASTER_CTRL				GPIOA
#define MASTER_TXD 				GPIO_Pin_9
#define MASTER_RXD 				GPIO_Pin_10

// ������ֵַ
#define MASTER_ADDR				0x1

// �����������СΪ32���ֽ�
#define BUF_MAXSIZE				32

// USART1���ջ������ṹ������
typedef __packed struct {
	unsigned char buf[BUF_MAXSIZE];
	int buf_index;
	unsigned char sbuf[BUF_MAXSIZE];
	int sbuf_index;
	unsigned char isNeedChange[BUF_MAXSIZE];
	int isnc_index;
}REC_BUFFER;



void GPIO_USART1_Init(void);
void USART1Nvic_Config_Init(void);
void USART1_Master_Init(u32 bound);
void Init_USART1_Buffer(void);

// USART1���ջ�������������
//extern volatile unsigned char buf[30];
extern volatile REC_BUFFER rec_buffer;
#endif



