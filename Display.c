#include "stm32f10x.h"
#include "Declare.h"

#define WLCR   0x00
#define MISC   0x01
#define ADSR   0x03
#define INTR   0x0F
#define WCCR   0x10
#define CHWI   0x11
#define MAMR   0x12

#define AWRR   0x20
#define DWWR   0x21
#define AWBR   0x30
#define DWHR   0x31
#define AWLR   0x40
#define AWTR   0x50
#define CPXR   0x60
#define BGSG   0x61
#define EDSG   0x62
#define CPYR   0x70
#define BGCM   0x71
#define EDCM   0x72
#define BTMR   0x80
#define ITCR   0x90
#define PNTR   0xe0

#define FNCR   0xF0
#define FVHT   0xf1


uint8_t hz[]={
"** * * * * * * * * * * * * * * * * * * *"
"*                                      *"
"*                                      *"
"*      临沂市安福电子科技有限公司      *"
"*　　　　　　　　　　　　　            *"
"*                                      *"
"*      AF116 电气火灾监控设备　　　  *"
"*          　　　     　　　　　       *"
"*               V1.0                   *"
"*　　　　　　　　　　　　　            *"
"*　　　　　　　　　　　　　            *"
"*                　　　　　　　　　    *"
"* 地址：山东省临沂市河东经济技术开发区 *"
"* TEL ：0539-6012963 FAX：0539-8165301 *"
"** * * * * * * * * * * * * * * * * * * *"
};
uint8_t Read_BUSY(void)
{
	if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==Bit_RESET)
		return 0 ;
	else 
		return 1;
	
}
////////////////////////////////
void delay_nms(unsigned int n)
{
        unsigned int i,j;
		for(i=n;i>0;i--)
		{
		    for(j=125;j>0;j--)
				{
				}
		}
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void Soft_RST(void)
{
	delay_nms(2);
	CS1_0();//cs1=0;
	RD_1();//rd = 1;
	RST_0();//rst=0;
	delay_nms(5);
	RST_1();//rst=1;
	delay_nms(5);
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void SendData(unsigned char dat)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOC,GPIO_Pin_6) ;
				else GPIO_ResetBits(GPIOC,GPIO_Pin_6) ;
				break;						
			}
			case 1:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_15) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_15) ;
				break;						
			}
			case 2:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_14) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_14) ;
				break;						
			}		
			case 3:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_13) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_13) ;
				break;						
			}				
			case 4:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_12) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_12) ;
				break;						
			}		
			case 5:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_11) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_11) ;
				break;						
			}	
			case 6:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_10) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_10) ;
				break;						
			}	
			case 7:
			{
				if((dat&0x80)==0x80) GPIO_SetBits(GPIOD,GPIO_Pin_9) ;
				else GPIO_ResetBits(GPIOD,GPIO_Pin_9) ;
				break;						
			}
			default:break;
		}
		dat<<=1;			
	}		

}


void LCD_CmdWrite(unsigned char dat)//8080
{		
	uint32_t m;
	m=0xFFFFFFFF;
	Delay1us(50);
//	while(m--) 
//	{
//		if(Read_BUSY()==1){ break;}//防止死循环
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_1();//rs=1;//发送命令
	//BUS=cmdaddr;//将数据写入并行总线
	SendData(dat);
	WR_0();//wr=0;
	WR_1();//wr=1;
	CS1_1();//cs1=1;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void LCD_DataWrite(unsigned char dat)
{  
	uint32_t m;
	m=0xFFFFFFFF;
	Delay1us(50);
//	while(m--) 
//	{
//		if(Read_BUSY()==1){ break;}//防止死循环
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_0();//rs=0;	//写入数据
	//BUS=dat;//将数据写入并行总线
	SendData(dat);	
	WR_0();//wr=0;
	WR_1();//wr=1;
	CS1_1();//cs1=1;
	Delay1us(50);
}


void GotoXY(unsigned char x,unsigned char y,unsigned char TP)
{     
   LCD_CmdWrite(CPXR); //x坐标
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y坐标
   LCD_DataWrite(y);
   LCD_CmdWrite(0x00); 
   LCD_DataWrite(TP);
 
   LCD_CmdWrite(0xb0); 
}

void Open_Cur(unsigned char x,unsigned char y)
{
   LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
   LCD_DataWrite(0x07);//(0x06);
   LCD_CmdWrite(CPXR); //x坐标
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y坐标
   LCD_DataWrite(y);
}


void Close_Cur(void)
{
  LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
  LCD_DataWrite(0x00);
}

///////////////////////////////////////////
void lcd_inital(void)
{ 
	LCD_CmdWrite(WLCR);		//[00H] , Default --> 0x00
	LCD_DataWrite(0x00);	

	LCD_CmdWrite(MISC);		//[01H] , Default --> 0x00
	LCD_DataWrite(0x88);//LCD_DataWrite(0x08);

	LCD_CmdWrite(ADSR);		//[03H] , Default --> 0x00 
	LCD_DataWrite(0x00);

	LCD_CmdWrite(INTR);		//[0FH] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CHWI);		//[11H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(MAMR);		//[12H] , Default --> 0x11 
	LCD_DataWrite(0x11);

	LCD_CmdWrite(AWRR);		//[20H] , Default --> 0x27
	LCD_DataWrite(39);

	LCD_CmdWrite(DWWR);		//[21H] , Default --> 0x27
	LCD_DataWrite(39);

	LCD_CmdWrite(AWBR);		//[30H] , Default --> 0xEF	
	LCD_DataWrite(239);

	LCD_CmdWrite(DWHR);		//[31H] , Default --> 0xEF
	LCD_DataWrite(239);

	LCD_CmdWrite(AWLR);		//[40H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(AWTR);		//[50H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CPXR);		//[60H] , Default --> 0x00 
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BGSG);		//[61H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(EDSG);		//[62H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(CPYR);		//[70H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BGCM);		//[71H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(EDCM);		//[72H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(BTMR);		//[80H] , Default --> 0x00
	LCD_DataWrite(0x33);

	LCD_CmdWrite(ITCR);		//[90H] , Default --> 0x00    需要调整
	LCD_DataWrite(0x80);

	LCD_CmdWrite(PNTR);		//[E0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FNCR);		//[F0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FVHT);		//[F1H] , Default --> 0x00
	LCD_DataWrite(0x00);
}
/////////////////清屏子程序//////////////////////////
void Clr_Display(void)
{ 
  LCD_CmdWrite(0x00);
  LCD_DataWrite(0x04);     //选择绘图模式     
  LCD_CmdWrite(0xe0);
  LCD_DataWrite(0x00);
  LCD_CmdWrite(0xf0);
  LCD_DataWrite(0xa8);
  delay_nms(100);
}

/////////////显示中文字库和字符////////////////////
void Display_S(unsigned char *Str,unsigned int length)
{ 
	unsigned int ii;
  
	for(ii=0;ii<length;ii++)//strlen(Str)
	{
		LCD_DataWrite(*Str);  
		++Str;
		// delay_nms(1);
	}   
}

void dis_char(uint16_t temp2)
{
	uint8_t i;

	for(i = 0;i < 16;i++)
	{   
		SCLK_dis_0();
		Delay1us(5);
		if(temp2 & 0x8000) 
			SDA_dis_1();
		else  
			SDA_dis_0();
		Delay1us(5);
		SCLK_dis_1();
		Delay1us(5);
		temp2 = (temp2<<1);
	}
}

void Dis_State_LED_ON(void)//状态指示灯全亮
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0x0000; 
   dis_char(temp2);
   DIS_ON();
}

void Dis_State_LED_OFF(void)//状态指示灯全灭
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0xFFFF; 
   dis_char(temp2);
   DIS_ON();
}


void Dis_State_LED(void)//状态指示灯显示
{
	uint16_t temp2;

	DIS_OFF();
	/*
	if(Alarm_Rec_Position!=0)  
		Set_World_Flag_Flag(2,1);//启动

	if(XAlarm_Rec_Position!=0)
	{ 
		if(Flash_Flag)	 
		{
			Set_World_Flag_Flag(2,1);
			Flash_Flag=0;
		}//启动闪亮＝未反馈
		else 
		{
			Set_World_Flag_Flag(2,0);
			Flash_Flag=1;
		}
	} 
	if(RAlarm_Rec_Position!=0) 
		Set_World_Flag_Flag(4,1);//反馈
	else 
		Set_World_Flag_Flag(4,0); 
*/
	temp2=0xFFFF-World_Flag; 
	dis_char(temp2);
	DIS_ON();
}

void Display_LowPower(void)
{
  uint8_t hz1[]={"备用电源电压不足"};
  //uint8_t hz2[]={"请及时采用主电给系统供电！"};


   Clr_Display();
	 GotoXY(12,100,Dis_T);
   Display_S(hz1,16);
}

void SD_Display_60S(unsigned char TNum)//上电显示
{
  unsigned char i;

  Clr_Display();
  GotoXY(0,0,Dis_T);
  Display_S(hz,600);
  
  for(i=TNum;i>0;i--)
  {
    
     GotoXY(30,145,Dis_T);
     LCD_DataWrite('<');  
     LCD_DataWrite(ChCode[i/10]); 
     LCD_DataWrite(ChCode[i%10]); 
     LCD_DataWrite('>');  
     Delay1ms(800);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
     WDOG(); 
   }
}

void Line_X(unsigned char x,unsigned char y, unsigned char x1)
{
  unsigned char i;
  GotoXY(x,y,Dis_P);//绘图方式 
  for(i=0;i<=(x1-x);i++) {LCD_DataWrite(0xFF); }
}

void Line_Y(unsigned char x,unsigned char y, unsigned char y1)
{
  unsigned char i;
 
  for(i=0;i<=(y1-y);i++)
  { 
     
     if (x==40) 
     { GotoXY(39,(y+i),Dis_P);
       LCD_DataWrite(0x01);
      }
     else
     { GotoXY(x,(y+i),Dis_P);//绘图方式
       LCD_DataWrite(0x80); 
     }
   }
 
}

void Display_Main_Face(void)
{
  unsigned char hz0[]={"系统正常监控中..."};
  unsigned char hz1[]={"故障回路信息：     "};
  unsigned char hz2[]={"报警回路信息：     "};
  unsigned char hz3[]={"系统故障信息：     "};
	
	Clr_Display();

	//GotoXY(3,103,Dis_T);//文字显示方式，显示系统正常监控中
	//Display_S(hz0,17);
	
	Line_Y(0,0,239);
	Line_Y(40,0,239);
	Line_Y(21,0,221);
	
	//Line_X(0,18,39);
	//Line_X(0,239,39);
	
	Line_X(0,0,39);
	Line_X(0,239,39);
	
	GotoXY(1,1,Dis_T);//显示运行状态
	Display_S(hz1,14);

	GotoXY(23,1,Dis_T);//显示报警信息
	Display_S(hz2,14);
	//Line_X(0,35,39);
	Line_X(0,17,39);
	
	GotoXY(23,124+18,Dis_T);//显示故障信息
	Display_S(hz3,14);
	Line_X(21,123+18,39);
	Line_X(21,140+18,39);

	//----------------------------------

	Line_X(0,221,39);
}

void Dis_NoAlarmR(void)	//显示无报警记录
{  
	unsigned char hz0[]={"无报警记录！"};

  GotoXY(25,70,Dis_T);
  Display_S(hz0,12);
}

void Dis_NoFaultR(void)	//显示无故障记录
{ 
	unsigned char hz0[]={"无故障记录！"};
  unsigned char hz1[]={"                   "};
  unsigned char X,Y,i;
	
  X=25;
  Y=145+18;
	for(i=0;i<3;i++)//	for(i=0;i<4;i++)
	{  
		GotoXY(X,Y+i*18,Dis_T);
		Display_S(hz1,14);
	} 

  GotoXY(25,163+18,Dis_T);
  Display_S(hz0,12);
}

