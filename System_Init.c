#include "stm32f10x.h"
#include "Declare.h"


void Eeprom_Init(void)
{  
	uint32_t Addr,iTemp,j;
	uint8_t Eeprom_Buff[25];
	uint8_t i,ReWrite=0;

// ----------Pass1------------

     Addr=0x01;
     RW24XX(Pass1,4,Addr,0xA1);
     if((Pass1[0]>9)||(Pass1[1]>9)||(Pass1[2]>9)||(Pass1[3]>9))   // ֻҪ������ڴ�������������
     {
         Pass1[0]=8;
         Pass1[1]=2;  
         Pass1[2]=3; 
         Pass1[3]=4;     
         RW24XX(Pass1,4,Addr,0xA0);// �ֽ�д��	
      }
     Delay1ms(10);
// ----------Pass2------------

     Addr=0x05;
     RW24XX(Pass2,4,Addr,0xA1);
     if((Pass2[0]>9)||(Pass2[1]>9)||(Pass2[2]>9)||(Pass2[3]>9))   // ֻҪ������ڴ�������������
     {
         Pass2[0]=2;
         Pass2[1]=2;  
         Pass2[2]=3; 
         Pass2[3]=4;     
         RW24XX(Pass2,4,Addr,0xA0);// �ֽ�д��	
     	  
      }    
     Delay1ms(10);
			
	//-------------��������-------------	
		Addr=0x40;
		RW24XX(GC_Name,21,Addr,0xA1);
		if(GC_Name[16]>99)  //
		{
			 for(i=0;i<16;i++)GC_Name[i]=0xA1;//�ո�
			 GC_Name[16]=16;
			 GC_Name[17]=11;
			 GC_Name[18]=16;
			 GC_Name[19]=15;
			 GC_Name[20]=30;			 
			 RW24XX(GC_Name,21,Addr,0xA0);// �ֽ�д��	

		}    
    Delay1ms(10);
//-----------------��������------------------
		Delay1ms(10);
		Addr=0x20;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);
		if ((Eeprom_Buff[0]>3)||(Eeprom_Buff[1]>3))   
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=0;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// �ֽ�д��	
		}

		LDK[0]=Eeprom_Buff[0];
		LDK[1]=Eeprom_Buff[1];
			 
//-----------------��ӡ��״̬-------------------------
  //  =0x00 ��ӡ���ر�
  //  =0x55 ֻ����������¼��ӡ
  //  =0xAA ��������ȫ����ӡ
     Addr=0x15;
     RW24XX(Eeprom_Buff,1,Addr,0xA1);
     if ((Eeprom_Buff[0]!=0x55)&&(Eeprom_Buff[0]!=0xAA))    
      {
         Eeprom_Buff[0]=0;
         RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);//�ֽ�д��
       }
      
     Print_State=Eeprom_Buff[0];
     Delay1ms(10);
//-----------------�����ַ------------------
		Delay1ms(10);
		Addr=0x16;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if (Eeprom_Buff[0]>99)  
		{
			Eeprom_Buff[0]=1;
			RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);// �ֽ�д��	
		}

		Self_Addr=Eeprom_Buff[0];
//-----------------ˢ��Ƶ��-------------------------
		Delay1ms(10);
		Addr=0x17;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if (Eeprom_Buff[0]>9)  
		{
			Eeprom_Buff[0]=1;
			RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);// �ֽ�д��	
		}

		ShowFrq=Eeprom_Buff[0];
//-----------------ͨ��ĩ��ַ------------------------
      
		Addr=0x09;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			 Eeprom_Buff[0]=0;
			 Eeprom_Buff[1]=1;
			 RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// �ֽ�д��	
		 }

		End_Addr=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);
//-----------------��·��ͨ���׵�ַ------------------------
	//LoopStart LoopEnd
		Addr=0x0B;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=1;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// �ֽ�д��	
		}

		LoopStart=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);	 
//-----------------��·��ͨ��ĩ��ַ------------------------
	//LoopStart LoopEnd
		Addr=0x0D;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=1;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// �ֽ�д��	
		}

		LoopEnd=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);		
 
//------------�����ֽ�1�������Ρ�0��ʾ��ʾ------------
//End_Addr=1;
     Addr=0x80;
		 if ((End_Addr==1)||(End_Addr==0))
     {
        for(i=0;i<64;i++) 
					Shield_Flag[i]=0;//���ڷ�����״̬
        RW24XX(Shield_Flag,64,Addr,0xA0); 
     }
     else 
		 {
				RW24XX(Shield_Flag,64,Addr,0xA1); 
		 }
		 Delay1ms(10);
		 Sum_Shield();
		 
