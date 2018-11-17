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
"*      ÁÙÒÊÊÐ°²¸£µç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾      *"
"*¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡            *"
"*                                      *"
"*    ¡M  AF116 µçÆø»ðÔÖ¼à¿ØÉè±¸¡¡¡¡¡¡  *"
"*          ¡¡¡¡¡¡     ¡¡¡¡¡¡¡¡¡¡       *"
"*               V1.0                   *"
"*¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡            *"
"*¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡            *"
"*                ¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡    *"
"* µØÖ·£ºÉ½¶«Ê¡ÁÙÒÊÊÐºÓ¶«¾­¼Ã¼¼Êõ¿ª·¢Çø *"
"* TEL £º0539-6012963 FAX£º0539-8165301 *"
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
//		if(Read_BUSY()==1){ break;}//·ÀÖ¹ËÀÑ­»·
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_1();//rs=1;//·¢ËÍÃüÁî
	//BUS=cmdaddr;//½«Êý¾ÝÐ´Èë²¢ÐÐ×ÜÏß
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
//		if(Read_BUSY()==1){ break;}//·ÀÖ¹ËÀÑ­»·
//	}
	//while( Read_BUSY() == 0 );
	
	CS1_0();//cs1=0;
	RD_1();//rd=1;
	RS_0();//rs=0;	//Ð´ÈëÊý¾Ý
	//BUS=dat;//½«Êý¾ÝÐ´Èë²¢ÐÐ×ÜÏß
	SendData(dat);	
	WR_0();//wr=0;
	WR_1();//wr=1;
	CS1_1();//cs1=1;
	Delay1us(50);
}


void GotoXY(unsigned char x,unsigned char y,unsigned char TP)
{     
   LCD_CmdWrite(CPXR); //x×ø±ê
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y×ø±ê
   LCD_DataWrite(y);
   LCD_CmdWrite(0x00); 
   LCD_DataWrite(TP);
 
   LCD_CmdWrite(0xb0); 
}

void Open_Cur(unsigned char x,unsigned char y)
{
   LCD_CmdWrite(WCCR);		//[10H] , Default --> 0x00
   LCD_DataWrite(0x07);//(0x06);
   LCD_CmdWrite(CPXR); //x×ø±ê
   LCD_DataWrite(x);
   LCD_CmdWrite(CPYR); //Y×ø±ê
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

	LCD_CmdWrite(ITCR);		//[90H] , Default --> 0x00    ÐèÒªµ÷Õû
	LCD_DataWrite(0x80);

	LCD_CmdWrite(PNTR);		//[E0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FNCR);		//[F0H] , Default --> 0x00
	LCD_DataWrite(0x00);

	LCD_CmdWrite(FVHT);		//[F1H] , Default --> 0x00
	LCD_DataWrite(0x00);
}
/////////////////ÇåÆÁ×Ó³ÌÐò//////////////////////////
void Clr_Display(void)
{ 
  LCD_CmdWrite(0x00);
  LCD_DataWrite(0x04);     //Ñ¡Ôñ»æÍ¼Ä£Ê½     
  LCD_CmdWrite(0xe0);
  LCD_DataWrite(0x00);
  LCD_CmdWrite(0xf0);
  LCD_DataWrite(0xa8);
  delay_nms(100);
}

/////////////ÏÔÊ¾ÖÐÎÄ×Ö¿âºÍ×Ö·û////////////////////
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

void Dis_State_LED_ON(void)//×´Ì¬Ö¸Ê¾µÆÈ«ÁÁ
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0x0000; 
   dis_char(temp2);
   DIS_ON();
}

void Dis_State_LED_OFF(void)//×´Ì¬Ö¸Ê¾µÆÈ«Ãð
{
   uint16_t  temp2;

   DIS_OFF();
   temp2 =0xFFFF; 
   dis_char(temp2);
   DIS_ON();
}


void Dis_State_LED(void)//×´Ì¬Ö¸Ê¾µÆÏÔÊ¾
{
	uint16_t temp2;

	DIS_OFF();
	/*
	if(Alarm_Rec_Position!=0)  
		Set_World_Flag_Flag(2,1);//Æô¶¯

	if(XAlarm_Rec_Position!=0)
	{ 
		if(Flash_Flag)	 
		{
			Set_World_Flag_Flag(2,1);
			Flash_Flag=0;
		}//Æô¶¯ÉÁÁÁ£½Î´·´À¡
		else 
		{
			Set_World_Flag_Flag(2,0);
			Flash_Flag=1;
		}
	} 
	if(RAlarm_Rec_Position!=0) 
		Set_World_Flag_Flag(4,1);//·´À¡
	else 
		Set_World_Flag_Flag(4,0); 
*/
	temp2=0xFFFF-World_Flag; 
	dis_char(temp2);
	DIS_ON();
}

void Display_LowPower(void)
{
  uint8_t hz1[]={"±¸ÓÃµçÔ´µçÑ¹²»×ã"};
  //uint8_t hz2[]={"Çë¼°Ê±²ÉÓÃÖ÷µç¸øÏµÍ³¹©µç£¡"};


   Clr_Display();
	 GotoXY(12,100,Dis_T);
   Display_S(hz1,16);
}

void SD_Display_60S(unsigned char TNum)//ÉÏµçÏÔÊ¾
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
  GotoXY(x,y,Dis_P);//»æÍ¼·½Ê½ 
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
     { GotoXY(x,(y+i),Dis_P);//»æÍ¼·½Ê½
       LCD_DataWrite(0x80); 
     }
   }
 
}

void Display_Main_Face(void)
{
  unsigned char hz0[]={"ÏµÍ³Õý³£¼à¿ØÖÐ..."};
  unsigned char hz1[]={"¹ÊÕÏ»ØÂ·ÐÅÏ¢£º     "};
  unsigned char hz2[]={"±¨¾¯»ØÂ·ÐÅÏ¢£º     "};
  unsigned char hz3[]={"ÏµÍ³¹ÊÕÏÐÅÏ¢£º     "};
	
	Clr_Display();

	//GotoXY(3,103,Dis_T);//ÎÄ×ÖÏÔÊ¾·½Ê½£¬ÏÔÊ¾ÏµÍ³Õý³£¼à¿ØÖÐ
	//Display_S(hz0,17);
	
	Line_Y(0,0,239);
	Line_Y(40,0,239);
	Line_Y(21,0,221);
	
	//Line_X(0,18,39);
	//Line_X(0,239,39);
	
	Line_X(0,0,39);
	Line_X(0,239,39);
	
	GotoXY(1,1,Dis_T);//ÏÔÊ¾ÔËÐÐ×´Ì¬
	Display_S(hz1,14);

	GotoXY(23,1,Dis_T);//ÏÔÊ¾±¨¾¯ÐÅÏ¢
	Display_S(hz2,14);
	//Line_X(0,35,39);
	Line_X(0,17,39);
	
	GotoXY(23,124+18,Dis_T);//ÏÔÊ¾¹ÊÕÏÐÅÏ¢
	Display_S(hz3,14);
	Line_X(21,123+18,39);
	Line_X(21,140+18,39);

	//----------------------------------

	Line_X(0,221,39);
}

void Dis_NoAlarmR(void)	//ÏÔÊ¾ÎÞ±¨¾¯¼ÇÂ¼
{  
	unsigned char hz0[]={"ÎÞ±¨¾¯¼ÇÂ¼£¡"};

  GotoXY(25,70,Dis_T);
  Display_S(hz0,12);
}

void Dis_NoFaultR(void)	//ÏÔÊ¾ÎÞ¹ÊÕÏ¼ÇÂ¼
{ 
	unsigned char hz0[]={"ÎÞ¹ÊÕÏ¼ÇÂ¼£¡"};
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
	unsigned char hz0[]={"µ±Ç°Ê±¼ä£º20"};
	unsigned char nian[]={"Äê"};
	unsigned char yue[]={"ÔÂ"};
	unsigned char ri[]={"ÈÕ"};
	unsigned char shi[]={"Ê±"};
	unsigned char fen[]={"·Ö"};
	unsigned char miao[]={"Ãë"};
	
	uint8_t temp;

  GotoXY(1,222,Dis_T);
  Display_S(hz0,12);
	
	GotoXY(13,222,Dis_T);

	temp=Real_Time.year%2000/10;//Äê
  LCD_DataWrite(ChCode[temp]); //Äê
	temp=Real_Time.year%2000%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	temp=Real_Time.month/10;//ÔÂ
	LCD_DataWrite(ChCode[temp]); //ÔÂ
	temp=Real_Time.month%10;
	LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite('-');

	
	temp=Real_Time.day/10;//ÈÕ
	LCD_DataWrite(ChCode[temp]); //ÈÕ
	temp=Real_Time.day%10;
  LCD_DataWrite(ChCode[temp]);
  LCD_DataWrite(' ');
 
 	temp=Real_Time.hour/10;//Ê±
	LCD_DataWrite(ChCode[temp]); //Ê±
	temp=Real_Time.hour%10;
	LCD_DataWrite(ChCode[temp]); //Ê±
  LCD_DataWrite(':');
 
	temp=Real_Time.min/10;//·Ö
	LCD_DataWrite(ChCode[temp]); //·Ö
	temp=Real_Time.min%10;
  LCD_DataWrite(ChCode[temp]); //·Ö
  LCD_DataWrite(':');

	temp=Real_Time.sec/10;//Ãë
	LCD_DataWrite(ChCode[temp]); //Ãë
	temp=Real_Time.sec%10;
	LCD_DataWrite(ChCode[temp]); //Ãë
}

//------------------------

void Clear_Dispaly_Feel(void)
{
		unsigned char i;
		unsigned char hz10[]={"                     "};
		for(i=0;i<12;i++)//ÐèÒªË¢ÐÂÏÔÊ¾ÇøÓò
		{
			GotoXY(2,18+i*17,Dis_T);
			Display_S(hz10,19);
		}		
}


