#include "stm32f10x.h"
#include "declare.h"

/*����DMA*/
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ȫ��DMA1ʱ��
	
	DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;  //DMA����ADC����ַ
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  //DMA�ڴ����ַ
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	                                                    //�DDMA_DIR_PeripheralDST; ָ������ΪĿ�ĵ�ַ
	DMA_InitStructure.DMA_BufferSize = ADC_COUNT*ADC_Chanel;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //������ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
	
	DMA_Cmd(DMA1_Channel1, ENABLE);//������ɺ�����DMAͨ��
	
 /*  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //ʹ��DMA1ʱ��
    DMA_DeInit(DMA1_Channel4);    //Ĭ�ϳ�ʼ��DMA1ͨ��4
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(USART1->DR);;    //����ͨ�����������ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxBuffer1;      //����ͨ���Ĵ洢������ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;     //ָ������ΪĿ�ĵ�ַ
    DMA_InitStructure.DMA_BufferSize = num;   //ͨ�����������ݵ�Ԫ��С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //����Ĵ�����ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;    //��ǰ�洢�Ĵ�����ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //�������ݿ��Ϊ8λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;    //�洢�����ݿ��Ϊ8λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;   //ʹ����������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;   //DMAͨ�����ȼ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       //��ֹ�洢�����洢������
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);   //��ʼ��DMA1
*/
}