void Display_System_Timer(void)
{ 
	unsigned char hz0[]={"当前时间：20"};
	unsigned char nian[]={"年"};
	unsigned char yue[]={"月"};
	unsigned char ri[]={"日"};
	unsigned char shi[]={"时"};
	unsigned char fen[]={"分"};
	unsigned char miao[]={"秒"};
	
	uint8_t temp;

  GotoXY(1,222,Dis_T);
  Display_S(hz0,12);
	
	GotoXY(13,222,Dis_T);

	temp=Real_Time.year%2000/10;//年
  LCD_DataWrite(ChCode[temp]); //年
	temp=Real_Time.year%2000%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	temp=Real_Time.month/10;//月
	LCD_DataWrite(ChCode[temp]); //月
	temp=Real_Time.month%10;
	LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	
	temp=Real_Time.day/10;//日
	LCD_DataWrite(ChCode[temp]); //日
	temp=Real_Time.day%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite(' ');
 
 	temp=Real_Time.hour/10;//时
	LCD_DataWrite(ChCode[temp]); //时
	temp=Real_Time.hour%10;
	LCD_DataWrite(ChCode[temp]); //时
  LCD_DataWrite(':');
 
	temp=Real_Time.min/10;//分
	LCD_DataWrite(ChCode[temp]); //分
	temp=Real_Time.min%10;
  LCD_DataWrite(ChCode[temp]); //分
  LCD_DataWrite(':');

	temp=Real_Time.sec/10;//秒
	LCD_DataWrite(ChCode[temp]); //秒
	temp=Real_Time.sec%10;
	LCD_DataWrite(ChCode[temp]); //秒
}

//------------------------

void Clear_Dispaly_Feel(void)
{
		unsigned char i;
		unsigned char hz10[]={"                     "};
		for(i=0;i<12;i++)//需要刷新显示区域
		{
			GotoXY(2,18+i*17,Dis_T);
			Display_S(hz10,19);
		}		
}


void Display_Feel_Fault(void)//仅显示故障
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"正常　　"};
		unsigned char hz1[]={"报警　★"};
		unsigned char hz2[]={"故障　◇"};
		unsigned char hz3[]={"通讯故障&报警"};
		unsigned char hz4[]={"探测器ID　 运行状态"};
		unsigned char hz5[]={"探测器ID  地址 状态"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"开路"};
		unsigned char hz8[]={"短路"};
		unsigned char hz9[]={"系统正常监控中..."};
		unsigned char hz10[]={"                     "};
		unsigned char hz11[]={"区"};
		unsigned char hz12[]={"号"};
		unsigned char hz13[]={"单元"};
		GotoXY(1,1,Dis_T);//通讯故障&报警
		Display_S(hz3,14);
		
		GotoXY(16,1,Dis_T);//通讯故障&报警
		Display_S(hz10,4);

		if( LoopEnd > 256 )	//EndAddr大于256检测4次通讯错误
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;
		

		
		if( Fault_Num == 0 )
		{		
			Clear_Dispaly_Feel();
			
			GotoXY(3,103,Dis_T);//文字显示方式，显示系统正常监控中
			Display_S(hz9,17);
		}
		else
		{
			i=0;
			X=2;
			Y=18;
			
			while(i<12)//每次显示12行探测器数据 //只显示故障和报警
			{ 
				 if ((!Check_Shield_State(Dis_Num))&&((Uart_Fault_Timer(Dis_Num)>=cTemp)||(Check_Alarm_State(Dis_Num)))) //没有屏蔽并且小于64
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num+1)/100;
							 LCD_DataWrite(ChCode[temp]);  //地址号 
							 temp=(Dis_Num+1)%100/10;
							 LCD_DataWrite(ChCode[temp]);
							 temp=(Dis_Num+1)%10;
							 LCD_DataWrite(ChCode[temp]);
							 LCD_DataWrite(' ');
							 
							if(Dis_Num >= End_Addr)
							{
								 LCD_DataWrite('H');	//表示设备在回路板上
								 LCD_DataWrite('1');
								 LCD_DataWrite(' ');
							}
							else	
							{							
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
							}
							
							 LCD_DataWrite(' ');

							 GotoXY(X+10,Y+i*17,Dis_T);
						
							if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8次通讯失败任务通讯故障
								Display_S(hz2,8);//故障 
							else if (Check_Alarm_State(Dis_Num))
								Display_S(hz1,8);//报警
							else  
								Display_S(hz0,8);//正常
							
							if(DisplayAddr == 1)//显示设备安装地址
							{
								GotoXY(X+8,Y+i*17,Dis_T);

								temp=address[Dis_Num][0]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][0]%10;
								LCD_DataWrite(ChCode[temp]);			
								
								Display_S(hz11,2);//区

								temp=address[Dis_Num][1]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][1]%10;
								LCD_DataWrite(ChCode[temp]);
								Display_S(hz12,2);//号
		
								temp=address[Dis_Num][2]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][2]%10;
								LCD_DataWrite(ChCode[temp]);								
							}
							else
							{
								GotoXY(X+7,Y+i*17,Dis_T);
								Display_S(hz6,3);//正常
							}
					 i++; 
				 }//如果没有屏蔽时处理结束

				 
				 if( LoopOpenFlag == 1)	//开启回路1功能
				 {
						if (Dis_Num<(End_Addr-1)) //EndAddr
						{
							Dis_Num++; 
						}
						else if( Dis_Num < (LoopStart-1) )
						{
							Dis_Num = LoopStart-1;
						}
						else if(Dis_Num < (LoopEnd -1))
						{
							Dis_Num++; 
						}
						else
						{
							Dis_Num=0;
							while (i<12)
							{   
								if (i==0) 
									break;
								
								GotoXY(X,Y+i*17,Dis_T);
								
								for(j=0;j<18;j++) 
									LCD_DataWrite(' ');  //地址号 
								i++;
							}
							break; 
						} 
				 
				 }
				 else	//只使用主回路
				 {
						if (Dis_Num<(End_Addr-1)) //EndAddr
						{
							Dis_Num++; 
						}
						else
						{
							Dis_Num=0;
							while (i<12)
							{   
								if (i==0) 
									break;
								
								GotoXY(X,Y+i*17,Dis_T);
								
								for(j=0;j<18;j++) 
									LCD_DataWrite(' ');  //地址号 
								i++;
							}
							break; 
						} 
				 } 
			}//while 结束
		
		}

}

void Display_Main_Fault(void)
{
		unsigned char pn,X,Y;
		unsigned char i,j,temp;
		unsigned char hz0[]={"正常　　"};
		unsigned char hz1[]={"报警　★"};
		unsigned char hz2[]={"故障　◇"};
		unsigned char hz3[]={"通讯故障"};
		unsigned char hz4[]={"回路开路"};
		unsigned char hz5[]={"回路短路"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"开路"};
		unsigned char hz8[]={"短路"};
		unsigned char hz9[]={"系统正常监控中..."};
		unsigned char hz10[]={"                     "};	
		unsigned char hz11[]={"故障回路信息: "};
		uint8_t cTemp;
		uint8_t huilu;
		uint8_t huilustate;
		uint8_t first;
		
		GotoXY(1,1,Dis_T);//显示运行状态
		Display_S(hz11,14);
		
		pn = Fault_Rec;	//回路故障
		
		X=16;
		Y=1;
    GotoXY(X,Y,Dis_T);
    first=0;
		
		temp=pn/100;
    if (temp==0)  ;//LCD_DataWrite(' ');
    else 
		{ 
			LCD_DataWrite(ChCode[temp]);
			first=1;
		}
		
    temp=pn%100/10;
    if ((temp==0)&&(first==0))  
			LCD_DataWrite(' '); 
    else 
			LCD_DataWrite(ChCode[temp]);  
    temp=pn%10;
    LCD_DataWrite(ChCode[temp]); 		
		
		if( pn == 0 )//故障总数
		{
			for(i=0;i<12;i++)//需要刷新显示区域
			{
				GotoXY(2,18+i*17,Dis_T);
				Display_S(hz10,19);
			}		
			
			GotoXY(3,103,Dis_T);//文字显示方式，显示系统正常监控中
			Display_S(hz9,17);
		}
		else
		{
			GotoXY(3,103,Dis_T);//清除系统正常监控中
			Display_S(hz10,17);
			i=0;
			X=2;
			Y=18;
			
			if(pn>12)
				pn=12;
					
			while(i<pn)//每次显示12行探测器数据	//只显示故障和报警
			{  
				 Dis_Num = Fault_Position[i]&0x3FF;//低10位表示设备号
				 huilu = (Fault_Position[i]>>12)&0x0F;
				 huilustate=(Fault_Position[i]>>10) & 0x03;
				if (!Check_Shield_State(Dis_Num)) 
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num)/100;
							 LCD_DataWrite(ChCode[temp]);  //地址号 
							 temp=(Dis_Num)%100/10;
							 LCD_DataWrite(ChCode[temp]);
							 temp=(Dis_Num)%10;
							 LCD_DataWrite(ChCode[temp]);
							 LCD_DataWrite('-');
					 
							 temp=(huilu+1)/10;
							 LCD_DataWrite(ChCode[temp]);
							 temp=(huilu+1)%10;
							 LCD_DataWrite(ChCode[temp]);
					 
							if(Dis_Num > End_Addr)
							{
								 LCD_DataWrite(' ');
								 LCD_DataWrite('H');	//表示设备在回路板上
								 LCD_DataWrite('1');
							}
							else	
							{							
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
							}
							
							if(huilustate==1)//短路
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz5,8);//回路短路
							}
							else if(huilustate==2)//开路
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz4,8);//回路短路
							}
							else if(huilustate==3)//通讯故障
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz3,8);//回路短路
							}			
					i++;
				 }//如果没有屏蔽时处理结束	
					 
			}//while 结束
		
		}

}
void Display_Feel(void)
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"正常　　"};
		unsigned char hz1[]={"报警　★"};
		unsigned char hz2[]={"故障　◇"};
		unsigned char hz3[]={"        "};
		unsigned char hz4[]={"探测器ID　 运行状态"};
		unsigned char hz5[]={"探测器ID  地址 状态"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"开路"};
		unsigned char hz8[]={"短路"};
		unsigned char hz9[]={"系统正常监控中..."};
		if( LoopEnd > 256 )	//EndAddr大于256检测4次通讯错误
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;

		i=0;
		X=2;
		Y=18;
		
		while(i<12)//每次显示12行探测器数据
		{  
       if (!Check_Shield_State(Dis_Num)) //没有屏蔽并且小于64
       { 
             GotoXY(X,Y+i*17,Dis_T);
             temp=(Dis_Num+1)/100;
             LCD_DataWrite(ChCode[temp]);  //地址号 
             temp=(Dis_Num+1)%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=(Dis_Num+1)%10;
             LCD_DataWrite(ChCode[temp]);
             LCD_DataWrite(' ');
            
						if(Dis_Num >= End_Addr)
						{
							 LCD_DataWrite('H');	//表示设备在回路板上
							 LCD_DataWrite('1');
							 LCD_DataWrite(' ');
						}
						else	
						{							
							LCD_DataWrite(' ');
							LCD_DataWrite(' ');
							LCD_DataWrite(' ');
						}
						
             LCD_DataWrite(' ');

             GotoXY(X+10,Y+i*17,Dis_T);
            
						
					
            if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8次通讯失败任务通讯故障
							Display_S(hz2,8);//故障 
            else if (Check_Alarm_State(Dis_Num))	//超限报警
							Display_S(hz1,8);//报警
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz7,8);//开路
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz8,8);//短路
            else  
							Display_S(hz0,8);//正常
						
						if(DisplayAddr == 1)//显示设备安装地址
						{
							GotoXY(X+7,Y+i*17,Dis_T);

							temp=address[Dis_Num][0]/10;//年
							LCD_DataWrite(ChCode[temp]); //年
							temp=address[Dis_Num][0]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');

							temp=address[Dis_Num][1]/10;//月
							LCD_DataWrite(ChCode[temp]); //月
							temp=address[Dis_Num][1]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');
	
							temp=address[Dis_Num][2]/10;//日
							LCD_DataWrite(ChCode[temp]); //日
							temp=address[Dis_Num][2]%10;
							LCD_DataWrite(ChCode[temp]);		
						}
						else
						{
						  GotoXY(X+7,Y+i*17,Dis_T);
							Display_S(hz6,3);//正常
						}
         i++; 
       }//如果没有屏蔽时处理结束

			 
			 if( LoopOpenFlag == 1)	//开启回路1功能
			 {
					if (Dis_Num<(End_Addr-1)) //EndAddr
					{
						Dis_Num++; 
					}
					else if( Dis_Num < (LoopStart-1) )
					{
						Dis_Num = LoopStart-1;
					}
					else if(Dis_Num < (LoopEnd -1))
					{
						Dis_Num++; 
					}
					else
					{
						Dis_Num=0;
						while (i<12)
						{   
							if (i==0) 
								break;
							
							GotoXY(X,Y+i*17,Dis_T);
							
							for(j=0;j<18;j++) 
								LCD_DataWrite(' ');  //地址号 
							i++;
						}
						break; 
					} 
			 
			 }
			 else	//只使用主回路
			 {
					if (Dis_Num<(End_Addr-1)) //EndAddr
					{
						Dis_Num++; 
					}
					else
					{
						Dis_Num=0;
						while (i<12)
						{   
							if (i==0) 
								break;
							
							GotoXY(X,Y+i*17,Dis_T);
							
							for(j=0;j<18;j++) 
								LCD_DataWrite(' ');  //地址号 
							i++;
						}
						break; 
					} 
			 } 
    }//while 结束　
}


