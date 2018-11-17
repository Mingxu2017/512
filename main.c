#include "stm32f10x.h"		/* ���Ҫ��ST�Ĺ̼��⣬�����������ļ� */
#include "Declare.h"

uint8_t temp_Dis_Num;
uint8_t Dis_Count;

uint8_t Timer50ms=0,Timer50ms1=0;//��ʾʱ�������1S
uint16_t Back_Timer1S=0;
uint8_t DoorDelayTimer;
uint8_t Dis_System_Timer=0,Dis_Feel_Timer=0,Uart_Timer=0,Beep_Timer=0,LEDTimer=0;
uint8_t Set_Bat_Low_Flag=0;//��ʾ����ָʾ��־
uint8_t PowerLow_DisOFF=0;//=1��ʾ�������ʾ��ֻ�з�������

uint8_t TimemsCnt=0,Time100msFlag=0,Time100msCnt=0,Time1sFlag=0,Time1sCnt=0;
uint8_t PageNum=0;
uint8_t ZD_Test=0;
uint8_t FreshFlag=0;

uint8_t canbuf[8];
uint8_t TestKey=0;
uint8_t TestKey1=0;
//unsigned char K2_Pulse_Timer=0;
//bit K2_ON_Flag=0;//KC2��������
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
	if(Bat_Low_Flag)//������ϣ���������
	{
		if ( Set_Bat_Low_Flag == 0 )	//ȷ�Ͻ���ֻˢ��һ��
		{
			Set_Bat_Low_Flag = 1; 
			Beep_Alarm_Fault = 3;
			TCQ_Power_OFF();		//��������Դ�ر�
			Back_Led_OFF();			//�ر�LED����
			PageNum = 1;				//��ѹ��������
			Display_LowPower();	//��ʾ������ϵ���
			Dis_State_LED_OFF();//״ָ̬ʾ��ȫ��     
		}
		
		if (! GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))   //����ָ�����
		{  
			Set_Bat_Low_Flag=0;
			TCQ_Power_ON();				//��������Դ��
			Back_Led_ON();				//����ָ��󣬱��⿪��
			Bat_Low_Flag=0;
			Beep_Alarm_Fault=0; 
			Beep_OFF();		
		  World_Flag=0x1400;
			Dis_State_LED();			//״ָ̬ʾ����ʾ
			Delay1s(2);
			
			Display_Main_Face();	//����ˢ����ʾ����
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
			Display_Main_Face( );	//�����ָ�ˢ�½���
			PageNum = 0;					//�ָ�������ˢ��
		}
		
		Key_Control( );
	}

	if (! GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3))   //����ָ�����
	{  
		Dis_State_LED();//״ָ̬ʾ����ʾ
	} 
}
	
void KCS_Work(void)
{
	static uint8_t KCS_Flag=0;
	static uint8_t KCS_Up_Flag =0;
	if( KSC_Check() == 0 )//�ֶ���������
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
	
	//������·Ѳ��
	if(LoopOpenFlag == 1)//����������·����
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
	
	//Power_Check();			//������
	
	//Bat_Power_Check();	//������
	
	//����������ˢ��Ƶ��
	if(PageNum == 0)
	{
		if( ShowFrq > 9 ) 
		{
			ShowFrq=1;
		}

		if( Dis_Feel_Timer> (20*ShowFrq) )//ˢ��Ƶ��
		{   
			Dis_Feel_Timer=0;
			if(Display_Flag == 0)
				Display_Feel_Fault();//ֻ��ʾ���Ϻͱ���
			else
				Display_Main_Fault();

			Display_System_Sate();
			if (Self_Check_Flag==0) 
			{				
				Dis_State_LED();//״ָ̬ʾ����ʾ
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
			Function_Flag = 12;//��ѯһ�α������ֵ
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
	
	LED_Rev();	//����״ָ̬ʾ��ÿ����˸һ��
	
	Power_Check();			//������
	
	Bat_Power_Check();	//������
	
	Check_Fault_Alarm(); //���̽��������
	
	Check_Feel_Alarm();	//���̽��������
	
	if(PageNum == 0)
	{
		if (Dis_Key_Buff_Flag==0)
		{
			Read_RTC();	
			if(Dis_Alarm_Fault_Flag==0)
			{
				Display_System_Timer();	//ֻ�ڲ����������ʾʱ��
			}
		}
	}
	
}


int main(void)
{
	uint8_t i;
	
	System_Init();	//ϵͳ��ʼ��
	Back_Led_ON();//��ʾ�����⿪��
	
	Soft_RST();		//��ʾģ�鸴λ
	Delay1ms(100); 
  
	SD_Display_60S(2);//�ϵ���ʾ,��ʾ����������ʱ5��	
	
	Beep_ON();	//��λ���������
	lcd_inital();  //��ʾģ���ʼ��
	Delay1ms(500);
	Beep_OFF();
	Read_RTC();
	Save_Event_Record(1);//1:�������ϵ�  2������ػ�   3����λ   4�������¼   5����ʼ��
	Clr_Display();
	Display_Main_Face();
	//Display_Feel();
	Display_System_Sate();
	Dis_State_LED();//״ָ̬ʾ����ʾ
	Display_System_Timer();
	PageNum = 0;
	TCQ_ID_485 =LoopStart;

	SendPtr.SendCnt = 0;
	SendPtr.LoadCnt = 0;
	SendToPC1(11,0,0,0);
	while(1)
	{
		WDOG( );//ι��
		
		TimeMsWork();//���빤��	
		
//		#if 0//�ϴ�������PC
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
			CanSendWork();				//can���ͺ���	
			TimemsCnt = 0;
		}
		
		if( Time100msCnt >= 2 )	//100msѭ��ִ�еĹ���
		{
			Time100msCnt = 0;
			Time100msWork();
		}

		if( Time1sFlag )		//ÿ��ִ�еĹ���
		{
			Time1sFlag = 0;				
			SecondWork();	
		}
	}
}