void Display_Feel_Fault(void)//½öÏÔÊ¾¹ÊÕÏ
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"Õý³£¡¡¡¡"};
		unsigned char hz1[]={"±¨¾¯¡¡¡ï"};
		unsigned char hz2[]={"¹ÊÕÏ¡¡¡ó"};
		unsigned char hz3[]={"Í¨Ñ¶¹ÊÕÏ&±¨¾¯"};
		unsigned char hz4[]={"Ì½²âÆ÷ID¡¡ ÔËÐÐ×´Ì¬"};
		unsigned char hz5[]={"Ì½²âÆ÷ID  µØÖ· ×´Ì¬"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"¿ªÂ·"};
		unsigned char hz8[]={"¶ÌÂ·"};
		unsigned char hz9[]={"ÏµÍ³Õý³£¼à¿ØÖÐ..."};
		unsigned char hz10[]={"                     "};
		unsigned char hz11[]={"Çø"};
		unsigned char hz12[]={"ºÅ"};
		unsigned char hz13[]={"µ¥Ôª"};
		GotoXY(1,1,Dis_T);//Í¨Ñ¶¹ÊÕÏ&±¨¾¯
		Display_S(hz3,14);
		
		GotoXY(16,1,Dis_T);//Í¨Ñ¶¹ÊÕÏ&±¨¾¯
		Display_S(hz10,4);

		if( LoopEnd > 256 )	//EndAddr´óÓÚ256¼ì²â4´ÎÍ¨Ñ¶´íÎó
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;
		

		
		if( Fault_Num == 0 )
		{		
			Clear_Dispaly_Feel();
			
			GotoXY(3,103,Dis_T);//ÎÄ×ÖÏÔÊ¾·½Ê½£¬ÏÔÊ¾ÏµÍ³Õý³£¼à¿ØÖÐ
			Display_S(hz9,17);
		}
		else
		{
			i=0;
			X=2;
			Y=18;
			
			while(i<12)//Ã¿´ÎÏÔÊ¾12ÐÐÌ½²âÆ÷Êý¾Ý //Ö»ÏÔÊ¾¹ÊÕÏºÍ±¨¾¯
			{ 
				 if ((!Check_Shield_State(Dis_Num))&&((Uart_Fault_Timer(Dis_Num)>=cTemp)||(Check_Alarm_State(Dis_Num)))) //Ã»ÓÐÆÁ±Î²¢ÇÒÐ¡ÓÚ64
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num+1)/100;
							 LCD_DataWrite(ChCode[temp]);  //µØÖ·ºÅ 
							 temp=(Dis_Num+1)%100/10;
							 LCD_DataWrite(ChCode[temp]);
							 temp=(Dis_Num+1)%10;
							 LCD_DataWrite(ChCode[temp]);
							 LCD_DataWrite(' ');
							 
							if(Dis_Num >= End_Addr)
							{
								 LCD_DataWrite('H');	//±íÊ¾Éè±¸ÔÚ»ØÂ·°åÉÏ
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
						
							if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8´ÎÍ¨Ñ¶Ê§°ÜÈÎÎñÍ¨Ñ¶¹ÊÕÏ
								Display_S(hz2,8);//¹ÊÕÏ 
							else if (Check_Alarm_State(Dis_Num))
								Display_S(hz1,8);//±¨¾¯
							else  
								Display_S(hz0,8);//Õý³£
							
							if(DisplayAddr == 1)//ÏÔÊ¾Éè±¸°²×°µØÖ·
							{
								GotoXY(X+8,Y+i*17,Dis_T);

								temp=address[Dis_Num][0]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][0]%10;
								LCD_DataWrite(ChCode[temp]);			
								
								Display_S(hz11,2);//Çø

								temp=address[Dis_Num][1]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][1]%10;
								LCD_DataWrite(ChCode[temp]);
								Display_S(hz12,2);//ºÅ
		
								temp=address[Dis_Num][2]/10;
								LCD_DataWrite(ChCode[temp]); 
								temp=address[Dis_Num][2]%10;
								LCD_DataWrite(ChCode[temp]);								
							}
							else
							{
								GotoXY(X+7,Y+i*17,Dis_T);
								Display_S(hz6,3);//Õý³£
							}
					 i++; 
				 }//Èç¹ûÃ»ÓÐÆÁ±ÎÊ±´¦Àí½áÊø

				 
				 if( LoopOpenFlag == 1)	//¿ªÆô»ØÂ·1¹¦ÄÜ
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
									LCD_DataWrite(' ');  //µØÖ·ºÅ 
								i++;
							}
							break; 
						} 
				 
				 }
				 else	//Ö»Ê¹ÓÃÖ÷»ØÂ·
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
									LCD_DataWrite(' ');  //µØÖ·ºÅ 
								i++;
							}
							break; 
						} 
				 } 
			}//while ½áÊø
		
		}

}

void Display_Main_Fault(void)
{
		unsigned char pn,X,Y;
		unsigned char i,j,temp;
		unsigned char hz0[]={"Õý³£¡¡¡¡"};
		unsigned char hz1[]={"±¨¾¯¡¡¡ï"};
		unsigned char hz2[]={"¹ÊÕÏ¡¡¡ó"};
		unsigned char hz3[]={"Í¨Ñ¶¹ÊÕÏ"};
		unsigned char hz4[]={"»ØÂ·¿ªÂ·"};
		unsigned char hz5[]={"»ØÂ·¶ÌÂ·"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"¿ªÂ·"};
		unsigned char hz8[]={"¶ÌÂ·"};
		unsigned char hz9[]={"ÏµÍ³Õý³£¼à¿ØÖÐ..."};
		unsigned char hz10[]={"                     "};	
		unsigned char hz11[]={"¹ÊÕÏ»ØÂ·ÐÅÏ¢: "};
		uint8_t cTemp;
		uint8_t huilu;
		uint8_t huilustate;
		uint8_t first;
		
		GotoXY(1,1,Dis_T);//ÏÔÊ¾ÔËÐÐ×´Ì¬
		Display_S(hz11,14);
		
		pn = Fault_Rec;	//»ØÂ·¹ÊÕÏ
		
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
		
		if( pn == 0 )//¹ÊÕÏ×ÜÊý
		{
			for(i=0;i<12;i++)//ÐèÒªË¢ÐÂÏÔÊ¾ÇøÓò
			{
				GotoXY(2,18+i*17,Dis_T);
				Display_S(hz10,19);
			}		
			
			GotoXY(3,103,Dis_T);//ÎÄ×ÖÏÔÊ¾·½Ê½£¬ÏÔÊ¾ÏµÍ³Õý³£¼à¿ØÖÐ
			Display_S(hz9,17);
		}
		else
		{
			GotoXY(3,103,Dis_T);//Çå³ýÏµÍ³Õý³£¼à¿ØÖÐ
			Display_S(hz10,17);
			i=0;
			X=2;
			Y=18;
			
			if(pn>12)
				pn=12;
					
			while(i<pn)//Ã¿´ÎÏÔÊ¾12ÐÐÌ½²âÆ÷Êý¾Ý	//Ö»ÏÔÊ¾¹ÊÕÏºÍ±¨¾¯
			{  
				 Dis_Num = Fault_Position[i]&0x3FF;//µÍ10Î»±íÊ¾Éè±¸ºÅ
				 huilu = (Fault_Position[i]>>12)&0x0F;
				 huilustate=(Fault_Position[i]>>10) & 0x03;
				if (!Check_Shield_State(Dis_Num)) 
				 { 
							 GotoXY(X,Y+i*17,Dis_T);
							 temp=(Dis_Num)/100;
							 LCD_DataWrite(ChCode[temp]);  //µØÖ·ºÅ 
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
								 LCD_DataWrite('H');	//±íÊ¾Éè±¸ÔÚ»ØÂ·°åÉÏ
								 LCD_DataWrite('1');
							}
							else	
							{							
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
								LCD_DataWrite(' ');
							}
							
							if(huilustate==1)//¶ÌÂ·
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz5,8);//»ØÂ·¶ÌÂ·
							}
							else if(huilustate==2)//¿ªÂ·
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz4,8);//»ØÂ·¶ÌÂ·
							}
							else if(huilustate==3)//Í¨Ñ¶¹ÊÕÏ
							{
								GotoXY(X+10,Y+i*17,Dis_T);
								Display_S(hz3,8);//»ØÂ·¶ÌÂ·
							}			
					i++;
				 }//Èç¹ûÃ»ÓÐÆÁ±ÎÊ±´¦Àí½áÊø	
					 
			}//while ½áÊø
		
		}

}
void Display_Feel(void)
{
		unsigned char X,Y;
		unsigned char i,j,temp;
		uint8_t cTemp;
		unsigned char hz0[]={"Õý³£¡¡¡¡"};
		unsigned char hz1[]={"±¨¾¯¡¡¡ï"};
		unsigned char hz2[]={"¹ÊÕÏ¡¡¡ó"};
		unsigned char hz3[]={"        "};
		unsigned char hz4[]={"Ì½²âÆ÷ID¡¡ ÔËÐÐ×´Ì¬"};
		unsigned char hz5[]={"Ì½²âÆ÷ID  µØÖ· ×´Ì¬"};
		unsigned char hz6[]={"    "};
		unsigned char hz7[]={"¿ªÂ·"};
		unsigned char hz8[]={"¶ÌÂ·"};
		unsigned char hz9[]={"ÏµÍ³Õý³£¼à¿ØÖÐ..."};
		if( LoopEnd > 256 )	//EndAddr´óÓÚ256¼ì²â4´ÎÍ¨Ñ¶´íÎó
			cTemp = Max_Uart/2;
		else
			cTemp = Max_Uart;

		i=0;
		X=2;
		Y=18;
		
		while(i<12)//Ã¿´ÎÏÔÊ¾12ÐÐÌ½²âÆ÷Êý¾Ý
		{  
       if (!Check_Shield_State(Dis_Num)) //Ã»ÓÐÆÁ±Î²¢ÇÒÐ¡ÓÚ64
       { 
             GotoXY(X,Y+i*17,Dis_T);
             temp=(Dis_Num+1)/100;
             LCD_DataWrite(ChCode[temp]);  //µØÖ·ºÅ 
             temp=(Dis_Num+1)%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=(Dis_Num+1)%10;
             LCD_DataWrite(ChCode[temp]);
             LCD_DataWrite(' ');
            
						if(Dis_Num >= End_Addr)
						{
							 LCD_DataWrite('H');	//±íÊ¾Éè±¸ÔÚ»ØÂ·°åÉÏ
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
            
						
					
            if (Uart_Fault_Timer(Dis_Num)>=cTemp) //8´ÎÍ¨Ñ¶Ê§°ÜÈÎÎñÍ¨Ñ¶¹ÊÕÏ
							Display_S(hz2,8);//¹ÊÕÏ 
            else if (Check_Alarm_State(Dis_Num))	//³¬ÏÞ±¨¾¯
							Display_S(hz1,8);//±¨¾¯
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz7,8);//¿ªÂ·
//						else if(Check_Alarm_State(Dis_Num))
//							Display_S(hz8,8);//¶ÌÂ·
            else  
							Display_S(hz0,8);//Õý³£
						
						if(DisplayAddr == 1)//ÏÔÊ¾Éè±¸°²×°µØÖ·
						{
							GotoXY(X+7,Y+i*17,Dis_T);

							temp=address[Dis_Num][0]/10;//Äê
							LCD_DataWrite(ChCode[temp]); //Äê
							temp=address[Dis_Num][0]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');

							temp=address[Dis_Num][1]/10;//ÔÂ
							LCD_DataWrite(ChCode[temp]); //ÔÂ
							temp=address[Dis_Num][1]%10;
							LCD_DataWrite(ChCode[temp]);
							LCD_DataWrite('-');
	
							temp=address[Dis_Num][2]/10;//ÈÕ
							LCD_DataWrite(ChCode[temp]); //ÈÕ
							temp=address[Dis_Num][2]%10;
							LCD_DataWrite(ChCode[temp]);		
						}
						else
						{
						  GotoXY(X+7,Y+i*17,Dis_T);
							Display_S(hz6,3);//Õý³£
						}
         i++; 
       }//Èç¹ûÃ»ÓÐÆÁ±ÎÊ±´¦Àí½áÊø

			 
			 if( LoopOpenFlag == 1)	//¿ªÆô»ØÂ·1¹¦ÄÜ
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
								LCD_DataWrite(' ');  //µØÖ·ºÅ 
							i++;
						}
						break; 
					} 
			 
			 }
			 else	//Ö»Ê¹ÓÃÖ÷»ØÂ·
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
								LCD_DataWrite(' ');  //µØÖ·ºÅ 
							i++;
						}
						break; 
					} 
			 } 
    }//while ½áÊø¡¡
}