void Display_System_Sate(void)
{
	unsigned char hz0[]={"℃"};
	unsigned char hz1[]={"MA"};
	
	unsigned char hz3[]={"通讯故障：  "};
	unsigned char hz4[]={"探测故障：  "};
	unsigned char hz5[]={"主电故障    "};
	unsigned char hz6[]={"备电故障    "};
	unsigned char hz7[]={"充电故障    "};
	unsigned char hz8[]={"            "};
	unsigned char hz9[]={"                  "};
	unsigned char X,Y,i,j;
	unsigned int pn;
	uint8_t first=0;
	uint16_t nbit_F,temp;

	X=36;
	Y=1;

	GotoXY(X,Y,Dis_T);
	pn=Alarm_Rec_Position;//计算报警部位总数
	
	first=0;				//显示报警回路总数
	temp=pn/100;		//百位
	if (temp==0)  
		LCD_DataWrite(' ');
	else 
	{ 
		LCD_DataWrite(ChCode[temp]);
		first=1;
	}//通道号
	
	temp=pn%100/10;	//十位
	if ((temp==0)&&(first==0))  
		LCD_DataWrite(' '); 
	else 
		LCD_DataWrite(ChCode[temp]);  
	
	temp=pn%10;			//个位
	LCD_DataWrite(ChCode[temp]);

	if (pn==0) 
	{
		//显示前清理显示区域
		for(i=0;i<7;i++)
		{
			GotoXY(22,20+i*16,Dis_T);
			Display_S(hz9,17);
		}		
		Dis_NoAlarmR();
	}
	else
	{
		GotoXY(25,70,Dis_T);//清除无报警记录
		for(i=0;i<12;i++)   
			LCD_DataWrite(' ');

		Y=20;	//原为36
		//最多显示7条报警数据
		if (pn>7)
			pn=7;
		
		for(i=0;i<pn;i++)
		{  
			if (i<7) 
				X=22;
			else 
				X=31;
		
			temp=Alarm_Position[i]%4096/100;	//设备号  后12位数字，百位
			GotoXY(X,Y+i%7*16,Dis_T);
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%100/10;
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%10;
			LCD_DataWrite(ChCode[temp]);
			LCD_DataWrite('-');

			if ((Alarm_Position[i]/4096)==0) 	//001-02 回路号  表示高4位
			{ 
				LCD_DataWrite('T');
				LCD_DataWrite(' ');
			}
			else
			{
				temp=Alarm_Position[i]/4096/10;
				LCD_DataWrite(ChCode[temp]);
				temp=Alarm_Position[i]/4096%10;
				LCD_DataWrite(ChCode[temp]);
			}
			LCD_DataWrite(' ');
			first = 0;
			temp = Alarm_Data[i]/1000;		//千位
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%1000/100;	//百位
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			temp = Alarm_Data[i]%100/10;		//十位
			
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%10;				//个位
			LCD_DataWrite(ChCode[temp]);
			
			if ((Alarm_Position[i]/4096)==0) 	//001-02 回路号  表示高4位
			{ 
				LCD_DataWrite('T');
				LCD_DataWrite(' ');
			}
			else
			{
				LCD_DataWrite('m');
				LCD_DataWrite('A');
			}	
		}
	}
//------------------------------------------
   
  if (Fault_Rec_Position==0)//故障总数
	{
		Dis_NoFaultR();
	}
  else
  {
		GotoXY(25,163,Dis_T);
		for(i=0;i<12;i++)   
			LCD_DataWrite(' ');

		//X=25;
		//Y=145;		
		X=25;
		Y=145+18;//下移一行	
		i=0;
		GotoXY(X,Y,Dis_T);
		Display_S(hz3,13);//显示通讯故障
		//i++; 

		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 11);	//11主电故障
		if( nbit_F ) //	if (Check_World_Flag_State(11))
		{  
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz5,13);
			i++;  
		}//主电故障
		
		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 13);	//13 备电故障
		if ( nbit_F ) // if (Check_World_Flag_State(5))  
		{   
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz6,13);
			i++;
		}//备电故障
/*
		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 7);
		if( nbit_F )  //if (Check_World_Flag_State(7)) 
		{   
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz7,13);
			i++;
		}//充电故障
*/
		X=25;
		Y=145+18;//下移一行
		for(j=i+1;j<3;j++)//清理显示区域
		{  
			GotoXY(X,Y+j*18,Dis_T);
			Display_S(hz8,13);
		} 
   
    X=34;
    GotoXY(X,Y,Dis_T);
    first=0;
    
    pn=Fault_Rec_Position-i;//探测故障总数 减去增加的备电故障 主电故障
    Fault_Num = pn;
		temp=pn/100;
    if (temp==0)  ;//LCD_DataWrite(' ');
    else 
		{ 
			LCD_DataWrite(ChCode[temp]);
			first=1;
		}
		
    temp=pn%100/10;
    if ((temp==0)&&(first==0))  
			LCD_DataWrite(' '); 
    else 
			LCD_DataWrite(ChCode[temp]);  
    temp=pn%10;
    LCD_DataWrite(ChCode[temp]); 
   }
} 

 
void Display_Alarm(uint16_t Num)
{
	uint8_t hz1[]={"门启动　"};
	//uint8_t hz2[]={"已反馈　"};
	//uint8_t hz3[]={"未反馈　"};
	//uint8_t hz4[]={"反馈恢复"};

	//uint8_t hz6[]={"　启动：　反馈：　未反馈：　　　　"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//文字显示方式

	Display_S(hz1,17);
}


void Display_Fault(uint16_t Num)
{
	//uint8_t hz0[]={"　　　　"};
	uint8_t hz1[]={"门故障　"};
	//uint8_t hz2[]={"通讯故障"};
	//uint8_t hz3[]={"主电故障"};
	//uint8_t hz4[]={"备电故障"};
	//uint8_t hz5[]={"系统故障"};
	//uint8_t hz6[]={"　　故障信息总数：　　　　　　　　　　"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//文字显示方式

	Display_S(hz1,17);

}

void Dis_Pass1_Promt(void)//输入密码界面
{  
  unsigned char hz1[]={"请输入一级密码："};
  unsigned char i;
  unsigned char X,Y;
	Clr_Display();
	GotoXY(12,60,Dis_T);//文本方式 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

  X=14;
  Y=105;
  for (i=0;i<4;i++)
  {
     GotoXY(X+3*i,Y,Dis_T);//文本方式 
     LCD_DataWrite('*'); 
   }
  Open_Cur(X,Y+2);
}

void Dis_Pass(void)
{ 
  unsigned char X,Y;

  X=14;
  Y=105;
 
  GotoXY(X+3*Flicker_Position,Y,Dis_T);
  LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 
 
  if (Flicker_Position==3) 
	{	
		Open_Cur(X,Y+2);
	}
  else 
	{
		Open_Cur(X+3*(Flicker_Position+1),Y+2);
	}

}

void Self_Check(void)//系统自检提示
{ 
	unsigned char hz1[]={"系统正在进行自检，请稍候...  "};
	unsigned char temp;

	uint8_t i;
	
	Clr_Display();
	GotoXY(8,80,Dis_T);  
	Display_S(hz1,28);
	
	for (i=0;i<6;i++)
	{
		DIS_OFF();
		//dis_char(0xFFFF-(0x0003<<(2*i))&0xFFBF);
		dis_char(0xFFFF-(0x0003<<(2*i))&0xFFFF);
	 
		DIS_ON();
		Delay1ms(800);
		WDOG();
	}

   DIS_OFF();
   dis_char(0x0000);//全亮
   DIS_ON();
   Delay1ms(1000);
		
   DIS_OFF();
   //dis_char(0xFFBF);
	 dis_char(0xFFFF);
   DIS_ON();
	
	Beep_Alarm_Fault=2;          // 故障音  
	Delay1s(4);
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault!=2)   
	{  
		Beep_OFF(); 
	} 

	Speak_ON();        // 报警音  
	Delay1s(4);
	Speak_OFF();
	 
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault==1)   
	{  
		Speak_ON(); 
	}
}

void Dis_Err(void)//密码错误提示显示
{ 
	unsigned char hz1[]={"密码错误!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_Query_Menu(void)
{ 
	unsigned char hz0[]={"记录查询菜单列表"};
	unsigned char hz1[]={"1 报警记录查询"
											 "2 故障记录查询"
											 "3 事件记录查询"};
                        
                      
  unsigned char X,Y,i;
   
	Clr_Display();

	GotoXY(11,12,Dis_T);
	Display_S(hz0,16);

	X=12;Y=60;
	for(i=0;i<3;i++)
	{    
		 GotoXY(X,Y+40*i,Dis_T); 
		 Display_S(&hz1[14*i],14);
	}  
	Line_Y(8,40,200);
	Line_Y(29,40,200);

	Line_X(8,40,28);
	Line_X(8,200,28);
}

void Dis_No_Record(void)
{
  unsigned char hz0[]={"没有查询记录！"};

  Clr_Display();
  GotoXY(14,100,Dis_T);
  Display_S(hz0,16);
}

void Display_Alarm_Record_Bar(void)
{
	unsigned char hz0[]={"序号　 探测ID 　回路号　　报警时间      "};

	Clr_Display();

	GotoXY(2,1,Dis_T);
	Display_S(hz0,37);


	Line_Y(0,0,239);
	Line_Y(40,0,239);

	Line_X(0,0,39);
	Line_X(0,239,39);
}


void Display_Alarm_Record(unsigned int AlarmNum)
{
	unsigned char hz0[]={"序号　 探测ID 　回路号　　报警时间      "};//{"序号  探测ID 回路号　　报警时间        "};
	unsigned char hz1[]={"通过↑↓翻页 "};
	unsigned char hz2[]={"★"};
	unsigned char hz3[]={"  "}; 

  unsigned char X,Y;
  unsigned char i,j,temp;

	unsigned char DataBuff[10];

	unsigned int Addr;
	unsigned int temp2;
 
   Clr_Display();
   GotoXY(2,1,Dis_T);
   Display_S(hz0,37);
   Line_Y(0,0,220);
   Line_Y(40,0,220);
   Line_X(0,0,39);
   Line_X(0,220,39);

   GotoXY(3,222,Dis_T);//显示第几页
   Display_S(hz1,12);
   GotoXY(28,222,Dis_T);
   temp=(AlarmNum/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(AlarmNum/12+1)%10;
   LCD_DataWrite(ChCode[temp]);
   LCD_DataWrite(' ');
   LCD_DataWrite('/');
   LCD_DataWrite(' ');
   temp=(AlarmRecount/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(AlarmRecount/12+1)%10;
   LCD_DataWrite(ChCode[temp]);

   i=0;
   X=1;
   Y=19;
   while(i<12)
   {  
      if (AlarmNum<1)//通道号、浓度值清空
      { while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//清空
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x502 + (AlarmNum-1) * 16;//计算地址�
					//EA=0; 
					Delay1ms(1);
				  RW24XX(DataBuff,10,Addr,0xA1);
					Delay1ms(1);
					//EA=1;
	
  				GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Alarm_Rec_Position+Alarm_RecP;
          if (temp2>AlarmRecount)    Display_S(hz2,2);//显示★
          else    Display_S(hz3,2);

					temp2=DataBuff[0]*256+DataBuff[1];
					temp=temp2/100;         //报警记录数2字节
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);
				
//          temp=DataBuff[0]%10;         //报警记录数2字节
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]/10;
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]%10;
//          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];
					
					temp=temp2/100;
					
          GotoXY(X+8,Y+i*16,Dis_T);         //探测ID
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);

          GotoXY(X+16,Y+i*16,Dis_T);  
          if (DataBuff[4]==0) 
          { 
            LCD_DataWrite(' ');
            LCD_DataWrite('T');
            
           }
          else 
          {
            temp=DataBuff[4]/10;//回路号
            LCD_DataWrite(ChCode[temp]);
            temp=DataBuff[4]%10;     
            LCD_DataWrite(ChCode[temp]);
           }
           //读时间：年月日时分－－[5]..[9]                 
          temp=DataBuff[5]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//年
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6]/10;                   
          LCD_DataWrite(ChCode[temp]);//月
          temp=DataBuff[6]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[7]/10;
          LCD_DataWrite(ChCode[temp]);//日
          temp=DataBuff[7]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[8]/10;        
          LCD_DataWrite(ChCode[temp]);//时
          temp=DataBuff[8]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[9]/10;
          LCD_DataWrite(ChCode[temp]);//分
          temp=DataBuff[9]%10;
          LCD_DataWrite(ChCode[temp]);
    
         
        }
        i++;
     
       if (AlarmNum>0) AlarmNum--;
       else AlarmNum=0; 

      }
}

