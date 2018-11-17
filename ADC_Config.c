#include "stm32f10x.h"
#include "declare.h"


uint16_t AD_Value[ADC_COUNT][ADC_Chanel]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
uint32_t AD_Average[ADC_Chanel];



//Ĭ�Ͻ�����ͨ��0~3																	   
void  ADC_Config(void)
{ 	
	ADC_InitTypeDef  ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_DeInit(ADC1);  //������ ADC10 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC10�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode =DISABLE;//ֻ��һ��ͨ��ѡ��DISABLE������ENABLE;	//ģ��ת��������ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ����ת���ر�
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = ADC_Chanel;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
	
	/* ADC1 regular channel11 configuration */ 
	//����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	//ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );


	ADC_TempSensorVrefintCmd(ENABLE); //ʹ���¶ȴ��������ڲ��ο���ѹͨ�� 
		
	ADC_DMACmd(ADC1, ENABLE);	 // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
	
	ADC_Cmd(ADC1, ENABLE);	   //ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	  //��λָ����ADC1��У׼�Ĵ���
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�

	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
	
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//����adc�ɼ�

}

//�ֽڽ���
void swap(uint16_t *tdata, uint16_t *sdata)   //������С��ֵ
{
    uint16_t tmp;

    tmp = *tdata;
    *tdata = *sdata;
    *sdata = tmp;
}
//ð�ݷ�����
void paixu()                            //ð�ݷ��ӴﵽС����
{
	uint8_t i,j,m;

	for (m=0; m<ADC_Chanel; m++)//�ڼ�ͨ��
	{
		for (i=0; i<ADC_COUNT; i++)//�ɼ�����
		{
			for (j=i+1; j<ADC_COUNT; j++)
			{
				if (AD_Value[i][m] > AD_Value[j][m])//���ǰһ���Ⱥ�һ�����򽻻�
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
