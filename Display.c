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
"*      �����а������ӿƼ����޹�˾      *"
"*��������������������������            *"
"*                                      *"
"*    �M  AF116 �������ּ���豸������  *"
"*          ������     ����������       *"
"*               V1.0                   *"
"*��������������������������            *"
"*��������������������������            *"
"*                ������������������    *"
"* ��ַ��ɽ��ʡ�����кӶ����ü��������� *"
"* TEL ��0539-6012963 FAX��0539-8165301 *"
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
//		if(Read_BUSY()==1){ break;}//��ֹ��ѭ��
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_1();//rs=1;//��������
	//BUS=cmdaddr;//������д�벢������
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
//		if(Read_BUSY()==1){ break;}//��ֹ��ѭ��
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_0();//rs=0;	//д������
	//BUS=dat;//������д�벢������
	SendData(dat);	
	WR_0();//wr=0;
	WR_1();//wr=1;
	CS1_1();//cs1=1;
	Delay1us(50);
}


void GotoXY(unsigned char x,unsigned char y,unsigned char TP)
{     
   LCD_CmdWrite(CPXR); //x����
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y����
   LCD_DataWrite(y);
   LCD_CmdWrite(0x00); 
   LCD_DataWrite(TP);
 
   LCD_CmdWrite(0xb0); 
}

void Open_Cur(unsigned char x,unsigned char y)
{
   LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
   LCD_DataWrite(0x07);//(0x06);
   LCD_CmdWrite(CPXR); //x����
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y����
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

	LCD_CmdWrite(ITCR);		//[90H] , Default --> 0x00    ��Ҫ����
	LCD_DataWrite(0x80);

	LCD_CmdWrite(PNTR);		//[E0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FNCR);		//[F0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FVHT);		//[F1H] , Default --> 0x00
	LCD_DataWrite(0x00);
}
/////////////////�����ӳ���//////////////////////////
void Clr_Display(void)
{ 
  LCD_CmdWrite(0x00);
  LCD_DataWrite(0x04);     //ѡ���ͼģʽ     
  LCD_CmdWrite(0xe0);
  LCD_DataWrite(0x00);
  LCD_CmdWrite(0xf0);
  LCD_DataWrite(0xa8);
  delay_nms(100);
}

/////////////��ʾ�����ֿ���ַ�////////////////////
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

void Dis_State_LED_ON(void)//״ָ̬ʾ��ȫ��
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0x0000; 
   dis_char(temp2);
   DIS_ON();
}

void Dis_State_LED_OFF(void)//״ָ̬ʾ��ȫ��
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0xFFFF; 
   dis_char(temp2);
   DIS_ON();
}


void Dis_State_LED(void)//״ָ̬ʾ����ʾ
{
	uint16_t temp2;

	DIS_OFF();
	/*
	if(Alarm_Rec_Position!=0)  
		Set_World_Flag_Flag(2,1);//����

	if(XAlarm_Rec_Position!=0)
	{ 
		if(Flash_Flag)	 
		{
			Set_World_Flag_Flag(2,1);
			Flash_Flag=0;
		}//����������δ����
		else 
		{
			Set_World_Flag_Flag(2,0);
			Flash_Flag=1;
		}
	} 
	if(RAlarm_Rec_Position!=0) 
		Set_World_Flag_Flag(4,1);//����
	else 
		Set_World_Flag_Flag(4,0); 
*/
	temp2=0xFFFF-World_Flag; 
	dis_char(temp2);
	DIS_ON();
}

void Display_LowPower(void)
{
  uint8_t hz1[]={"���õ�Դ��ѹ����"};
  //uint8_t hz2[]={"�뼰ʱ���������ϵͳ���磡"};


   Clr_Display();
	 GotoXY(12,100,Dis_T);
   Display_S(hz1,16);
}

void SD_Display_60S(unsigned char TNum)//�ϵ���ʾ
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
  GotoXY(x,y,Dis_P);//��ͼ��ʽ 
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
     { GotoXY(x,(y+i),Dis_P);//��ͼ��ʽ
       LCD_DataWrite(0x80); 
     }
   }
 
}

void Display_Main_Face(void)
{
  unsigned char hz0[]={"ϵͳ���������..."};
  unsigned char hz1[]={"���ϻ�·��Ϣ��     "};
  unsigned char hz2[]={"������·��Ϣ��     "};
  unsigned char hz3[]={"ϵͳ������Ϣ��     "};
	
	Clr_Display();

	//GotoXY(3,103,Dis_T);//������ʾ��ʽ����ʾϵͳ���������
	//Display_S(hz0,17);
	
	Line_Y(0,0,239);
	Line_Y(40,0,239);
	Line_Y(21,0,221);
	
	//Line_X(0,18,39);
	//Line_X(0,239,39);
	
	Line_X(0,0,39);
	Line_X(0,239,39);
	
	GotoXY(1,1,Dis_T);//��ʾ����״̬
	Display_S(hz1,14);

	GotoXY(23,1,Dis_T);//��ʾ������Ϣ
	Display_S(hz2,14);
	//Line_X(0,35,39);
	Line_X(0,17,39);
	
	GotoXY(23,124+18,Dis_T);//��ʾ������Ϣ
	Display_S(hz3,14);
	Line_X(21,123+18,39);
	Line_X(21,140+18,39);

	//----------------------------------

	Line_X(0,221,39);
}

void Dis_NoAlarmR(void)	//��ʾ�ޱ�����¼
{  
	unsigned char hz0[]={"�ޱ�����¼��"};

  GotoXY(25,70,Dis_T);
  Display_S(hz0,12);
}

void Dis_NoFaultR(void)	//��ʾ�޹��ϼ�¼
{ 
	unsigned char hz0[]={"�޹��ϼ�¼��"};
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
	unsigned char hz0[]={"��ǰʱ�䣺20"};
	unsigned char nian[]={"��"};
	unsigned char yue[]={"��"};
	unsigned char ri[]={"��"};
	unsigned char shi[]={"ʱ"};
	unsigned char fen[]={"��"};
	unsigned char miao[]={"��"};
	
	uint8_t temp;

  GotoXY(1,222,Dis_T);
  Display_S(hz0,12);
	
	GotoXY(13,222,Dis_T);

	temp=Real_Time.year%2000/10;//��
  LCD_DataWrite(ChCode[temp]); //��
	temp=Real_Time.year%2000%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	temp=Real_Time.month/10;//��
	LCD_DataWrite(ChCode[temp]); //��
	temp=Real_Time.month%10;
	LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	
	temp=Real_Time.day/10;//��
	LCD_DataWrite(ChCode[temp]); //��
	temp=Real_Time.day%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite(' ');
 
 	temp=Real_Time.hour/10;//ʱ
	LCD_DataWrite(ChCode[temp]); //ʱ
	temp=Real_Time.hour%10;
	LCD_DataWrite(ChCode[temp]); //ʱ
  LCD_DataWrite(':');
 
	temp=Real_Time.min/10;//��
	LCD_DataWrite(ChCode[temp]); //��
	temp=Real_Time.min%10;
  LCD_DataWrite(ChCode[temp]); //��
  LCD_DataWrite(':');

	temp=Real_Time.sec/10;//��
	LCD_DataWrite(ChCode[temp]); //��
	temp=Real_Time.sec%10;
	LCD_DataWrite(ChCode[temp]); //��
}

//------------------------

void Clear_Dispaly_Feel(void)
{
		unsigned char i;
		unsigned char hz10[]={"                     "};
		for(i=0;i<12;i++)//��Ҫˢ����ʾ����
		{
			GotoXY(2,18+i*17,Dis_T);
			Display_S(hz10,19);
		}		
}


