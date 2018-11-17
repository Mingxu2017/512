#include "stm32f10x.h"		/* Èç¹ûÒªÓÃSTµÄ¹Ì¼þ¿â£¬±ØÐë°üº¬Õâ¸öÎÄ¼þ */
#include "Declare.h"


uint8_t Key_Num=0xFF;

uint8_t Key_Value;
uint8_t menu;

uint8_t Key_Flag=0;
uint16_t  Query_Alarm_Num;
uint16_t  Query_Fault_Num;
uint16_t Query_SD_Num;

uint8_t Cursor;

uint8_t PB_Flag;
uint8_t KCS_Flag=0;//ÊÖ¶¯¿ØÖÆ±êÖ¾

//¼üÅÌÉ¨Ãè?
#define Key_1          1
#define Key_2          2
#define Key_3          3
#define Key_4          4
#define Key_5          5
#define Key_6          6
#define Key_7          7
#define Key_8          8
#define Key_9          9
#define Key_0          0

#define Key_E          12//#
#define Key_C          10//*   Êµ¼ÊÊÇ¼üÖµÊÇ10

#define Key_Selfcheck1     13
#define Key_Selfcheck2     14

#define Key_Reset1         15
#define Key_Reset2         16

#define Key_Add            17
#define Key_Query          18

#define Key_Menu_Sure      19
#define Key_Sure 19

#define Key_Cancel         20
#define Key_Sub            21

#define Key_NoLock1        22
#define Key_NoLock2        23

#define Key_NoSound1       24
#define Key_NoSound2       25

#define Key_KCS            50 

uint8_t  Get_KeyValue (uint8_t i,uint16_t key1);

void Beep_Err(void)
{
  Delay1ms(200);
  Beep_ON();
  Delay1ms(120);
  Beep_OFF();
  Delay1ms(80);
  Beep_ON();
  Delay1ms(120);
  if (Beep_Alarm_Fault != 2) Beep_OFF();
  WDOG();
}


void Key_Scan(void) 
{ 
	uint8_t i;

	uint16_t IOA_Data,IOC_Data,temp2;

  WDOG();
		
  if (!Key_Down_Flag) //Ã»ÓÐ°´ÏÂ£¬¼ì²âÊÇ·ñÓÐ¼ü°´ÏÂ
  {  
		
	  for(i=0;i<5;i++) //É¨ÃèµÚ¶þÐÐ¿ª¹Ø   
    {
	    if(i<4) 
			{
				IOA_Data=GPIO_ReadInputData(GPIOA);		
        IOA_Data=IOA_Data&0xFF0F;
			  temp2=(0xFFFF-(0x10<<i))&0x00F0;//Ñ­»·×óÒÆ
			  IOA_Data=IOA_Data|temp2;
			  GPIO_Write(GPIOA,IOA_Data);//1110 XXXX      Key5=0,Key2\3\4\=1;
				
				IOC_Data=GPIO_ReadInputData(GPIOC);		//PC4
        IOC_Data=IOC_Data&0xFFCF|0x0030;
        GPIO_Write(GPIOC,IOC_Data);
        Delay1us(10); 

			  IOA_Data=GPIO_ReadInputData(GPIOA);
        IOA_Data=IOA_Data&0x00F0;
 
				IOC_Data=GPIO_ReadInputData(GPIOC);
        IOC_Data=IOC_Data&0x0030;
				
        if((IOA_Data^temp2)!=0)   //ÓÐ¼ü°´ÏÂ
  	    { 
		      Delay1ms(10);
          IOA_Data=GPIO_ReadInputData(GPIOA);
          IOA_Data=IOA_Data&0x00F0;
		      if((IOA_Data^temp2)!=0)
          {
           Key_Down_Flag=1;
           Key_Value=Get_KeyValue (i,IOA_Data); 
           Key_Num=i;
					 Beep_ON();
           break;
           }
				 }	
        else 
				if(IOC_Data!=0x0030)   //ÓÐ¼ü°´ÏÂ
  	    { 
		      Delay1ms(10);
          IOC_Data=GPIO_ReadInputData(GPIOC);
          IOC_Data=IOC_Data&0x0030;
		      if(IOC_Data!=0x0030)
          {
            Key_Down_Flag=1;
            Key_Value=Get_KeyValue (i,IOC_Data); 
            Key_Num=i;
						Beep_ON();
            break;
           }
				 }				
         
        }//<4¼ì²â½áÊø
			//-------------------------------------------------	
			else
			if(i==4)
      {
				IOA_Data=GPIO_ReadInputData(GPIOA);		
        IOA_Data=IOA_Data&0xFF0F|0x00F0;
			  GPIO_Write(GPIOA,IOA_Data);
				
				IOC_Data=GPIO_ReadInputData(GPIOC);		
        IOC_Data=IOC_Data&0xFFCF|0x0020;
        GPIO_Write(GPIOC,IOC_Data);
        Delay1us(10); 

			  IOA_Data=GPIO_ReadInputData(GPIOA);
        IOA_Data=IOA_Data&0x00F0;
				
 				IOC_Data=GPIO_ReadInputData(GPIOC);
        IOC_Data=IOC_Data&0x0030;
        if(IOA_Data!=0x00F0)   //ÓÐ¼ü°´ÏÂ
  	    { 
		      Delay1ms(10);
          IOA_Data=GPIO_ReadInputData(GPIOA);
          IOA_Data=IOA_Data&0x00F0;

		      if(IOA_Data!=0x00F0)
          {
           Key_Down_Flag=1;
           Key_Value=Get_KeyValue (i,IOA_Data); 
           Key_Num=i;
					 Beep_ON();
           break;
          }
				 }	
				  else 
				if(IOC_Data!=0x0020)   //ÓÐ¼ü°´ÏÂ
  	    { 
		      Delay1ms(10);
          IOC_Data=GPIO_ReadInputData(GPIOC);
          IOC_Data=IOC_Data&0x0030;
		      if(IOC_Data!=0x0020)
          {
            Key_Down_Flag=1;
            Key_Value=Get_KeyValue (i,IOC_Data); 
            Key_Num=i;
						Beep_ON();
            break;
           }
				 }				
       }
			 //-------------------------------------------------	
			
     }
    }
   else  //ÓÐ¼ü°´ÏÂ£¬¼ì²â´Ë¼üÊÇ·ñÌ§ÆðÀ´
   { 
		 
		 if(Key_Num<4)
		 { 
			  IOA_Data=GPIO_ReadInputData(GPIOA);		
        IOA_Data=IOA_Data&0xFF0F;
			  temp2=(0xFFFF-(0x10<<Key_Num))&0x00F0;//Ñ­»·×óÒÆ
			  IOA_Data=IOA_Data|temp2;
			  GPIO_Write(GPIOA,IOA_Data);
			 
			  IOC_Data=GPIO_ReadInputData(GPIOC);		
        IOC_Data=IOC_Data&0xFFCF|0x0030;
        GPIO_Write(GPIOC,IOC_Data);
        Delay1us(10); 
			 
			  IOA_Data=GPIO_ReadInputData(GPIOA);
        IOA_Data=IOA_Data&0x00F0;
		 
			  IOC_Data=GPIO_ReadInputData(GPIOC);
        IOC_Data=IOC_Data&0x0030;
			  
        if(((IOA_Data^temp2)==0)&&(IOC_Data==0x0030))   //ÒÑÌ§Æð
  	    {
	   	     Delay1ms(10);
           IOA_Data=GPIO_ReadInputData(GPIOA);
           IOA_Data=IOA_Data&0x00F0;
           IOC_Data=GPIO_ReadInputData(GPIOC);
           IOC_Data=IOC_Data&0x0030;
           if(((IOA_Data^temp2)==0)&&(IOC_Data==0x0030))
           {
               Key_Up_Flag=1;
               Beep_OFF();
           }
         }
		   }//--------------------------------------------------
			else if(Key_Num==4)
		  {
				IOA_Data=GPIO_ReadInputData(GPIOA);		
        IOA_Data=IOA_Data&0xFF0F|0x00F0;
			  GPIO_Write(GPIOA,IOA_Data);
				
				IOC_Data=GPIO_ReadInputData(GPIOC);		
        IOC_Data=IOC_Data&0xFFCF|0x0020;
        GPIO_Write(GPIOC,IOC_Data);
        Delay1us(10); 
				
				IOA_Data=GPIO_ReadInputData(GPIOA);
        IOA_Data=IOA_Data&0x00F0;
				
				IOC_Data=GPIO_ReadInputData(GPIOC);
        IOC_Data=IOC_Data&0x0030;
        if((IOA_Data==0x00F0)&&(IOC_Data==0x0020))    //ÒÑÌ§Æð
  	    {
	   	     Delay1ms(10);
           IOA_Data=GPIO_ReadInputData(GPIOA);
           IOA_Data=IOA_Data&0x00F0;
           IOC_Data=GPIO_ReadInputData(GPIOC);
           IOC_Data=IOC_Data&0x0030;
           if((IOA_Data==0x00F0)&&(IOC_Data==0x0020))  
           {
               Key_Up_Flag=1;
               Beep_OFF();
           }
         }
       }	
  		//--------------------------------------------------
     
     }  
  if ((Key_Down_Flag)&&(Key_Up_Flag))//ÓÐ¼ü°´ÏÂ£¬²¢ÇÒÌ§ÆðÀ´ÁË
  {
    Back_Timer1S=0;
    //Back_Led_ON();
   } 
}



