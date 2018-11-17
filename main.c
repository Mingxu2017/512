#include "stm32f10x.h"		/* 如果要用ST的固件库，必须包含这个文件 */
#include "Declare.h"

uint8_t temp_Dis_Num;
uint8_t Dis_Count;

uint8_t Timer50ms=0,Timer50ms1=0;//显示时间控制在1S
uint16_t Back_Timer1S=0;
uint8_t DoorDelayTimer;
uint8_t Dis_System_Timer=0,Dis_Feel_Timer=0,Uart_Timer=0,Beep_Timer=0,LEDTimer=0;
uint8_t Set_Bat_Low_Flag=0;//显示馈电指示标志
uint8_t PowerLow_DisOFF=0;//=1表示馈电关显示，只有蜂鸣器响

uint8_t TimemsCnt=0,Time100msFlag=0,Time100msCnt=0,Time1sFlag=0,Time1sCnt=0;
uint8_t PageNum=0;
uint8_t ZD_Test=0;
uint8_t FreshFlag=0;

uint8_t canbuf[8];
uint8_t TestKey=0;
uint8_t TestKey1=0;
//unsigned char K2_Pulse_Timer=0;
//bit K2_ON_Flag=0;//KC2产生脉冲
void LED_Rev(void)
{
	static uint8_t ledrevflag=0;
	static uint8_t cnt=0;
	if(ledrevflag == 0)
	{
		Power_LED_ON();
		ledrevflag = 1;
	}
	else
	{
		Power_LED_OFF();
		ledrevflag = 0;
	}

}

void TimeMsWork(void)
{
	if(Bat_Low_Flag)//备电故障，弹窗报警
	{
		if ( Set_Bat_Low_Flag == 0 )	//确认界面只刷新一次
		{
			Set_Bat_Low_Flag = 1; 
			Beep_Alarm_Fault = 3;
			TCQ_Power_OFF();		//传感器电源关闭
			Back_Led_OFF();			//关闭LED背光
			PageNum = 1;				//低压报警界面
			Display_LowPower();	//显示备电故障弹窗
			Dis_State_LED_OFF();//状态指示灯全灭     
		}
		
		if (! GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))   //主电恢复正常
		{  
			Set_Bat_Low_Flag=0;
			TCQ_Power_ON();				//传感器电源打开
			Back_Led_ON();				//主电恢复后，背光开启
			Bat_Low_Flag=0;
			Beep_Alarm_Fault=0; 
			Beep_OFF();		
		  World_Flag=0x1400;
			Dis_State_LED();			//状态指示灯显示
			Delay1s(2);
			
			Display_Main_Face();	//重新刷新显示界面
			//Display_Feel();
			Display_System_Sate();
			PowerLow_DisOFF=0; 
		} 
	}
	else
	{
		if( Set_Bat_Low_Flag == 1 )
		{
			Set_Bat_Low_Flag = 0; 
			Display_Main_Face( );	//弹窗恢复刷新界面
			PageNum = 0;					//恢复主界面刷新
		}
		
		Key_Control( );
	}

	if (! GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))   //主电恢复正常
	{  
		Dis_State_LED();//状态指示灯显示
	} 
}
	
void KCS_Work(void)
{
	static uint8_t KCS_Flag=0;
	static uint8_t KCS_Up_Flag =0;
	if( KSC_Check() == 0 )//手动按键按下
	{
		if( KCS_Up_Flag )
		{
			KCS_Up_Flag = 0;
			if(KCS_Flag==0)
			{
				KCS_Flag = 1;
				KC1_ON();
			}
			else
			{
				KCS_Flag = 0;
				KC1_OFF();
			}
		}
		
	}
	else
	{
		KCS_Up_Flag = 1;
	}
}

