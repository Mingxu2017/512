#include "stm32f10x.h"
#include "declare.h"

/*配置DMA*/
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //全能DMA1时钟
	
	DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;  //DMA外设ADC基地址
	
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_Value;  //DMA内存基地址
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //内存作为数据传输的目的地
	                                                    //DMA_DIR_PeripheralDST; 指定外设为目的地址
	DMA_InitStructure.DMA_BufferSize = ADC_COUNT*ADC_Chanel;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //工作在循环缓存模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道
	
	DMA_Cmd(DMA1_Channel1, ENABLE);//配置完成后，启动DMA通道
	
 /*  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);    //使能DMA1时钟
    DMA_DeInit(DMA1_Channel4);    //默认初始化DMA1通道4
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&(USART1->DR);;    //定义通道的外设基地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxBuffer1;      //定义通道的存储器基地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;     //指定外设为目的地址
    DMA_InitStructure.DMA_BufferSize = num;   //通道缓冲区数据单元大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //外设寄存器地址不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;    //当前存储寄存器地址增加
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //外设数据宽度为8位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;    //存储器数据宽度为8位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;   //使用正常缓冲模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;   //DMA通道优先级非常高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       //禁止存储器到存储器传输
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);   //初始化DMA1
*/
}