uint8_t  Get_KeyValue (uint8_t i,uint16_t key1)
{
  uint8_t key=0xff;
   
 switch(i)
 {
  case  0:
       {  
						switch(key1)
					 {
							case  0xC0:  {key=22;break;}//22    1100 XXXX
							case  0xA0:  {key=23;break;}//23    1010 XXXX
							case  0x60:  {key=24;break;} //24   0110 XXXX
							case  0x20:  {key=25;break;}//PC4
							case  0x10:  {key=21;break;}//PC5
							default:break;
						}
          break;
        }  //--------------------------------
  case  1:
     {  switch(key1)
				 {
						case  0xC0:  {key=17;break;}//    1100 XXXX
						case  0x90:  {key=18;break;}//    1001 XXXX
						case  0x50:  {key=19;break;} //   0101 XXXX
						case  0x20:  {key=20;break;}//PB
						case  0x10:  {key=16;break;}//PC5
						default:break;
					}
          break;
       }  //-------------------------------------

  case  2:
      {  switch(key1)
				 {
						case  0xA0:  {key=12;break;}//    1010 XXXX
						case  0x90:  {key=13;break;}//    1001 XXXX
						case  0x30:  {key=14;break;} //   0011 XXXX
						case  0x20:  {key=15;break;}//PB
						case  0x10:  {key=0;break;}//PC5
						default:break;
					}
          break;
       }  //-------------------------------------
  case  3:
      {  switch(key1)
				 {
						case  0x60:  {key=7;break;}//    0110 XXXX
						case  0x50:  {key=8;break;}//    0101 XXXX
						case  0x30:  {key=9;break;} //   0011 XXXX
						case  0x20:  {key=10;break;}//PB
						case  0x10:  {key=6;break;}//PC5
						default:break;
					}
          break;
       }  //-------------------------------------
	 case  4:
      {  switch(key1)
				 {
						case  0xE0:  {key=2;break;}//    1110 XXXX
						case  0xD0:  {key=3;break;}//    1101 XXXX
						case  0xB0:  {key=4;break;} //   1011 XXXX
						case  0x70:  {key=5;break;}//    0111
						case  0x00:  {key=1;break;}//PC5
						default:break;
					}
          break;
       }  //-------------------------------------
//		case  5: 
//     {  switch(key1)
//				 {
//						case  0xE0:  {key=21;break;}//    1110 XXXX
//						case  0xD0:  {key=16;break;}//    1101 XXXX
//						case  0xB0:  {key=11;break;}//   1011 XXXX
//						case  0x70:  {key=6;break;}//   0111
//						case  0x00:  {key=1;break;}//PC4
//						default:break;
//					}
//          break;
//       } 

  default:break;
 }
 return key;
}

//¼üÅÌ´¦Àí
void Key_Control(void)
{  
	uint8_t  temp;
	uint8_t buff[30];
	uint8_t flag;
	uint16_t i,temp2;
	//uint32_t Addr;
	u8 displayflag=0;
	Key_Scan(); 
	if ((!Key_Down_Flag)||(!Key_Up_Flag)) return;
	Key_Down_Flag=0;
	Key_Up_Flag=0; 
      
	switch(Key_Value)
	{	// Ö÷½çÃæÊý×Ö¼ü¿ì½Ý²Ëµ¥
		case Key_1:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto PB_Menu;				//ÏµÍ³ÈÝÁ¿ÉèÖÃ
			}

			break;
		case Key_2:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto System_Set;		//ÏµÍ³²ÎÊý´òÓ¡»úÅäÖÃ
			}
	
			break;
		case Key_3:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto Read_TCQ_State;//ÏÔÊ¾Ì½²âÅäÖÃ
			}
	
			break;
		case Key_4:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto LD_Test_Menu; 	//Áª¶¯²âÊÔ;
			}

			break;
		case Key_5:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto Test_FL;				//ÊµÊ±ÏÔÊ¾²âÁ¿Öµ
			}
			break;
		case Key_6:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto Timer_Menu;		//ÉèÖÃÏµÍ³Ê±ÖÓ
			}
			break;
		case Key_7:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto ShowFrq_Menu;	//ÉèÖÃË¢ÐÂÆµÂÊ
			}
			break;
		case Key_8:
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto Set_Addr;			//ÉèÖÃ±¾»úµØÖ·
			}
			break;
		case Key_9: 
			if(SuperPassFlag)
			{
				Dis_Key_Buff_Flag=1;
				goto Pass2_Menu;		//½øÈë¶þ¼¶²Ù×÷
			}
			break;
		case Key_C://*		//ÇÐ»»ÏÔÊ¾
			
			Clear_Dispaly_Feel();
		
			if(Display_Flag==0)
			{
				Display_Flag = 1;
				Display_Main_Fault();
			}
			else
			{
				Display_Flag = 0;
				Display_Feel_Fault();
			}
			break;
		case Key_E://#
			if(DisplayAddr == 0)
			{
				DisplayAddr = 1;
			}
			else
			{
			  DisplayAddr = 0;
			}
			
			if(Display_Flag == 0)
				Display_Feel_Fault();//Ö»ÏÔÊ¾¹ÊÕÏºÍ±¨¾¯
			else
				Display_Main_Fault();
			
			break;
		case Key_Add:
//			if( Dis_Num < 499 )
//			{
//				Dis_Num =Dis_Num+12;
//			}
			Dis_Feel_Timer = 20*ShowFrq;
			break;
		case Key_Sub:
			if(Dis_Num > 24)//½ô½Ó×ÅË¢ÐÂÁË12ÐÐÏÔÊ¾£¬¼õ12Ã»Ð§¹û
			{
				Dis_Num =Dis_Num - 24;
			}
			else
			{
				Dis_Num = 0;
			}
			Dis_Feel_Timer = 20*ShowFrq;
			break;
		case Key_Selfcheck1:	//×Ô¼ì½çÃæ
		case Key_Selfcheck2:	//×Ô¼ì½çÃæ
			{   
				Dis_Key_Buff_Flag=1;
				Key_Flag=1;
				goto Pass1_Menu;
			}
		case Key_Reset1:		//¸´Î»
		case Key_Reset2:		//¸´Î»
			{   
				Dis_Key_Buff_Flag=1;         
				Key_Flag=2;
				goto Pass1_Menu;
			}
		case Key_Query:		//²éÑ¯
		{    
			Dis_Key_Buff_Flag=1;
			Key_Flag = 3;
			goto Query_Menu;
		}

		case Key_NoSound1:	//ÏûÒô¡¢·µ»Ø		
		case Key_NoSound2:	//ÏûÒô¡¢·µ»Ø				
		{     
			Dis_Key_Buff_Flag = 0;

			if(Beep_Alarm_Fault!=0)
				Set_World_Flag_Flag(7,1);						 
			Beep_Alarm_Fault = 0;
			Beep_OFF();
			Speak_OFF();
			Key_Flag=0; 
			Function_Flag=4;//·¢ËÍÏûÒôÃüÁî
			break;   
		}	//ÏûÒô¼ü
		case Key_Cancel: 
			Dis_Key_Buff_Flag=0;
			Dis_Alarm_Fault_Flag=0;
		  Clr_Display();
			Display_Main_Face();
			break;
		case Key_Menu_Sure:		//È·ÈÏ¼ü
		{
			Key_Flag = 4;
			Dis_Key_Buff_Flag=1;
			goto Pass1_Menu;
		}
		case Key_NoLock1:			
		case Key_NoLock2:  //½âËø
		{
			Key_Flag = 5;
			Dis_Key_Buff_Flag=1;
			goto Pass1_Menu;
		}
		default:
			Dis_Key_Buff_Flag = 0;
			break;
	}//switch½áÊø
	return;
	
