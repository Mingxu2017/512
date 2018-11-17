#include "stm32f10x.h"
#include "declare.h"


uint16_t AD_Value[ADC_COUNT][ADC_Chanel]; //用来存放ADC转换结果，也是DMA的目标地址
uint32_t AD_Average[ADC_Chanel];



//默认将开启通道0~3																	   
void  ADC_Config(void)
{ 	
	ADC_InitTypeDef  ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_DeInit(ADC1);  //将外设 ADC10 的全部寄存器重设为缺省值
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC10工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode =DISABLE;//只有一个通道选择DISABLE，否则ENABLE;	//模数转换工作在扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//外部触发转换关闭
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = ADC_Chanel;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
	
	/* ADC1 regular channel11 configuration */ 
	//设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	//ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );


	ADC_TempSensorVrefintCmd(ENABLE); //使能温度传感器和内部参考电压通道 
		
	ADC_DMACmd(ADC1, ENABLE);	 // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
	
	ADC_Cmd(ADC1, ENABLE);	   //使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	  //复位指定的ADC1的校准寄存器
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1复位校准寄存器的状态,设置状态则等待

	ADC_StartCalibration(ADC1);		//开始指定ADC1的校准状态
	
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//开启adc采集

}

//字节交换
void swap(uint16_t *tdata, uint16_t *sdata)   //调换大小数值
{
    uint16_t tmp;

    tmp = *tdata;
    *tdata = *sdata;
    *sdata = tmp;
}
//冒泡法排序
void paixu()                            //冒泡法从达到小排序
{
	uint8_t i,j,m;

	for (m=0; m<ADC_Chanel; m++)//第几通道
	{
		for (i=0; i<ADC_COUNT; i++)//采集次数
		{
			for (j=i+1; j<ADC_COUNT; j++)
			{
				if (AD_Value[i][m] > AD_Value[j][m])//如果前一个比后一个大，则交换
				{
					swap(&AD_Value[i][m], &AD_Value[j][m]);
				}
			}
		}
	}
}

 //void Get_Adc_Average(void)
void Power_ADC_Return(void)
{
	uint8_t m,i;
	paixu();
	//	 for(m=0;m<ADC_Chanel;m++)
	m=0;
	{ 
		AD_Average[m]=0;
		for(i=4;i<(ADC_COUNT-4);i++)
		{
			AD_Average[m] = AD_Average[m]+AD_Value[i][m];
		}
		AD_Average[m] = AD_Average[m]/(ADC_COUNT-8);

	}
	Bat_Power=AD_Average[m]; 
}		