void Dis_Query_Menu1(void)
{  
	unsigned char hz2[]={"→"};
	unsigned char i;
	unsigned char X,Y;

	X=10;Y=62;
	for(i=0;i<3;i++)
	{    
		GotoXY(X,Y+40*i,Dis_T); 
		if (i==menu)   
		{
			Display_S(hz2,2);
		}
		else  
		{
			LCD_DataWrite(' '); 
			LCD_DataWrite(' '); 
		}
	}
}

void Dis_Main_Menu(void)
{  
 unsigned char hz0[]={"一级菜单列表"};

 unsigned char hz1[]={"   1 设置系统容量       6 设置系统时钟  "
                           "   2 系统参数配置       7 设置刷新频率  "
                           "   3 显示探测配置     　8 设置本机地址  "
                           "   4 手动测试脱扣    　 9 进入二级操作  "
                           "   5 实时显示测量值     10设备安装位置  "};
	unsigned char hz2[]={"按数字1至10或↑、↓选择菜单  "};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,5,Dis_T);
	Display_S(hz0,12);
//显示菜单
	X=0;Y=45;
	for (i=0;i<5;i++)
	{
		GotoXY(X,Y+35*i,Dis_T);
		Display_S(&hz1[40*i],40);
	}
//画边框
	Line_Y(0,28,220);
	Line_Y(40,28,220);

	Line_X(0,28,39);
	Line_X(0,220,39);
//显示提示文字
	GotoXY(7,223,Dis_T);
	Display_S(hz2,30);
}

void Dis_Main_Menu1(void)
{  
	unsigned char hz2[]={"→"};//显示菜单指示

	unsigned char i;
	unsigned char X,Y;

	X=0;Y=47;

	for(i=0;i<5;i++)
	{    
		GotoXY(X+1,Y+35*i,Dis_T); 
		if (i==menu)   
		{
			Display_S(hz2,2);
		}
		else  
		{
			LCD_DataWrite(' '); 
			LCD_DataWrite(' '); 
		}
	}

	for(i=5;i<10;i++)
	{    
		GotoXY(X+22,Y+35*(i-5),Dis_T); 
		if (i==menu)
		{			
			Display_S(hz2,2);
		}
		else  
		{
			LCD_DataWrite(' '); 
			LCD_DataWrite(' '); 
		}
	}

}

   
void Dis_PB_Bar(void)
{  
	u8 hz1[]={"请输入探测器ID范围："};
	u8 hz2[]={"主机回路ID范围："};
	u8 hz3[]={"辅助回路ID范围："};
	u8 X,Y;

	Clr_Display();
	GotoXY(10,10,Dis_T);//文本方式 
	Display_S(hz1,20);//

	GotoXY(11,40,Dis_T);//文本方式 
	Display_S(hz2,16);//

	Line_Y(8,70,110);
	Line_Y(30,70,110);
	
	Line_X(8,70,29);
	Line_X(8,110,29);

	
	if( LoopOpenFlag ==1 )
	{
		//辅助回路ID范围
		GotoXY(11,130,Dis_T);//文本方式 
		Display_S(hz3,20);//
		
		Line_Y(8,160,200);
		Line_Y(30,160,200);
		
		Line_X(8,160,29);
		Line_X(8,200,29);
		X=13;
		Y=170;
		GotoXY(X,Y,Dis_T);

		LCD_DataWrite(ChCode[dis_buff[3]]); 
		LCD_DataWrite(ChCode[dis_buff[4]]); 
		LCD_DataWrite(ChCode[dis_buff[5]]); 
		LCD_DataWrite(' '); 
		LCD_DataWrite('-'); 
		LCD_DataWrite('-'); 
		LCD_DataWrite('-'); 

		X=21;
		Y=170;
		GotoXY(X,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[6]]); 
		LCD_DataWrite(ChCode[dis_buff[7]]); 
		LCD_DataWrite(ChCode[dis_buff[8]]); 
	}
	
	X=13;
	Y=80;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite('0'); 
	LCD_DataWrite('0'); 
	LCD_DataWrite('1'); 
	LCD_DataWrite(' '); 
	LCD_DataWrite('-'); 
	LCD_DataWrite('-'); 
	LCD_DataWrite('-'); 

	X=21;
	Y=80;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[0]]); 
	LCD_DataWrite(ChCode[dis_buff[1]]); 
	LCD_DataWrite(ChCode[dis_buff[2]]); 
	
	Open_Cur(X,Y+2);
}