////////////////////////////////////////////////
Pass1_Menu:
	 Flicker_Position = 0;
   dis_buff[0]=0;
   dis_buff[1]=2;
   dis_buff[2]=3;
   dis_buff[3]=4;  
   Clr_Display();
   Dis_Pass1_Promt();
   //Dis_Pass(); 
	while(Dis_Key_Buff_Flag)
	{  
		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
			{
				dis_buff[Flicker_Position] = Key_Value;  
				Dis_Pass();
				if (Flicker_Position<3) Flicker_Position++;
				else Flicker_Position=0;
				break;
			}
			case Key_Add: 
			{
				if(dis_buff[Flicker_Position] < 9)    
					dis_buff[Flicker_Position]++;
				else   
					dis_buff[Flicker_Position] = 0; 
				Dis_Pass(); 
				break;
			}
			case Key_Sub:                            // ¼õ
			{
				if(dis_buff[Flicker_Position] > 0)    
					dis_buff[Flicker_Position]--;
				else   
					dis_buff[Flicker_Position] = 9;  
				Dis_Pass(); 
				break;
			}
			case Key_Query:                       //¹¦ÄÜÒÆÎ»
			{   
				if(Flicker_Position < 3)  
					Flicker_Position++;
				else 
					Flicker_Position = 0;
				Dis_Pass(); 
				break;
			}
			case Key_Cancel: 
			{
				Dis_Key_Buff_Flag = 0;
				Close_Cur();
				Clr_Display();
				Display_Main_Face();
				return;
			}
			case Key_Menu_Sure:                          //È·ÈÏ
			{  
					 if (((dis_buff[0]==Pass1[0])&&(dis_buff[1]==Pass1[1])&&(dis_buff[2]==Pass1[2])&&(dis_buff[3]==Pass1[3]))
                    ||((dis_buff[0]==Pass2[0])&&(dis_buff[1]==Pass2[1])&&(dis_buff[2]==Pass2[2])&&(dis_buff[3]==Pass2[3]))
                    ||((dis_buff[0]==5)&&(dis_buff[1]==8)&&(dis_buff[2]==1)&&(dis_buff[3]==9)))//³¬¼¶ÃÜÂë
					//ÃÜÂëÕýÈ·
					{   
						if((dis_buff[0]==5)&&(dis_buff[1]==8)&&(dis_buff[2]==1)&&(dis_buff[3]==9))
						{
							SuperPassFlag = 1;
						}
						
						Close_Cur();//¹Ø±Õ¹â±ê
						if (Key_Flag==1)//×Ô¼ì
						{  
							Function_Flag=2;//·¢ËÍ×Ô¼ìÃüÁî

							Self_Check_Flag=1;
							Self_Check();
							Self_Check_Flag=0;
							Dis_Key_Buff_Flag = 0;
							Display_Main_Face();
						}
						else if (Key_Flag==2)//¸´Î»
						{  
							Data_Init();
							Device_Init();

							Save_Event_Record(3);//1:´ú±í¿ª»úÉÏµç  2£º´ú±í¹Ø»ú   3£º¸´Î»   4£ºÇå³ý¼ÇÂ¼   5£º³õÊ¼»¯
							Display_Main_Face();
							
							if(Display_Flag == 0)
								Display_Feel_Fault();//Ö»ÏÔÊ¾¹ÊÕÏºÍ±¨¾¯
							else
								Display_Main_Fault();
			
							Display_System_Sate();
							Display_System_Timer();
							Function_Flag=3;//·¢ËÍ¸´Î»ÃüÁî
						}
						else if (Key_Flag==5)//½âËø
						{ 
							Set_World_Flag_Flag(8,1);
							KEY_LOCK_Flag=0; //ÖÃ½âËø±êÖ¾
							KEY_LOCK_Timer1S=0;

							Dis_Key_Buff_Flag = 0;
							Clr_Display();
							if(Dis_Alarm_Fault_Flag==0)
								Display_Main_Face();
						}		
						else if (Key_Flag==4)//ÉèÖÃ
						{   
							menu=1; 
							goto Set_Menu;
						}    
					}
					else 
					{
						Dis_Err(); //ÃÜÂë²»ÕýÈ·ÏÔÊ¾Err·µ»Ø½çÃæ
						Beep_Err();
						goto Pass1_Menu;
					}
		      break;
			}

			default: 
				break;
			}///switch ½áÊø

		}
		return;  
////////////////////////////////////////////////////
Set_Menu:
 
   menu = 0;
Set_Menu1:
   Close_Cur();	//¹Ø±Õ¹â±ê

   Clr_Display();
   Dis_Main_Menu();
   Dis_Main_Menu1();

   while(Dis_Key_Buff_Flag)
   {  

			Delay1ms(30);
			Key_Scan();
			if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
			Key_Down_Flag=0;
			Key_Up_Flag=0;
    
			switch(Key_Value)
			{

       case Key_1:
       case Key_2:
       case Key_3:
       case Key_4:
       case Key_5:
       case Key_6:
       case Key_7:
       case Key_8:
	     case Key_9:		
				{
					menu =Key_Value-1; //¹â±êÖ±½ÓÖ¸µ½¶ÔÓ¦²Ëµ¥Î»ÖÃ
					Dis_Main_Menu1();
					break;
				}
			case Key_Add://Ôö¼Ó
				{
					if(menu > 0)    
						menu--;
					else   
						menu = 9;  
					Dis_Main_Menu1();
					break;
				}
	      case Key_Sub://¼õ
				{
					if(menu < 9)    
						menu++;
					else   
						menu = 0; 
					Dis_Main_Menu1();
					break;
				}

				case Key_Query:                       //¹¦ÄÜÒÆÎ»
				{   
					if(menu < 4)  
						menu=menu+4;
					else 
						menu = menu-4;
					Dis_Main_Menu1();
					break;
				}
				case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
				{
					Dis_Key_Buff_Flag = 0; 
					Dis_Alarm_Fault_Flag=0;
					Clr_Display();
					Display_Main_Face();
					
					//if(Dis_Alarm_Fault_Flag==0)   Display_Main_Face();
					Key_Flag=0; 
					break;
				}

				case Key_Menu_Sure:                          //È·ÈÏ
				{
						if(menu==0) goto PB_Menu;							//ÏµÍ³ÈÝÁ¿ÉèÖÃ
						else if(menu==1)  goto System_Set;		//ÏµÍ³²ÎÊý´òÓ¡»úÅäÖÃ¡¡
						else if(menu==2)  goto Read_TCQ_State;//ÏÔÊ¾Ì½²âÅäÖÃ
						else if(menu==3)  goto LD_Test_Menu; 	//Áª¶¯²âÊÔ;
						else if(menu==4)  goto Test_FL;				//ÊµÊ±ÏÔÊ¾²âÁ¿Öµ
						else if(menu==5)  goto Timer_Menu;		//ÉèÖÃÏµÍ³Ê±ÖÓ
						else if(menu==6)  goto ShowFrq_Menu;	//ÉèÖÃË¢ÐÂÆµÂÊ
						else if(menu==7)  goto Set_Addr;			//ÉèÖÃ±¾»úµØÖ·
						else if(menu==8)  goto Pass2_Menu;		//½øÈë¶þ¼¶²Ù×÷
						else if(menu==9)  goto Install_Addr;			//½øÈëÉè±¸°²×°Î»ÖÃ

					break;
				}
					default: 
						break;
	   }///switch ½áÊø

  }
  return; 
/////////////////////////////////////////////////////
Query_Menu:
   
		Clr_Display();
		Dis_Query_Menu();
		Dis_Query_Menu1();
		while(Dis_Key_Buff_Flag)
		{  
			Delay1ms(30);
			Key_Scan();
			if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
			Key_Down_Flag=0;
			Key_Up_Flag=0;

			switch(Key_Value)
			{
				case Key_1:
				case Key_2:
				case Key_3:
				{   
					menu =Key_Value-1;  
					Dis_Query_Menu1();
					break;
				}
				case Key_Add:   //Ôö¼Ó
				{
					if(menu > 0)    
						menu--;
					else   
						menu = 2;  

					Dis_Query_Menu1();
					break;
				}
				case Key_Sub:                            // ¼õ
				{
					if(menu < 2)    
						menu++;
					else   
						menu = 0; 
					
					Dis_Query_Menu1();
					break;
				}
           
				case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
				{  
					Clr_Display();
					if(Dis_Alarm_Fault_Flag==0)
					{
						Display_Main_Face();
					}
				
					Dis_Key_Buff_Flag=0;
					Key_Flag=0; 
					break;
				}

				case Key_Menu_Sure:                          //È·ÈÏ
				{
					if (menu==0) goto Query_Alarm;//²éÑ¯±¨¾¯¼ÇÂ¼
					else if (menu==1) goto Query_Fault; //²éÑ¯¹ÊÕÏ¼ÇÂ¼
					else if (menu==2) goto Query_SD;//²éÑ¯ÊÂ¼þ¼ÇÂ¼

					break;
				}
				default: break;
			}///switch ½áÊø

		}
		return;