void Time100msWork(void)
{
	static u8 time500mscnt;
	
	//辅助回路巡检
	if(LoopOpenFlag == 1)//开启辅助回路功能
	{
		if(time500mscnt<3)
		{
			time500mscnt++;
		}
		else
		{
			time500mscnt = 0;
			if( Function_Flag == 1)
			{			
				RS485SendWork(0x01);	
			}
		}
	}
	
	//Power_Check();			//主电检测
	
	//Bat_Power_Check();	//备电检测
	
	//调整传感器刷新频率
	if(PageNum == 0)
	{
		if( ShowFrq > 9 ) 
		{
			ShowFrq=1;
		}

		if( Dis_Feel_Timer> (20*ShowFrq) )//刷新频率
		{   
			Dis_Feel_Timer=0;
			if(Display_Flag == 0)
				Display_Feel_Fault();//只显示故障和报警
			else
				Display_Main_Fault();

			Display_System_Sate();
			if (Self_Check_Flag==0) 
			{				
				Dis_State_LED();//状态指示灯显示
			}
		}
	}
}

void SecondWork(void)
{
	static unsigned char time10scnt=0;
	
	if( Alarm_Rec_Position )
	{
		if( time10scnt < 10 )
		{
			time10scnt++;
		}
		else
		{
			time10scnt = 0;
			Function_Flag = 12;//查询一次报警最大值
		}
	}
	
	if( SendPtr.LoadCnt != SendPtr.SendCnt )
	{
		SendToPC1(SendFunction[SendPtr.SendCnt].Command,SendFunction[SendPtr.SendCnt].TCQ_Num,SendFunction[SendPtr.SendCnt].TDH,SendFunction[SendPtr.SendCnt].type);
		SendPtr.SendCnt++;
	}
	else
	{
		SendToPC1(11,0,0,0);
	}
	
	LED_Rev();	//运行状态指示，每秒闪烁一次
	
	Power_Check();			//主电检测
	
	Bat_Power_Check();	//备电检测
	
	Check_Fault_Alarm(); //检测探测器故障
	
	Check_Feel_Alarm();	//检测探测器报警
	
	if(PageNum == 0)
	{
		if (Dis_Key_Buff_Flag==0)
		{
			Read_RTC();	
			if(Dis_Alarm_Fault_Flag==0)
			{
				Display_System_Timer();	//只在部分情况下显示时钟
			}
		}
	}
	
}


int main(void)
{
	uint8_t i;
	
	System_Init();	//系统初始化
	Back_Led_ON();//显示屏背光开启
	
	Soft_RST();		//显示模块复位
	Delay1ms(100); 
  
	SD_Display_60S(2);//上电显示,显示安福，倒计时5秒	
	
	Beep_ON();	//复位后蜂鸣器响
	lcd_inital();  //显示模块初始化
	Delay1ms(500);
	Beep_OFF();
	Read_RTC();
	Save_Event_Record(1);//1:代表开机上电  2：代表关机   3：复位   4：清除记录   5：初始化
	Clr_Display();
	Display_Main_Face();
	//Display_Feel();
	Display_System_Sate();
	Dis_State_LED();//状态指示灯显示
	Display_System_Timer();
	PageNum = 0;
	TCQ_ID_485 =LoopStart;

	SendPtr.SendCnt = 0;
	SendPtr.LoadCnt = 0;
	SendToPC1(11,0,0,0);
	while(1)
	{
		WDOG( );//喂狗
		
		TimeMsWork();//毫秒工作	
		
//		#if 0//上传到本地PC
//		if(SendToPC_Flag == 1)
//		{
//			SendToPC_Flag = 0;
//			SendToPC();	
//		}
//		#endif
		
		if(ReceiveFlag == 2)
		{
			RS485DataPro();
			ReceiveFlag = 0; 
		}
		
		if(ReceiveFlag2 == 2)
		{
			PC485DataPro();
			ReceiveFlag2 = 0;
			ReceivePoint2 = 0;
		}
		
		if( TimemsCnt > 2 )			//100ms
		{
			CanSendWork();				//can发送函数	
			TimemsCnt = 0;
		}
		
		if( Time100msCnt >= 2 )	//100ms循环执行的工作
		{
			Time100msCnt = 0;
			Time100msWork();
		}

		if( Time1sFlag )		//每秒执行的工作
		{
			Time1sFlag = 0;				
			SecondWork();	
		}
	}
}