void Display_Feel_Fault(void)//����ʾ����
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"��������"};
		unsigned char hz1[]={"��������"};
		unsigned char hz2[]={"���ϡ���"};
		unsigned char hz3[]={"ͨѶ����&����"};
		unsigned char hz4[]={"̽����ID�� ����״̬"};
		unsigned char hz5[]={"̽����ID  ��ַ ״̬"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"��·"};
		unsigned char hz8[]={"��·"};
		unsigned char hz9[]={"ϵͳ���������..."};
		unsigned char hz10[]={"                     "};
		unsigned char hz11[]={"��"};
		unsigned char hz12[]={"��"};
		unsigned char hz13[]={"��Ԫ"};
		GotoXY(1,1,Dis_T);//ͨѶ����&����
		Display_S(hz3,14);
		
		GotoXY(16,1,Dis_T);//ͨѶ����&����
		Display_S(hz10,4);

		if( LoopEnd > 256 )	//EndAddr����256���4��ͨѶ����
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;
		

		
		if( Fault_Num == 0 )
		{		
			Clear_Dispaly_Feel();
			
			GotoXY(3,103,Dis_T);//������ʾ��ʽ����ʾϵͳ���������
			Display_S(hz9,17);
		}
		else
		{
			i=0;
			X=2;
			Y=18;
			
			while(i<12)//ÿ����ʾ12��̽�������� //ֻ��ʾ���Ϻͱ���
			{ 
				 if ((!Check_Shield_State(Dis_Num))&&((Uart_Fault_Timer(Dis_Num)>=cTemp)||(Check_Alarm_State(Dis_Num)))) //û�����β���С��64
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num+1)/100;
							 LCD_DataWrite(ChCode[temp]);  //��ַ�� 
							 temp=(Dis_Num+1)%100/10;
							 LCD_DataWrite(ChCode[temp]);
							 temp=(Dis_Num+1)%10;
							 LCD_DataWrite(ChCode[temp]);
							 LCD_DataWrite(' ');
							 
							if(Dis_Num >= End_Addr)
							{
								 LCD_DataWrite('H');	//��ʾ�豸�ڻ�·����
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
						
							if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8��ͨѶʧ������ͨѶ����
								Display_S(hz2,8);//���� 
							else if (Check_Alarm_State(Dis_Num))
								Display_S(hz1,8);//����
							else  
								Display_S(hz0,8);//����
							
							if(DisplayAddr == 1)//��ʾ�豸��װ��ַ
							{
								GotoXY(X+8,Y+i*17,Dis_T);

								temp=address[Dis_Num][0]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][0]%10;
								LCD_DataWrite(ChCode[temp]);			
								
								Display_S(hz11,2);//��

								temp=address[Dis_Num][1]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][1]%10;
								LCD_DataWrite(ChCode[temp]);
								Display_S(hz12,2);//��
		
								temp=address[Dis_Num][2]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][2]%10;
								LCD_DataWrite(ChCode[temp]);								
							}
							else
							{
								GotoXY(X+7,Y+i*17,Dis_T);
								Display_S(hz6,3);//����
							}
					 i++; 
				 }//���û������ʱ�������

				 
				 if( LoopOpenFlag == 1)	//������·1����
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
									LCD_DataWrite(' ');  //��ַ�� 
								i++;
							}
							break; 
						} 
				 
				 }
				 else	//ֻʹ������·
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
									LCD_DataWrite(' ');  //��ַ�� 
								i++;
							}
							break; 
						} 
				 } 
			}//while ����
		
		}

}

void Display_Main_Fault(void)
{
		unsigned char pn,X,Y;
		unsigned char i,j,temp;
		unsigned char hz0[]={"��������"};
		unsigned char hz1[]={"��������"};
		unsigned char hz2[]={"���ϡ���"};
		unsigned char hz3[]={"ͨѶ����"};
		unsigned char hz4[]={"��·��·"};
		unsigned char hz5[]={"��·��·"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"��·"};
		unsigned char hz8[]={"��·"};
		unsigned char hz9[]={"ϵͳ���������..."};
		unsigned char hz10[]={"                     "};	
		unsigned char hz11[]={"���ϻ�·��Ϣ: "};
		uint8_t cTemp;
		uint8_t huilu;
		uint8_t huilustate;
		uint8_t first;
		
		GotoXY(1,1,Dis_T);//��ʾ����״̬
		Display_S(hz11,14);
		
		pn = Fault_Rec;	//��·����
		
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
		
		if( pn == 0 )//��������
		{
			for(i=0;i<12;i++)//��Ҫˢ����ʾ����
			{
				GotoXY(2,18+i*17,Dis_T);
				Display_S(hz10,19);
			}		
			
			GotoXY(3,103,Dis_T);//������ʾ��ʽ����ʾϵͳ���������
			Display_S(hz9,17);
		}
		else
		{
			GotoXY(3,103,Dis_T);//���ϵͳ���������
			Display_S(hz10,17);
			i=0;
			X=2;
			Y=18;
			
			if(pn>12)
				pn=12;
					
			while(i<pn)//ÿ����ʾ12��̽��������	//ֻ��ʾ���Ϻͱ���
			{  
				 Dis_Num = Fault_Position[i]&0x3FF;//��10λ��ʾ�豸��
				 huilu = (Fault_Position[i]>>12)&0x0F;
				 huilustate=(Fault_Position[i]>>10) & 0x03;
				if (!Check_Shield_State(Dis_Num)) 
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num)/100;
							 LCD_DataWrite(ChCode[temp]);  //��ַ�� 
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
								 LCD_DataWrite('H');	//��ʾ�豸�ڻ�·����
								 LCD_DataWrite('1');
							}
							else	
							{							
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
							}
							
							if(huilustate==1)//��·
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz5,8);//��·��·
							}
							else if(huilustate==2)//��·
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz4,8);//��·��·
							}
							else if(huilustate==3)//ͨѶ����
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz3,8);//��·��·
							}			
					i++;
				 }//���û������ʱ�������	
					 
			}//while ����
		
		}

}
void Display_Feel(void)
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"��������"};
		unsigned char hz1[]={"��������"};
		unsigned char hz2[]={"���ϡ���"};
		unsigned char hz3[]={"        "};
		unsigned char hz4[]={"̽����ID�� ����״̬"};
		unsigned char hz5[]={"̽����ID  ��ַ ״̬"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"��·"};
		unsigned char hz8[]={"��·"};
		unsigned char hz9[]={"ϵͳ���������..."};
		if( LoopEnd > 256 )	//EndAddr����256���4��ͨѶ����
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;

		i=0;
		X=2;
		Y=18;
		
		while(i<12)//ÿ����ʾ12��̽��������
		{  
       if (!Check_Shield_State(Dis_Num)) //û�����β���С��64
       { 
             GotoXY(X,Y+i*17,Dis_T);
             temp=(Dis_Num+1)/100;
             LCD_DataWrite(ChCode[temp]);  //��ַ�� 
             temp=(Dis_Num+1)%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=(Dis_Num+1)%10;
             LCD_DataWrite(ChCode[temp]);
             LCD_DataWrite(' ');
            
						if(Dis_Num >= End_Addr)
						{
							 LCD_DataWrite('H');	//��ʾ�豸�ڻ�·����
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
            
						
					
            if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8��ͨѶʧ������ͨѶ����
							Display_S(hz2,8);//���� 
            else if (Check_Alarm_State(Dis_Num))	//���ޱ���
							Display_S(hz1,8);//����
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz7,8);//��·
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz8,8);//��·
            else  
							Display_S(hz0,8);//����
						
						if(DisplayAddr == 1)//��ʾ�豸��װ��ַ
						{
							GotoXY(X+7,Y+i*17,Dis_T);

							temp=address[Dis_Num][0]/10;//��
							LCD_DataWrite(ChCode[temp]); //��
							temp=address[Dis_Num][0]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');

							temp=address[Dis_Num][1]/10;//��
							LCD_DataWrite(ChCode[temp]); //��
							temp=address[Dis_Num][1]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');
	
							temp=address[Dis_Num][2]/10;//��
							LCD_DataWrite(ChCode[temp]); //��
							temp=address[Dis_Num][2]%10;
							LCD_DataWrite(ChCode[temp]);		
						}
						else
						{
						  GotoXY(X+7,Y+i*17,Dis_T);
							Display_S(hz6,3);//����
						}
         i++; 
       }//���û������ʱ�������

			 
			 if( LoopOpenFlag == 1)	//������·1����
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
								LCD_DataWrite(' ');  //��ַ�� 
							i++;
						}
						break; 
					} 
			 
			 }
			 else	//ֻʹ������·
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
								LCD_DataWrite(' ');  //��ַ�� 
							i++;
						}
						break; 
					} 
			 } 
    }//while ������
}