void Dis_PB_Text(void)
{
	unsigned char X,Y;

	if(Flicker_Position<=2)
	{
		X=21;
		Y=80;
		GotoXY(X+Flicker_Position,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

//		if (Flicker_Position==2)
//		{
//			//X=13;
//			//Y=170;
//			Open_Cur(X,Y+2);
//		}
//		else 
			Open_Cur(X+Flicker_Position,Y+2); 
	}
	else if(Flicker_Position<=5)
	{	
		X=13;
		Y=170;
		GotoXY(X+Flicker_Position-3,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

//		if (Flicker_Position==5)
//		{
//			//X=21;
//			//Y=170;
//			Open_Cur(X,Y+2);
//		}
//		else 
			Open_Cur(X+Flicker_Position-3,Y+2); 
	
	}
	else if(Flicker_Position<=8)
	{
		X=21;
		Y=170;
		GotoXY(X+Flicker_Position-6,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

//		if (Flicker_Position==8)
//		{
//			//X=21;
//			//Y=80;
//			Open_Cur(X,Y+2);
//		}
//		else 
			Open_Cur(X+Flicker_Position-6,Y+2); 
	}
	
	
}

void Dis_PB_Bar1(void)
{ 
  unsigned char hz1[]={"主机回路ID屏蔽与开启设置窗口"};
  unsigned char hz2[]={"ID号"};
  unsigned char hz3[]={"状态"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//文本方式 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//竖线
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//ID号
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//状态
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text1(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"◎"};
	unsigned char hz2[]={"●"};//◎开启,●屏蔽
	unsigned char i;
	unsigned char X,Y;
	unsigned int temp;

  uint8_t first=0;
  

   for (i=0;i<35;i++)
   { 
     
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+1;//为通道号
     if (temp>End_Addr)    //大于64之后，
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //探测器ID清空
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //屏蔽状态清空
         LCD_DataWrite(' ');
        
         
      }
     else 
     {   GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//通道号
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i))//屏蔽状态
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+1;//为通道号
   if (temp>End_Addr)  return;  //大于64之后，
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//文本方式 //显示页号
    if ((Flicker_Position+1)/10==0)
    {  LCD_DataWrite(' ');
       LCD_DataWrite(ChCode[(Flicker_Position+1)%10]);
     }
    else 
    {
       LCD_DataWrite(ChCode[(Flicker_Position+1)/10]);
       LCD_DataWrite(ChCode[(Flicker_Position+1)%10]);
     }
    
    LCD_DataWrite('/');
    if ((End_Addr/35+1)/10==0)
    {   
        LCD_DataWrite(ChCode[(End_Addr/35+1)%10]);
        LCD_DataWrite(' ');
     }
    else 
    {  LCD_DataWrite(ChCode[(End_Addr/35+1)/10]);
       LCD_DataWrite(ChCode[(End_Addr/35+1)%10]);
     }
//-----------------------------------------------------------------
    X=7+(Key_Input_Value%7)*5;
    Y=21*2*(Key_Input_Value/7)+23+22;
    GotoXY(X,Y,Dis_T);
    if (PB_Flag)  Display_S(hz2,2);// 屏蔽状态              
    else Display_S(hz1,2);
   
   //--------------下限值 闪烁----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_PB_Bar2(void)
{ 
  unsigned char hz1[]={"辅助回路ID屏蔽与开启设置窗口"};
  unsigned char hz2[]={"ID号"};
  unsigned char hz3[]={"状态"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//文本方式 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//竖线
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//ID号
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//状态
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text2(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"◎"};
	unsigned char hz2[]={"●"};//◎开启,●屏蔽
	unsigned char i;
	unsigned char X,Y;
	u16 temp;

  uint8_t first=0;
  
   for (i=0;i<35;i++)
   { 
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+LoopStart;//为通道号
     if (temp>LoopEnd)    //大于64之后，
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //探测器ID清空
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //屏蔽状态清空
         LCD_DataWrite(' ');    
      }
     else 
     {  
					GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//通道号
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i+LoopStart-1))//屏蔽状态
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+LoopStart;//为通道号
   if (temp>LoopEnd)  return;  //大于64之后，
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//文本方式 //显示页号
    if ((Flicker_Position+1)/10==0)
    {  LCD_DataWrite(' ');
       LCD_DataWrite(ChCode[(Flicker_Position+1)%10]);
     }
    else 
    {
       LCD_DataWrite(ChCode[(Flicker_Position+1)/10]);
       LCD_DataWrite(ChCode[(Flicker_Position+1)%10]);
     }
    
    LCD_DataWrite('/');
    if (((LoopEnd-LoopStart)/35+1)/10==0)
    {   
        LCD_DataWrite(ChCode[((LoopEnd-LoopStart)/35+1)%10]);
        LCD_DataWrite(' ');
     }
    else 
    {  LCD_DataWrite(ChCode[((LoopEnd-LoopStart)/35+1)/10]);
       LCD_DataWrite(ChCode[((LoopEnd-LoopStart)/35+1)%10]);
     }
//-----------------------------------------------------------------
    X=7+(Key_Input_Value%7)*5;
    Y=21*2*(Key_Input_Value/7)+23+22;
    GotoXY(X,Y,Dis_T);
    if (PB_Flag)  Display_S(hz2,2);// 屏蔽状态              
    else Display_S(hz1,2);
   
   //--------------下限值 闪烁----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_SystemP_Bar(void)
{

	unsigned char hz1[]={"系统打印机配置窗口"};
	unsigned char hz2[]={"打印机关闭"};
	unsigned char hz3[]={"打印机开启"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//文本方式 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//文本方式 
	Display_S(hz2,10);//
	GotoXY(14,100,Dis_T);//文本方式 
	Display_S(hz3,10);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_SystemP_Text1(void)
{  
	unsigned char X,Y;
	//unsigned char hz1[]={"√"};
	//unsigned char hz2[]={"●"};
	unsigned char hz1[]={"●"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"⊙ 报警记录打印"};
	unsigned char hz4[]={"⊙ 故障记录打印"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (Print_State==0)//选择打印机关闭
	{
		GotoXY(X,Y,Dis_T);
		Display_S(hz1,2);//
		GotoXY(X,Y+40,Dis_T);
		Display_S(hz2,2);

		GotoXY(X+2,Y+70,Dis_T);
		Display_S(hz5,15);
		GotoXY(X+2,Y+100,Dis_T);
		Display_S(hz5,15);
	}
	else	//打印机开启
	{  
		GotoXY(X,Y,Dis_T);
		Display_S(hz2,2);//
		GotoXY(X,Y+40,Dis_T);
		Display_S(hz1,2);

		GotoXY(X+2,Y+70,Dis_T);
		Display_S(hz3,15);
		GotoXY(X+2,Y+100,Dis_T);
		Display_S(hz4,15);
	} 
}

void Dis_Loop_Bar(void)
{

	unsigned char hz1[]={"探测器回路配置窗口"};
	unsigned char hz2[]={"回路功能关闭"};
	unsigned char hz3[]={"回路功能开启"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//文本方式 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//文本方式 
	Display_S(hz2,12);//
	GotoXY(14,100,Dis_T);//文本方式 
	Display_S(hz3,12);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_Loop_Text1(void)
{  
	unsigned char X,Y;
	unsigned char hz1[]={"●"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"⊙ 开启辅助回路"};
	unsigned char hz4[]={"⊙ 开启回路设置"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (LoopOpenFlag==0)//辅助回路关闭
	{
		GotoXY(X,Y,Dis_T);
		Display_S(hz1,2);//
		GotoXY(X,Y+40,Dis_T);
		Display_S(hz2,2);

		GotoXY(X+2,Y+70,Dis_T);
		Display_S(hz5,15);
		GotoXY(X+2,Y+100,Dis_T);
		Display_S(hz5,15);
	}
	else//回路开启
	{  
		GotoXY(X,Y,Dis_T);
		Display_S(hz2,2);//
		GotoXY(X,Y+40,Dis_T);
		Display_S(hz1,2);

		GotoXY(X+2,Y+70,Dis_T);
		Display_S(hz3,15);
		GotoXY(X+2,Y+100,Dis_T);
		Display_S(hz4,15);
	} 
}


void Dis_Addr_Bar(void)
{
	u8 X,Y;
	unsigned char hz1[]={"探测器位置信息设置"};
	unsigned char hz2[]={"探测器ID"};
	unsigned char hz3[]={"安装位置"};
	Clr_Display();

	GotoXY(10,10,Dis_T);//文本方式 
	Display_S(hz1,18);//

	GotoXY(10,60,Dis_T);//文本方式 
	Display_S(hz2,8);//

	GotoXY(20,60,Dis_T);//文本方式 
	Display_S(hz3,8);//
	
	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
	
	X=12;
	Y=90;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[0]]); 
	LCD_DataWrite(ChCode[dis_buff[1]]); 
	LCD_DataWrite(ChCode[dis_buff[2]]);  
	LCD_DataWrite(' '); 
	Open_Cur(X,Y+2);
	X=20;
	Y=90;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[3]]); 
	LCD_DataWrite(ChCode[dis_buff[4]]); 
	LCD_DataWrite('-'); 
	LCD_DataWrite(ChCode[dis_buff[5]]); 
	LCD_DataWrite(ChCode[dis_buff[6]]);
	LCD_DataWrite('-'); 
	LCD_DataWrite(ChCode[dis_buff[7]]); 
	LCD_DataWrite(ChCode[dis_buff[8]]);
	
	//Open_Cur(X,Y+2);
}


void Dis_Addr_Text1(void)
{  
	unsigned char X,Y;

	if(Flicker_Position<=2)
	{
		X=12;
		Y=90;
		GotoXY(X+Flicker_Position,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

		Open_Cur(X+Flicker_Position,Y+2); 
	}
	else if(Flicker_Position<=4)
	{	
		X=20;
		Y=90;
		GotoXY(X+Flicker_Position-3,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

		Open_Cur(X+Flicker_Position-3,Y+2); 
	
	}
	else if(Flicker_Position<=6)
	{
		X=23;
		Y=90;
		GotoXY(X+Flicker_Position-5,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]);  
		
		Open_Cur(X+Flicker_Position-5,Y+2); 
	}
	else if(Flicker_Position<=8)
	{
		X=26;
		Y=90;
		GotoXY(X+Flicker_Position-7,Y,Dis_T);
		LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]);  
		
		Open_Cur(X+Flicker_Position-7,Y+2); 
	}
}




void Dis_OK(void)
{
  unsigned char hz1[]={"设置成功!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_SetPOK(void)
{
	unsigned char hz1[]={"设置成功!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}

void Dis_SetPErr(void)
{ 
	unsigned char hz1[]={"保存失败!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}


void Dis_TCQ_State_Bar1(void)
{ 
	unsigned char hz1[]={"探测器配置状态窗口"};
	unsigned char hz2[]={"回路ID号"};
	unsigned char hz3[]={"设 定 值"};
	unsigned char hz4[]={"检测类别"};
	unsigned char hz5[]={"脱扣状态"};
	unsigned char hz6[]={"请输入探测器ID号："};
	unsigned char i,X,Y;
    
    Clr_Display();
   
    GotoXY(10,0,Dis_T);//文本方式 
    Display_S(hz1,18);//

   X=5;
   Y=18;


   for(i=0;i<8;i++)
   {  
     if (i==0) Line_Y(0,18,216);
     else if (i==1) Line_Y(10,18,216);
          else if(i==7) Line_Y(5+5*i,18,216);//竖线
          else Line_Y(5+5*i,18,196);//竖线
    }


    X=1;
    Y=18;
    Line_X(0,Y,39);
    for(i=0;i<3;i++)
    {  
       GotoXY(X,Y+3*i*20+2,Dis_T);//ID号
       Display_S(hz2,8);//
       Line_X(0,Y+(3*i+1)*20-1,39);
 
       GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//设定值
       Display_S(hz3,8);//
       Line_X(0,Y+(3*i+2)*20-1,39);

       GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//检测类别
       Display_S(hz4,8);//
       Line_X(0,Y+(3*i+3)*20-1,39);
      
     }

     GotoXY(X,Y+3*i*20+2,Dis_T);//脱扣状态
     Display_S(hz5,8);//
     Line_X(0,Y+(3*i+1)*20-1,39);
   
 
     GotoXY(0,222,Dis_T);//输入探测ID号
     Display_S(hz6,18);//

     X=17;
     Y=219;
     Line_Y(X,Y,Y+19);
     Line_Y(X+8,Y,Y+19);
     Line_X(X,Y,X+7);
     Line_X(X,Y+19,X+7);

     X=19;
     Y=220;
     GotoXY(X,Y,Dis_T);
     for(i=0;i<3;i++)
     {
       
        LCD_DataWrite(ChCode[dis_buff[i]]);

      }
    Open_Cur(X,Y+1);
}


void Dis_TCQ_State_Text1(void)
{ 
  unsigned char X,Y,i;
 
  X=19;
  Y=220;
  GotoXY(X,Y,Dis_T);
	for(i=0;i<3;i++)
	{
		LCD_DataWrite(ChCode[dis_buff[i]]);
	}
 // GotoXY(X+Flicker_Position,Y,Dis_T);
//  LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 
 
  if (Flicker_Position==2) Open_Cur(X,Y+1);
  else Open_Cur(X+(Flicker_Position+1),Y+1);
}
void Read_Error(void)
{
	unsigned char hz0[]={"读取失败！"};
	unsigned char hz1[]={"读取中..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  //Display_S(hz1,10);	//读取中
  Display_S(hz0,10);//读取失败
}


void Clear_Read_State(void)
{
	unsigned char hz0[]={"读取失败！"};
	unsigned char hz1[]={"读取中..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);	//读取中
  //Display_S(hz0,10);//读取失败

  GotoXY(13,200,Dis_T);//脱扣状态
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//回路号
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//设定值
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//检测类别
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}
void Plase_Check(void)
{
	unsigned char hz0[]={"请确认！"};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz0,10);//

  GotoXY(13,200,Dis_T);//脱扣状态
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//回路号
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//设定值
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//检测类别
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}

void Dis_TCQ_State_Return(void)
{
	unsigned char hz0[]={"℃"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"开启状态"};
	unsigned char hz3[]={"已被屏蔽"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"读取成功！"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//脱扣状态 =1开启 =0开启    13 14
  
	lTemp = 0;
	lTemp = Rec_Buff[13];//检测类型
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //其中有一路开启则显示脱扣开启
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Rec_Buff[5];//检测类型
		temp3 = ((lTemp<<8)|Rec_Buff[6])&(0x01<<i);
		//temp3= Rec_Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Rec_Buff[7];//屏蔽状态
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//地址回路号 0回路17 18 1回路20 21
			temp2= (Rec_Buff[17+4*i]& 0x03) *256+Rec_Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID号
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//通道号
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//设定值
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//检测类别
			if (temp3==0)//CAN根据最高位判断，485回路0都是温度？
			{  
				Display_S(hz0,2); 
			}
			else
			{
				Display_S(hz1,2);
			}
		}
	}
	
}
void Dis_485_State_Return(void)
{
	unsigned char hz0[]={"℃"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"开启状态"};
	unsigned char hz3[]={"已被屏蔽"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"读取成功！"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//脱扣状态 =1开启 =0开启    13 14
  
	lTemp = 0;
	lTemp = Buff[13];//检测类型
	lTemp = (lTemp<<8)|Buff[14];
	
	if (lTemp) //其中有一路开启则显示脱扣开启
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Buff[5];//检测类型
		temp3 = ((lTemp<<8)|Buff[6])&(0x01<<i);
		//temp3= Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Buff[7];//屏蔽状态
		temp4 = ((lTemp<<8)|Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//地址回路号 0回路17 18 1回路20 21
			temp2= (Buff[17+4*i]& 0x03) *256+Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID号
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//通道号
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//设定值
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//检测类别
			if (temp3==0)//CAN根据最高位判断，485回路0都是温度？
			{  
				Display_S(hz0,2); 
			}
			else
			{
				Display_S(hz1,2);
			}
		}
	}
	
}

void Dis_LD_Bar(void)
{    
	unsigned char hz0[]={"↓"};
	unsigned char hz1[]={"脱扣测试输出窗口"};
	unsigned char hz2[]={"主控设备:"};
	unsigned char hz3[]={"探测器ID:"};
	unsigned char hz4[]={"开启"};
	unsigned char hz5[]={"关闭"};
	// code unsigned char hz6[]={"按〈确认〉键进行测试"};
	unsigned char X,Y,i;

	Clr_Display();

	GotoXY(10,0,Dis_T);//
	Display_S(hz1,16);//

	X=4;
	Y=60;
	GotoXY(X,Y,Dis_T);
	Display_S(hz2,10);//主控设备

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//开启

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//关闭

	X=4;
	Y=120;
	GotoXY(X,Y,Dis_T);
	Display_S(hz3,10);//探测器ID

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//开启

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//关闭

	X=19;
	Y=40;
	GotoXY(X,Y,Dis_T); //显示↓
	Display_S(hz0,2);

	X=17;  //开启
	Y=57;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=57;//　　关闭
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=17; //开启
	Y=117;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=117;//　　关闭
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);
	
	/*   X=13;
	Y=120;
	Line_Y(X,Y,Y+19);
	Line_Y(X+5,Y,Y+19);
	Line_X(X,Y,X+4);
	Line_X(X,Y+19,X+4);
	*/
	X=13;
	Y=120;
	GotoXY(X,Y,Dis_T);
	for(i=0;i<3;i++)
	{
		LCD_DataWrite(ChCode[dis_buff[i]]);
	}
	Open_Cur(X,Y+1);    
}


void Dis_LD_Text(void)
{ 

	unsigned char hz0[]={"↓"};
	unsigned char X,Y,i;

	X=19;
	Y=40;
	for(i=0;i<4;i++)
	{    
		GotoXY(X+(i%2)*10,Y+60*(i/2),Dis_T); 
		if (i==Key_Input_Value)  
		{			
			Display_S(hz0,2);
		}
		else  
		{
			LCD_DataWrite(' '); LCD_DataWrite(' '); 
		}

	}

	X=13;
	Y=120;
	GotoXY(X+Flicker_Position,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

	if (Flicker_Position==2) 
		Open_Cur(X,Y+1);
	else 
		Open_Cur(X+(Flicker_Position+1),Y+1);
}

void Dis_Test_Fl_Bar1(void)
{ 
	unsigned char hz1[]={"实时监测探测器数据窗口"};
	unsigned char hz2[]={"回路ID号"};
	unsigned char hz3[]={"设 定 值"};
	unsigned char hz4[]={"检测类别"};
	unsigned char hz5[]={"脱扣状态"};
	unsigned char hz6[]={"请输入探测器ID号："};
	unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(8,0,Dis_T);//文本方式 
	Display_S(hz1,22);//

	X=5;
	Y=18;

	for(i=0;i<8;i++)
	{  
		if (i==0) Line_Y(0,18,216);
		else if (i==1) Line_Y(10,18,216);
		else if(i==7) Line_Y(5+5*i,18,216);//竖线
		else Line_Y(5+5*i,18,196);//竖线
	}
	
	X=1;
	Y=18;
	Line_X(0,Y,39);
	for(i=0;i<3;i++)
	{  
		GotoXY(X,Y+3*i*20+2,Dis_T);//ID号
		Display_S(hz2,8);//
		Line_X(0,Y+(3*i+1)*20-1,39);

		GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//设定值
		Display_S(hz3,8);//
		Line_X(0,Y+(3*i+2)*20-1,39);

		GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//检测类别
		Display_S(hz4,8);//
		Line_X(0,Y+(3*i+3)*20-1,39);
	}

	GotoXY(X,Y+3*i*20+2,Dis_T);//脱扣状态
	Display_S(hz5,8);//
	Line_X(0,Y+(3*i+1)*20-1,39);


	GotoXY(0,222,Dis_T);//输入探测ID号
	Display_S(hz6,18);//

	X=17;
	Y=219;
	Line_Y(X,Y,Y+19);
	Line_Y(X+8,Y,Y+19);
	Line_X(X,Y,X+7);
	Line_X(X,Y+19,X+7);

	X=19;
	Y=220;
	GotoXY(X,Y,Dis_T);
	for(i=0;i<3;i++)
	{
		LCD_DataWrite(ChCode[dis_buff[i]]);
	}
	Open_Cur(X,Y+1);
}

void Dis_Test_Fl_Text1(void)
{ 
	unsigned char X,Y,i;

	X=19;
	Y=220;
	GotoXY(X,Y,Dis_T);
	for(i=0;i<3;i++)
	{
		LCD_DataWrite(ChCode[dis_buff[i]]);
	}
 // GotoXY(X+Flicker_Position,Y,Dis_T);
 // LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 
 
  if (Flicker_Position==2) 
		Open_Cur(X,Y+1);
  else 
		Open_Cur(X+(Flicker_Position+1),Y+1);
}

void Clear_Read_Fl(void)
{
	unsigned char hz0[]={"读取失败！"};
	unsigned char hz1[]={"读取中..."};
	unsigned char hz2[]={"        "};
	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);//

  GotoXY(13,200,Dis_T);//脱扣状态
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {

			//----------------------------------
			X=11+(i%6)*5;
			Y=20+20*3*(i/6);     
			GotoXY(X,Y,Dis_T);//回路号

			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+20,Dis_T);//设定值
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+40,Dis_T);//检测类别
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
   }
}

void Dis_Test_Fl_Return(void)
{
	unsigned char hz0[]={"℃"};
	unsigned char hz1[]={"MA"};
	unsigned char hz3[]={"已被屏蔽"};
	unsigned char hz2[]={"开启状态"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"读取成功！"};

	#if 1
	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//脱扣状态
	
	lTemp = 0;
	lTemp = Rec_Buff[13];//检测类型
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //其中有一路开启则显示脱扣开启
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Rec_Buff[5];
		temp3 = ((lTemp<<8)|Rec_Buff[6])&(0x01<<i);
		lTemp = 0;
		lTemp = Rec_Buff[7];//屏蔽状态
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);

		if(temp4==0)
		{
			temp=i;//地址回路号 0回路19 20 1回路23 24
			temp2= (Rec_Buff[19+4*i]& 0x03) *256+Rec_Buff[20+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID号
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//通道号
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//设定值
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//检测类别
			if (temp3==0) 
			{  
				Display_S(hz0,2); 
			}
			else
			{
				Display_S(hz1,2);
			}
		}	
	
	}
	#else
	/*
  GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//脱扣状态
  if ((Rec_Buff[5]& 0x80)==0) 
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);

  for(i=0;i<(TCQ_Return_Length-3)/2;i++)
  {
     temp=(Rec_Buff[5+2*i]& 0x7C)>>2;//地址回路号

     temp2= (Rec_Buff[5+2*i]& 0x03) *256+Rec_Buff[6+2*i]; 
    //----------------------------------
     X=11+(temp%6)*5;
     Y=20+20*3*(temp/6);     
     GotoXY(X,Y,Dis_T);//ID号
     first=0;
     if ((temp/100)==0) ;// LCD_DataWrite(' ');
     else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//通道号
     if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
     else LCD_DataWrite(ChCode[temp%100/10]);
     LCD_DataWrite(ChCode[temp%10]);
     //---------------------------------
      Y=40+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//设定值
      temp1=temp2/100;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%100/10;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%10;
      LCD_DataWrite(ChCode[temp1]);
     //---------------------------------
      Y=60+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//检测类别
      if (temp==0) 
      {  Display_S(hz0,2); 
       }
      else
      {
        Display_S(hz1,2);
       }
    }
		*/
	#endif
}

void Dis_Set_System_Timer_Promt(void)
{
	unsigned char hz1[]={"请输入系统时间："};
	unsigned char hz2[]={"20  年  月  日　时  分  秒"};
	unsigned char i,X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//请输入系统时间
	Display_S(hz1,16);//

	GotoXY(8,105,Dis_T);// 年  月  日　时  分  秒
	Display_S(hz2,26);

	Line_Y(6,90,140);
	Line_Y(36,90,140);
	Line_X(6,90,35);
	Line_X(6,140,35);


	X=10;
	Y=105;

	for (i=0;i<6;i++)
	{
		 GotoXY(X+4*i,Y,Dis_T);
		 LCD_DataWrite(ChCode[dis_buff[2*i]]); 
		 LCD_DataWrite(ChCode[dis_buff[2*i+1]]); 
	}
	Open_Cur(X,Y+2);
}

void Dis_Set_System_Timer(void)
{  
	unsigned char X,Y;

	X=10;
	Y=105;

	GotoXY(X+Flicker_Position+2*(Flicker_Position/2),Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 



 if (Flicker_Position==11) Open_Cur(X,Y+2);
 else Open_Cur(X+Flicker_Position+1+2*((Flicker_Position+1)/2),Y+2);
  
}


void Dis_ShowFrq_Bar(void)
{

	unsigned char hz1[]={"请输入刷新时间："};
	unsigned char hz2[]={"秒"};

	Clr_Display();

	GotoXY(12,60,Dis_T);//文本方式 
	Display_S(hz1,16);//
	GotoXY(21,105,Dis_T);//文本方式 
	Display_S(hz2,2);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29); 
}


void Dis_ShowFrq_Text1(void)
{  
	unsigned char X,Y;

	X=18;
	Y=105;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite(ChCode[ShowFrq]); 

	Open_Cur(X,Y+2);
}

void Dis_Err1(void)
{  
	unsigned char hz1[]={"保存失败!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);

}


void Dis_SetAddr_Bar(void)
{
	unsigned char hz1[]={"请输入本机地址："};
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//文本方式 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

	X=18;
	Y=105;
	GotoXY(X,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[0]]); 
	LCD_DataWrite(ChCode[dis_buff[1]]); 
	Open_Cur(X,Y+2);
}

void Dis_SetAddr_Text1(void)
{ 
	unsigned char X,Y;

	X=18;
	Y=105;
	GotoXY(X+Flicker_Position,Y,Dis_T);
	LCD_DataWrite(ChCode[dis_buff[Flicker_Position]]); 

	if (Flicker_Position==0)
		Open_Cur(X+1,Y+2);
	else 
		Open_Cur(X,Y+2);
   
}


void Dis_Pass2_Promt(void)
{  
	unsigned char hz1[]={"请输入二级密码："};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//文本方式 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);



	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
	 GotoXY(X+3*i,Y,Dis_T);//文本方式 
	 LCD_DataWrite('*'); 
	}
	Open_Cur(X,Y+2);
 
}


void Dis_Main_Menu2(void)
{ 
	unsigned char hz0[]={"二级菜单列表"};
	unsigned char hz1[]={"更改一级密码"
											 "更改二级密码"
											 "清除系统记录"
	                     "回路功能设置"};
	unsigned char hz2[]={"→"};
	unsigned char X,Y,i;

	Clr_Display();

	GotoXY(12,12,Dis_T);
	Display_S(hz0,12);

	X=13;Y=60;
	for(i=0;i<4;i++)
	{    
		GotoXY(X,Y+40*i,Dis_T); 
		Display_S(&hz1[12*i],12);
	}  
	Line_Y(8,40,200);
	Line_Y(29,40,200);

	Line_X(8,40,28);
	Line_X(8,200,28);

	for(i=0;i<4;i++)
	{    
		GotoXY(10,Y+40*i,Dis_T); 
		if (i==menu)   Display_S(hz2,2);
		else  {LCD_DataWrite(' '); LCD_DataWrite(' '); }
	}
}

void Display_Fault_Record_Bar(void)
{
	unsigned char hz0[]={"序号  探测ID 故障描述　    故障时间　        "};

	Clr_Display();

	GotoXY(2,1,Dis_T);
	Display_S(hz0,37);

	Line_Y(0,0,239);
	Line_Y(40,0,239);

	Line_X(0,0,39);
	Line_X(0,239,39);
}

void Display_Fault_Record(unsigned int FaultNum)
{   
	unsigned char hz0[]={"序号  探测ID 故障描述　    故障时间　        "};
	unsigned char hz1[]={"通过↑↓翻页 "};
	unsigned char hz2[]={"◇"};
	unsigned char hz3[]={"  "}; 

  unsigned char hz4[]={"通讯故障"};
  unsigned char hz5[]={"主电故障"};
  unsigned char hz6[]={"备电故障"};
  unsigned char hz7[]={"充电故障"};
	unsigned char hz8[]={"回路开路"};
	unsigned char hz9[]={"回路短路"};
	unsigned char X,Y;
	unsigned char i,j,temp;

	unsigned char DataBuff[10];

	unsigned int Addr;
	unsigned int temp2;
	uint8_t type_error;//故障类型
 
   Clr_Display();
   GotoXY(2,1,Dis_T);
   Display_S(hz0,37);
   Line_Y(0,0,220);
   Line_Y(40,0,220);
   Line_X(0,0,39);
   Line_X(0,220,39);

   GotoXY(3,222,Dis_T);//显示第几页
   Display_S(hz1,12);
   GotoXY(28,222,Dis_T);
   temp=(FaultNum/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(FaultNum/12+1)%10;
   LCD_DataWrite(ChCode[temp]);
   LCD_DataWrite(' ');
   LCD_DataWrite('/');
   LCD_DataWrite(' ');
   temp=(FaultRecount/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(FaultRecount/12+1)%10;
   LCD_DataWrite(ChCode[temp]);

   i=0;
   X=1;
   Y=19;
   while(i<12)
   {  
      if (FaultNum<1)//通道号、浓度值清空
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//清空
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x4602 + (FaultNum-1) * 16;
					Delay1ms(1);
					RW24XX(DataBuff,9+1,Addr,0xA1);//增加了buf4故障类型
					Delay1ms(1);
                 
          GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Fault_Rec_Position;//修改为256
          if (temp2>FaultRecount)    
						Display_S(hz2,2);//显示◇
          else    
						Display_S(hz3,2);
					temp2=DataBuff[0]*256+DataBuff[1];
					temp = temp2/100;
					LCD_DataWrite(ChCode[temp]);
					temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];	//探测器ID
					type_error = DataBuff[4];
					GotoXY(X+8,Y+i*16,Dis_T);         //探测ID
          
					if (type_error== 0)		//通讯故障
          {
             temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						 GotoXY(X+14,Y+i*16,Dis_T); 
						 Display_S(hz4,8);	//通讯故障
          }
          else if(type_error== 0xF0)//主电故障
          {
							LCD_DataWrite(' ');
							LCD_DataWrite(' ');
              LCD_DataWrite(' ');
						
						  GotoXY(X+14,Y+i*16,Dis_T); 
						  Display_S(hz5,8);//主电故障
           }  
					else if(type_error== 0xF1)//备电故障
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz6,8);//备电故障
					}  
					else if(type_error== 0xF2)//充电故障
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz7,8);//充电故障
					} 
					else//1-16回路开路 17-32短路
					{
						 temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						if( (type_error <=16)&&(type_error > 0))//开路
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=type_error/10;
							LCD_DataWrite(ChCode[temp]);
							temp=type_error%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz8,8);//回路开路
						}
						else if( (type_error <=32)&&(type_error >= 17))//短路
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=(type_error-16)/10;
							LCD_DataWrite(ChCode[temp]);
							temp=(type_error-16)%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz9,8);//回路短路
						}
						else
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=type_error/10;
							LCD_DataWrite(ChCode[temp]);
							temp=type_error%10;
							LCD_DataWrite(ChCode[temp]);
						}
					}

                 
           //读时间：年月日时分－－[5]..[9]                 
          temp=DataBuff[4+1]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//年
          temp=DataBuff[4+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[5+1]/10;                   
          LCD_DataWrite(ChCode[temp]);//月
          temp=DataBuff[5+1]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6+1]/10;
          LCD_DataWrite(ChCode[temp]);//日
          temp=DataBuff[6+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[7+1]/10;        
          LCD_DataWrite(ChCode[temp]);//时
          temp=DataBuff[7+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[8+1]/10;
          LCD_DataWrite(ChCode[temp]);//分
          temp=DataBuff[8+1]%10;
          LCD_DataWrite(ChCode[temp]);         
        }
        i++;
     
       if (FaultNum>0) FaultNum--;
       else FaultNum=0; 

      }
}

