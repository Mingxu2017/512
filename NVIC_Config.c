#include "stm32f10x.h"


//NVIC设置 系统中断管理
void NVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//定义抢占优先级和响应优先级的分配方式
	// 分组1:两种抢占优先级，8种响应优先级
	/*第0组：所有4位用于指定响应优先级
   第1组：最高1位用于指定抢占式优先级，最低3位用于指定响应优先级
   第2组：最高2位用于指定抢占式优先级，最低2位用于指定响应优先级
   第3组：最高3位用于指定抢占式优先级，最低1位用于指定响应优先级
   第4组：所有4位用于指定抢占式优先级
   */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;      
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占式中断优先级设置为0或1，0最高
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应式中断优先级设置为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能中断
    NVIC_Init(&NVIC_InitStructure);
	
	
//-------------------------------------------------
 	/* NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //CAN 中断
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;// 指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占式优先级别 
	NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn;//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;// 指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//-------------------------------------------------------
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  // 抢占式优先级别 
	NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn;//指定中断源
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;// 指定响应优先级别1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
//----------------------------------------------------------------
  
 /* NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //CAN 中断
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

