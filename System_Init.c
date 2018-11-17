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
     if((Pass1[0]>9)||(Pass1[1]>9)||(Pass1[2]>9)||(Pass1[3]>9))   // 只要密码存在错误则重置密码
     {
         Pass1[0]=8;
         Pass1[1]=2;  
         Pass1[2]=3; 
         Pass1[3]=4;     
         RW24XX(Pass1,4,Addr,0xA0);// 字节写入	
      }
     Delay1ms(10);
// ----------Pass2------------

     Addr=0x05;
     RW24XX(Pass2,4,Addr,0xA1);
     if((Pass2[0]>9)||(Pass2[1]>9)||(Pass2[2]>9)||(Pass2[3]>9))   // 只要密码存在错误则重置密码
     {
         Pass2[0]=2;
         Pass2[1]=2;  
         Pass2[2]=3; 
         Pass2[3]=4;     
         RW24XX(Pass2,4,Addr,0xA0);// 字节写入	
     	  
      }    
     Delay1ms(10);
			
	//-------------工程名称-------------	
		Addr=0x40;
		RW24XX(GC_Name,21,Addr,0xA1);
		if(GC_Name[16]>99)  //
		{
			 for(i=0;i<16;i++)GC_Name[i]=0xA1;//空格
			 GC_Name[16]=16;
			 GC_Name[17]=11;
			 GC_Name[18]=16;
			 GC_Name[19]=15;
			 GC_Name[20]=30;			 
			 RW24XX(GC_Name,21,Addr,0xA0);// 字节写入	

		}    
    Delay1ms(10);
//-----------------联动控制------------------
		Delay1ms(10);
		Addr=0x20;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);
		if ((Eeprom_Buff[0]>3)||(Eeprom_Buff[1]>3))   
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=0;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// 字节写入	
		}

		LDK[0]=Eeprom_Buff[0];
		LDK[1]=Eeprom_Buff[1];
			 
//-----------------打印机状态-------------------------
  //  =0x00 打印机关闭
  //  =0x55 只开启报警记录打印
  //  =0xAA 报警故障全部打印
     Addr=0x15;
     RW24XX(Eeprom_Buff,1,Addr,0xA1);
     if ((Eeprom_Buff[0]!=0x55)&&(Eeprom_Buff[0]!=0xAA))    
      {
         Eeprom_Buff[0]=0;
         RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);//字节写入
       }
      
     Print_State=Eeprom_Buff[0];
     Delay1ms(10);
//-----------------自身地址------------------
		Delay1ms(10);
		Addr=0x16;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if (Eeprom_Buff[0]>99)  
		{
			Eeprom_Buff[0]=1;
			RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);// 字节写入	
		}

		Self_Addr=Eeprom_Buff[0];
//-----------------刷新频率-------------------------
		Delay1ms(10);
		Addr=0x17;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if (Eeprom_Buff[0]>9)  
		{
			Eeprom_Buff[0]=1;
			RW24XX(&Eeprom_Buff[0],1,Addr,0xA0);// 字节写入	
		}

		ShowFrq=Eeprom_Buff[0];
//-----------------通道末地址------------------------
      
		Addr=0x09;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			 Eeprom_Buff[0]=0;
			 Eeprom_Buff[1]=1;
			 RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// 字节写入	
		 }

		End_Addr=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);
//-----------------回路板通道首地址------------------------
	//LoopStart LoopEnd
		Addr=0x0B;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=1;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// 字节写入	
		}

		LoopStart=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);	 
//-----------------回路板通道末地址------------------------
	//LoopStart LoopEnd
		Addr=0x0D;
		RW24XX(Eeprom_Buff,2,Addr,0xA1);

		if ((Eeprom_Buff[0]*256+Eeprom_Buff[1])>MaxEndAddr)  
		{
			Eeprom_Buff[0]=0;
			Eeprom_Buff[1]=1;
			RW24XX(&Eeprom_Buff[0],2,Addr,0xA0);// 字节写入	
		}

		LoopEnd=Eeprom_Buff[0]*256+Eeprom_Buff[1];
		Delay1ms(10);		
 
//------------屏蔽字节1代表屏蔽　0表示显示------------
//End_Addr=1;
     Addr=0x80;
		 if ((End_Addr==1)||(End_Addr==0))
     {
        for(i=0;i<64;i++) 
					Shield_Flag[i]=0;//处于非屏蔽状态
        RW24XX(Shield_Flag,64,Addr,0xA0); 
     }
     else 
		 {
				RW24XX(Shield_Flag,64,Addr,0xA1); 
		 }
		 Delay1ms(10);
		 Sum_Shield();
		 
//--------------门信息参数----------------------------

	for(iTemp=0;iTemp<LoopEnd;iTemp++)
	{ 
		Addr=0x8600+iTemp*3;
		RW24XX(Eeprom_Buff,3,Addr,0xA1); 
		for(j=0;j<3;j++) 
			address[iTemp][j]=Eeprom_Buff[j];
		Delay1ms(3);
	}
	
//---------- 报警记录总数2-------999------

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
 //---------- 上电记录总数----500-----
		Addr=0x1A;
		RW24XX(Eeprom_Buff,1,Addr,0xA1);
		if(Eeprom_Buff[0]>99)   //99条故障记录
		{
			Eeprom_Buff[0]=0;

			RW24XX(Eeprom_Buff,1,Addr,0xA0);
		}
		SDRecount=Eeprom_Buff[0];   
		Delay1ms(10);

//////////////////////////
     //---------- 故障记录总数---500----------		
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
	BD_ON();//启动
	Beep_OFF();
	Speak_OFF();
	KC1_OFF();
	KC2_OFF();
	Set_World_Flag_Flag(2,0);//输出指示灯灭
	Dis_State_LED();//状态指示灯显示
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
	//  Alarm_RecP=0;//报警回路重复次数

	//KEY_Uart_Fault_Flag=0;
	//HMDoor_Flag=0;//手控门标志

	Dis_Alarm_Fault_Flag=0;
	Fault_RecP=0;

	World_Flag=0x1400;//主电工作、键盘解锁
	Set_World_Flag_Flag(6,0);

	
	Self_Check_Flag=0;//自检标志

	ARec_Position=0;//

	for(i=0;i<10;i++)
	{
		Alarm_Position[i] = 0;
	}


	for (i=0;i<512;i++)
	{
		Set_Uart_Fault_Timer0(i);//通讯次数	//Uart_Err_Timer[i]=0;
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
	KEYDoor_Flag=0;//按键控有效标识
	NOBack_Flag=0;//未反馈标识
	Function_Flag=1;//上电巡检状态

	RecPCCnt=0;
	RecPC_Begin_Flag=0;
	PCFunction_Flag=11;//上电询问
	
	Set_World_Flag_Flag(12,1);//上电默认备电正常
	
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