void Display_SD_Record_Bar(void)
{
	unsigned char hz0[]={"序号　   事件描述　　    事件时间　　   　　"};

	Clr_Display();

	GotoXY(2,1,Dis_T);
	Display_S(hz0,37);

	Line_Y(0,0,239);
	Line_Y(40,0,239);

	Line_X(0,0,39);
	Line_X(0,239,39);
}

void Display_SD_Record(unsigned char SDNum)
{
	unsigned char hz0[]={"序号　   事件描述　　    事件时间　　   　　"};
	unsigned char hz00[]={"通过↑↓翻页 "};
	unsigned char hz1[]={"系统开机　"};
	//unsigned char hz2[]={"系统关机　"};
	unsigned char hz3[]={"系统复位　"};
	unsigned char hz4[]={"清除记录　"};
	unsigned char hz5[]={"系统初始化"};

	unsigned char X,Y;
	unsigned char i,j,temp;

	unsigned char DataBuff[10];

	unsigned int Addr;

   Clr_Display();
   GotoXY(2,1,Dis_T);
   Display_S(hz0,37);
   Line_Y(0,0,220);
   Line_Y(40,0,220);
   Line_X(0,0,39);
   Line_X(0,220,39);

   GotoXY(3,222,Dis_T);//显示第几页
   Display_S(hz00,12);
   GotoXY(28,222,Dis_T);
   temp=(SDNum/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(SDNum/12+1)%10;
   LCD_DataWrite(ChCode[temp]);
   LCD_DataWrite(' ');
   LCD_DataWrite('/');
   LCD_DataWrite(' ');
   temp=(SDRecount/12+1)/10;
   LCD_DataWrite(ChCode[temp]);
   temp=(SDRecount/12+1)%10;
   LCD_DataWrite(ChCode[temp]);

   i=0;
   X=2;
   Y=19;
   while(i<12)
   {  
      if (SDNum<1)//通道号、浓度值清空
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//清空
              
         	i++;
         }
       }
      else 
      {   
					Addr= 0x141 + (SDNum-1) * 8;//141~941
          //EA=0; 
					RW24XX(DataBuff,7,Addr,0xA1);
					//EA=1;
         
          GotoXY(X,Y+i*16,Dis_T);

          temp=DataBuff[0]/10;         //上电记录数1字节
          LCD_DataWrite(ChCode[temp]);
          temp=DataBuff[0]%10;
          LCD_DataWrite(ChCode[temp]);

          GotoXY(X+9,Y+i*16,Dis_T);
          if (DataBuff[1]==1) Display_S(hz1,10);;//事件名称描述
          if (DataBuff[1]==3) Display_S(hz3,10);
          if (DataBuff[1]==4) Display_S(hz4,10);
          if (DataBuff[1]==5) Display_S(hz5,10);        
           //读时间：年月日时分－－[5]..[9]                 
          temp=DataBuff[2]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//年
          temp=DataBuff[2]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[3]/10;                   
          LCD_DataWrite(ChCode[temp]);//月
          temp=DataBuff[3]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[4]/10;
          LCD_DataWrite(ChCode[temp]);//日
          temp=DataBuff[4]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[5]/10;        
          LCD_DataWrite(ChCode[temp]);//时
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[6]/10;
          LCD_DataWrite(ChCode[temp]);//分
          temp=DataBuff[6]%10;
          LCD_DataWrite(ChCode[temp]);
   
        }
        i++;
     
       if (SDNum>0) SDNum--;
       else SDNum=0; 

      }
}