void Display_System_Sate(void)
{
	unsigned char hz0[]={"¡æ"};
	unsigned char hz1[]={"MA"};
	
	unsigned char hz3[]={"Í¨Ñ¶¹ÊÕÏ£º  "};
	unsigned char hz4[]={"Ì½²â¹ÊÕÏ£º  "};
	unsigned char hz5[]={"Ö÷µç¹ÊÕÏ    "};
	unsigned char hz6[]={"±¸µç¹ÊÕÏ    "};
	unsigned char hz7[]={"³äµç¹ÊÕÏ    "};
	unsigned char hz8[]={"            "};
	unsigned char hz9[]={"                  "};
	unsigned char X,Y,i,j;
	unsigned int pn;
	uint8_t first=0;
	uint16_t nbit_F,temp;

	X=36;
	Y=1;

	GotoXY(X,Y,Dis_T);
	pn=Alarm_Rec_Position;//¼ÆËã±¨¾¯²¿Î»×ÜÊý
	
	first=0;				//ÏÔÊ¾±¨¾¯»ØÂ·×ÜÊý
	temp=pn/100;		//°ÙÎ»
	if (temp==0)  
		LCD_DataWrite(' ');
	else 
	{ 
		LCD_DataWrite(ChCode[temp]);
		first=1;
	}//Í¨µÀºÅ
	
	temp=pn%100/10;	//Ê®Î»
	if ((temp==0)&&(first==0))  
		LCD_DataWrite(' '); 
	else 
		LCD_DataWrite(ChCode[temp]);  
	
	temp=pn%10;			//¸öÎ»
	LCD_DataWrite(ChCode[temp]);

	if (pn==0) 
	{
		//ÏÔÊ¾Ç°ÇåÀíÏÔÊ¾ÇøÓò
		for(i=0;i<7;i++)
		{
			GotoXY(22,20+i*16,Dis_T);
			Display_S(hz9,17);
		}		
		Dis_NoAlarmR();
	}
	else
	{
		GotoXY(25,70,Dis_T);//Çå³ýÎÞ±¨¾¯¼ÇÂ¼
		for(i=0;i<12;i++)   
			LCD_DataWrite(' ');

		Y=20;	//Ô­Îª36
		//×î¶àÏÔÊ¾7Ìõ±¨¾¯Êý¾Ý
		if (pn>7)
			pn=7;
		
		for(i=0;i<pn;i++)
		{  
			if (i<7) 
				X=22;
			else 
				X=31;
		
			temp=Alarm_Position[i]%4096/100;	//Éè±¸ºÅ  ºó12Î»Êý×Ö£¬°ÙÎ»
			GotoXY(X,Y+i%7*16,Dis_T);
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%100/10;
			LCD_DataWrite(ChCode[temp]);
			temp=Alarm_Position[i]%4096%10;
			LCD_DataWrite(ChCode[temp]);
			LCD_DataWrite('-');

			if ((Alarm_Position[i]/4096)==0) 	//001-02 »ØÂ·ºÅ  ±íÊ¾¸ß4Î»
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
			temp = Alarm_Data[i]/1000;		//Ç§Î»
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%1000/100;	//°ÙÎ»
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			temp = Alarm_Data[i]%100/10;		//Ê®Î»
			
			if ((temp==0)&&(first==0)) 
			{				
				LCD_DataWrite(' ');
			}				
			else 
			{
				first = 1;
				LCD_DataWrite(ChCode[temp]);  
			}
			
			temp = Alarm_Data[i]%10;				//¸öÎ»
			LCD_DataWrite(ChCode[temp]);
			
			if ((Alarm_Position[i]/4096)==0) 	//001-02 »ØÂ·ºÅ  ±íÊ¾¸ß4Î»
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
   
  if (Fault_Rec_Position==0)//¹ÊÕÏ×ÜÊý
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
		Y=145+18;//ÏÂÒÆÒ»ÐÐ	
		i=0;
		GotoXY(X,Y,Dis_T);
		Display_S(hz3,13);//ÏÔÊ¾Í¨Ñ¶¹ÊÕÏ
		//i++; 

		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 11);	//11Ö÷µç¹ÊÕÏ
		if( nbit_F ) //	if (Check_World_Flag_State(11))
		{  
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz5,13);
			i++;  
		}//Ö÷µç¹ÊÕÏ
		
		temp=World_Flag;
		nbit_F = 0;
		nbit_F=temp & (1 << 13);	//13 ±¸µç¹ÊÕÏ
		if ( nbit_F ) // if (Check_World_Flag_State(5))  
		{   
			Y=Y+18;
			GotoXY(X,Y,Dis_T);
			Display_S(hz6,13);
			i++;
		}//±¸µç¹ÊÕÏ
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
		}//³äµç¹ÊÕÏ
*/
		X=25;
		Y=145+18;//ÏÂÒÆÒ»ÐÐ
		for(j=i+1;j<3;j++)//ÇåÀíÏÔÊ¾ÇøÓò
		{  
			GotoXY(X,Y+j*18,Dis_T);
			Display_S(hz8,13);
		} 
   
    X=34;
    GotoXY(X,Y,Dis_T);
    first=0;
    
    pn=Fault_Rec_Position-i;//Ì½²â¹ÊÕÏ×ÜÊý ¼õÈ¥Ôö¼ÓµÄ±¸µç¹ÊÕÏ Ö÷µç¹ÊÕÏ
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
	uint8_t hz1[]={"ÃÅÆô¶¯¡¡"};
	//uint8_t hz2[]={"ÒÑ·´À¡¡¡"};
	//uint8_t hz3[]={"Î´·´À¡¡¡"};
	//uint8_t hz4[]={"·´À¡»Ö¸´"};

	//uint8_t hz6[]={"¡¡Æô¶¯£º¡¡·´À¡£º¡¡Î´·´À¡£º¡¡¡¡¡¡¡¡"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//ÎÄ×ÖÏÔÊ¾·½Ê½

	Display_S(hz1,17);
}


void Display_Fault(uint16_t Num)
{
	//uint8_t hz0[]={"¡¡¡¡¡¡¡¡"};
	uint8_t hz1[]={"ÃÅ¹ÊÕÏ¡¡"};
	//uint8_t hz2[]={"Í¨Ñ¶¹ÊÕÏ"};
	//uint8_t hz3[]={"Ö÷µç¹ÊÕÏ"};
	//uint8_t hz4[]={"±¸µç¹ÊÕÏ"};
	//uint8_t hz5[]={"ÏµÍ³¹ÊÕÏ"};
	//uint8_t hz6[]={"¡¡¡¡¹ÊÕÏÐÅÏ¢×ÜÊý£º¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡"};

	Clr_Display();

	GotoXY(12,0,Dis_T);//ÎÄ×ÖÏÔÊ¾·½Ê½

	Display_S(hz1,17);

}

void Dis_Pass1_Promt(void)//ÊäÈëÃÜÂë½çÃæ
{  
  unsigned char hz1[]={"ÇëÊäÈëÒ»¼¶ÃÜÂë£º"};
  unsigned char i;
  unsigned char X,Y;
	Clr_Display();
	GotoXY(12,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

  X=14;
  Y=105;
  for (i=0;i<4;i++)
  {
     GotoXY(X+3*i,Y,Dis_T);//ÎÄ±¾·½Ê½ 
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

void Self_Check(void)//ÏµÍ³×Ô¼ìÌáÊ¾
{ 
	unsigned char hz1[]={"ÏµÍ³ÕýÔÚ½øÐÐ×Ô¼ì£¬ÇëÉÔºò...  "};
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
   dis_char(0x0000);//È«ÁÁ
   DIS_ON();
   Delay1ms(1000);
		
   DIS_OFF();
   //dis_char(0xFFBF);
	 dis_char(0xFFFF);
   DIS_ON();
	
	Beep_Alarm_Fault=2;          // ¹ÊÕÏÒô  
	Delay1s(4);
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault!=2)   
	{  
		Beep_OFF(); 
	} 

	Speak_ON();        // ±¨¾¯Òô  
	Delay1s(4);
	Speak_OFF();
	 
	Beep_Alarm_Fault=temp; 
	if (Beep_Alarm_Fault==1)   
	{  
		Speak_ON(); 
	}
}

void Dis_Err(void)//ÃÜÂë´íÎóÌáÊ¾ÏÔÊ¾
{ 
	unsigned char hz1[]={"ÃÜÂë´íÎó!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_Query_Menu(void)
{ 
	unsigned char hz0[]={"¼ÇÂ¼²éÑ¯²Ëµ¥ÁÐ±í"};
	unsigned char hz1[]={"1 ±¨¾¯¼ÇÂ¼²éÑ¯"
											 "2 ¹ÊÕÏ¼ÇÂ¼²éÑ¯"
											 "3 ÊÂ¼þ¼ÇÂ¼²éÑ¯"};
                        
                      
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
  unsigned char hz0[]={"Ã»ÓÐ²éÑ¯¼ÇÂ¼£¡"};

  Clr_Display();
  GotoXY(14,100,Dis_T);
  Display_S(hz0,16);
}

void Display_Alarm_Record_Bar(void)
{
	unsigned char hz0[]={"ÐòºÅ¡¡ Ì½²âID ¡¡»ØÂ·ºÅ¡¡¡¡±¨¾¯Ê±¼ä      "};

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
	unsigned char hz0[]={"ÐòºÅ¡¡ Ì½²âID ¡¡»ØÂ·ºÅ¡¡¡¡±¨¾¯Ê±¼ä      "};//{"ÐòºÅ  Ì½²âID »ØÂ·ºÅ¡¡¡¡±¨¾¯Ê±¼ä        "};
	unsigned char hz1[]={"Í¨¹ý¡ü¡ý·­Ò³ "};
	unsigned char hz2[]={"¡ï"};
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

   GotoXY(3,222,Dis_T);//ÏÔÊ¾µÚ¼¸Ò³
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
      if (AlarmNum<1)//Í¨µÀºÅ¡¢Å¨¶ÈÖµÇå¿Õ
      { while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//Çå¿Õ
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x502 + (AlarmNum-1) * 16;//¼ÆËãµØÖ··
					//EA=0; 
					Delay1ms(1);
				  RW24XX(DataBuff,10,Addr,0xA1);
					Delay1ms(1);
					//EA=1;
	
  				GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Alarm_Rec_Position+Alarm_RecP;
          if (temp2>AlarmRecount)    Display_S(hz2,2);//ÏÔÊ¾¡ï
          else    Display_S(hz3,2);

					temp2=DataBuff[0]*256+DataBuff[1];
					temp=temp2/100;         //±¨¾¯¼ÇÂ¼Êý2×Ö½Ú
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);
				
//          temp=DataBuff[0]%10;         //±¨¾¯¼ÇÂ¼Êý2×Ö½Ú
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]/10;
//          LCD_DataWrite(ChCode[temp]);
//          temp=DataBuff[1]%10;
//          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];
					
					temp=temp2/100;
					
          GotoXY(X+8,Y+i*16,Dis_T);         //Ì½²âID
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
            temp=DataBuff[4]/10;//»ØÂ·ºÅ
            LCD_DataWrite(ChCode[temp]);
            temp=DataBuff[4]%10;     
            LCD_DataWrite(ChCode[temp]);
           }
           //¶ÁÊ±¼ä£ºÄêÔÂÈÕÊ±·Ö£­£­[5]..[9]                 
          temp=DataBuff[5]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//Äê
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6]/10;                   
          LCD_DataWrite(ChCode[temp]);//ÔÂ
          temp=DataBuff[6]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[7]/10;
          LCD_DataWrite(ChCode[temp]);//ÈÕ
          temp=DataBuff[7]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[8]/10;        
          LCD_DataWrite(ChCode[temp]);//Ê±
          temp=DataBuff[8]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[9]/10;
          LCD_DataWrite(ChCode[temp]);//·Ö
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
	unsigned char hz2[]={"¡ú"};
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
 unsigned char hz0[]={"Ò»¼¶²Ëµ¥ÁÐ±í"};

 unsigned char hz1[]={"   1 ÉèÖÃÏµÍ³ÈÝÁ¿       6 ÉèÖÃÏµÍ³Ê±ÖÓ  "
                           "   2 ÏµÍ³²ÎÊýÅäÖÃ       7 ÉèÖÃË¢ÐÂÆµÂÊ  "
                           "   3 ÏÔÊ¾Ì½²âÅäÖÃ     ¡¡8 ÉèÖÃ±¾»úµØÖ·  "
                           "   4 ÊÖ¶¯²âÊÔÍÑ¿Û    ¡¡ 9 ½øÈë¶þ¼¶²Ù×÷  "
                           "   5 ÊµÊ±ÏÔÊ¾²âÁ¿Öµ     10Éè±¸°²×°Î»ÖÃ  "};
	unsigned char hz2[]={"°´Êý×Ö1ÖÁ10»ò¡ü¡¢¡ýÑ¡Ôñ²Ëµ¥  "};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,5,Dis_T);
	Display_S(hz0,12);
//ÏÔÊ¾²Ëµ¥
	X=0;Y=45;
	for (i=0;i<5;i++)
	{
		GotoXY(X,Y+35*i,Dis_T);
		Display_S(&hz1[40*i],40);
	}
//»­±ß¿ò
	Line_Y(0,28,220);
	Line_Y(40,28,220);

	Line_X(0,28,39);
	Line_X(0,220,39);
//ÏÔÊ¾ÌáÊ¾ÎÄ×Ö
	GotoXY(7,223,Dis_T);
	Display_S(hz2,30);
}

