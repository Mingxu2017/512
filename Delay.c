/*
*********************************************************************************************************

*
*********************************************************************************************************
*/

#include "stm32f10x.h"
#include <stdio.h>
#include "Declare.h" 
 
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й��� 
//����delay_us,delay_ms   
//�������ж��е��ó�����ѭ���Ĵ��� 
//��ֹ��ʱ��׼ȷ,����do while�ṹ! 
   


//��ʼ���ӳٺ��� 
/*void delay_Config(uint8_t SYSCLK)   // ϵͳʱ����72M ��SYSCLK ȡ72 ���������� 
{ 
SysTick->CTRL&=0xfffffffb;//ѡ���ڲ�ʱ�� HCLK/8 
// SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
fac_us=SYSCLK/8;
fac_ms=(u16)fac_us*1000; 
}           

void Delay1us(uint32_t nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
	}

//��ʱNms 
//ע��Nms�ķ�Χ 
//Nms<=0xffffff*8/SYSCLK 
//��72M������,Nms<=1864 
void Delay1ms(uint16_t nms) 
{          
uint32_t temp;      
SysTick->LOAD=(u32)nms*fac_ms;//ʱ����� 
//SysTick_SetReload((u32)nms*fac_ms); 
SysTick->VAL =0x00;            //��ռ����� 
//SysTick_CounterCmd(SysTick_Counter_Clear); 
SysTick->CTRL=0x01 ;           //��ʼ���� 
//SysTick_CounterCmd(SysTick_Counter_Enable); 
do 
{ 
   temp=SysTick->CTRL; 
} 
while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��    
SysTick->CTRL=0x00;        //�رռ����� 
SysTick->VAL =0x00;        //��ռ�����   
      
}   
*/
void Delay1us(u32 nus) 
{  
	uint32_t temp;  
	SysTick->LOAD = 9*nus;  
	SysTick->VAL=0X00;//��ռ�����

	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ

	do 
	{  
		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��

	SysTick->CTRL=0x00; //�رռ�����

	SysTick->VAL =0X00; //��ռ�����
	WDOG();
}  


void Delay1ms(u16 nms) 
{  
	uint32_t temp;  
	SysTick->LOAD = 9000*nms;  
	SysTick->VAL=0X00;//��ռ�����
	WDOG(); 
	SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ

	do 
	{  
		temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	}while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��

	SysTick->CTRL=0x00; //�رռ�����

	SysTick->VAL =0X00; //��ռ�����
	WDOG();
}  

void Delay1s(u16 ns)
{
	u8 i;
	for(i=ns;i>0;i--)
	{
		Delay1ms(1000);
		WDOG();
	}
}