void Display_System_Sate(void)
{
	unsigned char hz0[]={"��"};
	unsigned char hz1[]={"MA"};
	
	unsigned char hz3[]={"ͨѶ���ϣ�  "};
	unsigned char hz4[]={"̽����ϣ�  "};
	unsigned char hz5[]={"�������    "};
	unsigned char hz6[]={"�������    "};
	unsigned char hz7[]={"������    "};
	unsigned char hz8[]={"            "};
	unsigned char hz9[]={"                  "};
	unsigned char X,Y,i,j;
	unsigned int pn;
	uint8_t first=0;
	uint16_t nbit_F,temp;

	X=36;
	Y=1;

	GotoXY(X,Y,Dis_T);
	pn=Alarm_Rec_Position;//���㱨����λ����
	
	first=0;				//��ʾ������·����
	temp=pn/100;		//��λ
	if (temp==0)  
		LCD_DataWrite(' ');
	else 
	{ 
		LCD_DataWrite(ChCode[temp]);
		first=1;
	}//ͨ����
	
	temp=pn%100/10;	//ʮλ
	if ((temp==0)&&(first==0))  
		LCD_DataWrite(' '); 
	else 
		LCD_DataWrite(ChCode[temp]);  
	
	temp=pn%10;			//��λ
	LCD_DataWrite(ChCode[temp]);

	if (pn==0) 
	{
		//��ʾǰ������ʾ����
		for(i=0;i<7;i++)
		{
			GotoXY(22,20+i*16,Dis_T);
			Display_S(hz9,17);
		}		
		Dis_NoAlarmR();
	}
	else
	{
		GotoXY(25,70,Dis_T);//����ޱ�����¼
		for(i=0;i<12;i++)   
			LCD_DataWrite(' ');

		Y=20;	//ԭΪ36
		//�����ʾ7����������
		if (pn>7)
			pn=7;
		
		for(i=0;i<pn;i++)
		{  
			if (i<7) 
				X=22;
			else 
				X=31;
		
			temp=Alarm_Position[i]%4096/100;	//�豸��  ��12λ���֣���λ
			GotoXY(X,Y+i%7*16,Dis_T);
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%100/10;
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%10;
			LCD_DataWrite(ChCode[temp]);
			LCD_DataWrite('-');

			if ((Alarm_Position[i]/4096)==0) 	//001-02 ��·��  ��ʾ��4λ
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
			temp = Alarm_Data[i]/1000;		//ǧλ
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%1000/100;	//��λ
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			temp = Alarm_Data[i]%100/10;		//ʮλ
			
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%10;				//��λ
			LCD_DataWrite(ChCode[temp]);
			
			if ((Alarm_Position[i]/4096)==0) 	//001-02 ��·��  ��ʾ��4λ
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
   
  if (Fault_Rec_Position==0)//��������
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
		Y=145+18;//����һ��	
		i=0;
		GotoXY(X,Y,Dis_T);
		Display_S(hz3,13);//��ʾͨѶ����
		//i++; 

		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 11);	//11�������
		if( nbit_F ) //	if (Check_World_Flag_State(11))
		{  
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz5,13);
			i++;  
		}//�������
		
		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 13);	//13 �������
		if ( nbit_F ) // if (Check_World_Flag_State(5))  
		{   
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz6,13);
			i++;
		}//�������
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
		}//������
*/
		X=25;
		Y=145+18;//����һ��
		for(j=i+1;j<3;j++)//������ʾ����
		{  
			GotoXY(X,Y+j*18,Dis_T);
			Display_S(hz8,13);
		} 
   
    X=34;
    GotoXY(X,Y,Dis_T);
    first=0;
    
    pn=Fault_Rec_Position-i;//̽��������� ��ȥ���ӵı������ �������
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
	uint8_t hz1[]={"��������"};
	//uint8_t hz2[]={"�ѷ�����"};
	//uint8_t hz3[]={"δ������"};
	//uint8_t hz4[]={"�����ָ�"};

	//uint8_t hz6[]={"������������������δ��������������"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//������ʾ��ʽ

	Display_S(hz1,17);
}


void Display_Fault(uint16_t Num)
{
	//uint8_t hz0[]={"��������"};
	uint8_t hz1[]={"�Ź��ϡ�"};
	//uint8_t hz2[]={"ͨѶ����"};
	//uint8_t hz3[]={"�������"};
	//uint8_t hz4[]={"�������"};
	//uint8_t hz5[]={"ϵͳ����"};
	//uint8_t hz6[]={"����������Ϣ��������������������������"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//������ʾ��ʽ

	Display_S(hz1,17);

}

void Dis_Pass1_Promt(void)//�����������
{  
  unsigned char hz1[]={"������һ�����룺"};
  unsigned char i;
  unsigned char X,Y;
	Clr_Display();
	GotoXY(12,60,Dis_T);//�ı���ʽ 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

  X=14;
  Y=105;
  for (i=0;i<4;i++)
  {
     GotoXY(X+3*i,Y,Dis_T);//�ı���ʽ 
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

void Self_Check(void)//ϵͳ�Լ���ʾ
{ 
	unsigned char hz1[]={"ϵͳ���ڽ����Լ죬���Ժ�...  "};
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
   dis_char(0x0000);//ȫ��
   DIS_ON();
   Delay1ms(1000);
		
   DIS_OFF();
   //dis_char(0xFFBF);
	 dis_char(0xFFFF);
   DIS_ON();
	
	Beep_Alarm_Fault=2;          // ������  
	Delay1s(4);
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault!=2)   
	{  
		Beep_OFF(); 
	} 

	Speak_ON();        // ������  
	Delay1s(4);
	Speak_OFF();
	 
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault==1)   
	{  
		Speak_ON(); 
	}
}

