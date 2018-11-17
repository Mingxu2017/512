#include "stm32f10x.h"
#include "declare.h"


T_Struct Real_Time;//ʱ��ṹ�����

uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//ƽ����·����ڱ�


void RTC_config(void)
{
	 uint8_t temp2=0;
	
	//����ǲ��ǵ�һ������ʱ��
 
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)		//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
	{	 			
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
		PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ������� 
		BKP_DeInit();	//��λ�������� 	
		RCC_LSEConfig(RCC_LSE_ON);	//�����ⲿ���پ���(LSE),ʹ��������پ���
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//���ָ����RCC��־λ�������,�ȴ����پ������
		{
			temp2++;
			Delay1ms(10);
			if(temp2>=250)return ;//��ʼ��ʱ��ʧ��,����������	 
		}
		
		 
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
		RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ��  
		
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_WaitForSynchro();		//�ȴ�RTC�Ĵ���ͬ��  
			
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		//ʹ��RTC���ж�
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_EnterConfigMode();/// ��������	
		RTC_SetPrescaler(32767); //����RTCԤ��Ƶ��ֵ
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		Real_Time.year=2016;
		Real_Time.month=10;
		Real_Time.day=2;
		Real_Time.hour=16;
		Real_Time.min=34;
		Real_Time.sec=0;
		Set_RTC(Real_Time);  //����ʱ��	
			
		RTC_ExitConfigMode(); //�˳�����ģʽ  
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);	//��ָ���ĺ󱸼Ĵ�����д���û���������
	}
	else//ϵͳ������ʱ
	{
		RTC_WaitForSynchro();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//ʹ��RTC���ж�
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	}
  				     
	//Read_RTC();//����ʱ��	


}		 				   
//���:������ǲ�������.1,��.0,����
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	 		


void Set_RTC(T_Struct time)
{
	uint16_t t,temp;
	uint32_t seccount=0;
	
	temp=time.year;
	if(temp<1970||temp>2099)return ;	   
	for(t=1970;t<temp;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	temp=time.month;
	temp-=1;
	for(t=0;t<temp;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(time.year)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	
	temp=time.day;
	seccount+=(u32)(temp-1)*86400;//��ǰ�����ڵ���������� 
	
	temp=time.hour;
	seccount+=(u32)temp*3600;//Сʱ������
	
	temp=time.min;
  seccount+=(u32)temp*60;	 //����������
	
	temp=time.sec;
	seccount+=temp;//�������Ӽ���ȥ

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	RTC_SetCounter(seccount);	//����RTC��������ֵ

	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
   
}


void Read_RTC(void)
{
	static uint16_t daycnt=0;
	uint32_t timecount=0; 
	uint32_t temp=0;
	uint16_t temp1=0;	  
	
 	timecount=RTC->CNTH;//�õ��������е�ֵ(������)
	timecount<<=16;
	timecount+=RTC->CNTL;
	//timecount = RTC_GetCounter();	
 	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{	  
		daycnt=temp;
		temp1=1970;	//��1970�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)
				{
					temp-=366;//�����������
				}
				else 
				{
					temp1++;
					break;
				}  
			}
			else
			{				
				temp-=365;	  //ƽ�� 
			}
			
			temp1++;  
		}   
		Real_Time.year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(Real_Time.year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)temp-=29;//�����������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
				else break;
			}
			temp1++;  
		}
		Real_Time.month=temp1+1;	//�õ��·�
		Real_Time.day=temp+1;  	//�õ����� 
	}
	temp=timecount%86400;     		//�õ�������   	   
	Real_Time.hour=temp/3600;     	//Сʱ
	Real_Time.min=(temp%3600)/60; 	//����	
	Real_Time.sec=(temp%3600)%60; 	//����
	//Real_Time.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//��ȡ����   

}