///////////////////////////////////////////
Query_Alarm:

	Query_Alarm_Num=AlarmRecount;
	
	//Display_Alarm_Record_Bar();
	Clr_Display();
	
	if (Query_Alarm_Num==0)
	{  
		Dis_No_Record();
		Beep_Err();
		Dis_Key_Buff_Flag = 0;
		Key_Flag=0; 
		Clr_Display();
		Display_Main_Face();
		return;         
	} 
  
  Display_Alarm_Record(Query_Alarm_Num);
  while(Dis_Key_Buff_Flag)
  {   
    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_Add:                           //Ôö¼Ó
			{
				if((Query_Alarm_Num+12) <= AlarmRecount)
				{
					Query_Alarm_Num=Query_Alarm_Num+12;
					Clr_Display();
					Display_Alarm_Record(Query_Alarm_Num);
				}
				break;
			}

			case Key_Sub:                            // ¼õ
			{
				if(Query_Alarm_Num > 12) 
				{
					Query_Alarm_Num=Query_Alarm_Num-12;
					Clr_Display();
					Display_Alarm_Record(Query_Alarm_Num);
				}
				break;
			}

			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				goto Query_Menu;
			}	//ÏûÒô¼ü

			default: break;
		}///switch ½áÊø

	}
	
	
/////////////////////////////////////////////////////
Query_SD:
  Query_SD_Num=SDRecount;
	Clr_Display();
	
	if (Query_SD_Num==0)
	{ 
		Dis_No_Record();
		Beep_Err();
		Dis_Key_Buff_Flag = 0;
		Key_Flag=0; 
		Display_Main_Face();
		return;         
	} 

  //Display_SD_Record_Bar();
  Display_SD_Record(Query_SD_Num);
  while(Dis_Key_Buff_Flag)
  {   
    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_Add:                           //Ôö¼Ó
			{
				if((Query_SD_Num+12) <= SDRecount)
				{
					Query_SD_Num=Query_SD_Num+12;
				}
				Clr_Display();
				Display_SD_Record(Query_SD_Num);
				break;
			}

			case Key_Sub:                            // ¼õ
			{
				if(Query_SD_Num > 12) 
				{
					Query_SD_Num=Query_SD_Num-12;
					Clr_Display();
					Display_SD_Record(Query_SD_Num);
				}
				break;
			}

			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				goto Query_Menu; 
			}	//ÏûÒô¼ü

			default: 
				break;
		}///switch ½áÊø

	}
///////////////////////////////////////////////////////////////////
Query_Fault:
  Query_Fault_Num=FaultRecount;
	Clr_Display();
  
	if (Query_Fault_Num==0)
	{ 
		Dis_No_Record();
		Beep_Err();
		Dis_Key_Buff_Flag = 0;
		Key_Flag=0; 
		Display_Main_Face();
		return;         
	} 
  
  //Display_Fault_Record_Bar();
  Display_Fault_Record(Query_Fault_Num);

	while(Dis_Key_Buff_Flag)
	{ 
		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_Add:                           //Ôö¼Ó
			{
				if((Query_Fault_Num+12) <= FaultRecount)
				{
					Query_Fault_Num=Query_Fault_Num+12;
					Clr_Display();
					Display_Fault_Record(Query_Fault_Num);
				}
				//Clr_Display();
				//Display_Fault_Record(Query_Fault_Num);
				break;
			}

			case Key_Sub:                            // ¼õ
			{
				if(Query_Fault_Num > 12) 
				{
					Query_Fault_Num=Query_Fault_Num-12;
					Clr_Display();
					Display_Fault_Record(Query_Fault_Num);
				}
				break;
			}

			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				goto Query_Menu;  
			}	//ÏûÒô¼ü

			default: break;
		}///switch ½áÊø

	}
///////////////////////////////////////////////////////////////
PB_Menu:

		Flicker_Position = 0;

		dis_buff[0]=End_Addr/100;
		dis_buff[1]=End_Addr%100/10;
		dis_buff[2]=End_Addr%10;
		dis_buff[3]=LoopStart/100;
		dis_buff[4]=LoopStart%100/10;
		dis_buff[5]=LoopStart%10;
		dis_buff[6]=LoopEnd/100;
		dis_buff[7]=LoopEnd%100/10;
		dis_buff[8]=LoopEnd%10;
		
		temp2=End_Addr;
	  Clr_Display();
		Dis_PB_Bar();
		//Dis_PB_Text();
		while(Dis_Key_Buff_Flag)
		{  
			Delay1ms(30);
			Key_Scan();
			if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
			Key_Down_Flag=0;
			Key_Up_Flag=0;
    
			switch(Key_Value)
			{
				case Key_0:
				case Key_1:
				case Key_2:
				case Key_3:
				case Key_4:
				case Key_5:
				case Key_6:
				case Key_7:
				case Key_8:
				case Key_9:  
				{   
					dis_buff[Flicker_Position]=Key_Value;
					
					Dis_PB_Text();
					
					if( displayflag == 0)
					{
						if(Flicker_Position <2)  
							Flicker_Position++;
						else 
							Flicker_Position = 0;
					}
					else
					{
						if(Flicker_Position <8)  
							Flicker_Position++;
						else 
							Flicker_Position = 3;
					}
					
					Dis_PB_Text();

				break;
				}

				case Key_Query:                       //ÒÆÎ»
				{  
					if(LoopOpenFlag)
					{
						if(Flicker_Position <8)  
							Flicker_Position++;
						else 
							Flicker_Position = 0;			
					}
					else
					{
						if(Flicker_Position <2)  
							Flicker_Position++;
						else 
							Flicker_Position = 0;					
					}
							
					if(Flicker_Position>2)
						displayflag = 1;
					else 
						displayflag = 0;
					
					Dis_PB_Text();
					break; 
				} 	
				case Key_Cancel:                        //·µ»Ø
				{
					End_Addr=temp2;
					Close_Cur();
					goto Set_Menu1;
				}					
				case Key_Sure:                        
				{
						if(Flicker_Position>2)//ÏÔÊ¾¸¨Öú»ØÂ·1·¶Î§ÉèÖÃ
						{
							temp2=dis_buff[3]*100+dis_buff[4]*10+dis_buff[5];
							
							if ((temp2 <End_Addr)||(temp2==0))//Êý¾Ý³¬ÏÞÔò±¨¾¯ÌáÊ¾
							{
								Beep_Err();break;
							}
							
							if (temp2!=LoopStart)
							{
								LoopStart=temp2;

								buff[0]=LoopStart/256;
								buff[1]=LoopStart%256;
								Delay1ms(1);
								RW24XX(&buff[0],2,0x0B,0xA0);    //???EEPROM  ??40H??
								Delay1ms(1);
								for (i=0;i<256;i++)
								{	
									Set_Uart_Fault_Timer0(i);
								}
								for (i=0;i<64;i++)
								{ 
									Alarm_Flag[i]=0;
									Fault_Flag[i]=0;
								}
							}		
							
							temp2=dis_buff[6]*100+dis_buff[7]*10+dis_buff[8];
							
							if ((temp2>MaxEndAddr)||(temp2==0))//Êý¾Ý³¬ÏÞÔò±¨¾¯ÌáÊ¾
							{
								Beep_Err();break;
							}
							
							if (temp2!=LoopEnd)
							{
								LoopEnd=temp2;

								buff[0]=LoopEnd/256;
								buff[1]=LoopEnd%256;
								Delay1ms(1);
								RW24XX(&buff[0],2,0x0D,0xA0);    //???EEPROM  ??40H??
								Delay1ms(1);
								for (i=0;i<256;i++)
								{	
									Set_Uart_Fault_Timer0(i);
								}
								for (i=0;i<64;i++)
								{ 
									Alarm_Flag[i]=0;
									Fault_Flag[i]=0;
								}
							}		
							goto PB_Menu2;
							
						}
						else//ÏÔÊ¾Ö÷»ú»ØÂ··¶Î§ÉèÖÃ
						{
							temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
						
							if ((temp2>MaxEndAddr)||(temp2==0))//Êý¾Ý³¬ÏÞÔò±¨¾¯ÌáÊ¾
							{
								Beep_Err();break;
							}
							
							if (temp2!=End_Addr)
							{
								End_Addr=temp2;

								buff[0]=End_Addr/256;
								buff[1]=End_Addr%256;
								Delay1ms(1);
								RW24XX(&buff[0],2,0x09,0xA0);    //???EEPROM  ??40H??
								Delay1ms(1);
								for (i=0;i<256;i++)
								{	
									Set_Uart_Fault_Timer0(i);
								}
								for (i=0;i<64;i++)
								{ 
									Alarm_Flag[i]=0;
									Fault_Flag[i]=0;
								}
							}		
					
							goto PB_Menu1;
						}
				}
				
		    default: 
					break;
	   }///switch ½áÊø

  }
  return;   
///////////////////////////////////////////////////

