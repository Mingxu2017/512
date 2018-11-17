#include "stm32f10x.h"


// ((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+7199)/72M)*10=1ms */
void TIM3_Config(void)
 {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//允许TIM3的时钟
	 
    TIM_DeInit(TIM3);       //复位TIM3定时器

    TIM_TimeBaseStructure.TIM_Period = 499;        //  9=1ms   499=50ms   
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;    // 分频       
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;// TIM_CKD_DIV1;  // 时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //计数方向向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM3, TIM_FLAG_Update);//[清除TIM2溢出中断标志] 
 
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //TIM2溢出中断允许

    //TIM_Cmd(TIM3, DISABLE);
		TIM_Cmd(TIM3, ENABLE);//时钟开启
 }
