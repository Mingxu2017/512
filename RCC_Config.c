#include "stm32f10x.h"

/** ***************************************88                          
����RCC  
*********************************************************************/

void RCC_Configuration(void) 
{ ErrorStatus HSEStartUpStatus;     
 
  RCC_DeInit();  //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
 
  RCC_HSEConfig(RCC_HSE_ON);   //���ⲿ���پ���
	
  HSEStartUpStatus = RCC_WaitForHSEStartUp();  //�ȴ��ⲿ����ʱ��׼���� 
  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  { 
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //����FLASH��Ԥȡ����
 
    FLASH_SetLatency(FLASH_Latency_2); //FLASH�ӳ�2������
  
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHB(HCLK)ʱ��=SYSCLK     
    
    RCC_PCLK2Config(RCC_HCLK_Div1);   //����APB2(PCLK2=72M)��=AHBʱ��
  
    RCC_PCLK1Config(RCC_HCLK_Div2);  //����APB1(PCLK1=36M)��=AHB 1/2ʱ��
 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);  //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz  

    RCC_PLLCmd(ENABLE); //ʹ��PLLʱ��
  
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  //�ȴ�PLLʱ�Ӿ���
    { 
    } 
  
 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //����ϵͳʱ�� = PLLʱ��
  
  
 
    while(RCC_GetSYSCLKSource() != 0x08) ; //���PLLʱ���Ƿ���Ϊϵͳʱ��
	} 
	
	 


}  