PB_Menu1: 	
   
	Key_Input_Value=0;
	Flicker_Position=0;
	temp=Shield_Flag[Key_Input_Value/8];
  Clr_Display();
	Dis_PB_Bar1();
	Dis_PB_Text1();

	while(Dis_Key_Buff_Flag)
	{  
		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
				case Key_1:
				case Key_2:
				case Key_3:
				case Key_4:
				case Key_5:
				case Key_6:
				case Key_7:
				case Key_8:
				case Key_9:				//Êý×Ö¼üÖ±½Ó·­µ½¶ÔÓ¦Ò³
				{   
					Flicker_Position=Key_Value-1;
					Key_Input_Value=0;
					temp2=Flicker_Position*35+Key_Input_Value;
					PB_Flag=Check_Shield_State(temp2);
					Dis_PB_Text1();
					break;
				}
				
				case Key_Add:     //ÉÏ·­
				case Key_Sub:     //ÏÂ·­ 					
				{   
					if (PB_Flag==1) 
						PB_Flag=0;  //ÆÁ±Îºó·µ»Ø1¡¡·ñÔò·µ»Ø0  
					else 
						PB_Flag=1;

					Dis_PB_Text1();
					break;
				}

				case Key_Query:                       //²éÑ¯ÒÆÎ»
				{   
					if(Flicker_Position < End_Addr/35)  
						Flicker_Position++;
					else 
						Flicker_Position = 0;
					Key_Input_Value=0;

					temp2=Flicker_Position*35+Key_Input_Value;
					PB_Flag=Check_Shield_State(temp2);

					Dis_PB_Text1();
					break;
				}
				case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
				{   
					goto Set_Menu1;
				}

				case Key_Menu_Sure:                          //È·ÈÏ
				{
					if (PB_Flag!=Check_Shield_State(temp2))  //Èç¹û×´Ì¬¸Ä±äÁË£¬±£PBÖµ
					 {  
							Set_Shield_Flag(temp2,PB_Flag);
							//EA=0;
							Delay1ms(1);						 
							RW24XX(&Shield_Flag[temp2/8],1,(0x80+temp2/8),0xA0);    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
							Delay1ms(1);
							Set_Uart_Fault_Timer0(temp2);
							Set_Fault_Flag(temp2,0); //Í¨Ñ¶¹ÊÕÏÖÃ¹ÊÕÏ±êÖ¾
							Set_Alarm_Flag(temp2,0); 
							//EA=1;														
						}
						 //ÏÔÊ¾ÏÂÒ»Â·	 
						if (temp2<(End_Addr-1))
						{
								temp2++;
						 }
						else temp2=0;

						Flicker_Position=temp2/35;
						Key_Input_Value=temp2%35;
						PB_Flag=Check_Shield_State(temp2);

						Dis_PB_Text1();
					break;
				}
			default: break;
		}///switch ½áÊø

	}
	return;  	
	///////////////////////////////////////////////////

PB_Menu2: 	
   
	Key_Input_Value=0;
	Flicker_Position=0;
	temp=Shield_Flag[Key_Input_Value/8];
	
	
	temp2=Flicker_Position*35+Key_Input_Value+LoopStart;	
	PB_Flag=Check_Shield_State(temp2-1);
	Clr_Display();
	Dis_PB_Bar2();
	Dis_PB_Text2();
	while(Dis_Key_Buff_Flag)
	{  
		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
				case Key_1:
				case Key_2:
				case Key_3:
				case Key_4:
				case Key_5:
				case Key_6:
				case Key_7:
				case Key_8:
				case Key_9:				//Êý×Ö¼üÖ±½Ó·­µ½¶ÔÓ¦Ò³
				{   
					Flicker_Position=Key_Value-1;
					Key_Input_Value=0;
					temp2=Flicker_Position*35+Key_Input_Value+LoopStart;
					
					PB_Flag=Check_Shield_State(temp2-1);
					Dis_PB_Text2();

					break;
				}
				
				case Key_Add:     //ÉÏ·­
				case Key_Sub:     //ÏÂ·­ 					
				{   
					if (PB_Flag==1) 
						PB_Flag=0;  //ÆÁ±Îºó·µ»Ø1¡¡·ñÔò·µ»Ø0  
					else 
						PB_Flag=1;

					Dis_PB_Text2();
					break;
				}

				case Key_Query:                       //²éÑ¯ÒÆÎ»
				{   
					if(Flicker_Position < (LoopEnd-LoopStart)/35)  
						Flicker_Position++;
					else 
						Flicker_Position = 0;
					
					Key_Input_Value=0;

					temp2=Flicker_Position*35+Key_Input_Value+LoopStart;
					PB_Flag=Check_Shield_State(temp2-1);

					Dis_PB_Text2();
					break;
				}
				case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
				{   
					goto Set_Menu1;
				}

				case Key_Menu_Sure:                          //È·ÈÏ
				{
					 if (PB_Flag!=Check_Shield_State(temp2-1))  //Èç¹û×´Ì¬¸Ä±äÁË£¬±£PBÖµ
					 {  
							Set_Shield_Flag(temp2-1,PB_Flag);
							//EA=0; 
						 	Delay1ms(1);
							RW24XX(&Shield_Flag[(temp2-1)/8],1,(0x80+(temp2-1)/8),0xA0);    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
							Delay1ms(1);
							Set_Uart_Fault_Timer0(temp2-1);
							Set_Fault_Flag(temp2-1,0); //Í¨Ñ¶¹ÊÕÏÖÃ¹ÊÕÏ±êÖ¾
							Set_Alarm_Flag(temp2-1,0); 
							//EA=1;														
						}
						 //ÏÔÊ¾ÏÂÒ»Â·	 
						if (temp2<LoopEnd)
						{
								temp2++;
						}
						else
						{							
							temp2=LoopStart;
						}
						
						Flicker_Position=(temp2-LoopStart)/35;
						Key_Input_Value=(temp2-LoopStart)%35;
						PB_Flag=Check_Shield_State(temp2-1);

						Dis_PB_Text2();
					break;
				}
			default: break;
		}///switch ½áÊø

	}
	return;  
////////////////////////////////////////////////////////////
	
System_Set:
	temp=Print_State;
	Key_Input_Value=0;
	Flicker_Position=0;
	Clr_Display();
	Dis_SystemP_Bar();
	Dis_SystemP_Text1();

	while(Dis_Key_Buff_Flag)
	{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{  
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:    
				break;

			case Key_Add: //¼Ó 
			{
				if (Print_State==0) 
					Print_State=0xAA;  //0¹Ø±Õ£¬AA´ò¿ª
				else 
					Print_State=0;

				Dis_SystemP_Text1();
				break;
			}
			case Key_Sub: //¼õ                      
			{
				if (Print_State==0) 
					Print_State=0xAA;  //0¹Ø±Õ£¬AA´ò¿ª
				else 
					Print_State=0;

				Dis_SystemP_Text1();
				break;
			}

			case Key_Query:                       //²éÑ¯ÒÆÎ»
				break;
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{   
				Print_State = temp;
				goto Set_Menu1;
			}
      case Key_Menu_Sure:                          //È·ÈÏ
			{
				//±£´æ¼ä¸ôÊ±¼äµÄÖµ
				buff[0]=Print_State;
				//EA=0;
				Delay1ms(1);
				flag=RW24XX(&buff[0],1,0x15,0xA0);
				Delay1ms(1);
				//EA=1;
				if (!flag) 
					Dis_SetPOK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else 
					Dis_SetPErr();

				Delay1ms(1000);
				goto Set_Menu1;                 
			}

		    default: break;
	   }///switch ½áÊø

  }
return; 
	
Loop_Set:
	temp=LoopOpenFlag;
	Key_Input_Value=0;
	Flicker_Position=0;
	Clr_Display();
	Dis_Loop_Bar();
	Dis_Loop_Text1();

	while(Dis_Key_Buff_Flag)
	{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{  
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:    
				break;

			case Key_Add: //¼Ó 
			{
				if (LoopOpenFlag==0) 
					LoopOpenFlag=1;  //0¹Ø±Õ£¬AA´ò¿ª
				else 
					LoopOpenFlag=0;

				Dis_Loop_Text1();
				break;
			}
			case Key_Sub: //¼õ                      
			{
				if (LoopOpenFlag==0) 
					LoopOpenFlag=1;  //0¹Ø±Õ£¬AA´ò¿ª
				else 
					LoopOpenFlag=0;

				Dis_Loop_Text1();
				break;
			}

			case Key_Query:                       //²éÑ¯ÒÆÎ»
				break;
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{   
				LoopOpenFlag = temp;
				goto Set_Menu2;
			}
      case Key_Menu_Sure:                          //È·ÈÏ
			{
				//±£´æ¼ä¸ôÊ±¼äµÄÖµ
				buff[0]=LoopOpenFlag;
				Delay1ms(1);
				flag=RW24XX(&buff[0],1,0x1E,0xA0);
				Delay1ms(1);
				if (!flag) 
					Dis_SetPOK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else 
					Dis_SetPErr();

				Delay1ms(1000);
				goto Set_Menu2;                 
			}

		    default: break;
	   }///switch ½áÊø

  }
return; 