void Dis_Main_Menu1(void)
{  
	unsigned char hz2[]={"¡ú"};//ÏÔÊ¾²Ëµ¥Ö¸Ê¾

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
	u8 hz1[]={"ÇëÊäÈëÌ½²âÆ÷ID·¶Î§£º"};
	u8 hz2[]={"Ö÷»ú»ØÂ·ID·¶Î§£º"};
	u8 hz3[]={"¸¨Öú»ØÂ·ID·¶Î§£º"};
	u8 X,Y;

	Clr_Display();
	GotoXY(10,10,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,20);//

	GotoXY(11,40,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz2,16);//

	Line_Y(8,70,110);
	Line_Y(30,70,110);
	
	Line_X(8,70,29);
	Line_X(8,110,29);

	
	if( LoopOpenFlag ==1 )
	{
		//¸¨Öú»ØÂ·ID·¶Î§
		GotoXY(11,130,Dis_T);//ÎÄ±¾·½Ê½ 
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
  unsigned char hz1[]={"Ö÷»ú»ØÂ·IDÆÁ±ÎÓë¿ªÆôÉèÖÃ´°¿Ú"};
  unsigned char hz2[]={"IDºÅ"};
  unsigned char hz3[]={"×´Ì¬"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//ÊúÏß
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//IDºÅ
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//×´Ì¬
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text1(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"¡ò"};
	unsigned char hz2[]={"¡ñ"};//¡ò¿ªÆô,¡ñÆÁ±Î
	unsigned char i;
	unsigned char X,Y;
	unsigned int temp;

  uint8_t first=0;
  

   for (i=0;i<35;i++)
   { 
     
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+1;//ÎªÍ¨µÀºÅ
     if (temp>End_Addr)    //´óÓÚ64Ö®ºó£¬
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //Ì½²âÆ÷IDÇå¿Õ
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //ÆÁ±Î×´Ì¬Çå¿Õ
         LCD_DataWrite(' ');
        
         
      }
     else 
     {   GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//Í¨µÀºÅ
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i))//ÆÁ±Î×´Ì¬
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+1;//ÎªÍ¨µÀºÅ
   if (temp>End_Addr)  return;  //´óÓÚ64Ö®ºó£¬
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//ÎÄ±¾·½Ê½ //ÏÔÊ¾Ò³ºÅ
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
    if (PB_Flag)  Display_S(hz2,2);// ÆÁ±Î×´Ì¬              
    else Display_S(hz1,2);
   
   //--------------ÏÂÏÞÖµ ÉÁË¸----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_PB_Bar2(void)
{ 
  unsigned char hz1[]={"¸¨Öú»ØÂ·IDÆÁ±ÎÓë¿ªÆôÉèÖÃ´°¿Ú"};
  unsigned char hz2[]={"IDºÅ"};
  unsigned char hz3[]={"×´Ì¬"};

  unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(4,0,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,26);//

	X=5;
	Y=22;
	Line_Y(0,Y,230);

	for(i=0;i<9;i++)
	{  
		Line_Y(X+5*i,22,230);//ÊúÏß
	}


	X=1;
	Y=22;
	Line_X(0,Y,39);
	for(i=0;i<5;i++)
	{  
		 GotoXY(X,Y+2*i*21+2,Dis_T);//IDºÅ
		 Display_S(hz2,4);//
		 Line_X(0,Y+(2*i+1)*21-1,39);

		 GotoXY(X,Y+(2*i+1)*21+2,Dis_T);//×´Ì¬
		 Display_S(hz3,4);//
		 Line_X(0,Y+(2*i+2)*21-1,39);
	}
}

void Dis_PB_Text2(void)
{
	// unsigned char Page[]={'-','>','P','a','g','e',' ','d','o','w','n'};
	unsigned char hz1[]={"¡ò"};
	unsigned char hz2[]={"¡ñ"};//¡ò¿ªÆô,¡ñÆÁ±Î
	unsigned char i;
	unsigned char X,Y;
	u16 temp;

  uint8_t first=0;
  
   for (i=0;i<35;i++)
   { 
     first=0;
     X=6+(i%7)*5;
     Y=21*2*(i/7)+23;

     temp=35*Flicker_Position+i+LoopStart;//ÎªÍ¨µÀºÅ
     if (temp>LoopEnd)    //´óÓÚ64Ö®ºó£¬
     {
         GotoXY(X,Y,Dis_T);
         LCD_DataWrite(' '); //Ì½²âÆ÷IDÇå¿Õ
         LCD_DataWrite(' ');
         LCD_DataWrite(' ');

         GotoXY(X+1,Y+22,Dis_T);
         LCD_DataWrite(' '); //ÆÁ±Î×´Ì¬Çå¿Õ
         LCD_DataWrite(' ');    
      }
     else 
     {  
					GotoXY(X,Y,Dis_T);
         if ((temp/100)==0)  LCD_DataWrite(' ');
         else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//Í¨µÀºÅ
    

         
         if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
         else LCD_DataWrite(ChCode[temp%100/10]);
    
         LCD_DataWrite(ChCode[temp%10]);


         GotoXY(X+1,Y+22,Dis_T);
         if (Check_Shield_State(35*Flicker_Position+i+LoopStart-1))//ÆÁ±Î×´Ì¬
            Display_S(hz2,2);//               
         else Display_S(hz1,2);
 
       }
   }
   
   temp=35*Flicker_Position+Key_Input_Value+LoopStart;//ÎªÍ¨µÀºÅ
   if (temp>LoopEnd)  return;  //´óÓÚ64Ö®ºó£¬
//--------------------------------------------------------
    GotoXY(35,0,Dis_T);//ÎÄ±¾·½Ê½ //ÏÔÊ¾Ò³ºÅ
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
    if (PB_Flag)  Display_S(hz2,2);// ÆÁ±Î×´Ì¬              
    else Display_S(hz1,2);
   
   //--------------ÏÂÏÞÖµ ÉÁË¸----------
 
    GotoXY(X,Y,Dis_T);
    Open_Cur(X,Y);
}


void Dis_SystemP_Bar(void)
{

	unsigned char hz1[]={"ÏµÍ³´òÓ¡»úÅäÖÃ´°¿Ú"};
	unsigned char hz2[]={"´òÓ¡»ú¹Ø±Õ"};
	unsigned char hz3[]={"´òÓ¡»ú¿ªÆô"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz2,10);//
	GotoXY(14,100,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz3,10);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_SystemP_Text1(void)
{  
	unsigned char X,Y;
	//unsigned char hz1[]={"¡Ì"};
	//unsigned char hz2[]={"¡ñ"};
	unsigned char hz1[]={"¡ñ"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"¡Ñ ±¨¾¯¼ÇÂ¼´òÓ¡"};
	unsigned char hz4[]={"¡Ñ ¹ÊÕÏ¼ÇÂ¼´òÓ¡"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (Print_State==0)//Ñ¡Ôñ´òÓ¡»ú¹Ø±Õ
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
	else	//´òÓ¡»ú¿ªÆô
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

	unsigned char hz1[]={"Ì½²âÆ÷»ØÂ·ÅäÖÃ´°¿Ú"};
	unsigned char hz2[]={"»ØÂ·¹¦ÄÜ¹Ø±Õ"};
	unsigned char hz3[]={"»ØÂ·¹¦ÄÜ¿ªÆô"};

	Clr_Display();

	GotoXY(10,10,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,18);//
	GotoXY(14,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz2,12);//
	GotoXY(14,100,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz3,12);//

	Line_Y(4,40,200);
	Line_Y(35,40,200);
	Line_X(4,40,34);
	Line_X(4,200,34);
}


void Dis_Loop_Text1(void)
{  
	unsigned char X,Y;
	unsigned char hz1[]={"¡ñ"};
	unsigned char hz2[]={"  "};
	unsigned char hz3[]={"¡Ñ ¿ªÆô¸¨Öú»ØÂ·"};
	unsigned char hz4[]={"¡Ñ ¿ªÆô»ØÂ·ÉèÖÃ"};
	unsigned char hz5[]={"                "};
	X=10;
	Y=60;

	if (LoopOpenFlag==0)//¸¨Öú»ØÂ·¹Ø±Õ
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
	else//»ØÂ·¿ªÆô
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
	unsigned char hz1[]={"Ì½²âÆ÷Î»ÖÃÐÅÏ¢ÉèÖÃ"};
	unsigned char hz2[]={"Ì½²âÆ÷ID"};
	unsigned char hz3[]={"°²×°Î»ÖÃ"};
	Clr_Display();

	GotoXY(10,10,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,18);//

	GotoXY(10,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz2,8);//

	GotoXY(20,60,Dis_T);//ÎÄ±¾·½Ê½ 
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
  unsigned char hz1[]={"ÉèÖÃ³É¹¦!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);
}

void Dis_SetPOK(void)
{
	unsigned char hz1[]={"ÉèÖÃ³É¹¦!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}

void Dis_SetPErr(void)
{ 
	unsigned char hz1[]={"±£´æÊ§°Ü!"};

	GotoXY(16,210,Dis_T);
	Display_S(hz1,9);
}


void Dis_TCQ_State_Bar1(void)
{ 
	unsigned char hz1[]={"Ì½²âÆ÷ÅäÖÃ×´Ì¬´°¿Ú"};
	unsigned char hz2[]={"»ØÂ·IDºÅ"};
	unsigned char hz3[]={"Éè ¶¨ Öµ"};
	unsigned char hz4[]={"¼ì²âÀà±ð"};
	unsigned char hz5[]={"ÍÑ¿Û×´Ì¬"};
	unsigned char hz6[]={"ÇëÊäÈëÌ½²âÆ÷IDºÅ£º"};
	unsigned char i,X,Y;
    
    Clr_Display();
   
    GotoXY(10,0,Dis_T);//ÎÄ±¾·½Ê½ 
    Display_S(hz1,18);//

   X=5;
   Y=18;


   for(i=0;i<8;i++)
   {  
     if (i==0) Line_Y(0,18,216);
     else if (i==1) Line_Y(10,18,216);
          else if(i==7) Line_Y(5+5*i,18,216);//ÊúÏß
          else Line_Y(5+5*i,18,196);//ÊúÏß
    }


    X=1;
    Y=18;
    Line_X(0,Y,39);
    for(i=0;i<3;i++)
    {  
       GotoXY(X,Y+3*i*20+2,Dis_T);//IDºÅ
       Display_S(hz2,8);//
       Line_X(0,Y+(3*i+1)*20-1,39);
 
       GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//Éè¶¨Öµ
       Display_S(hz3,8);//
       Line_X(0,Y+(3*i+2)*20-1,39);

       GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//¼ì²âÀà±ð
       Display_S(hz4,8);//
       Line_X(0,Y+(3*i+3)*20-1,39);
      
     }

     GotoXY(X,Y+3*i*20+2,Dis_T);//ÍÑ¿Û×´Ì¬
     Display_S(hz5,8);//
     Line_X(0,Y+(3*i+1)*20-1,39);
   
 
     GotoXY(0,222,Dis_T);//ÊäÈëÌ½²âIDºÅ
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
	unsigned char hz0[]={"¶ÁÈ¡Ê§°Ü£¡"};
	unsigned char hz1[]={"¶ÁÈ¡ÖÐ..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  //Display_S(hz1,10);	//¶ÁÈ¡ÖÐ
  Display_S(hz0,10);//¶ÁÈ¡Ê§°Ü
}


void Clear_Read_State(void)
{
	unsigned char hz0[]={"¶ÁÈ¡Ê§°Ü£¡"};
	unsigned char hz1[]={"¶ÁÈ¡ÖÐ..."};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);	//¶ÁÈ¡ÖÐ
  //Display_S(hz0,10);//¶ÁÈ¡Ê§°Ü

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//»ØÂ·ºÅ
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//Éè¶¨Öµ
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//¼ì²âÀà±ð
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}
void Plase_Check(void)
{
	unsigned char hz0[]={"ÇëÈ·ÈÏ£¡"};
	unsigned char hz2[]={"        "};

	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz0,10);//

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {
    //----------------------------------
     X=11+(i%6)*5;
     Y=20+20*3*(i/6);     
     GotoXY(X,Y,Dis_T);//»ØÂ·ºÅ
     
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     LCD_DataWrite(' ');
     //---------------------------------
     
      GotoXY(X,Y+20,Dis_T);//Éè¶¨Öµ
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
     //---------------------------------
        
      GotoXY(X,Y+40,Dis_T);//¼ì²âÀà±ð
      LCD_DataWrite(' ');
      LCD_DataWrite(' ');
   }
}

void Dis_TCQ_State_Return(void)
{
	unsigned char hz0[]={"¡æ"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"¿ªÆô×´Ì¬"};
	unsigned char hz3[]={"ÒÑ±»ÆÁ±Î"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"¶ÁÈ¡³É¹¦£¡"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬ =1¿ªÆô =0¿ªÆô    13 14
  
	lTemp = 0;
	lTemp = Rec_Buff[13];//¼ì²âÀàÐÍ
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //ÆäÖÐÓÐÒ»Â·¿ªÆôÔòÏÔÊ¾ÍÑ¿Û¿ªÆô
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Rec_Buff[5];//¼ì²âÀàÐÍ
		temp3 = ((lTemp<<8)|Rec_Buff[6])&(0x01<<i);
		//temp3= Rec_Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Rec_Buff[7];//ÆÁ±Î×´Ì¬
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//µØÖ·»ØÂ·ºÅ 0»ØÂ·17 18 1»ØÂ·20 21
			temp2= (Rec_Buff[17+4*i]& 0x03) *256+Rec_Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//IDºÅ
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//Í¨µÀºÅ
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//Éè¶¨Öµ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//¼ì²âÀà±ð
			if (temp3==0)//CAN¸ù¾Ý×î¸ßÎ»ÅÐ¶Ï£¬485»ØÂ·0¶¼ÊÇÎÂ¶È£¿
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
	unsigned char hz0[]={"¡æ"};
	unsigned char hz1[]={"MA"};
	unsigned char hz2[]={"¿ªÆô×´Ì¬"};
	unsigned char hz3[]={"ÒÑ±»ÆÁ±Î"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"¶ÁÈ¡³É¹¦£¡"};

	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬ =1¿ªÆô =0¿ªÆô    13 14
  
	lTemp = 0;
	lTemp = Buff[13];//¼ì²âÀàÐÍ
	lTemp = (lTemp<<8)|Buff[14];
	
	if (lTemp) //ÆäÖÐÓÐÒ»Â·¿ªÆôÔòÏÔÊ¾ÍÑ¿Û¿ªÆô
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);
	
	//for(i=0;i<16;i++)
	for(i=0;i<(TCQ_Return_Length-12)/4;i++)
	{
		lTemp = 0;
		lTemp = Buff[5];//¼ì²âÀàÐÍ
		temp3 = ((lTemp<<8)|Buff[6])&(0x01<<i);
		//temp3= Buff[17+4*i]&0x80;
		lTemp = 0;
		lTemp = Buff[7];//ÆÁ±Î×´Ì¬
		temp4 = ((lTemp<<8)|Buff[8])&(0x01<<i);
		
		if(temp4 == 0)
		{
			temp=i;//µØÖ·»ØÂ·ºÅ 0»ØÂ·17 18 1»ØÂ·20 21
			temp2= (Buff[17+4*i]& 0x03) *256+Buff[18+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//IDºÅ
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//Í¨µÀºÅ
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//Éè¶¨Öµ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//¼ì²âÀà±ð
			if (temp3==0)//CAN¸ù¾Ý×î¸ßÎ»ÅÐ¶Ï£¬485»ØÂ·0¶¼ÊÇÎÂ¶È£¿
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
	unsigned char hz0[]={"¡ý"};
	unsigned char hz1[]={"ÍÑ¿Û²âÊÔÊä³ö´°¿Ú"};
	unsigned char hz2[]={"Ö÷¿ØÉè±¸:"};
	unsigned char hz3[]={"Ì½²âÆ÷ID:"};
	unsigned char hz4[]={"¿ªÆô"};
	unsigned char hz5[]={"¹Ø±Õ"};
	// code unsigned char hz6[]={"°´¡´È·ÈÏ¡µ¼ü½øÐÐ²âÊÔ"};
	unsigned char X,Y,i;

	Clr_Display();

	GotoXY(10,0,Dis_T);//
	Display_S(hz1,16);//

	X=4;
	Y=60;
	GotoXY(X,Y,Dis_T);
	Display_S(hz2,10);//Ö÷¿ØÉè±¸

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//¿ªÆô

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//¹Ø±Õ

	X=4;
	Y=120;
	GotoXY(X,Y,Dis_T);
	Display_S(hz3,10);//Ì½²âÆ÷ID

	GotoXY(X+14,Y,Dis_T);
	Display_S(hz4,4);//¿ªÆô

	GotoXY(X+24,Y,Dis_T);
	Display_S(hz5,4);//¹Ø±Õ

	X=19;
	Y=40;
	GotoXY(X,Y,Dis_T); //ÏÔÊ¾¡ý
	Display_S(hz0,2);

	X=17;  //¿ªÆô
	Y=57;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=57;//¡¡¡¡¹Ø±Õ
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=17; //¿ªÆô
	Y=117;
	Line_Y(X,Y,Y+24);
	Line_Y(X+6,Y,Y+24);
	Line_X(X,Y,X+5);
	Line_X(X,Y+24,X+5);

	X=27;
	Y=117;//¡¡¡¡¹Ø±Õ
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

	unsigned char hz0[]={"¡ý"};
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
	unsigned char hz1[]={"ÊµÊ±¼à²âÌ½²âÆ÷Êý¾Ý´°¿Ú"};
	unsigned char hz2[]={"»ØÂ·IDºÅ"};
	unsigned char hz3[]={"Éè ¶¨ Öµ"};
	unsigned char hz4[]={"¼ì²âÀà±ð"};
	unsigned char hz5[]={"ÍÑ¿Û×´Ì¬"};
	unsigned char hz6[]={"ÇëÊäÈëÌ½²âÆ÷IDºÅ£º"};
	unsigned char i,X,Y;
    
	Clr_Display();

	GotoXY(8,0,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,22);//

	X=5;
	Y=18;

	for(i=0;i<8;i++)
	{  
		if (i==0) Line_Y(0,18,216);
		else if (i==1) Line_Y(10,18,216);
		else if(i==7) Line_Y(5+5*i,18,216);//ÊúÏß
		else Line_Y(5+5*i,18,196);//ÊúÏß
	}
	
	X=1;
	Y=18;
	Line_X(0,Y,39);
	for(i=0;i<3;i++)
	{  
		GotoXY(X,Y+3*i*20+2,Dis_T);//IDºÅ
		Display_S(hz2,8);//
		Line_X(0,Y+(3*i+1)*20-1,39);

		GotoXY(X,Y+(3*i+1)*20+2,Dis_T);//Éè¶¨Öµ
		Display_S(hz3,8);//
		Line_X(0,Y+(3*i+2)*20-1,39);

		GotoXY(X,Y+(3*i+2)*20+2,Dis_T);//¼ì²âÀà±ð
		Display_S(hz4,8);//
		Line_X(0,Y+(3*i+3)*20-1,39);
	}

	GotoXY(X,Y+3*i*20+2,Dis_T);//ÍÑ¿Û×´Ì¬
	Display_S(hz5,8);//
	Line_X(0,Y+(3*i+1)*20-1,39);


	GotoXY(0,222,Dis_T);//ÊäÈëÌ½²âIDºÅ
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
	unsigned char hz0[]={"¶ÁÈ¡Ê§°Ü£¡"};
	unsigned char hz1[]={"¶ÁÈ¡ÖÐ..."};
	unsigned char hz2[]={"        "};
	unsigned char X,Y,i;

  GotoXY(28,222,Dis_T);
  Display_S(hz1,10);//

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬
  Display_S(hz2,8);

  for(i=0;i<18;i++)
  {

			//----------------------------------
			X=11+(i%6)*5;
			Y=20+20*3*(i/6);     
			GotoXY(X,Y,Dis_T);//»ØÂ·ºÅ

			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+20,Dis_T);//Éè¶¨Öµ
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
			//---------------------------------

			GotoXY(X,Y+40,Dis_T);//¼ì²âÀà±ð
			LCD_DataWrite(' ');
			LCD_DataWrite(' ');
   }
}

void Dis_Test_Fl_Return(void)
{
	unsigned char hz0[]={"¡æ"};
	unsigned char hz1[]={"MA"};
	unsigned char hz3[]={"ÒÑ±»ÆÁ±Î"};
	unsigned char hz2[]={"¿ªÆô×´Ì¬"};
	unsigned char X,Y,i,temp,temp1;
	unsigned int temp2,temp4,temp3=0,lTemp;
	uint8_t first=0;
	unsigned char hz4[]={"¶ÁÈ¡³É¹¦£¡"};

	#if 1
	GotoXY(28,222,Dis_T);
  Display_S(hz4,10);//

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬
	
	lTemp = 0;
	lTemp = Rec_Buff[13];//¼ì²âÀàÐÍ
	lTemp = (lTemp<<8)|Rec_Buff[14];
	
	if (lTemp) //ÆäÖÐÓÐÒ»Â·¿ªÆôÔòÏÔÊ¾ÍÑ¿Û¿ªÆô
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
		lTemp = Rec_Buff[7];//ÆÁ±Î×´Ì¬
		temp4 = ((lTemp<<8)|Rec_Buff[8])&(0x01<<i);

		if(temp4==0)
		{
			temp=i;//µØÖ·»ØÂ·ºÅ 0»ØÂ·19 20 1»ØÂ·23 24
			temp2= (Rec_Buff[19+4*i]& 0x03) *256+Rec_Buff[20+4*i]; 
			
			X=11+(temp%6)*5;
			Y=20+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//IDºÅ
			
			first=0;
			if ((temp/100)==0) ;// LCD_DataWrite(' ');
			else  
			{ 
				LCD_DataWrite(ChCode[(temp+1)/100]);
				first=1;
			}//Í¨µÀºÅ
			 
			if (((temp%100/10)==0)&&(first==0))  
				LCD_DataWrite(' ');
			else 
				LCD_DataWrite(ChCode[(temp+1)%100/10]);

			LCD_DataWrite(ChCode[(temp+1)%10]);
				 //---------------------------------
			Y=40+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//Éè¶¨Öµ
			temp1=temp2/100;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%100/10;
			LCD_DataWrite(ChCode[temp1]);
			temp1=temp2%10;
			LCD_DataWrite(ChCode[temp1]);
				 //---------------------------------
			Y=60+20*3*(temp/6);     
			GotoXY(X,Y,Dis_T);//¼ì²âÀà±ð
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

  GotoXY(13,200,Dis_T);//ÍÑ¿Û×´Ì¬
  if ((Rec_Buff[5]& 0x80)==0) 
		Display_S(hz2,8);
  else 
		Display_S(hz3,8);

  for(i=0;i<(TCQ_Return_Length-3)/2;i++)
  {
     temp=(Rec_Buff[5+2*i]& 0x7C)>>2;//µØÖ·»ØÂ·ºÅ

     temp2= (Rec_Buff[5+2*i]& 0x03) *256+Rec_Buff[6+2*i]; 
    //----------------------------------
     X=11+(temp%6)*5;
     Y=20+20*3*(temp/6);     
     GotoXY(X,Y,Dis_T);//IDºÅ
     first=0;
     if ((temp/100)==0) ;// LCD_DataWrite(' ');
     else  { LCD_DataWrite(ChCode[temp/100]);first=1;}//Í¨µÀºÅ
     if (((temp%100/10)==0)&&(first==0))  LCD_DataWrite(' ');
     else LCD_DataWrite(ChCode[temp%100/10]);
     LCD_DataWrite(ChCode[temp%10]);
     //---------------------------------
      Y=40+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//Éè¶¨Öµ
      temp1=temp2/100;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%100/10;
      LCD_DataWrite(ChCode[temp1]);
      temp1=temp2%10;
      LCD_DataWrite(ChCode[temp1]);
     //---------------------------------
      Y=60+20*3*(temp/6);     
      GotoXY(X,Y,Dis_T);//¼ì²âÀà±ð
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
	unsigned char hz1[]={"ÇëÊäÈëÏµÍ³Ê±¼ä£º"};
	unsigned char hz2[]={"20  Äê  ÔÂ  ÈÕ¡¡Ê±  ·Ö  Ãë"};
	unsigned char i,X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//ÇëÊäÈëÏµÍ³Ê±¼ä
	Display_S(hz1,16);//

	GotoXY(8,105,Dis_T);// Äê  ÔÂ  ÈÕ¡¡Ê±  ·Ö  Ãë
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

	unsigned char hz1[]={"ÇëÊäÈëË¢ÐÂÊ±¼ä£º"};
	unsigned char hz2[]={"Ãë"};

	Clr_Display();

	GotoXY(12,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,16);//
	GotoXY(21,105,Dis_T);//ÎÄ±¾·½Ê½ 
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
	unsigned char hz1[]={"±£´æÊ§°Ü!"};
 
  GotoXY(16,155,Dis_T);
  Display_S(hz1,9);

}


void Dis_SetAddr_Bar(void)
{
	unsigned char hz1[]={"ÇëÊäÈë±¾»úµØÖ·£º"};
	unsigned char X,Y;

	Clr_Display();

	GotoXY(12,60,Dis_T);//ÎÄ±¾·½Ê½ 
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
	unsigned char hz1[]={"ÇëÊäÈë¶þ¼¶ÃÜÂë£º"};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,16);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);



	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
	 GotoXY(X+3*i,Y,Dis_T);//ÎÄ±¾·½Ê½ 
	 LCD_DataWrite('*'); 
	}
	Open_Cur(X,Y+2);
 
}


void Dis_Main_Menu2(void)
{ 
	unsigned char hz0[]={"¶þ¼¶²Ëµ¥ÁÐ±í"};
	unsigned char hz1[]={"¸ü¸ÄÒ»¼¶ÃÜÂë"
											 "¸ü¸Ä¶þ¼¶ÃÜÂë"
											 "Çå³ýÏµÍ³¼ÇÂ¼"
	                     "»ØÂ·¹¦ÄÜÉèÖÃ"};
	unsigned char hz2[]={"¡ú"};
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
	unsigned char hz0[]={"ÐòºÅ  Ì½²âID ¹ÊÕÏÃèÊö¡¡    ¹ÊÕÏÊ±¼ä¡¡        "};

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
	unsigned char hz0[]={"ÐòºÅ  Ì½²âID ¹ÊÕÏÃèÊö¡¡    ¹ÊÕÏÊ±¼ä¡¡        "};
	unsigned char hz1[]={"Í¨¹ý¡ü¡ý·­Ò³ "};
	unsigned char hz2[]={"¡ó"};
	unsigned char hz3[]={"  "}; 

  unsigned char hz4[]={"Í¨Ñ¶¹ÊÕÏ"};
  unsigned char hz5[]={"Ö÷µç¹ÊÕÏ"};
  unsigned char hz6[]={"±¸µç¹ÊÕÏ"};
  unsigned char hz7[]={"³äµç¹ÊÕÏ"};
	unsigned char hz8[]={"»ØÂ·¿ªÂ·"};
	unsigned char hz9[]={"»ØÂ·¶ÌÂ·"};
	unsigned char X,Y;
	unsigned char i,j,temp;

	unsigned char DataBuff[10];

	unsigned int Addr;
	unsigned int temp2;
	uint8_t type_error;//¹ÊÕÏÀàÐÍ
 
   Clr_Display();
   GotoXY(2,1,Dis_T);
   Display_S(hz0,37);
   Line_Y(0,0,220);
   Line_Y(40,0,220);
   Line_X(0,0,39);
   Line_X(0,220,39);

   GotoXY(3,222,Dis_T);//ÏÔÊ¾µÚ¼¸Ò³
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
      if (FaultNum<1)//Í¨µÀºÅ¡¢Å¨¶ÈÖµÇå¿Õ
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//Çå¿Õ
              
         	i++;
         }
       }
      else 
      {
          Addr= 0x4602 + (FaultNum-1) * 16;
					Delay1ms(1);
					RW24XX(DataBuff,9+1,Addr,0xA1);//Ôö¼ÓÁËbuf4¹ÊÕÏÀàÐÍ
					Delay1ms(1);
                 
          GotoXY(X,Y+i*16,Dis_T);

          temp2=DataBuff[0]*256+DataBuff[1]+Fault_Rec_Position;//ÐÞ¸ÄÎª256
          if (temp2>FaultRecount)    
						Display_S(hz2,2);//ÏÔÊ¾¡ó
          else    
						Display_S(hz3,2);
					temp2=DataBuff[0]*256+DataBuff[1];
					temp = temp2/100;
					LCD_DataWrite(ChCode[temp]);
					temp=temp2%100/10;
          LCD_DataWrite(ChCode[temp]);
          temp=temp2%10;
          LCD_DataWrite(ChCode[temp]);

          temp2=DataBuff[2]*256+DataBuff[3];	//Ì½²âÆ÷ID
					type_error = DataBuff[4];
					GotoXY(X+8,Y+i*16,Dis_T);         //Ì½²âID
          
					if (type_error== 0)		//Í¨Ñ¶¹ÊÕÏ
          {
             temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						 GotoXY(X+14,Y+i*16,Dis_T); 
						 Display_S(hz4,8);	//Í¨Ñ¶¹ÊÕÏ
          }
          else if(type_error== 0xF0)//Ö÷µç¹ÊÕÏ
          {
							LCD_DataWrite(' ');
							LCD_DataWrite(' ');
              LCD_DataWrite(' ');
						
						  GotoXY(X+14,Y+i*16,Dis_T); 
						  Display_S(hz5,8);//Ö÷µç¹ÊÕÏ
           }  
					else if(type_error== 0xF1)//±¸µç¹ÊÕÏ
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz6,8);//±¸µç¹ÊÕÏ
					}  
					else if(type_error== 0xF2)//³äµç¹ÊÕÏ
					{
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');
						LCD_DataWrite(' ');

						GotoXY(X+14,Y+i*16,Dis_T); 
						Display_S(hz7,8);//³äµç¹ÊÕÏ
					} 
					else//1-16»ØÂ·¿ªÂ· 17-32¶ÌÂ·
					{
						 temp=temp2/100;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%100/10;
             LCD_DataWrite(ChCode[temp]);
             temp=temp2%10;
             LCD_DataWrite(ChCode[temp]);
						
						if( (type_error <=16)&&(type_error > 0))//¿ªÂ·
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=type_error/10;
							LCD_DataWrite(ChCode[temp]);
							temp=type_error%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz8,8);//»ØÂ·¿ªÂ·
						}
						else if( (type_error <=32)&&(type_error >= 17))//¶ÌÂ·
						{
							GotoXY(X+12,Y+i*16,Dis_T);
							temp=(type_error-16)/10;
							LCD_DataWrite(ChCode[temp]);
							temp=(type_error-16)%10;
							LCD_DataWrite(ChCode[temp]);
						
							Display_S(hz9,8);//»ØÂ·¶ÌÂ·
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

                 
           //¶ÁÊ±¼ä£ºÄêÔÂÈÕÊ±·Ö£­£­[5]..[9]                 
          temp=DataBuff[4+1]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//Äê
          temp=DataBuff[4+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[5+1]/10;                   
          LCD_DataWrite(ChCode[temp]);//ÔÂ
          temp=DataBuff[5+1]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[6+1]/10;
          LCD_DataWrite(ChCode[temp]);//ÈÕ
          temp=DataBuff[6+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[7+1]/10;        
          LCD_DataWrite(ChCode[temp]);//Ê±
          temp=DataBuff[7+1]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[8+1]/10;
          LCD_DataWrite(ChCode[temp]);//·Ö
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
	unsigned char hz0[]={"ÐòºÅ¡¡   ÊÂ¼þÃèÊö¡¡¡¡    ÊÂ¼þÊ±¼ä¡¡¡¡   ¡¡¡¡"};

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
	unsigned char hz0[]={"ÐòºÅ¡¡   ÊÂ¼þÃèÊö¡¡¡¡    ÊÂ¼þÊ±¼ä¡¡¡¡   ¡¡¡¡"};
	unsigned char hz00[]={"Í¨¹ý¡ü¡ý·­Ò³ "};
	unsigned char hz1[]={"ÏµÍ³¿ª»ú¡¡"};
	//unsigned char hz2[]={"ÏµÍ³¹Ø»ú¡¡"};
	unsigned char hz3[]={"ÏµÍ³¸´Î»¡¡"};
	unsigned char hz4[]={"Çå³ý¼ÇÂ¼¡¡"};
	unsigned char hz5[]={"ÏµÍ³³õÊ¼»¯"};

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

   GotoXY(3,222,Dis_T);//ÏÔÊ¾µÚ¼¸Ò³
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
      if (SDNum<1)//Í¨µÀºÅ¡¢Å¨¶ÈÖµÇå¿Õ
      { 
				while (i<12)
        {   GotoXY(1,Y+i*16,Dis_T);
           	for (j=1;j<38;j++)
               LCD_DataWrite(' ');//Çå¿Õ
              
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

          temp=DataBuff[0]/10;         //ÉÏµç¼ÇÂ¼Êý1×Ö½Ú
          LCD_DataWrite(ChCode[temp]);
          temp=DataBuff[0]%10;
          LCD_DataWrite(ChCode[temp]);

          GotoXY(X+9,Y+i*16,Dis_T);
          if (DataBuff[1]==1) Display_S(hz1,10);;//ÊÂ¼þÃû³ÆÃèÊö
          if (DataBuff[1]==3) Display_S(hz3,10);
          if (DataBuff[1]==4) Display_S(hz4,10);
          if (DataBuff[1]==5) Display_S(hz5,10);        
           //¶ÁÊ±¼ä£ºÄêÔÂÈÕÊ±·Ö£­£­[5]..[9]                 
          temp=DataBuff[2]/10; 
          GotoXY(X+23,Y+i*16,Dis_T);        
          LCD_DataWrite(ChCode[temp]);//Äê
          temp=DataBuff[2]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[3]/10;                   
          LCD_DataWrite(ChCode[temp]);//ÔÂ
          temp=DataBuff[3]%10; 
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite('-');

          temp=DataBuff[4]/10;
          LCD_DataWrite(ChCode[temp]);//ÈÕ
          temp=DataBuff[4]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(' ');

          temp=DataBuff[5]/10;        
          LCD_DataWrite(ChCode[temp]);//Ê±
          temp=DataBuff[5]%10;
          LCD_DataWrite(ChCode[temp]);
          LCD_DataWrite(':');

          temp=DataBuff[6]/10;
          LCD_DataWrite(ChCode[temp]);//·Ö
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

	unsigned char hz1[]={"ÇëÊäÈëÒ»¼¶ÐÂÃÜÂë£º"};
	unsigned char i;
	unsigned char X,Y;

	Clr_Display();
	GotoXY(12,60,Dis_T);//ÎÄ±¾·½Ê½ 
	Display_S(hz1,18);//

	Line_Y(10,90,140);
	Line_Y(30,90,140);
	Line_X(10,90,29);
	Line_X(10,140,29);

	X=14;
	Y=105;
	for (i=0;i<4;i++)
	{
		GotoXY(X+3*i,Y,Dis_T);//ÎÄ±¾·½Ê½ 
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
		GotoXY(X+3*i,Y,Dis_T);//ÎÄ±¾·½Ê½ 
		LCD_DataWrite(ChCode[dis_buff[i]]); 
	}

	if (Flicker_Position==3) 
		Open_Cur(X,Y+2);
	else 
		Open_Cur(X+3*(Flicker_Position+1),Y+2);
}

void Dis_SetPass2_Promt(void)
{  
    unsigned char hz1[]={"ÇëÊäÈë¶þ¼¶ÐÂÃÜÂë£º"};
    unsigned char i;
    unsigned char X,Y;

    Clr_Display();
    GotoXY(11,60,Dis_T);//ÎÄ±¾·½Ê½ 
    Display_S(hz1,18);//

    Line_Y(10,90,140);
    Line_Y(30,90,140);
    Line_X(10,90,29);
    Line_X(10,140,29);

   X=14;
   Y=105;
   for (i=0;i<4;i++)
   {
     GotoXY(X+3*i,Y,Dis_T);//ÎÄ±¾·½Ê½ 
     LCD_DataWrite(ChCode[dis_buff[i]]); 
    }
    Open_Cur(X,Y+2);
}

void Clear_REC_Sure(void)
{
	unsigned char hz1[]={"Çå³ýÏµÍ³¼ÇÂ¼ºó£¬¼ÇÂ¼½«¶ªÊ§£¡"};
	unsigned char hz2[]={"²¢ÎÞ·¨»Ö¸´£¡È·ÈÏ£¯È¡Ïû£¿"};

	Clr_Display();
	GotoXY(5,60,Dis_T);
	Display_S(hz1,28);

	GotoXY(6,90,Dis_T);
	Display_S(hz2,24);
}

void Clear_REC_Promt(void)
{  
	unsigned char hz1[]={"ÕýÇå³ýÏµÍ³Êý¾Ý£¬ÇëÉÔºò...     "};

	Clr_Display();
	GotoXY(6,90,Dis_T);
	Display_S(hz1,28);   
}

void Clear_REC_OK(void)
{  
	unsigned char hz1[]={"ÇåÏµÍ³Êý¾ÝÍê³É£¡"};

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
  RW24XX(&buf[0],2,0x18,0xA0); //±¨¾¯¼ÇÂ¼×ÜÊý
  Delay1ms(10);
 
  FaultRecount=0;
  buf[0]=0;
  buf[1]=0;
  RW24XX(&buf[0],2,0x1C,0xA0); //¹ÊÕÏ¼ÇÂ¼×ÜÊý
  Delay1ms(10);
  
  
  SDRecount=0;    //ÉÏµç´ÎÊý
  buf[0]=SDRecount; 
  RW24XX(buf,1,0x1A,0xA0);
  Delay1ms(10);
 
	//EA=1;
}

uint8_t CD_Check(void)
{
	uint8_t power;
	Power_ADC_Return();  //±¸µçµçÑ¹ADÖµ
	if(CD_Flag == 1)
	{
		if (Bat_Power>3350)   //>20V ´ËÊ±±¸µç²»Õý³£
			power = 1;	//³äµçÕý³£
		else
			power = 0;	//³äµç²»Õý³£
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
		///-------------------Ö÷µç¼ì²â-----------------------------------
		//Ö÷µçÕý³£Main_Power_Check=0
		//Ö÷µç¹ÊÕÏMain_Power_Check=1
		This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
	
		Main_Power_Check = This_Main_Power & Last_Main_Power;
	
		Last_Main_Power = This_Main_Power;	//±ØÐëÁ¬ÐøÁ½´ÎÏàÍ¬µÄ×´Ì¬²ÅÅÐ¶Ï½ÓÊÜ
	
		if (Check_World_Flag_State(10)) //Ö®Ç°Ö÷µç×´Ì¬Õý³£
		{   
			if (Main_Power_Check==1)   //´ËÊ±Ö÷µç²»Õý³£
			{ 
					Set_World_Flag_Flag(10,0);//Ö÷µçÕý³£
					Set_World_Flag_Flag(0,1);//¹©µçÖÐ¶ÏÖ¸Ê¾µÆÁÁ

					SendFunction[SendPtr.LoadCnt].Command = 7;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(7,0,0,0);				//Ö÷µç¹ÊÕÏ
				
          Set_World_Flag_Flag(11,1);//Ö÷µç¹ÊÕÏ
          Set_World_Flag_Flag(7,0);//ÏûÒôµÆ¹Ø±Õ
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;
					}
					else 
					{
						FaultRecount=0;
					}//¹ÊÕÏ¼ÇÂ¼×ÜÊý¼Ó1
					
					Save_Fault_Record(0,0xF0);//Ö÷µç¹ÊÕÏ			
			}
			else //Ö÷µçÕý³££¬¼ì²â³äµç×´Ì¬
			{
			// World_Flag=Set_Flag(World_Flag,2,1);
			// World_Flag=Set_Flag(World_Flag,3,0);  
			}
		}
		else  //Ö®Ç°Ö÷µç×´Ì¬²»Õý³£
		{ 
			if (Main_Power_Check==0)   //´ËÊ±Ö÷µçÕý³£
			{
					Set_World_Flag_Flag(10,1);//Ö÷µçÕý³£
          Set_World_Flag_Flag(11,0);//Ö÷µç¹ÊÕÏ
					Set_World_Flag_Flag(0,0);//¹©µçÖÐ¶ÏÖ¸Ê¾µÆÁÁ
					SendFunction[SendPtr.LoadCnt].Command = 8;
					SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
					SendFunction[SendPtr.LoadCnt].TDH = 0;
					SendFunction[SendPtr.LoadCnt].type = 0;
					SendPtr.LoadCnt++;

					//SendToPC1(8,0,0,0);	//Ö÷µç¹ÊÕÏ
			}
		}

		
}


///-------------------±¸µç¼ì²â-------------------------
void Bat_Power_Check(void)
{
	static uint8_t Last_Main_Power,This_Main_Power;
  uint8_t Main_Power_Check; 	//24¶ÔÓ¦3916 23V¶ÔÓ¦3745  22.5¶ÔÓ¦3663  21V ¶ÔÓ¦3391
 
	This_Main_Power = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Main_Power_Check = This_Main_Power & Last_Main_Power;

	Last_Main_Power = This_Main_Power;	//±ØÐëÁ¬ÐøÁ½´ÎÏàÍ¬µÄ×´Ì¬²ÅÅÐ¶Ï½ÓÊÜ
	
	//Main_Power_Check=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);

	Power_ADC_Return();  //±¸µçµçÑ¹ADÖµ
	
	if (Main_Power_Check==0) //Ö÷µçÕý³£À£µç±êÖ¾Îª0
	{
		Bat_Low_Flag=0;
	}  
	else //Ö÷µç²»Õý³£¼ì²â±¸µç
	{
		if (Bat_Power>=3671) 
		{
			Bat_Low_Flag=0;
			//Set_World_Flag_Flag(6,0);//6 Ç·Ñ¹Ö¸Ê¾µÆÃð£¬µçÑ¹Õý³£
		} //µç³ØµçÑ¹´óÓÚ22.5V-3671   23V-3745,±íÊ¾µçÑ¹Õý³£
		else if ((Bat_Power>=3580)&&(Bat_Power<3650)) 
		{
			Bat_Low_Flag=1;
			//Set_World_Flag_Flag(6,1);//6 Ç·Ñ¹Ö¸Ê¾µÆÁÁ
		} //605 22V--22.5V ±íÊ¾À£µç±êÖ¾
		else if ((Bat_Power<3570)&&(Main_Power_Check==1)) 
		{
			BD_OFF();
		}//µç³ØµÍÓÚ21.5V²¢ÇÒ²»Õý³££¬ÔòÏµÍ³¶Ïµç±£»¤µç³Ø
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
		
	if (Check_World_Flag_State(12)) //Ö®Ç°±¸µç×´Ì¬Õý³£
	{
		if (Bat_Power<3350)   //<20V ´ËÊ±±¸µç²»Õý³£
		{ 
			Set_World_Flag_Flag(12,0);//±¸µçÕý³£
			Set_World_Flag_Flag(13,1);//±¸µç¹ÊÕÏ
			//Set_World_Flag_Flag(0,1);//¹©µçÖÐ¶ÏÖ¸Ê¾µÆÁÁ
			 
			SendFunction[SendPtr.LoadCnt].Command = 9;
			SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
			SendFunction[SendPtr.LoadCnt].TDH = 0;
			SendFunction[SendPtr.LoadCnt].type = 0;
			SendPtr.LoadCnt++;

			//SendToPC1(9,0,0,0);	//±¸µç¹ÊÕÏ
			
			Set_World_Flag_Flag(7,0);//ÏûÒôµÆ¹Ø±Õ
			Beep_Alarm_Fault=2;

			if (FaultRecount<500)
			{
				FaultRecount ++;
			}
			else 
			{
				FaultRecount=0;
			}//¹ÊÕÏ¼ÇÂ¼×ÜÊý¼Ó1
			Save_Fault_Record(0,0xF1);//±¸µç¹ÊÕÏ
			
			CD_Flag = 0;	//±¸µç¹ÊÕÏ£¬¹Ø±Õ³äµç
			//CDK_OFF();
		}
		else
		{
			if(Main_Power_Check == 0)//Ö÷µçÕý³££¬±¸µçÕý³£¿ªÊ¼³äµç
			{
				CD_Flag = 1;
				//CDK_ON();
			}
		}
	}
	else  //Ö®Ç°±¸µç×´Ì¬²»Õý³£
	{ 
			if (Bat_Power>3390)   //>20V ±íÊ¾´ËÊ±±¸µçÕý³£
			{
				Set_World_Flag_Flag(12,1);//±¸µçÕý³£
				Set_World_Flag_Flag(13,0);//±¸µç¹ÊÕÏ
				//Set_World_Flag_Flag(0,0);//¹©µçÖÐ¶ÏÖ¸Ê¾µÆÁÁ
				
				SendFunction[SendPtr.LoadCnt].Command = 10;
				SendFunction[SendPtr.LoadCnt].TCQ_Num = 0;
				SendFunction[SendPtr.LoadCnt].TDH = 0;
				SendFunction[SendPtr.LoadCnt].type = 0;
				SendPtr.LoadCnt++;

				//SendToPC1(10,0,0,0);	//±¸µç»Ö¸´
				
				if(Main_Power_Check == 0)//Ö÷µçÕý³££¬±¸µçÕý³£¿ªÊ¼³äµç
				{
					CD_Flag = 1;
					//CDK_ON();
				}
			}
			else
			{
				CD_Flag = 0;	//±¸µç¹ÊÕÏ£¬¹Ø±Õ³äµç
				//CDK_OFF();
			}
	}
/*
	//----------------------³äµç¼ì²â-------------------------
			if (!Check_World_Flag_State(7)) //Ö®Ç°³äµç×´Ì¬Õý³£
			{      
				if ((CD_Check()==0)||(Main_Power_Check==1)||(Bat_Power<3350))   //´ËÊ±³äµç²»Õý³£
				{ 
					Set_World_Flag_Flag(7,1);//³äµç¹ÊÕÏµÆÁÁ
					Beep_Alarm_Fault=2;

					if (FaultRecount<500)
					{
						FaultRecount ++;//¹ÊÕÏ¼ÇÂ¼×ÜÊý¼Ó1
					}
					else 
					{
						FaultRecount=0;
					}
					Save_Fault_Record(0,0xF2);//³äµç¹ÊÕÏ
				}

			}
			else  //Ö®Ç°×´Ì¬²»Õý³£
			{ 
				if ((CD_Check()==1)&&(Main_Power_Check==0))   //´ËÊ±³äµçÕý³£
				{
					Set_World_Flag_Flag(7,0);//
				}
			}
*/
}

void TCQ_Data_Control(void)//¶ÁÈ¡´«¸ÐÆ÷×´Ì¬£¬½ÓÊÕ´«¸ÐÆ÷·µ»ØµÄÊý¾Ý
{
	uint8_t i,k,m,pn;
	uint8_t flag=0;
	uint16_t lTemp = 0;
	
	TCDID=Rec_Buff[0]*256+Rec_Buff[1];			//Éè±¸IDºÅ
	Type_State=Rec_Buff[5]*256+Rec_Buff[6];	//¼ì²âÀàÐÍ=1µçÁ÷ =0ÎÂ¶È
	PB_State =Rec_Buff[7]*256+Rec_Buff[8];	//ÆÁ±Î×´Ì¬=1ÆÁ±Î =0¹¤×÷
	State1=Rec_Buff[9]*256+Rec_Buff[10];		//±¨¾¯×´Ì¬ºÍ¹ÊÕÏ×´Ì¬¸ßÎ»
	State2=Rec_Buff[11]*256+Rec_Buff[12];		//±¨¾¯×´Ì¬ºÍ¹ÊÕÏ×´Ì¬µÍÎ»
	SKC_State=Rec_Buff[13]*256+Rec_Buff[14];//ÍÑ¿Û×´Ì¬=1ÆÁ±Î =0¿ªÆô
	//MKC_State=Rec_Buff[15]*256+Rec_Buff[16];
	 
	Alarm_State=0;
	Fault_State=0;
	
	Set_Uart_Fault_Timer0(TCDID-1);//Uart_Err_Timer[TCDID-1]=0;
	
	if((Function_Flag==7)||(Function_Flag==6))//Ð´×´Ì¬·µ»ØÖµ
	{
		TCQ_Return_OK=1;
	
		for(i=0;i<16;i++)//16¸ö»ØÂ·×´Ì¬
		{
			temp1 =PB_State&(1 << i);
			if (temp1!=0)//=1±íÊ¾¸ÃÂ·ÎªÆÁ±Î×´Ì¬  
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
				continue;
			}
			
			temp1 =State1 & (1 << i);
			temp2 =State2 & (1 << i);
			if((temp1==0)&&(temp2==0))//Õý³£			 
			{
				Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			}
			else if((temp1^temp2)!=0) //¹ÊÕÏ»ò±¨¾¯  01¶ÌÂ· 10¶ÏÂ·
			{
				if(!Check_Sensor_Fault0_State(TCDID-1,i))//»ØÂ·¹ÊÕÏ
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
		if (temp1!=0)//=1ÆÁ±Î×´Ì¬ =0¹¤×÷×´Ì¬
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
			continue;
		}

		temp1 =State1 & (1 << i);//±¨¾¯×´Ì¬ºÍ¹ÊÕÏ×´Ì¬¸ßÎ»
		temp2 =State2 & (1 << i);
		    
		if((temp1==0)&&(temp2==0))//Õý³££¬ÎÞ¹ÊÕÏ±¨¾¯	
		{
			Set_Sensor_Fault0_Flag(TCDID-1,i,0);
		}
		else if((temp1^temp2)!=0) //ÓÐ¹ÊÕÏ 01 ¶ÌÂ· 10 ¶ÏÂ·
		{
			if(!Check_Sensor_Fault0_State(TCDID-1,i))//Ö®Ç°ÎÞ¹ÊÕÏ±¨¾¯
			{
				Fault_State=Fault_State|(1<<i);
				Set_Sensor_Fault0_Flag(TCDID-1,i,1);
				
				if (FaultRecount<500) //¹ÊÕÏ¼ÇÂ¼×ÜÊý500Ìõ
				{
					FaultRecount++;
				}
				else 
				{
					FaultRecount=1;//±¨¾¯¼ÇÂ¼×ÜÊý¼Ó1
				}	
				
				Beep_Alarm_Fault = 2;//·¢³ö¹ÊÕÏ±¨¾¯ÉùÒô
				Set_World_Flag_Flag(7,0);//ÏûÒôµÆ¹Ø±Õ
				Beep_ON();
				
				pn=Fault_Rec;//Ö÷½çÃæÏÔÊ¾µÄ¹ÊÕÏÊý
				if (pn>12) 
				{
					pn=12;  
				}
				
				if((temp1 != 0)&&(temp2==0))
				{
					//´æÈë¿ªÂ·¹ÊÕÏ
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0800 | TCDID);
					Save_Fault_Record(TCDID,i+1);		//¿ªÂ·
				}
				else 
				{
					//´æÈë¶ÌÂ·¹ÊÕÏ
					lTemp = i;
					Fault_Position[pn]=((lTemp<<12)|0x0400 | TCDID);
					Save_Fault_Record(TCDID,i+17);	//¶ÌÂ·
				}
				
				flag=0;
				for(k=0;k<pn;k++)//ÓÐÏàÍ¬µÄ£¬ºó±ßµÄÇ°ÒÆÒ»Î»
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
					Fault_Rec++;	//±¨¾¯×ÜÊý¼Ó1
					//×î¶àÏÔÊ¾12Ìõ¹ÊÕÏ
					if (pn==12)
					for(m=0;m<12;m++) 
					{
						Fault_Position[m]=Fault_Position[m+1];
					}
				}		
		
			}
		}
		else if((temp1!=0)&&(temp2!=0))//11 ±¨¾¯×´Ì¬
		{	 
			//Feel[i]=(Rec_Buff[19+4*i]&0x7F)*256+Rec_Buff[20+4*i];
			Alarm_State=Alarm_State|(1<<i); 
			Set_Alarm_Flag(TCDID-1,1);
			Set_Alarm_Flag_16(TCDID-1,i,1);
			Speak_ON();
			Beep_Alarm_Fault=1; 
			
			KC1_ON();
			KC2_ON();
			Set_World_Flag_Flag(2,1);//Êä³öÖ¸Ê¾µÆÁÁ
			Dis_State_LED();//×´Ì¬Ö¸Ê¾µÆÏÔÊ¾
	
			// if (First_Alarm==0)  {First_Alarm=TCDID*16+i+1;} 
			//-----------------------------------------------------------------------     
			Function_Flag = 15;	//¶ÁÈ¡±¨¾¯×î´óÖµ
			
			pn=Alarm_Rec_Position;
			if (pn>7) 
			{
				pn=7;  
			}
			//¸ßÎ»±íÊ¾¼ì²âÀàÐÍ
			if((Type_State& (1<<i))==0) //¼ì²âÀàÐÍ=1µçÁ÷ =0ÎÂ¶È
				Alarm_Position[pn]=0*4096+TCDID;
			else 
				Alarm_Position[pn]=(i+1)*4096+TCDID; 

			//Alarm_Data[pn]=Feel[i];
			
			flag=0;
			for(k=0;k<pn;k++)//ÓÐÏàÍ¬µÄ£¬ºó±ßµÄÇ°ÒÆÒ»Î»
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
				Alarm_Rec_Position++;	//±¨¾¯×ÜÊý¼Ó1
				//×î¶àÏÔÊ¾7Ìõ
				if (pn==7)
				for(m=0;m<7;m++) 
				{
					Alarm_Position[m]=Alarm_Position[m+1];
					Alarm_Data[m]=Alarm_Data[m+1];
				}
			}				
		}//end else
	}//end for 	

	if(Alarm_State!=0)//ÓÐ±¨¾¯×´Ì¬
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
		
		//SendToPC1(4,TCDID,1,0x31);//·¢ËÍ±¨¾¯ÐÅÏ¢µ½Ö÷»ú
	}

//	if(Fault_State!=0)//»¥¸ÐÆ÷¹ÊÕÏ
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

void Set_Sensor_Fault0_Flag(uint8_t Num,uint8_t nbit,uint8_t flag)//½«»¥¸ÐÆ÷Ä³Ò»»ØÂ·±¨¾¯±êÖ¾ÖÃ1»òÇå0
{
	uint16_t x,temp;

	temp=Sensor_Fault0_Flag[Num];

	x= 1 << nbit; 

	if (flag==1)   //=1½«ÏàÓ¦µÄÎ»ÖÃÖÃ1
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

uint8_t Check_Sensor_Fault0_State(uint8_t Num,uint8_t nbit)//¹ÊÕÏ·µ»Ø1
{
	uint16_t temp;
	temp=Sensor_Fault0_Flag[Num];

	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1;  
}




