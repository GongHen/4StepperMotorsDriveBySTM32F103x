/*
 * @ Author: �̺���
 * @ Description: ��������˿���������
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "motor_ioinit.h"
#include "motor.h"
#include "motor_ctrl.h"

// lwip ͷ�ļ�
#include "string.h"
#include "bsp_debug_usart.h"

#include "lwip/opt.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "app_ethernet.h"
#include "tcp_echoserver.h"


// �������ṹ�����
volatile MOTOR motor_rail;
volatile MOTOR motor_camera;

// ����lwip����Э����ر���
struct netif gnetif; // ��������ӿڱ���




int main(void)
{
	
	/* ��λ�������裬��ʼ��Flash�ӿں�ϵͳ�δ�ʱ�� */
	HAL_Init();
	/* ����ϵͳʱ�� */
	SystemClock_Config();
	/* ��ʼ�����ڲ����ô����ж����ȼ� */
	MX_DEBUG_USART_Init();
	/* ��ʼ��LWIP�ں� */
	lwip_init();
	/* ��������ӿڣ�����ʹ�õ��Ǿ�̬IP��ַ������DHCP */
	Netif_Config();
	
	while(1) 
	{	
		tcp_echoserver_connect(); // ���д���TCPserver
		
	}
	
	 
	
}

/**
  * ��������: ϵͳʱ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	__HAL_RCC_PWR_CLK_ENABLE();                                     //ʹ��PWRʱ��
  
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  //���õ�ѹ�������ѹ����1
  
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;      // �ⲿ����8MHz
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;                        //��HSE 
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                    //��PLL
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;            //PLLʱ��Դѡ��HSE
	RCC_OscInitStruct.PLL.PLLM = 8;                                 //8��ƵMHz
	RCC_OscInitStruct.PLL.PLLN = 336;                               //336��Ƶ
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                     //2��Ƶ���õ�168MHz��ʱ��
	RCC_OscInitStruct.PLL.PLLQ = 7;                                 //USB/SDIO/������������ȵ���PLL��Ƶϵ��
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;       // ϵͳʱ�ӣ�168MHz
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;              // AHBʱ�ӣ� 168MHz
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;               // APB1ʱ�ӣ�42MHz
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;               // APB2ʱ�ӣ�84MHz
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

	HAL_RCC_EnableCSS();                                            // ʹ��CSS���ܣ�����ʹ���ⲿ�����ڲ�ʱ��ԴΪ����

	// HAL_RCC_GetHCLKFreq()/1000    1ms�ж�һ�Σ�HAL_Delay()��ʱ��λΪ1ms��
	// HAL_RCC_GetHCLKFreq()/100000	 10us�ж�һ�Σ�HAL_Delay()��ʱ��λΪ10us��
	// HAL_RCC_GetHCLKFreq()/1000000 1us�ж�һ�Σ�HAL_Delay()��ʱ��λΪ1us��
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/100000);                // ���ò�����ϵͳ�δ�ʱ��
	/* ϵͳ�δ�ʱ��ʱ��Դ */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* ϵͳ�δ�ʱ���ж����ȼ����� */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}



/**
  * ��������: ��������ӿ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */
static void Netif_Config(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;
  
  /* Initializes the dynamic memory heap defined by MEM_SIZE.*/
  mem_init();
  
  /* Initializes the memory pools defined by MEMP_NUM_x.*/
  memp_init();  
#ifdef USE_DHCP
  ip_addr_set_zero_ip4(&ipaddr);
  ip_addr_set_zero_ip4(&netmask);
  ip_addr_set_zero_ip4(&gw);
#else
  IP_ADDR4(&ipaddr,IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
  IP_ADDR4(&netmask,NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
  IP_ADDR4(&gw,GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
  
	printf("��̬IP��ַ........................%d.%d.%d.%d\r\n",IP_ADDR0,IP_ADDR1,IP_ADDR2,IP_ADDR3);
	printf("��������..........................%d.%d.%d.%d\r\n",NETMASK_ADDR0,NETMASK_ADDR1,NETMASK_ADDR2,NETMASK_ADDR3);
	printf("Ĭ������..........................%d.%d.%d.%d\r\n",GW_ADDR0,GW_ADDR1,GW_ADDR2,GW_ADDR3);
#endif /* USE_DHCP */
  
  /* Add the network interface */    
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);
  
  /* Registers the default network interface */
  netif_set_default(&gnetif);
  
  if (netif_is_link_up(&gnetif))
  {
    printf("�ɹ���������\n");
    /* When the netif is fully configured this function must be called */
    netif_set_up(&gnetif);
  }
  else
  {
    /* When the netif link is down this function must be called */
    netif_set_down(&gnetif);
  }
  
  /* Set the link callback function, this function is called on change of link status*/
  netif_set_link_callback(&gnetif, ethernetif_update_config);
}

