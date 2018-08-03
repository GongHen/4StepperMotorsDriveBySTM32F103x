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

// �����������С
#define BUF_MAXSIZE				64
#define SBUF_MAXSIZE			32
#define	ISNC_MAXSIZE			32

// USART1���ջ������ṹ������
typedef __packed struct {
	unsigned char buf_id;
	unsigned char buf[BUF_MAXSIZE];
	int buf_index;
	unsigned char isbufNull;
	unsigned char sbuf_id;
	unsigned char sbuf[SBUF_MAXSIZE];
	int sbuf_index;
	unsigned char issbufNull;
	unsigned char isnc_id;
	unsigned char isNeedChange[ISNC_MAXSIZE];
	int isnc_index;
	unsigned char isisncNull;
}REC_BUFFER;



void GPIO_USART1_Init(void);
void USART1Nvic_Config_Init(void);
void USART1_Master_Init(u32 bound);
void Init_USART1_Buffer(void);
unsigned char Check_Null_Buffer(unsigned char BUF_ID);

// USART1���ջ�������������
//extern volatile unsigned char buf[30];
extern volatile REC_BUFFER rec_buffer;
#endif

