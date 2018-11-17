#include "stm32f10x.h"


//NVIC���� ϵͳ�жϹ���
void NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//������ռ���ȼ�����Ӧ���ȼ��ķ��䷽ʽ
	// ����1:������ռ���ȼ���8����Ӧ���ȼ�
	/*��0�飺����4λ����ָ����Ӧ���ȼ�
   ��1�飺���1λ����ָ����ռʽ���ȼ������3λ����ָ����Ӧ���ȼ�
   ��2�飺���2λ����ָ����ռʽ���ȼ������2λ����ָ����Ӧ���ȼ�
   ��3�飺���3λ����ָ����ռʽ���ȼ������1λ����ָ����Ӧ���ȼ�
   ��4�飺����4λ����ָ����ռʽ���ȼ�
   */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;      
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռʽ�ж����ȼ�����Ϊ0��1��0���
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ӧʽ�ж����ȼ�����Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
    NVIC_Init(&NVIC_InitStructure);
	
	
//-------------------------------------------------
 	/* NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //CAN �ж�
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;// ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // ��ռʽ���ȼ��� 
	NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn;//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;// ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//-------------------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // ��ռʽ���ȼ��� 
	NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn;//ָ���ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;// ָ����Ӧ���ȼ���1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//----------------------------------------------------------------
  
 /* NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //CAN �ж�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);*/

//===== NVIC_RTC =================================================== 	
	/* Enable the RTC Interrupt */
	/*NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);			*/	

}