Install_Addr://Éè±¸°²×°µØÖ·ÉèÖÃ
	Flicker_Position = 3;

	dis_buff[0]=InstallAddr/100;
	dis_buff[1]=InstallAddr%100/10;
	dis_buff[2]=InstallAddr%100%10;
	
	if(InstallAddr<512)
	{
		temp2 = InstallAddr-1;
	}

	if(address[temp2][0]>99)
	{
			address[temp2][0] = 0;
	}
	
	dis_buff[3]=address[temp2][0]/10;
	dis_buff[4]=address[temp2][0]%10;
	
	if(address[temp2][1]>99)
	{
			address[temp2][1] = 0;
	}
	dis_buff[5]=address[temp2][1]/10;
	dis_buff[6]=address[temp2][1]%10;
	
	if(address[temp2][2]>99)
	{
			address[temp2][2] = 0;
	}
	dis_buff[7]=address[temp2][2]/10;
	dis_buff[8]=address[temp2][2]%10;
	Clr_Display();	
	Dis_Addr_Bar();
	Dis_Addr_Text1();

	while(Dis_Key_Buff_Flag)
	{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{  
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
				dis_buff[Flicker_Position]=Key_Value;
				Dis_Addr_Text1();
				if(Flicker_Position<8)
					Flicker_Position++;
				else
					Flicker_Position=0;

				Dis_Addr_Text1();
			
				break;

			case Key_Add: //¼Ó 
			{
				if(Flicker_Position<8)
					Flicker_Position++;
				else
					Flicker_Position=0;
				
				Dis_Addr_Text1();
				break;
			}
			case Key_Sub: //¼õ                      
			{
				if(Flicker_Position>0)
					Flicker_Position--;
				else
					Flicker_Position=8;

				Dis_Addr_Text1();
				break;
			}

			case Key_Query:                       //²éÑ¯ÒÆÎ»
			{
				if(Flicker_Position<8)
					Flicker_Position++;
				else
					Flicker_Position=0;
				
				Dis_Addr_Text1();
				break;
			}
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{   
				Flicker_Position = 0;
				Close_Cur();
				goto Set_Menu1;
			}
      case Key_Menu_Sure:                          //È·ÈÏ
			{
				InstallAddr = dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
				
				if(InstallAddr>0)
				{
					temp2 = InstallAddr-1;
				}
				
				if(temp2 < 512)
				{
					address[temp2][0] = dis_buff[3]*10+dis_buff[4];
					address[temp2][1] = dis_buff[5]*10+dis_buff[6];
					address[temp2][2] = dis_buff[7]*10+dis_buff[8];
				
					buff[0]=address[temp2][0];
					buff[1]=address[temp2][1];
					buff[2]=address[temp2][2];
				}
				Delay1ms(1);
				flag=RW24XX(&buff[0],3,0x8600+temp2*3,0xA0);
				Delay1ms(1);
				if (!flag) 
					Dis_SetPOK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else 
					Dis_SetPErr();

				Delay1ms(100);
				if( InstallAddr < 512 )
					InstallAddr++;
				else
					InstallAddr=0;
				goto Install_Addr;                 
			}

		    default: break;
	   }///switch ½áÊø

  }
return; 
	
Read_TCQ_State: //ÏÔÊ¾Ì½²âÅäÖÃ   
   Flicker_Position=0;
 
   dis_buff[0]=0;
   dis_buff[1]=0;
   dis_buff[2]=0;
	 Clr_Display();
   Dis_TCQ_State_Bar1();
  // Dis_TCQ_State_Text1();

   while(Dis_Key_Buff_Flag)
   {  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;

    switch(Key_Value)
	 {
          case Key_0:
          case Key_1:
          case Key_2:
          case Key_3:
          case Key_4:
          case Key_5:
          case Key_6:
          case Key_7:
          case Key_8:
          case Key_9:  
					{
						dis_buff[Flicker_Position] =Key_Value;  
						Dis_TCQ_State_Text1();
						if (Flicker_Position<2) Flicker_Position++;
						else Flicker_Position=0;
						
						Plase_Check();  //ceshi0512
						break;
					}
					case Key_Add: 
          {
               temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
               
							 if(temp2<512) 
								 temp2++;
               else 
								 temp2=1;
							 
               dis_buff[0]=temp2/100;
               dis_buff[1]=temp2%100/10;
               dis_buff[2]=temp2%10;
               Dis_TCQ_State_Text1();
               Flicker_Position=1;
							
							 Plase_Check();  //ceshi0512
               break;

           }  
					case Key_Sub:      						
					{   
						temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
						if(temp2>1) 
							temp2--;
						else 
							temp2=512;
						dis_buff[0]=temp2/100;
						dis_buff[1]=temp2%100/10;
						dis_buff[2]=temp2%10;
						Dis_TCQ_State_Text1();
						Flicker_Position=1;
						
						Plase_Check();  //ceshi0512
						break;
					}
					case Key_Query:
					{
						if (Flicker_Position<3) 
							Flicker_Position++;
						else 
							Flicker_Position=0;
						break;
					}  
         
          case Key_Cancel://ÏûÒô¡¢·µ»Ø
					{   				
						goto Set_Menu1;					 
					}
		
          case Key_Menu_Sure://È·ÈÏ
		      {           
						Function_Flag=6;
						TCQ_Return_Timer=0;
						Clear_Read_State();  
							
						//CanSendWork();	//È·±£CANÊý¾Ý·¢ËÍ£¬³ÌÐòµÈ´ý²»ÄÜ½øÈë100ºÁÃ×º¯Êý
						canflag=3;				//TIMERÖÐ²éÑ¯
						
						while(TCQ_Return_Timer<40)//2S 
						{
							WDOG();
							
							if(ReceiveFlag == 2)//´¦Àí485À©Õ¹»ØÂ·µÄÊý¾Ý
							{
								RS485DataPro();
								ReceiveFlag = 0;
							}
		
							if (TCQ_Return_OK==1) 
								break;
						}    					
						
						if (TCQ_Return_OK==1)   
						{
							Dis_TCQ_State_Return(); 
							TCQ_Return_OK=0;
							canflag=0;
							ReceivePoint = 0;
							ReceiveFlag = 0;
						}
						else//¶ÁÈ¡Ê§°Ü
						{
							Read_Error();
						}
			
						Function_Flag=1;
						break;
	         }
		    default: 
					break;
	   }///switch ½áÊø

  }
  return;  
////////////////////////////////////////////////
LD_Test_Menu:  //Áª¶¯²âÊÔ=ÊÖ¶¯²âÊÔÍÑ¿Û
		// LD_State=P4;//±£´æµ±Ç°¼ÌµçÆ÷×´Ì
		Flicker_Position =0;
		Key_Input_Value=0;
		dis_buff[0]=0;
		dis_buff[1]=0;
		dis_buff[2]=0;
	  Clr_Display();
		Dis_LD_Bar();

		while(Dis_Key_Buff_Flag)
		{  
			Delay1ms(30);
			Key_Scan();
			if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
			Key_Down_Flag=0;
			Key_Up_Flag=0;

			switch(Key_Value)
			{
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
			{   
				dis_buff[Flicker_Position] =Key_Value; 
				Key_Input_Value=2;
				Dis_LD_Text();
				if (Flicker_Position<2) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				break;
			}
			
			case Key_Add:                           //Ôö¼Ó
			{  
				if (Key_Input_Value<1)    Key_Input_Value++;
				else   Key_Input_Value = 0;  
				Dis_LD_Text();
				break;
			}

			case Key_Sub:                            // ¼õ
			{
			if (Key_Input_Value>0)    Key_Input_Value--;
			else   Key_Input_Value = 1;  
			Dis_LD_Text();
			break;
			}
			case Key_Query:
			{
				if (Key_Input_Value<3) 
					Key_Input_Value++;
				else 
					Key_Input_Value=0;
				Dis_LD_Text();
				break;
			}  

		case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
		{
			//P4 =LD_State;
			goto Set_Menu1;
		}

		case Key_Menu_Sure://È·ÈÏ
		{
			if(Key_Input_Value==0) //Ö÷¿ØÉè±¸¿ªÆô
			{ 
				KC1_ON();
				KC2_ON();
				Set_World_Flag_Flag(2,1);//Êä³öÖ¸Ê¾µÆÁÁ
				Dis_State_LED();//×´Ì¬Ö¸Ê¾µÆÏÔÊ¾
			}
			else if(Key_Input_Value==1)//Ö÷¿ØÉè±¸¹Ø±Õ
			{ 
				KC1_OFF();
				KC2_OFF();
				Set_World_Flag_Flag(2,0);//Êä³öÖ¸Ê¾µÆÃð
				Dis_State_LED();//×´Ì¬Ö¸Ê¾µÆÏÔÊ¾
			}
			else if ((Key_Input_Value==2)||(Key_Input_Value==3))//Ì½²âÆ÷ID001 ¿ªÆô ¹Ø±Õ
			{
				Function_Flag=5;
				
				CanSendWork();//CAN·¢ËÍº¯Êý
			}

			break;
		}
		default: 
			break;
		}///switch ½áÊø

	}