void Dis_SetPass1_Promt(void)
{  

	unsigned char hz1[]={"请输入一级新密码："};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//文本方式 
	Display_S(hz1,18);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
		GotoXY(X+3*i,Y,Dis_T);//文本方式 
		LCD_DataWrite(ChCode[dis_buff[i]]); 
	}
	Open_Cur(X,Y+2);
}
    
void Dis_SetPass(void)
{ 
	unsigned char X,Y,i;

	X=14;
	Y=105;

	for (i=0;i<4;i++)
	{
		GotoXY(X+3*i,Y,Dis_T);//文本方式 
		LCD_DataWrite(ChCode[dis_buff[i]]); 
	}

	if (Flicker_Position==3) 
		Open_Cur(X,Y+2);
	else 
		Open_Cur(X+3*(Flicker_Position+1),Y+2);
}

void Dis_SetPass2_Promt(void)
{  
    unsigned char hz1[]={"请输入二级新密码："};
    unsigned char i;
    unsigned char X,Y;

    Clr_Display();
    GotoXY(11,60,Dis_T);//文本方式 
    Display_S(hz1,18);//

    Line_Y(10,90,140);
    Line_Y(30,90,140);
    Line_X(10,90,29);
    Line_X(10,140,29);

   X=14;
   Y=105;
   for (i=0;i<4;i++)
   {
     GotoXY(X+3*i,Y,Dis_T);//文本方式 
     LCD_DataWrite(ChCode[dis_buff[i]]); 
    }
    Open_Cur(X,Y+2);
}

void Clear_REC_Sure(void)
{
	unsigned char hz1[]={"清除系统记录后，记录将丢失！"};
	unsigned char hz2[]={"并无法恢复！确认／取消？"};

	Clr_Display();
	GotoXY(5,60,Dis_T);
	Display_S(hz1,28);

	GotoXY(6,90,Dis_T);
	Display_S(hz2,24);
}

void Clear_REC_Promt(void)
{  
	unsigned char hz1[]={"正清除系统数据，请稍候...     "};

	Clr_Display();
	GotoXY(6,90,Dis_T);
	Display_S(hz1,28);   
}

void Clear_REC_OK(void)
{  
	unsigned char hz1[]={"清系统数据完成！"};

	Clr_Display();
	GotoXY(10,90,Dis_T);
	Display_S(hz1,16);
}

void CLR_Record(void)
{
  unsigned char buf[4];
	//EA=0;
  AlarmRecount=0;
  buf[0]=0;
  buf[1]=0;
  RW24XX(&buf[0],2,0x18,0xA0); //报警记录总数
  Delay1ms(10);
 
  FaultRecount=0;
  buf[0]=0;
  buf[1]=0;
  RW24XX(&buf[0],2,0x1C,0xA0); //故障记录总数
  Delay1ms(10);
  
  
  SDRecount=0;    //上电次数
  buf[0]=SDRecount; 
  RW24XX(buf,1,0x1A,0xA0);
  Delay1ms(10);
 
	//EA=1;
}

uint8_t CD_Check(void)
{
	uint8_t power;
	Power_ADC_Return();  //备电电压AD值
	if(CD_Flag == 1)
	{
		if (Bat_Power>3350)   //>20V 此时备电不正常
			power = 1;	//充电正常
		else
			power = 0;	//充电不正常
	}
	else
	{
		power = 3;
	}
	return power;
}


void Power_Check(void)
{  
		static uint8_t Last_Main_Power,This_Main_Power;
	
		uint8_t Main_Power_Check;
		//uint8_t CD_Check;
		///-------------------主电检测-----------------------------------
		//主电正常Main_Power_Check=0
		//主电故障Main_Power_Check=1
		This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	
		Main_Power_Check = This_Main_Power & Last_Main_Power;
	
		Last_Main_Power = This_Main_Power;	//必须连续两次相同的状态才判断接受
	
		if (Check_World_Flag_State(10)) //之前主电状态正常
		{   
			if (Main_Power_Check==1)   //此时主电不正常
			{ 
					Set_World_Flag_Flag(10,0);//主电正常
					Set_World_Flag_Flag(0,1);//供电中断指示灯亮

					SendFunction[SendPtr.LoadCnt].Command = 7;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(7,0,0,0);				//主电故障
				
          Set_World_Flag_Flag(11,1);//主电故障
          Set_World_Flag_Flag(7,0);//消音灯关闭
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;
					}
					else 
					{
						FaultRecount=0;
					}//故障记录总数加1
					
					Save_Fault_Record(0,0xF0);//主电故障			
			}
			else //主电正常，检测充电状态
			{
			// World_Flag=Set_Flag(World_Flag,2,1);
			// World_Flag=Set_Flag(World_Flag,3,0);  
			}
		}
		else  //之前主电状态不正常
		{ 
			if (Main_Power_Check==0)   //此时主电正常
			{
					Set_World_Flag_Flag(10,1);//主电正常
          Set_World_Flag_Flag(11,0);//主电故障
					Set_World_Flag_Flag(0,0);//供电中断指示灯亮
					SendFunction[SendPtr.LoadCnt].Command = 8;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(8,0,0,0);	//主电故障
			}
		}

		
}


