#include "stm32f10x.h"
#include "declare.h"


T_Struct Real_Time;//时间结构体变量

uint8_t const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
const uint8_t mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};//平年的月份日期表


void RTC_config(void)
{
	 uint8_t temp2=0;
	
	//检查是不是第一次配置时钟
 
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)		//从指定的后备寄存器中读出数据:读出了与写入的指定数据不相乎
	{	 			
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟   
		PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问 
		BKP_DeInit();	//复位备份区域 	
		RCC_LSEConfig(RCC_LSE_ON);	//设置外部低速晶振(LSE),使用外设低速晶振
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)	//检查指定的RCC标志位设置与否,等待低速晶振就绪
		{
			temp2++;
			Delay1ms(10);
			if(temp2>=250)return ;//初始化时钟失败,晶振有问题	 
		}
		
		 
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//设置RTC时钟(RTCCLK),选择LSE作为RTC时钟    
		RCC_RTCCLKCmd(ENABLE);	//使能RTC时钟  
		
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		RTC_WaitForSynchro();		//等待RTC寄存器同步  
			
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		//使能RTC秒中断
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		RTC_EnterConfigMode();/// 允许配置	
		RTC_SetPrescaler(32767); //设置RTC预分频的值
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		Real_Time.year=2016;
		Real_Time.month=10;
		Real_Time.day=2;
		Real_Time.hour=16;
		Real_Time.min=34;
		Real_Time.sec=0;
		Set_RTC(Real_Time);  //设置时间	
			
		RTC_ExitConfigMode(); //退出配置模式  
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);	//向指定的后备寄存器中写入用户程序数据
	}
	else//系统继续计时
	{
		RTC_WaitForSynchro();	//等待最近一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//使能RTC秒中断
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
	}
  				     
	//Read_RTC();//更新时间	


}		 				   
//输出:该年份是不是闰年.1,是.0,不是
uint8_t Is_Leap_Year(uint16_t year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
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
	for(t=1970;t<temp;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	temp=time.month;
	temp-=1;
	for(t=0;t<temp;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(time.year)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	
	temp=time.day;
	seccount+=(u32)(temp-1)*86400;//把前面日期的秒钟数相加 
	
	temp=time.hour;
	seccount+=(u32)temp*3600;//小时秒钟数
	
	temp=time.min;
  seccount+=(u32)temp*60;	 //分钟秒钟数
	
	temp=time.sec;
	seccount+=temp;//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);	//设置RTC计数器的值

	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
   
}


void Read_RTC(void)
{
	static uint16_t daycnt=0;
	uint32_t timecount=0; 
	uint32_t temp=0;
	uint16_t temp1=0;	  
	
 	timecount=RTC->CNTH;//得到计数器中的值(秒钟数)
	timecount<<=16;
	timecount+=RTC->CNTL;
	//timecount = RTC_GetCounter();	
 	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{	  
		daycnt=temp;
		temp1=1970;	//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)
				{
					temp-=366;//闰年的秒钟数
				}
				else 
				{
					temp1++;
					break;
				}  
			}
			else
			{				
				temp-=365;	  //平年 
			}
			
			temp1++;  
		}   
		Real_Time.year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(Real_Time.year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		Real_Time.month=temp1+1;	//得到月份
		Real_Time.day=temp+1;  	//得到日期 
	}
	temp=timecount%86400;     		//得到秒钟数   	   
	Real_Time.hour=temp/3600;     	//小时
	Real_Time.min=(temp%3600)/60; 	//分钟	
	Real_Time.sec=(temp%3600)%60; 	//秒钟
	//Real_Time.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//获取星期   

}