//////////////////////////////////////////////////
Test_FL: //ÊµÊ±ÏÔÊ¾²âÁ¿Öµ
		Flicker_Position=0;

		dis_buff[0]=0;
		dis_buff[1]=0;
		dis_buff[2]=0;
    Clr_Display();
		Dis_Test_Fl_Bar1();

		while(Dis_Key_Buff_Flag)
		{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
			{
				dis_buff[Flicker_Position] =Key_Value;  
				Dis_Test_Fl_Text1();
				if (Flicker_Position<2) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				Plase_Check();  //ceshi0512
				break;
			}
	    case Key_Add: //×Ô¼ì
			{
				 temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
				 if(temp2<512) 
					 temp2++;
				 else 
					 temp2=1;
				 dis_buff[0]=temp2/100;
				 dis_buff[1]=temp2%100/10;
				 dis_buff[2]=temp2%10;
				 Dis_Test_Fl_Text1();
				 Flicker_Position=1;	
				 Plase_Check();  //ceshi0512
				 break;

			 } 
				case Key_Sub:     //¸´Î»                      
				{   
					temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
					if(temp2>1) temp2--;
					else temp2=512;
					dis_buff[0]=temp2/100;
					dis_buff[1]=temp2%100/10;
					dis_buff[2]=temp2%10;
					Dis_Test_Fl_Text1();
					Flicker_Position=1;
					Plase_Check();  //ceshi0512
					break;
				}
				case Key_Query:
				{
					if (Flicker_Position<3) Flicker_Position++;
					else Flicker_Position=0;
					break;
				}  

				case Key_Cancel://ÏûÒô¡¢·µ»Ø
				{   
					goto Set_Menu1;
				}

				case Key_Menu_Sure://È·ÈÏ
				{
					Function_Flag=7;
					TCQ_Return_Timer=0;
					Clear_Read_Fl();
					
					canflag = 3;//·¢ËÍCANÃüÁî£¬¶ÁÈ¡´«¸ÐÆ÷×´Ì¬²âÊÔ
					//while ((!Key_Down_Flag)||(!Key_Up_Flag))             
					while(TCQ_Return_Timer<40)//2S 
					{
						WDOG();	
		
						if(ReceiveFlag == 2)//´¦Àí485À©Õ¹»ØÂ·µÄÊý¾Ý
						{
							RS485DataPro();
							ReceiveFlag = 0;
						}
						
						if (TCQ_Return_OK==1) 
								break;		  
					}						
						
					if(TCQ_Return_OK==1) 
					{
						Dis_Test_Fl_Return();
						TCQ_Return_OK=0;
						canflag=0;
						ReceivePoint = 0;
						ReceiveFlag = 0;
					}
					else
					{
						Read_Error();
					}
						
					Key_Scan();
					Key_Down_Flag=0;
					Key_Up_Flag=0;
					Function_Flag=1;
					break;
				}
		    default: break;
	   }///switch ½áÊø

  }
  return;	
	
////////////////////////////////////////////////
Timer_Menu:
	Flicker_Position = 0;

	Read_RTC();
	
	DateTimer[0]= Real_Time.year%2000;//Äê
	DateTimer[1]= Real_Time.month;//ÔÂ
	DateTimer[2]= Real_Time.day;//ÈÕ
	DateTimer[3]= Real_Time.hour;//Ê±
	DateTimer[4]= Real_Time.min;//·Ö
	
	for (i=0;i<6;i++)
	{
		dis_buff[2*i]  =DateTimer[i]/10;//Äê
		dis_buff[2*i+1]=DateTimer[i]%10;
	}
  Clr_Display();
	Dis_Set_System_Timer_Promt();

	while(Dis_Key_Buff_Flag)
	{  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;
    
    switch(Key_Value)
	 {     
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:
			{   
				dis_buff[Flicker_Position]=Key_Value;
				Dis_Set_System_Timer();
				if(Flicker_Position < 12)  
					Flicker_Position++;
				else 
					Flicker_Position = 0;
				break;
			}
        
			case Key_Query:                       //¹¦ÄÜÒÆÎ»
			{   
				Dis_Set_System_Timer();
				if(Flicker_Position < 11)  
					Flicker_Position++;
				else 
					Flicker_Position = 0;
				
				break;
			}
			
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
					goto Set_Menu1;			 
			 }
		
      case Key_Menu_Sure:                          //È·ÈÏ
			{
				temp=dis_buff[0]*10+dis_buff[1];//Äê
				DateTimer[0]=temp;

				temp=dis_buff[2]*10+dis_buff[3];//ÔÂ
				if (temp>12)   
				{
						Beep_Err();
						Flicker_Position=1;
						Dis_Set_System_Timer();
						break;
				 }
				else
				{
					DateTimer[1]=temp;
				}
				
				temp=dis_buff[4]*10+dis_buff[5];//ÈÕ
				if (temp>31)   
				{
						Beep_Err();
						Flicker_Position=3;
						Dis_Set_System_Timer();
						break;
				 }
				else   DateTimer[2]=temp;

				temp=dis_buff[6]*10+dis_buff[7];//Ê±
				if (temp>23)   
				{
						Beep_Err();
						Flicker_Position=5;
						Dis_Set_System_Timer();
						break;
				 }
				else   DateTimer[4]=temp;

				temp=dis_buff[8]*10+dis_buff[9];//·Ö
				if (temp>59)   
				{
						Beep_Err();
						Flicker_Position=7;
						Dis_Set_System_Timer();
						break;
				 }
				else   DateTimer[5]=temp;
			 
				temp=dis_buff[10]*10+dis_buff[11];//Ãë
				if (temp>59)   
				{
						Beep_Err();
						Flicker_Position=9;
						Dis_Set_System_Timer();
						break;
				 }
				else   DateTimer[6]=temp;

				Real_Time.year=2000+DateTimer[0];//Äê
				Real_Time.month=DateTimer[1];//ÔÂ
				Real_Time.day=DateTimer[2];//ÈÕ
				 //DateTimer[3]//ÖÜ
				Real_Time.hour=DateTimer[4];//Ê±
				Real_Time.min=DateTimer[5];//·Ö
				Real_Time.sec= 30;//Ãë
				 
				Set_RTC(Real_Time);
				Dis_OK(); 
				Delay1ms(1000);
				goto Set_Menu1;                 
				}
		    default: break;
	   }///switch ½áÊø

  }
return;   
	
ShowFrq_Menu:
 
   temp=ShowFrq;
   Clr_Display();
   Dis_ShowFrq_Bar();
   Dis_ShowFrq_Text1();

   while(Dis_Key_Buff_Flag)
   {  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;
    
    switch(Key_Value)
	 {  
     
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:
			{   
				ShowFrq=Key_Value;
				Dis_ShowFrq_Text1();
				break;
			}
			case Key_Add:
			{
				if( ShowFrq < 9)
						ShowFrq++;
				else 
					 ShowFrq = 1;
				
				Dis_ShowFrq_Text1();
				break;
			}
			case Key_Sub:
			{
				if( ShowFrq > 1 )
					ShowFrq--;
				else
					ShowFrq=9;
				
				Dis_ShowFrq_Text1();
				break;
			}
         
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{   
				ShowFrq = temp;

				goto Set_Menu1;
			}

			case Key_Menu_Sure:                          //È·ÈÏ
			{
				//±£´æ¼ä¸ôÊ±¼äµÄÖµ
				buff[0]=ShowFrq;
				//EA=0;
				Delay1ms(1);
				flag=RW24XX(&buff[0],1,0x17,0xA0);
				Delay1ms(1);
				//EA=1;
				if (!flag) 
					Dis_OK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else 
					Dis_Err1();

				Delay1ms(1000);
				goto Set_Menu1;                 
			}

			default: break;
	   }///switch ½áÊø

  }
	return; 

////////////////////////////////////////////////
Set_Addr:
		Flicker_Position=0;
		dis_buff[0]=Self_Addr/10;
		dis_buff[1]=Self_Addr%10;
    Clr_Display();
		Dis_SetAddr_Bar();
		Dis_SetAddr_Text1();

		while(Dis_Key_Buff_Flag)
		{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:
			{   
				dis_buff[Flicker_Position]=Key_Value;
				Dis_SetAddr_Text1();
				if(Flicker_Position ==0)  
					Flicker_Position=1;
				else 
					Flicker_Position = 0;
				break;
			}
        
	    
			case Key_Query:                            // ¸´Î»
			{   
				Dis_SetAddr_Text1();
				if(Flicker_Position ==0)  
					Flicker_Position=1;
				else 
					Flicker_Position = 0;
				break;
			}

			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{   
				goto Set_Menu1;
			}
		
			case Key_Menu_Sure:                          //È·ÈÏ
			{
				//±£´æ¼ä¸ôÊ±¼äµÄÖµ
				buff[0]=dis_buff[0]*10+dis_buff[1];
				Delay1ms(1);
				flag=RW24XX(&buff[0],1,0x16,0xA0);
				Delay1ms(1);
				if (!flag) {Dis_OK();Self_Addr=buff[0];}    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else Dis_Err1();

				Delay1ms(1000);
				goto Set_Menu1;                 
			}
  
		    default: break;
	   }///switch ½áÊø

  }
  return;   