void Dis_Err(void)//���������ʾ��ʾ
{ 
	unsigned char hz1[]={"�������!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_Query_Menu(void)
{ 
	unsigned char hz0[]={"��¼��ѯ�˵��б�"};
	unsigned char hz1[]={"1 ������¼��ѯ"
											 "2 ���ϼ�¼��ѯ"
											 "3 �¼���¼��ѯ"};
                        
                      
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
  unsigned char hz0[]={"û�в�ѯ��¼��"};

  Clr_Display();
  GotoXY(14,100,Dis_T);
  Display_S(hz0,16);
}

void Display_Alarm_Record_Bar(void)
{
	unsigned char hz0[]={"��š� ̽��ID ����·�š�������ʱ��      "};

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
	unsigned char hz0[]={"��š� ̽��ID ����·�š�������ʱ��      "};//{"���  ̽��ID ��·�š�������ʱ��        "};
	unsigned char hz1[]={"ͨ��������ҳ "};
	unsigned char hz2[]={"��"};
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

   GotoXY(3,222,Dis_T);//��ʾ�ڼ�ҳ
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
      if (AlarmNum<1)//ͨ���š�Ũ��ֵ���
      { while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//���
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x502 + (AlarmNum-1) * 16;//�����ַ�
					//EA=0; 
					Delay1ms(1);
				  RW24XX(DataBuff,10,Addr,0xA1);
					Delay1ms(1);
					//EA=1;
	
  				GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Alarm_Rec_Position+Alarm_RecP;
          if (temp2>AlarmRecount)    Display_S(hz2,2);//��ʾ��
          else    Display_S(hz3,2);

					temp2=DataBuff[0]*256+DataBuff[1];
					temp=temp2/100;         //������¼��2�ֽ�
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);
				
//          temp=DataBuff[0]%10;         //������¼��2�ֽ�
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]/10;
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]%10;
//          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];
					
					temp=temp2/100;
					
          GotoXY(X+8,Y+i*16,Dis_T);         //̽��ID
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
            temp=DataBuff[4]/10;//��·��
            LCD_DataWrite(ChCode[temp]);
            temp=DataBuff[4]%10;     
            LCD_DataWrite(ChCode[temp]);
           }
           //��ʱ�䣺������ʱ�֣���[5]..[9]                 
          temp=DataBuff[5]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6]/10;                   
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[6]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[7]/10;
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[7]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[8]/10;        
          LCD_DataWrite(ChCode[temp]);//ʱ
          temp=DataBuff[8]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[9]/10;
          LCD_DataWrite(ChCode[temp]);//��
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
	unsigned char hz2[]={"��"};
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
 unsigned char hz0[]={"һ���˵��б�"};

 unsigned char hz1[]={"   1 ����ϵͳ����       6 ����ϵͳʱ��  "
                           "   2 ϵͳ��������       7 ����ˢ��Ƶ��  "
                           "   3 ��ʾ̽������     ��8 ���ñ�����ַ  "
                           "   4 �ֶ������ѿ�    �� 9 �����������  "
                           "   5 ʵʱ��ʾ����ֵ     10�豸��װλ��  "};
	unsigned char hz2[]={"������1��10�������ѡ��˵�  "};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,5,Dis_T);
	Display_S(hz0,12);
//��ʾ�˵�
	X=0;Y=45;
	for (i=0;i<5;i++)
	{
		GotoXY(X,Y+35*i,Dis_T);
		Display_S(&hz1[40*i],40);
	}
//���߿�
	Line_Y(0,28,220);
	Line_Y(40,28,220);

	Line_X(0,28,39);
	Line_X(0,220,39);
//��ʾ��ʾ����
	GotoXY(7,223,Dis_T);
	Display_S(hz2,30);
}

