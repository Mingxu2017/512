#include "stm32f10x.h"


// ((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*10=1ms */
void TIM3_Config(void)
 {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����TIM3��ʱ��
	 
    TIM_DeInit(TIM3);       //��λTIM3��ʱ��

    TIM_TimeBaseStructure.TIM_Period = 499;        //  9=1ms   499=50ms   
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;    // ��Ƶ       
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;// TIM_CKD_DIV1;  // ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //�����������ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);//[���TIM2����жϱ�־] 
 
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //TIM2����ж�����

    //TIM_Cmd(TIM3, DISABLE);
		TIM_Cmd(TIM3, ENABLE);//ʱ�ӿ���
 }