//--------------����Ϣ����----------------------------

	for(iTemp=0;iTemp<LoopEnd;iTemp++)
	{ 
		Addr=0x8600+iTemp*3;
		RW24XX(Eeprom_Buff,3,Addr,0xA1); 
		for(j=0;j<3;j++) 
			address[iTemp][j]=Eeprom_Buff[j];
		Delay1ms(3);
	}
	
//---------- ������¼����2-------999------

		Addr=0x18;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);
		if((Eeprom_Buff[0]*256+Eeprom_Buff[1])>999)   // 9999
		{
			Eeprom_Buff[0]=0;  
			Eeprom_Buff[1]=0;
			RW24XX(Eeprom_Buff,2,Addr,0xA0);
		}
		AlarmRecount=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);
//////////////////////////
 //---------- �ϵ��¼����----500-----
		Addr=0x1A;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if(Eeprom_Buff[0]>99)   //99�����ϼ�¼
		{
			Eeprom_Buff[0]=0;

			RW24XX(Eeprom_Buff,1,Addr,0xA0);
		}
		SDRecount=Eeprom_Buff[0];   
		Delay1ms(10);

//////////////////////////
     //---------- ���ϼ�¼����---500----------		
		Addr=0x1C;
	
		RW24XX(Eeprom_Buff,2,Addr,0xA1);
		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>500)  
		{
			Eeprom_Buff[0]=0;  
			Eeprom_Buff[1]=0;
			RW24XX(Eeprom_Buff,2,Addr,0xA0);
		}
		FaultRecount=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);

//-----------------------------------------------------------
		Addr=0x1E;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if(Eeprom_Buff[0]>1)   
		{
			Eeprom_Buff[0]=1;

			RW24XX(Eeprom_Buff,1,Addr,0xA0);
		}
		LoopOpenFlag=Eeprom_Buff[0];   
		Delay1ms(10);
}

void Device_Init(void)
{  
	BD_ON();//����
	Beep_OFF();
	Speak_OFF();
	KC1_OFF();
	KC2_OFF();
	Set_World_Flag_Flag(2,0);//���ָʾ����
	Dis_State_LED();//״ָ̬ʾ����ʾ
	//TCQ_Power_ON(); 
	//Back_Led_ON();
} 	

void Data_Init(void)
{  
	uint16_t i,j;
	Dis_Key_Buff_Flag = 0;

	Dis_Num=0;
	SuperPassFlag = 0;
	Alarm_Rec_Position=0;
	Fault_Rec_Position=0;
	Fault_Rec=0;
	
	//XAlarm_Rec_Position=0;
	//  Alarm_RecP=0;//������·�ظ�����

	//KEY_Uart_Fault_Flag=0;
	//HMDoor_Flag=0;//�ֿ��ű�־

	Dis_Alarm_Fault_Flag=0;
	Fault_RecP=0;

	World_Flag=0x1400;//���繤�������̽���
	Set_World_Flag_Flag(6,0);

	
	Self_Check_Flag=0;//�Լ��־

	ARec_Position=0;//

	for(i=0;i<10;i++)
	{
		Alarm_Position[i] = 0;
	}


	for (i=0;i<512;i++)
	{
		Set_Uart_Fault_Timer0(i);//ͨѶ����	//Uart_Err_Timer[i]=0;
		Alarm_Flag_16[i] = 0;
	}
  
	for (i=0;i<64;i++)
	{ 
		Alarm_Flag[i]=0;
		Fault_Flag[i]=0;
	}
	
	for (i=0;i<24;i++)
	{ 
		Fault_Position[i]=0;
	}
	
	Key_Down_Flag=0;
	Key_Up_Flag=0;
		
	RecCnt=0;
	Rec_Begin_Flag=0;
	Rec_Flag=0;

	KEY_RecCnt=0;
	KEY_Rec_Begin_Flag=0;
	KEY_Uart_Err_Timer=0;
	KEYDoor_Flag=0;//��������Ч��ʶ
	NOBack_Flag=0;//δ������ʶ
	Function_Flag=1;//�ϵ�Ѳ��״̬

	RecPCCnt=0;
	RecPC_Begin_Flag=0;
	PCFunction_Flag=11;//�ϵ�ѯ��
	
	Set_World_Flag_Flag(12,1);//�ϵ�Ĭ�ϱ�������
	
	//SendToPC_Flag=0; 
}


void System_Init(void)
{ 
	RCC_Configuration() ;
	GPIO_Confing();

	IWDG_Configuration();
	WDOG();

	TIM3_Config(); 
	RTC_config();

	DMA_Config();
	ADC_Config();

	UART1Init();
	UART2Init();
	UART3Init();
	UART4Init();
	CAN_Config();	
	NVIC_Config(); 

	Eeprom_Init();
	Data_Init(); 
	Device_Init(); 
}