void Dis_Main_Menu1(void)
{  
	unsigned char hz2[]={"��"};//��ʾ�˵�ָʾ

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
	u8 hz1[]={"������̽����ID��Χ��"};
	u8 hz2[]={"������·ID��Χ��"};
	u8 hz3[]={"������·ID��Χ��"};
	u8 X,Y;

	Clr_Display();
	GotoXY(10,10,Dis_T);//�ı���ʽ 
	Display_S(hz1,20);//

	GotoXY(11,40,Dis_T);//�ı���ʽ 
	Display_S(hz2,16);//

	Line_Y(8,70,110);
	Line_Y(30,70,110);
	
	Line_X(8,70,29);
	Line_X(8,110,29);

	
	if( LoopOpenFlag ==1 )
	{
		//������·ID��Χ
		GotoXY(11,130,Dis_T);//�ı���ʽ 
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
  unsigned char hz1[]={"������·ID�����뿪�����ô���"};
  unsigned char hz2[]={"ID��"};
  unsigned char hz3[]={"״̬"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//�ı���ʽ 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//����
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//ID��
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//״̬
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text1(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"��"};
	unsigned char hz2[]={"��"};//����,������
	unsigned char i;
	unsigned char X,Y;
	unsigned int temp;

  uint8_t first=0;
  

   for (i=0;i<35;i++)
   { 
     
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+1;//Ϊͨ����
     if (temp>End_Addr)    //����64֮��
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //̽����ID���
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //����״̬���
         LCD_DataWrite(' ');
        
         
      }
     else 
     {   GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//ͨ����
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i))//����״̬
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+1;//Ϊͨ����
   if (temp>End_Addr)  return;  //����64֮��
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//�ı���ʽ //��ʾҳ��
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
    if (PB_Flag)  Display_S(hz2,2);// ����״̬              
    else Display_S(hz1,2);
   
   //--------------����ֵ ��˸----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_PB_Bar2(void)
{ 
  unsigned char hz1[]={"������·ID�����뿪�����ô���"};
  unsigned char hz2[]={"ID��"};
  unsigned char hz3[]={"״̬"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//�ı���ʽ 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//����
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//ID��
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//״̬
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text2(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"��"};
	unsigned char hz2[]={"��"};//����,������
	unsigned char i;
	unsigned char X,Y;
	u16 temp;

  uint8_t first=0;
  
   for (i=0;i<35;i++)
   { 
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+LoopStart;//Ϊͨ����
     if (temp>LoopEnd)    //����64֮��
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //̽����ID���
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //����״̬���
         LCD_DataWrite(' ');    
      }
     else 
     {  
					GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//ͨ����
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i+LoopStart-1))//����״̬
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+LoopStart;//Ϊͨ����
   if (temp>LoopEnd)  return;  //����64֮��
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//�ı���ʽ //��ʾҳ��
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
    if (PB_Flag)  Display_S(hz2,2);// ����״̬              
    else Display_S(hz1,2);
   
   //--------------����ֵ ��˸----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_SystemP_Bar(void)
{

	unsigned char hz1[]={"ϵͳ��ӡ�����ô���"};
	unsigned char hz2[]={"��ӡ���ر�"};
	unsigned char hz3[]={"��ӡ������"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//�ı���ʽ 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//�ı���ʽ 
	Display_S(hz2,10);//
	GotoXY(14,100,Dis_T);//�ı���ʽ 
	Display_S(hz3,10);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_SystemP_Text1(void)
{  
	unsigned char X,Y;
	//unsigned char hz1[]={"��"};
	//unsigned char hz2[]={"��"};
	unsigned char hz1[]={"��"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"�� ������¼��ӡ"};
	unsigned char hz4[]={"�� ���ϼ�¼��ӡ"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (Print_State==0)//ѡ���ӡ���ر�
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
	else	//��ӡ������
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

	unsigned char hz1[]={"̽������·���ô���"};
	unsigned char hz2[]={"��·���ܹر�"};
	unsigned char hz3[]={"��·���ܿ���"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//�ı���ʽ 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//�ı���ʽ 
	Display_S(hz2,12);//
	GotoXY(14,100,Dis_T);//�ı���ʽ 
	Display_S(hz3,12);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_Loop_Text1(void)
{  
	unsigned char X,Y;
	unsigned char hz1[]={"��"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"�� ����������·"};
	unsigned char hz4[]={"�� ������·����"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (LoopOpenFlag==0)//������·�ر�
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
	else//��·����
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
	unsigned char hz1[]={"̽����λ����Ϣ����"};
	unsigned char hz2[]={"̽����ID"};
	unsigned char hz3[]={"��װλ��"};
	Clr_Display();

	GotoXY(10,10,Dis_T);//�ı���ʽ 
	Display_S(hz1,18);//

	GotoXY(10,60,Dis_T);//�ı���ʽ 
	Display_S(hz2,8);//

	GotoXY(20,60,Dis_T);//�ı���ʽ 
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
  unsigned char hz1[]={"���óɹ�!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_SetPOK(void)
{
	unsigned char hz1[]={"���óɹ�!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}

void Dis_SetPErr(void)
{ 
	unsigned char hz1[]={"����ʧ��!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}


void Dis_TCQ_State_Bar1(void)
{ 
	unsigned char hz1[]={"̽��������״̬����"};
	unsigned char hz2[]={"��·ID��"};
	unsigned char hz3[]={"�� �� ֵ"};
	unsigned char hz4[]={"������"};
	unsigned char hz5[]={"�ѿ�״̬"};
	unsigned char hz6[]={"������̽����ID�ţ�"};
	unsigned char i,X,Y;
    
    Clr_Display();
   
    GotoXY(10,0,Dis_T);//�ı���ʽ 
    Display_S(hz1,18);//

   X=5;
   Y=18;


   for(i=0;i<8;i++)
   {  
     if (i==0) Line_Y(0,18,216);
     else if (i==1) Line_Y(10,18,216);
          else if(i==7) Line_Y(5+5*i,18,216);//����
          else Line_Y(5+5*i,18,196);//����
    }


    X=1;
    Y=18;
    Line_X(0,Y,39);
    for(i=0;i<3;i++)
    {  
       GotoXY(X,Y+3*i*20+2,Dis_T);//ID��
       Display_S(hz2,8);//
       Line_X(0,Y+(3*i+1)*20-1,39);
 
       GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//�趨ֵ
       Display_S(hz3,8);//
       Line_X(0,Y+(3*i+2)*20-1,39);

       GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//������
       Display_S(hz4,8);//
       Line_X(0,Y+(3*i+3)*20-1,39);
      
     }

     GotoXY(X,Y+3*i*20+2,Dis_T);//�ѿ�״̬
     Display_S(hz5,8);//
     Line_X(0,Y+(3*i+1)*20-1,39);
   
 
     GotoXY(0,222,Dis_T);//����̽��ID��
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
	unsigned char hz0[]={"��ȡʧ�ܣ�"};
	unsigned char hz1[]={"��ȡ��..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  //Display_S(hz1,10);	//��ȡ��
  Display_S(hz0,10);//��ȡʧ��
}


void Clear_Read_State(void)
{
	unsigned char hz0[]={"��ȡʧ�ܣ�"};
	unsigned char hz1[]={"��ȡ��..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);	//��ȡ��
  //Display_S(hz0,10);//��ȡʧ��

  GotoXY(13,200,Dis_T);//�ѿ�״̬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//��·��
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//�趨ֵ
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//������
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}
void Plase_Check(void)
{
	unsigned char hz0[]={"��ȷ�ϣ�"};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz0,10);//

  GotoXY(13,200,Dis_T);//�ѿ�״̬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//��·��
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//�趨ֵ
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//������
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}

void Dis_TCQ_State_Return(void)
{
	unsigned char hz0[]={"��"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"����״̬"};
	unsigned char hz3[]={"�ѱ�����"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"��ȡ�ɹ���"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//�ѿ�״̬ =1���� =0����    13 14
  
	lTemp = 0;
	lTemp = Rec_Buff[13];//�������
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //������һ·��������ʾ�ѿۿ���
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Rec_Buff[5];//�������
		temp3 = ((lTemp<<8)|Rec_Buff[6])&(0x01<<i);
		//temp3= Rec_Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Rec_Buff[7];//����״̬
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//��ַ��·�� 0��·17 18 1��·20 21
			temp2= (Rec_Buff[17+4*i]& 0x03) *256+Rec_Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID��
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//ͨ����
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//�趨ֵ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//������
			if (temp3==0)//CAN�������λ�жϣ�485��·0�����¶ȣ�
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
	unsigned char hz0[]={"��"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"����״̬"};
	unsigned char hz3[]={"�ѱ�����"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"��ȡ�ɹ���"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//�ѿ�״̬ =1���� =0����    13 14
  
	lTemp = 0;
	lTemp = Buff[13];//�������
	lTemp = (lTemp<<8)|Buff[14];
	
	if (lTemp) //������һ·��������ʾ�ѿۿ���
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Buff[5];//�������
		temp3 = ((lTemp<<8)|Buff[6])&(0x01<<i);
		//temp3= Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Buff[7];//����״̬
		temp4 = ((lTemp<<8)|Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//��ַ��·�� 0��·17 18 1��·20 21
			temp2= (Buff[17+4*i]& 0x03) *256+Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID��
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//ͨ����
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//�趨ֵ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//������
			if (temp3==0)//CAN�������λ�жϣ�485��·0�����¶ȣ�
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
	unsigned char hz0[]={"��"};
	unsigned char hz1[]={"�ѿ۲����������"};
	unsigned char hz2[]={"�����豸:"};
	unsigned char hz3[]={"̽����ID:"};
	unsigned char hz4[]={"����"};
	unsigned char hz5[]={"�ر�"};
	// code unsigned char hz6[]={"����ȷ�ϡ������в���"};
	unsigned char X,Y,i;

	Clr_Display();

	GotoXY(10,0,Dis_T);//
	Display_S(hz1,16);//

	X=4;
	Y=60;
	GotoXY(X,Y,Dis_T);
	Display_S(hz2,10);//�����豸

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//����

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//�ر�

	X=4;
	Y=120;
	GotoXY(X,Y,Dis_T);
	Display_S(hz3,10);//̽����ID

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//����

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//�ر�

	X=19;
	Y=40;
	GotoXY(X,Y,Dis_T); //��ʾ��
	Display_S(hz0,2);

	X=17;  //����
	Y=57;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=57;//�����ر�
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=17; //����
	Y=117;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=117;//�����ر�
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

	unsigned char hz0[]={"��"};
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
	unsigned char hz1[]={"ʵʱ���̽�������ݴ���"};
	unsigned char hz2[]={"��·ID��"};
	unsigned char hz3[]={"�� �� ֵ"};
	unsigned char hz4[]={"������"};
	unsigned char hz5[]={"�ѿ�״̬"};
	unsigned char hz6[]={"������̽����ID�ţ�"};
	unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(8,0,Dis_T);//�ı���ʽ 
	Display_S(hz1,22);//

	X=5;
	Y=18;

	for(i=0;i<8;i++)
	{  
		if (i==0) Line_Y(0,18,216);
		else if (i==1) Line_Y(10,18,216);
		else if(i==7) Line_Y(5+5*i,18,216);//����
		else Line_Y(5+5*i,18,196);//����
	}
	
	X=1;
	Y=18;
	Line_X(0,Y,39);
	for(i=0;i<3;i++)
	{  
		GotoXY(X,Y+3*i*20+2,Dis_T);//ID��
		Display_S(hz2,8);//
		Line_X(0,Y+(3*i+1)*20-1,39);

		GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//�趨ֵ
		Display_S(hz3,8);//
		Line_X(0,Y+(3*i+2)*20-1,39);

		GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//������
		Display_S(hz4,8);//
		Line_X(0,Y+(3*i+3)*20-1,39);
	}

	GotoXY(X,Y+3*i*20+2,Dis_T);//�ѿ�״̬
	Display_S(hz5,8);//
	Line_X(0,Y+(3*i+1)*20-1,39);


	GotoXY(0,222,Dis_T);//����̽��ID��
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
	unsigned char hz0[]={"��ȡʧ�ܣ�"};
	unsigned char hz1[]={"��ȡ��..."};
	unsigned char hz2[]={"        "};
	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);//

  GotoXY(13,200,Dis_T);//�ѿ�״̬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {

			//----------------------------------
			X=11+(i%6)*5;
			Y=20+20*3*(i/6);     
			GotoXY(X,Y,Dis_T);//��·��

			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+20,Dis_T);//�趨ֵ
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+40,Dis_T);//������
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
   }
}

void Dis_Test_Fl_Return(void)
{
	unsigned char hz0[]={"��"};
	unsigned char hz1[]={"MA"};
	unsigned char hz3[]={"�ѱ�����"};
	unsigned char hz2[]={"����״̬"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"��ȡ�ɹ���"};

	#if 1
	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//�ѿ�״̬
	
	lTemp = 0;
	lTemp = Rec_Buff[13];//�������
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //������һ·��������ʾ�ѿۿ���
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
		lTemp = Rec_Buff[7];//����״̬
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);

		if(temp4==0)
		{
			temp=i;//��ַ��·�� 0��·19 20 1��·23 24
			temp2= (Rec_Buff[19+4*i]& 0x03) *256+Rec_Buff[20+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//ID��
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//ͨ����
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//�趨ֵ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//������
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

  GotoXY(13,200,Dis_T);//�ѿ�״̬
  if ((Rec_Buff[5]& 0x80)==0) 
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);

  for(i=0;i<(TCQ_Return_Length-3)/2;i++)
  {
     temp=(Rec_Buff[5+2*i]& 0x7C)>>2;//��ַ��·��

     temp2= (Rec_Buff[5+2*i]& 0x03) *256+Rec_Buff[6+2*i]; 
    //----------------------------------
     X=11+(temp%6)*5;
     Y=20+20*3*(temp/6);     
     GotoXY(X,Y,Dis_T);//ID��
     first=0;
     if ((temp/100)==0) ;// LCD_DataWrite(' ');
     else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//ͨ����
     if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
     else LCD_DataWrite(ChCode[temp%100/10]);
     LCD_DataWrite(ChCode[temp%10]);
     //---------------------------------
      Y=40+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//�趨ֵ
      temp1=temp2/100;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%100/10;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%10;
      LCD_DataWrite(ChCode[temp1]);
     //---------------------------------
      Y=60+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//������
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
	unsigned char hz1[]={"������ϵͳʱ�䣺"};
	unsigned char hz2[]={"20  ��  ��  �ա�ʱ  ��  ��"};
	unsigned char i,X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//������ϵͳʱ��
	Display_S(hz1,16);//

	GotoXY(8,105,Dis_T);// ��  ��  �ա�ʱ  ��  ��
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

	unsigned char hz1[]={"������ˢ��ʱ�䣺"};
	unsigned char hz2[]={"��"};

	Clr_Display();

	GotoXY(12,60,Dis_T);//�ı���ʽ 
	Display_S(hz1,16);//
	GotoXY(21,105,Dis_T);//�ı���ʽ 
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
	unsigned char hz1[]={"����ʧ��!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);

}


void Dis_SetAddr_Bar(void)
{
	unsigned char hz1[]={"�����뱾����ַ��"};
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//�ı���ʽ 
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
	unsigned char hz1[]={"������������룺"};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//�ı���ʽ 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);



	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
	 GotoXY(X+3*i,Y,Dis_T);//�ı���ʽ 
	 LCD_DataWrite('*'); 
	}
	Open_Cur(X,Y+2);
 
}


void Dis_Main_Menu2(void)
{ 
	unsigned char hz0[]={"�����˵��б�"};
	unsigned char hz1[]={"����һ������"
											 "���Ķ�������"
											 "���ϵͳ��¼"
	                     "��·��������"};
	unsigned char hz2[]={"��"};
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
	unsigned char hz0[]={"���  ̽��ID ����������    ����ʱ�䡡        "};

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
	unsigned char hz0[]={"���  ̽��ID ����������    ����ʱ�䡡        "};
	unsigned char hz1[]={"ͨ��������ҳ "};
	unsigned char hz2[]={"��"};
	unsigned char hz3[]={"  "}; 

  unsigned char hz4[]={"ͨѶ����"};
  unsigned char hz5[]={"�������"};
  unsigned char hz6[]={"�������"};
  unsigned char hz7[]={"������"};
	unsigned char hz8[]={"��·��·"};
	unsigned char hz9[]={"��·��·"};
	unsigned char X,Y;
	unsigned char i,j,temp;

	unsigned char DataBuff[10];

	unsigned int Addr;
	unsigned int temp2;
	uint8_t type_error;//��������
 
   Clr_Display();
   GotoXY(2,1,Dis_T);
   Display_S(hz0,37);
   Line_Y(0,0,220);
   Line_Y(40,0,220);
   Line_X(0,0,39);
   Line_X(0,220,39);

   GotoXY(3,222,Dis_T);//��ʾ�ڼ�ҳ
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
      if (FaultNum<1)//ͨ���š�Ũ��ֵ���
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//���
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x4602 + (FaultNum-1) * 16;
					Delay1ms(1);
					RW24XX(DataBuff,9+1,Addr,0xA1);//������buf4��������
					Delay1ms(1);
                 
          GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Fault_Rec_Position;//�޸�Ϊ256
          if (temp2>FaultRecount)    
						Display_S(hz2,2);//��ʾ��
          else    
						Display_S(hz3,2);
					temp2=DataBuff[0]*256+DataBuff[1];
					temp = temp2/100;
					LCD_DataWrite(ChCode[temp]);
					temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];	//̽����ID
					type_error = DataBuff[4];
					GotoXY(X+8,Y+i*16,Dis_T);         //̽��ID
          
					if (type_error== 0)		//ͨѶ����
          {
             temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						 GotoXY(X+14,Y+i*16,Dis_T); 
						 Display_S(hz4,8);	//ͨѶ����
          }
          else if(type_error== 0xF0)//�������
          {
							LCD_DataWrite(' ');
							LCD_DataWrite(' ');
              LCD_DataWrite(' ');
						
						  GotoXY(X+14,Y+i*16,Dis_T); 
						  Display_S(hz5,8);//�������
           }  
					else if(type_error== 0xF1)//�������
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz6,8);//�������
					}  
					else if(type_error== 0xF2)//������
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz7,8);//������
					} 
					else//1-16��·��· 17-32��·
					{
						 temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						if( (type_error <=16)&&(type_error > 0))//��·
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=type_error/10;
							LCD_DataWrite(ChCode[temp]);
							temp=type_error%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz8,8);//��·��·
						}
						else if( (type_error <=32)&&(type_error >= 17))//��·
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=(type_error-16)/10;
							LCD_DataWrite(ChCode[temp]);
							temp=(type_error-16)%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz9,8);//��·��·
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

                 
           //��ʱ�䣺������ʱ�֣���[5]..[9]                 
          temp=DataBuff[4+1]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[4+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[5+1]/10;                   
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[5+1]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6+1]/10;
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[6+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[7+1]/10;        
          LCD_DataWrite(ChCode[temp]);//ʱ
          temp=DataBuff[7+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[8+1]/10;
          LCD_DataWrite(ChCode[temp]);//��
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
	unsigned char hz0[]={"��š�   �¼���������    �¼�ʱ�䡡��   ����"};

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
	unsigned char hz0[]={"��š�   �¼���������    �¼�ʱ�䡡��   ����"};
	unsigned char hz00[]={"ͨ��������ҳ "};
	unsigned char hz1[]={"ϵͳ������"};
	//unsigned char hz2[]={"ϵͳ�ػ���"};
	unsigned char hz3[]={"ϵͳ��λ��"};
	unsigned char hz4[]={"�����¼��"};
	unsigned char hz5[]={"ϵͳ��ʼ��"};

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

   GotoXY(3,222,Dis_T);//��ʾ�ڼ�ҳ
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
      if (SDNum<1)//ͨ���š�Ũ��ֵ���
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//���
              
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

          temp=DataBuff[0]/10;         //�ϵ��¼��1�ֽ�
          LCD_DataWrite(ChCode[temp]);
          temp=DataBuff[0]%10;
          LCD_DataWrite(ChCode[temp]);

          GotoXY(X+9,Y+i*16,Dis_T);
          if (DataBuff[1]==1) Display_S(hz1,10);;//�¼���������
          if (DataBuff[1]==3) Display_S(hz3,10);
          if (DataBuff[1]==4) Display_S(hz4,10);
          if (DataBuff[1]==5) Display_S(hz5,10);        
           //��ʱ�䣺������ʱ�֣���[5]..[9]                 
          temp=DataBuff[2]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[2]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[3]/10;                   
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[3]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[4]/10;
          LCD_DataWrite(ChCode[temp]);//��
          temp=DataBuff[4]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[5]/10;        
          LCD_DataWrite(ChCode[temp]);//ʱ
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[6]/10;
          LCD_DataWrite(ChCode[temp]);//��
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

	unsigned char hz1[]={"������һ�������룺"};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//�ı���ʽ 
	Display_S(hz1,18);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
		GotoXY(X+3*i,Y,Dis_T);//�ı���ʽ 
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
		GotoXY(X+3*i,Y,Dis_T);//�ı���ʽ 
		LCD_DataWrite(ChCode[dis_buff[i]]); 
	}

	if (Flicker_Position==3) 
		Open_Cur(X,Y+2);
	else 
		Open_Cur(X+3*(Flicker_Position+1),Y+2);
}

void Dis_SetPass2_Promt(void)
{  
    unsigned char hz1[]={"��������������룺"};
    unsigned char i;
    unsigned char X,Y;

    Clr_Display();
    GotoXY(11,60,Dis_T);//�ı���ʽ 
    Display_S(hz1,18);//

    Line_Y(10,90,140);
    Line_Y(30,90,140);
    Line_X(10,90,29);
    Line_X(10,140,29);

   X=14;
   Y=105;
   for (i=0;i<4;i++)
   {
     GotoXY(X+3*i,Y,Dis_T);//�ı���ʽ 
     LCD_DataWrite(ChCode[dis_buff[i]]); 
    }
    Open_Cur(X,Y+2);
}

void Clear_REC_Sure(void)
{
	unsigned char hz1[]={"���ϵͳ��¼�󣬼�¼����ʧ��"};
	unsigned char hz2[]={"���޷��ָ���ȷ�ϣ�ȡ����"};

	Clr_Display();
	GotoXY(5,60,Dis_T);
	Display_S(hz1,28);

	GotoXY(6,90,Dis_T);
	Display_S(hz2,24);
}

void Clear_REC_Promt(void)
{  
	unsigned char hz1[]={"�����ϵͳ���ݣ����Ժ�...     "};

	Clr_Display();
	GotoXY(6,90,Dis_T);
	Display_S(hz1,28);   
}

void Clear_REC_OK(void)
{  
	unsigned char hz1[]={"��ϵͳ������ɣ�"};

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
  RW24XX(&buf[0],2,0x18,0xA0); //������¼����
  Delay1ms(10);
 
  FaultRecount=0;
  buf[0]=0;
  buf[1]=0;
  RW24XX(&buf[0],2,0x1C,0xA0); //���ϼ�¼����
  Delay1ms(10);
  
  
  SDRecount=0;    //�ϵ����
  buf[0]=SDRecount; 
  RW24XX(buf,1,0x1A,0xA0);
  Delay1ms(10);
 
	//EA=1;
}

uint8_t CD_Check(void)
{
	uint8_t power;
	Power_ADC_Return();  //�����ѹADֵ
	if(CD_Flag == 1)
	{
		if (Bat_Power>3350)   //>20V ��ʱ���粻����
			power = 1;	//�������
		else
			power = 0;	//��粻����
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
		///-------------------������-----------------------------------
		//��������Main_Power_Check=0
		//�������Main_Power_Check=1
		This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	
		Main_Power_Check = This_Main_Power & Last_Main_Power;
	
		Last_Main_Power = This_Main_Power;	//��������������ͬ��״̬���жϽ���
	
		if (Check_World_Flag_State(10)) //֮ǰ����״̬����
		{   
			if (Main_Power_Check==1)   //��ʱ���粻����
			{ 
					Set_World_Flag_Flag(10,0);//��������
					Set_World_Flag_Flag(0,1);//�����ж�ָʾ����

					SendFunction[SendPtr.LoadCnt].Command = 7;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(7,0,0,0);				//�������
				
          Set_World_Flag_Flag(11,1);//�������
          Set_World_Flag_Flag(7,0);//�����ƹر�
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;
					}
					else 
					{
						FaultRecount=0;
					}//���ϼ�¼������1
					
					Save_Fault_Record(0,0xF0);//�������			
			}
			else //���������������״̬
			{
			// World_Flag=Set_Flag(World_Flag,2,1);
			// World_Flag=Set_Flag(World_Flag,3,0);  
			}
		}
		else  //֮ǰ����״̬������
		{ 
			if (Main_Power_Check==0)   //��ʱ��������
			{
					Set_World_Flag_Flag(10,1);//��������
          Set_World_Flag_Flag(11,0);//�������
					Set_World_Flag_Flag(0,0);//�����ж�ָʾ����
					SendFunction[SendPtr.LoadCnt].Command = 8;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(8,0,0,0);	//�������
			}
		}

		
}


///-------------------������-------------------------
void Bat_Power_Check(void)
{
	static uint8_t Last_Main_Power,This_Main_Power;
  uint8_t Main_Power_Check; 	//24��Ӧ3916 23V��Ӧ3745  22.5��Ӧ3663  21V ��Ӧ3391
 
	This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Main_Power_Check = This_Main_Power & Last_Main_Power;

	Last_Main_Power = This_Main_Power;	//��������������ͬ��״̬���жϽ���
	
	//Main_Power_Check=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Power_ADC_Return();  //�����ѹADֵ
	
	if (Main_Power_Check==0) //�������������־Ϊ0
	{
		Bat_Low_Flag=0;
	}  
	else //���粻������ⱸ��
	{
		if (Bat_Power>=3671) 
		{
			Bat_Low_Flag=0;
			//Set_World_Flag_Flag(6,0);//6 Ƿѹָʾ���𣬵�ѹ����
		} //��ص�ѹ����22.5V-3671   23V-3745,��ʾ��ѹ����
		else if ((Bat_Power>=3580)&&(Bat_Power<3650)) 
		{
			Bat_Low_Flag=1;
			//Set_World_Flag_Flag(6,1);//6 Ƿѹָʾ����
		} //605 22V--22.5V ��ʾ�����־
		else if ((Bat_Power<3570)&&(Main_Power_Check==1)) 
		{
			BD_OFF();
		}//��ص���21.5V���Ҳ���������ϵͳ�ϵ籣�����
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
		
	if (Check_World_Flag_State(12)) //֮ǰ����״̬����
	{
		if (Bat_Power<3350)   //<20V ��ʱ���粻����
		{ 
			Set_World_Flag_Flag(12,0);//��������
			Set_World_Flag_Flag(13,1);//�������
			//Set_World_Flag_Flag(0,1);//�����ж�ָʾ����
			 
			SendFunction[SendPtr.LoadCnt].Command = 9;
			SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
			SendFunction[SendPtr.LoadCnt].TDH = 0;
			SendFunction[SendPtr.LoadCnt].type = 0;
			SendPtr.LoadCnt++;

			//SendToPC1(9,0,0,0);	//�������
			
			Set_World_Flag_Flag(7,0);//�����ƹر�
			Beep_Alarm_Fault=2;

			if (FaultRecount<500)
			{
				FaultRecount ++;
			}
			else 
			{
				FaultRecount=0;
			}//���ϼ�¼������1
			Save_Fault_Record(0,0xF1);//�������
			
			CD_Flag = 0;	//������ϣ��رճ��
			//CDK_OFF();
		}
		else
		{
			if(Main_Power_Check == 0)//��������������������ʼ���
			{
				CD_Flag = 1;
				//CDK_ON();
			}
		}
	}
	else  //֮ǰ����״̬������
	{ 
			if (Bat_Power>3390)   //>20V ��ʾ��ʱ��������
			{
				Set_World_Flag_Flag(12,1);//��������
				Set_World_Flag_Flag(13,0);//�������
				//Set_World_Flag_Flag(0,0);//�����ж�ָʾ����
				
				SendFunction[SendPtr.LoadCnt].Command = 10;
				SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
				SendFunction[SendPtr.LoadCnt].TDH = 0;
				SendFunction[SendPtr.LoadCnt].type = 0;
				SendPtr.LoadCnt++;

				//SendToPC1(10,0,0,0);	//����ָ�
				
				if(Main_Power_Check == 0)//��������������������ʼ���
				{
					CD_Flag = 1;
					//CDK_ON();
				}
			}
			else
			{
				CD_Flag = 0;	//������ϣ��رճ��
				//CDK_OFF();
			}
	}
/*
	//----------------------�����-------------------------
			if (!Check_World_Flag_State(7)) //֮ǰ���״̬����
			{      
				if ((CD_Check()==0)||(Main_Power_Check==1)||(Bat_Power<3350))   //��ʱ��粻����
				{ 
					Set_World_Flag_Flag(7,1);//�����ϵ���
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;//���ϼ�¼������1
					}
					else 
					{
						FaultRecount=0;
					}
					Save_Fault_Record(0,0xF2);//������
				}

			}
			else  //֮ǰ״̬������
			{ 
				if ((CD_Check()==1)&&(Main_Power_Check==0))   //��ʱ�������
				{
					Set_World_Flag_Flag(7,0);//
				}
			}
*/
}

void TCQ_Data_Control(void)//��ȡ������״̬�����մ��������ص�����
{
	uint8_t i,k,m,pn;
	uint8_t flag=0;
	uint16_t lTemp = 0;
	
	TCDID=Rec_Buff[0]*256+Rec_Buff[1];			//�豸ID��
	Type_State=Rec_Buff[5]*256+Rec_Buff[6];	//�������=1���� =0�¶�
	PB_State =Rec_Buff[7]*256+Rec_Buff[8];	//����״̬=1���� =0����
	State1=Rec_Buff[9]*256+Rec_Buff[10];		//����״̬�͹���״̬��λ
	State2=Rec_Buff[11]*256+Rec_Buff[12];		//����״̬�͹���״̬��λ
	SKC_State=Rec_Buff[13]*256+Rec_Buff[14];//�ѿ�״̬=1���� =0����
	//MKC_State=Rec_Buff[15]*256+Rec_Buff[16];
	 
	Alarm_State=0;
	Fault_State=0;
	
	Set_Uart_Fault_Timer0(TCDID-1);//Uart_Err_Timer[TCDID-1]=0;
	
	if((Function_Flag==7)||(Function_Flag==6))//д״̬����ֵ
	{
		TCQ_Return_OK=1;
	
		for(i=0;i<16;i++)//16����·״̬
		{
			temp1 =PB_State&(1 << i);
			if (temp1!=0)//=1��ʾ��·Ϊ����״̬  
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
				continue;
			}
			
			temp1 =State1 & (1 << i);
			temp2 =State2 & (1 << i);
			if((temp1==0)&&(temp2==0))//����			 
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			}
			else if((temp1^temp2)!=0) //���ϻ򱨾�  01��· 10��·
			{
				if(!Check_Sensor_Fault0_State(TCDID-1,i))//��·����
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
		if (temp1!=0)//=1����״̬ =0����״̬
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			continue;
		}

		temp1 =State1 & (1 << i);//����״̬�͹���״̬��λ
		temp2 =State2 & (1 << i);
		    
		if((temp1==0)&&(temp2==0))//�������޹��ϱ���	
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
		}
		else if((temp1^temp2)!=0) //�й��� 01 ��· 10 ��·
		{
			if(!Check_Sensor_Fault0_State(TCDID-1,i))//֮ǰ�޹��ϱ���
			{
				Fault_State=Fault_State|(1<<i);
				Set_Sensor_Fault0_Flag(TCDID-1,i,1);
				
				if (FaultRecount<500) //���ϼ�¼����500��
				{
					FaultRecount++;
				}
				else 
				{
					FaultRecount=1;//������¼������1
				}	
				
				Beep_Alarm_Fault = 2;//�������ϱ�������
				Set_World_Flag_Flag(7,0);//�����ƹر�
				Beep_ON();
				
				pn=Fault_Rec;//��������ʾ�Ĺ�����
				if (pn>12) 
				{
					pn=12;  
				}
				
				if((temp1 != 0)&&(temp2==0))
				{
					//���뿪·����
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0800 | TCDID);
					Save_Fault_Record(TCDID,i+1);		//��·
				}
				else 
				{
					//�����·����
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0400 | TCDID);
					Save_Fault_Record(TCDID,i+17);	//��·
				}
				
				flag=0;
				for(k=0;k<pn;k++)//����ͬ�ģ���ߵ�ǰ��һλ
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
					Fault_Rec++;	//����������1
					//�����ʾ12������
					if (pn==12)
					for(m=0;m<12;m++) 
					{
						Fault_Position[m]=Fault_Position[m+1];
					}
				}		
		
			}
		}
		else if((temp1!=0)&&(temp2!=0))//11 ����״̬
		{	 
			//Feel[i]=(Rec_Buff[19+4*i]&0x7F)*256+Rec_Buff[20+4*i];
			Alarm_State=Alarm_State|(1<<i); 
			Set_Alarm_Flag(TCDID-1,1);
			Set_Alarm_Flag_16(TCDID-1,i,1);
			Speak_ON();
			Beep_Alarm_Fault=1; 
			
			KC1_ON();
			KC2_ON();
			Set_World_Flag_Flag(2,1);//���ָʾ����
			Dis_State_LED();//״ָ̬ʾ����ʾ
	
			// if (First_Alarm==0)  {First_Alarm=TCDID*16+i+1;} 
			//-----------------------------------------------------------------------     
			Function_Flag = 15;	//��ȡ�������ֵ
			
			pn=Alarm_Rec_Position;
			if (pn>7) 
			{
				pn=7;  
			}
			//��λ��ʾ�������
			if((Type_State& (1<<i))==0) //�������=1���� =0�¶�
				Alarm_Position[pn]=0*4096+TCDID;
			else 
				Alarm_Position[pn]=(i+1)*4096+TCDID; 

			//Alarm_Data[pn]=Feel[i];
			
			flag=0;
			for(k=0;k<pn;k++)//����ͬ�ģ���ߵ�ǰ��һλ
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
				Alarm_Rec_Position++;	//����������1
				//�����ʾ7��
				if (pn==7)
				for(m=0;m<7;m++) 
				{
					Alarm_Position[m]=Alarm_Position[m+1];
					Alarm_Data[m]=Alarm_Data[m+1];
				}
			}				
		}//end else
	}//end for 	

	if(Alarm_State!=0)//�б���״̬
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
		
		//SendToPC1(4,TCDID,1,0x31);//���ͱ�����Ϣ������
	}

//	if(Fault_State!=0)//����������
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

void Set_Sensor_Fault0_Flag(uint8_t Num,uint8_t nbit,uint8_t flag)//��������ĳһ��·������־��1����0
{
	uint16_t x,temp;

	temp=Sensor_Fault0_Flag[Num];

	x= 1 << nbit; 

	if (flag==1)   //=1����Ӧ��λ����1
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

uint8_t Check_Sensor_Fault0_State(uint8_t Num,uint8_t nbit)//���Ϸ���1
{
	uint16_t temp;
	temp=Sensor_Fault0_Flag[Num];

	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1;  
}