///-------------------备电检测-------------------------
void Bat_Power_Check(void)
{
	static uint8_t Last_Main_Power,This_Main_Power;
  uint8_t Main_Power_Check; 	//24对应3916 23V对应3745  22.5对应3663  21V 对应3391
 
	This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Main_Power_Check = This_Main_Power & Last_Main_Power;

	Last_Main_Power = This_Main_Power;	//必须连续两次相同的状态才判断接受
	
	//Main_Power_Check=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Power_ADC_Return();  //备电电压AD值
	
	if (Main_Power_Check==0) //主电正常溃电标志为0
	{
		Bat_Low_Flag=0;
	}  
	else //主电不正常检测备电
	{
		if (Bat_Power>=3671) 
		{
			Bat_Low_Flag=0;
			//Set_World_Flag_Flag(6,0);//6 欠压指示灯灭，电压正常
		} //电池电压大于22.5V-3671   23V-3745,表示电压正常
		else if ((Bat_Power>=3580)&&(Bat_Power<3650)) 
		{
			Bat_Low_Flag=1;
			//Set_World_Flag_Flag(6,1);//6 欠压指示灯亮
		} //605 22V--22.5V 表示溃电标志
		else if ((Bat_Power<3570)&&(Main_Power_Check==1)) 
		{
			BD_OFF();
		}//电池低于21.5V并且不正常，则系统断电保护电池
	}
		
//	canbuf[0] = Main_Power_Check;
//	canbuf[1] = 0;
//	canbuf[2] = (Bat_Power>>8)&0xFF;
//	canbuf[3] = Bat_Power&0xFF;
//	Can_Send_Msg(0x111,canbuf,8);

/*24V   3907
	23.5  3837
  23    3745
  22.5  3671
  22    3584
  21.5  3494
  21    3413			*/	
		
	if (Check_World_Flag_State(12)) //之前备电状态正常
	{
		if (Bat_Power<3350)   //<20V 此时备电不正常
		{ 
			Set_World_Flag_Flag(12,0);//备电正常
			Set_World_Flag_Flag(13,1);//备电故障
			//Set_World_Flag_Flag(0,1);//供电中断指示灯亮
			 
			SendFunction[SendPtr.LoadCnt].Command = 9;
			SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
			SendFunction[SendPtr.LoadCnt].TDH = 0;
			SendFunction[SendPtr.LoadCnt].type = 0;
			SendPtr.LoadCnt++;

			//SendToPC1(9,0,0,0);	//备电故障
			
			Set_World_Flag_Flag(7,0);//消音灯关闭
			Beep_Alarm_Fault=2;

			if (FaultRecount<500)
			{
				FaultRecount ++;
			}
			else 
			{
				FaultRecount=0;
			}//故障记录总数加1
			Save_Fault_Record(0,0xF1);//备电故障
			
			CD_Flag = 0;	//备电故障，关闭充电
			//CDK_OFF();
		}
		else
		{
			if(Main_Power_Check == 0)//主电正常，备电正常开始充电
			{
				CD_Flag = 1;
				//CDK_ON();
			}
		}
	}
	else  //之前备电状态不正常
	{ 
			if (Bat_Power>3390)   //>20V 表示此时备电正常
			{
				Set_World_Flag_Flag(12,1);//备电正常
				Set_World_Flag_Flag(13,0);//备电故障
				//Set_World_Flag_Flag(0,0);//供电中断指示灯亮
				
				SendFunction[SendPtr.LoadCnt].Command = 10;
				SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
				SendFunction[SendPtr.LoadCnt].TDH = 0;
				SendFunction[SendPtr.LoadCnt].type = 0;
				SendPtr.LoadCnt++;

				//SendToPC1(10,0,0,0);	//备电恢复
				
				if(Main_Power_Check == 0)//主电正常，备电正常开始充电
				{
					CD_Flag = 1;
					//CDK_ON();
				}
			}
			else
			{
				CD_Flag = 0;	//备电故障，关闭充电
				//CDK_OFF();
			}
	}
/*
	//----------------------充电检测-------------------------
			if (!Check_World_Flag_State(7)) //之前充电状态正常
			{      
				if ((CD_Check()==0)||(Main_Power_Check==1)||(Bat_Power<3350))   //此时充电不正常
				{ 
					Set_World_Flag_Flag(7,1);//充电故障灯亮
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;//故障记录总数加1
					}
					else 
					{
						FaultRecount=0;
					}
					Save_Fault_Record(0,0xF2);//充电故障
				}

			}
			else  //之前状态不正常
			{ 
				if ((CD_Check()==1)&&(Main_Power_Check==0))   //此时充电正常
				{
					Set_World_Flag_Flag(7,0);//
				}
			}
*/
}

void TCQ_Data_Control(void)//读取传感器状态，接收传感器返回的数据
{
	uint8_t i,k,m,pn;
	uint8_t flag=0;
	uint16_t lTemp = 0;
	
	TCDID=Rec_Buff[0]*256+Rec_Buff[1];			//设备ID号
	Type_State=Rec_Buff[5]*256+Rec_Buff[6];	//检测类型=1电流 =0温度
	PB_State =Rec_Buff[7]*256+Rec_Buff[8];	//屏蔽状态=1屏蔽 =0工作
	State1=Rec_Buff[9]*256+Rec_Buff[10];		//报警状态和故障状态高位
	State2=Rec_Buff[11]*256+Rec_Buff[12];		//报警状态和故障状态低位
	SKC_State=Rec_Buff[13]*256+Rec_Buff[14];//脱扣状态=1屏蔽 =0开启
	//MKC_State=Rec_Buff[15]*256+Rec_Buff[16];
	 
	Alarm_State=0;
	Fault_State=0;
	
	Set_Uart_Fault_Timer0(TCDID-1);//Uart_Err_Timer[TCDID-1]=0;
	
	if((Function_Flag==7)||(Function_Flag==6))//写状态返回值
	{
		TCQ_Return_OK=1;
	
		for(i=0;i<16;i++)//16个回路状态
		{
			temp1 =PB_State&(1 << i);
			if (temp1!=0)//=1表示该路为屏蔽状态  
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
				continue;
			}
			
			temp1 =State1 & (1 << i);
			temp2 =State2 & (1 << i);
			if((temp1==0)&&(temp2==0))//正常			 
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			}
			else if((temp1^temp2)!=0) //故障或报警  01短路 10断路
			{
				if(!Check_Sensor_Fault0_State(TCDID-1,i))//回路故障
				{
					Fault_State=Fault_State|(1<<i);
					Set_Sensor_Fault0_Flag(TCDID-1,i,1);
				}		
			}
		
		}
		return;
  }

	
	for(i=0;i<16;i++)
	{
		temp1 =PB_State & (1 << i);
		if (temp1!=0)//=1屏蔽状态 =0工作状态
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			continue;
		}

		temp1 =State1 & (1 << i);//报警状态和故障状态高位
		temp2 =State2 & (1 << i);
		    
		if((temp1==0)&&(temp2==0))//正常，无故障报警	
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
		}
		else if((temp1^temp2)!=0) //有故障 01 短路 10 断路
		{
			if(!Check_Sensor_Fault0_State(TCDID-1,i))//之前无故障报警
			{
				Fault_State=Fault_State|(1<<i);
				Set_Sensor_Fault0_Flag(TCDID-1,i,1);
				
				if (FaultRecount<500) //故障记录总数500条
				{
					FaultRecount++;
				}
				else 
				{
					FaultRecount=1;//报警记录总数加1
				}	
				
				Beep_Alarm_Fault = 2;//发出故障报警声音
				Set_World_Flag_Flag(7,0);//消音灯关闭
				Beep_ON();
				
				pn=Fault_Rec;//主界面显示的故障数
				if (pn>12) 
				{
					pn=12;  
				}
				
				if((temp1 != 0)&&(temp2==0))
				{
					//存入开路故障
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0800 | TCDID);
					Save_Fault_Record(TCDID,i+1);		//开路
				}
				else 
				{
					//存入短路故障
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0400 | TCDID);
					Save_Fault_Record(TCDID,i+17);	//短路
				}
				
				flag=0;
				for(k=0;k<pn;k++)//有相同的，后边的前移一位
				{
					if (Fault_Position[k]==Fault_Position[pn])
					{
						for(m=k;m<(pn+1);m++)
						{
							Fault_Position[m]=Fault_Position[m+1];
						}
						flag=1;
						break;
					}
				}
				
				if (flag==1) 
				{
					Fault_RecP++;
				}
				else 
				{
					Fault_Rec++;	//报警总数加1
					//最多显示12条故障
					if (pn==12)
					for(m=0;m<12;m++) 
					{
						Fault_Position[m]=Fault_Position[m+1];
					}
				}		
		
			}
		}
		else if((temp1!=0)&&(temp2!=0))//11 报警状态
		{	 
			//Feel[i]=(Rec_Buff[19+4*i]&0x7F)*256+Rec_Buff[20+4*i];
			Alarm_State=Alarm_State|(1<<i); 
			Set_Alarm_Flag(TCDID-1,1);
			Set_Alarm_Flag_16(TCDID-1,i,1);
			Speak_ON();
			Beep_Alarm_Fault=1; 
			
			KC1_ON();
			KC2_ON();
			Set_World_Flag_Flag(2,1);//输出指示灯亮
			Dis_State_LED();//状态指示灯显示
	
			// if (First_Alarm==0)  {First_Alarm=TCDID*16+i+1;} 
			//-----------------------------------------------------------------------     
			Function_Flag = 15;	//读取报警最大值
			
			pn=Alarm_Rec_Position;
			if (pn>7) 
			{
				pn=7;  
			}
			//高位表示检测类型
			if((Type_State& (1<<i))==0) //检测类型=1电流 =0温度
				Alarm_Position[pn]=0*4096+TCDID;
			else 
				Alarm_Position[pn]=(i+1)*4096+TCDID; 

			//Alarm_Data[pn]=Feel[i];
			
			flag=0;
			for(k=0;k<pn;k++)//有相同的，后边的前移一位
			{
				if (Alarm_Position[k]==Alarm_Position[pn])//(i+1)*4096+TCDID) 
				{
					for(m=k;m<(pn+1);m++)
					{
						Alarm_Position[m]=Alarm_Position[m+1];
						Alarm_Data[m]= Alarm_Data[m+1];
					}
					flag=1;
					break;
				}
			}
			
			if (flag==1) 
			{
				Alarm_RecP++;
			}
			else 
			{
				Alarm_Rec_Position++;	//报警总数加1
				//最多显示7条
				if (pn==7)
				for(m=0;m<7;m++) 
				{
					Alarm_Position[m]=Alarm_Position[m+1];
					Alarm_Data[m]=Alarm_Data[m+1];
				}
			}				
		}//end else
	}//end for 	

	if(Alarm_State!=0)//有报警状态
	{
		for(i=0;i<(Rec_Buff[2]+3);i++)
		{
			Send_Buff[i]=Rec_Buff[i];
		}
		Send_Buff[3]=0x08;
		CAN_SendData();	
		
		Save_Alarm_Record(TCDID,Alarm_State,Type_State);
		
		SendFunction[SendPtr.LoadCnt].Command = 4;
		SendFunction[SendPtr.LoadCnt].TCQ_Num = TCDID;
		SendFunction[SendPtr.LoadCnt].TDH = 1;
		SendFunction[SendPtr.LoadCnt].type = 0x31;
		SendPtr.LoadCnt++;
		
		//SendToPC1(4,TCDID,1,0x31);//发送报警信息到主机
	}

//	if(Fault_State!=0)//互感器故障
//	{		
//		//Save_Fault_Record(TCDID);
//	}

}

void Read_TCQ_Data(void)
{
	uint8_t i;
	
	if(Function_Flag==10)
	{	
		TCQ_Return_OK=1;
		for(i=0;i<((Rec_Buff[2]-2)/4);i++)
		{  
			//Zero[i]=(Rec_Buff[5+4*i]*256+Rec_Buff[6+4*i])&0x7FFF;//
			//Fac[i]=((Rec_Buff[7+4*i]*256+Rec_Buff[8+4*i])&0x7FFF)/10;
		}
	}

}

void Set_Sensor_Fault0_Flag(uint8_t Num,uint8_t nbit,uint8_t flag)//将互感器某一回路报警标志置1或清0
{
	uint16_t x,temp;

	temp=Sensor_Fault0_Flag[Num];

	x= 1 << nbit; 

	if (flag==1)   //=1将相应的位置置1
	{
		temp=temp | x;
	} 
	else 
	{  
		x=0xFFFF-x;
		temp=temp & x;
	}
	Sensor_Fault0_Flag[Num]=temp;
}

uint8_t Check_Sensor_Fault0_State(uint8_t Num,uint8_t nbit)//故障返回1
{
	uint16_t temp;
	temp=Sensor_Fault0_Flag[Num];

	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1;  
}