//////////////////////////////////
Pass2_Menu:
   
   Flicker_Position = 0;
   dis_buff[0]=1;
   dis_buff[1]=2;
   dis_buff[2]=3;
   dis_buff[3]=4;
   Clr_Display();
   Dis_Pass2_Promt();
		//Dis_Pass(); 
   while(Dis_Key_Buff_Flag)
   {  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;
    
    switch(Key_Value)
	 {	 
          case Key_0:
          case Key_1:
          case Key_2:
          case Key_3:
          case Key_4:
          case Key_5:
          case Key_6:
          case Key_7:
          case Key_8:
          case Key_9:  
					{
						dis_buff[Flicker_Position] =Key_Value;  
						Dis_Pass();
						if (Flicker_Position<3) Flicker_Position++;
						else Flicker_Position=0;
						break;
					}
					
					case Key_Add: 
					{
						if(dis_buff[Flicker_Position] < 9)    
							dis_buff[Flicker_Position]++;
						else   
							dis_buff[Flicker_Position] = 0; 
						Dis_Pass(); 
						break;
					}
					case Key_Sub:                            // ¼õ
					{
						if(dis_buff[Flicker_Position] > 0)    
							dis_buff[Flicker_Position]--;
						else   
							dis_buff[Flicker_Position] = 9;  
						Dis_Pass(); 
						break;
					}
					
					case Key_Query:
					{
						if (Flicker_Position<3) Flicker_Position++;
						else Flicker_Position=0;
						break;
					}  

					case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
					{
						goto  Set_Menu1;
					}
		
           case Key_Menu_Sure:                          //È·ÈÏ
					{

						if (((dis_buff[0]==Pass2[0])&&(dis_buff[1]==Pass2[1])&&(dis_buff[2]==Pass2[2])&&(dis_buff[3]==Pass2[3]))
						||((dis_buff[0]==5)&&(dis_buff[1]==8)&&(dis_buff[2]==1)&&(dis_buff[3]==9))
						||((dis_buff[0]==5)&&(dis_buff[1]==9)&&(dis_buff[2]==1)&&(dis_buff[3]==0)))//³¬¼¶ÃÜÂë
						//ÃÜÂëÕýÈ·
						{   
							if((dis_buff[0]==5)&&(dis_buff[1]==9)&&(dis_buff[2]==1)&&(dis_buff[3]==0))//ÊäÈë5910³õÊ¼»¯µØÖ·¿Õ¼ä
							{
								buff[0]=0;
								buff[1]=0;
								buff[2]=0;
					
								for(i=0;i<512;i++)
								{
									Delay1ms(1);
									flag=RW24XX(&buff[0],3,0x8600+i*3,0xA0);
									Delay1ms(1);
									address[i][0] = 0;
									address[i][1] = 0;
									address[i][2] = 0;
									Delay1ms(8);
								}
							}	
							
							Close_Cur();//¹Ø±Õ¹â±ê
							menu=0;
							goto Set_Menu2;
						}
						else 
						{
							Dis_Err(); //ÃÜÂë²»ÕýÈ·ÏÔÊ¾Err·µ»Ø½çÃæ
							Beep_Err();
								 
							goto Pass2_Menu;
						}
					}
		    default: break;
	   }///switch ½áÊø

  }
  return;   

////////////////////////////////////	
////////////////////////////////////
Set_Menu2:

   
	Clr_Display();
	Dis_Main_Menu2();

	while(Dis_Key_Buff_Flag)
	{  
		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{   
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			{   
				menu=Key_Value-1;
				Dis_Main_Menu2();
				break;
			}
			
			case Key_Add:                           //Ôö¼Ó
			{
				if(menu > 0)    
					menu--;
				else   
					menu = 3;  

				Dis_Main_Menu2();
				break;
			}

			case Key_Sub:                            // ¼õ
			{
				if(menu < 3)    
					menu++;
				else   
					menu = 0; 
				Dis_Main_Menu2();
				break;
			}

			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				menu=8;
				goto Set_Menu1;
			}

			case Key_Menu_Sure:                          //È·ÈÏ
			{
				if (menu==0) goto P1_Set;//¸ü¸ÄÒ»¼¶ÃÜÂë
				else if (menu==1) goto P2_Set;//¸ü¸Ä¶þ¼¶ÃÜÂë
				else if (menu==2) goto CLR_REC;//Çå¼ÇÂ¼
				else if (menu==3) goto Loop_Set;//ÏµÍ³³õÊ¼»¯   
				break;
			}
			default: break;
		}///switch ½áÊø

	}
	

////////////////////////////////////////////////
P1_Set:   
   Flicker_Position = 0;

   for (i=0;i<4;i++)  { dis_buff[i]=Pass1[i]; }
	 Clr_Display();
   Dis_SetPass1_Promt();
  // Dis_Pass();
   while(Dis_Key_Buff_Flag)
   {  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;
    
    switch(Key_Value)
		{    
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
			{
				dis_buff[Flicker_Position] =Key_Value;  
				Dis_SetPass();
				if (Flicker_Position<3) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				break;
			}

			//case Key_Move:
			case Key_Query:
			{
				if (Flicker_Position<3) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				break;
			}  


			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				Close_Cur();
				goto Set_Menu2;
			}

			case Key_Sure:                          //È·ÈÏ
			{
				Pass1[0]=dis_buff[0];
				Pass1[1]=dis_buff[1];
				Pass1[2]=dis_buff[2];
				Pass1[3]=dis_buff[3];
				//EA=0;
				Delay1ms(1);
				flag=RW24XX(dis_buff,4,0x01,0xA0);	//Ò»¼¶ÃÜÂë´æ´¢Î»ÖÃ
				Delay1ms(1);
				Delay1ms(10);
				//EA=1;
				if (!flag) 
					Dis_OK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else 
					Dis_Err1();

				Delay1ms(1000);
				goto Set_Menu2;  
			}
			default: 
				break;
		}///switch ½áÊø
  }
 ////////////////////////////////////////////////
P2_Set:    
	Flicker_Position = 0;

	for (i=0;i<4;i++)  { dis_buff[i]=Pass2[i]; }
  Clr_Display();
	Dis_SetPass2_Promt();
	// Dis_SetPass1();
	while(Dis_Key_Buff_Flag)
	{  

		Delay1ms(30);
		Key_Scan();
		if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
		Key_Down_Flag=0;
		Key_Up_Flag=0;

		switch(Key_Value)
		{
			case Key_0:
			case Key_1:
			case Key_2:
			case Key_3:
			case Key_4:
			case Key_5:
			case Key_6:
			case Key_7:
			case Key_8:
			case Key_9:  
			{
				dis_buff[Flicker_Position] =Key_Value;  
				Dis_SetPass();
				if (Flicker_Position<3) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				break;
			}

			//case Key_Move:
			case Key_Query:
			{
				if (Flicker_Position<3) 
					Flicker_Position++;
				else 
					Flicker_Position=0;
				break;
			}  


			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				Close_Cur();
				goto Set_Menu2;
			}


			case Key_Sure:                          //È·ÈÏ
			{
				Pass2[0]=dis_buff[0];
				Pass2[1]=dis_buff[1];
				Pass2[2]=dis_buff[2];
				Pass2[3]=dis_buff[3];
				//EA=0;
				flag=RW24XX(dis_buff,4,0x05,0xA0);		//¶þ¼¶ÃÜÂë´æ´¢Î»ÖÃ
				Delay1ms(10);
				//EA=1;
				if (!flag) Dis_OK();    //±£´æµ½EEPROM  µØÖ·0014H¿ªÊ¼
				else Dis_Err1();

				Delay1ms(1000);
				goto Set_Menu2;  
			}
			default: break;
		}///switch ½áÊø

  }
/////////////////////////////////////////////////////
CLR_REC:  //Çå±¨¾¯¼ÇÂ¼¼°ÉÏµç¼ÇÂ¼
   Clr_Display();
   Clear_REC_Sure();   
   while(Dis_Key_Buff_Flag)
   {  

    Delay1ms(30);
    Key_Scan();
    if ((!Key_Down_Flag)||(!Key_Up_Flag)) continue;
    Key_Down_Flag=0;
    Key_Up_Flag=0;
    
		switch(Key_Value)
		{
			case Key_Cancel:                        //ÏûÒô¡¢·µ»Ø
			{
				goto  Set_Menu2;
			}

			case Key_Sure:                          //È·ÈÏ
			{
				Clear_REC_Promt();
				CLR_Record();
				Delay1ms(800);
				Clear_REC_OK();
				Save_Event_Record(4);//1:´ú±í¿ª»úÉÏµç  2£º´ú±í¹Ø»ú   3£º¸´Î»   4£ºÇå³ý¼ÇÂ¼   5£º³õÊ¼»¯
				Delay1ms(1000);
				goto Set_Menu2; 
			}
			default: 
				break;
		}///switch ½áÊø

  } 
//-----------------------------------------
	
}

