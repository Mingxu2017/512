#include "stm32f10x.h"		/* 如果要用ST的固件库，必须包含这个文件 */
#include "Declare.h"
uint8_t Bat_Low_Flag=0;
uint8_t CD_Flag=0;//充电标志

void Sum_Shield(void)
{
  uint8_t i,j,pn,temp;

    pn=0;
    for (j=0;j<(End_Addr-1)/8;j++)//
    {   temp=Shield_Flag[j];
        for (i=0;i<8;i++)
        {  if((temp&0x80)==0x80) pn++;
           temp=temp<<1;
         }
     }
   
    temp=Shield_Flag[j];
    j=8-(End_Addr)%8;
    while(j--) temp=temp<<1;
    for (i=0;i<(End_Addr)%8;i++)
    { 
			  if((temp&0x80)==0x80) pn++;
        temp=temp<<1;
        
     }
    
    Shiled_Rec_Position=pn;
   
}

//Num在0--63之间
uint8_t Check_Shield_State(uint16_t Num)//屏蔽后返回1　否则返回0
{
   uint8_t temp,i,nbit;
  
   i= Num/8;  //第Num路，判断在第几个字节中
   temp=Shield_Flag[i];
   nbit=Num%8; //判断在第几位中
   temp =temp & (1 << nbit);
   if (temp==0) return 0;
   else return 1; 
   
}

uint8_t Check_Fault_State(uint16_t Num)//报警返回1
{
		uint8_t temp,i,nbit;

		i= Num/8;  //第Num路，判断在第几个字节中
		temp=Fault_Flag[i];
		nbit=Num%8; //判断在第几位中
		temp =temp & (1 << nbit);
		if (temp==0) return 0;
		else return 1; 
}
void Add_Uart_Fault_Timer(unsigned int Num,unsigned char m)//故障次数加1
{
    unsigned  char temp;

   temp=Uart_Err_Timer[Num/2];
   
   if ((Num%2)==1) 
      temp+=(m<<4);  
   else temp+=m;

   Uart_Err_Timer[Num/2]=temp;
}
//-------------------------------------------------
uint8_t  Uart_Fault_Timer(uint16_t Num)//计算故障次数
{
	unsigned  char temp;
	//第Num路，判断在第几个字节中
	temp=Uart_Err_Timer[Num/2];

	if ((Num%2)==1) 
		temp=temp>>4;   //高半字节

	temp=temp&0x0F;   
	return temp;
}

uint8_t Check_Alarm_State(uint16_t Num)//报警返回1
{
	uint8_t temp,i,nbit;

	i = Num/8;
	temp=Alarm_Flag[i];
	nbit = Num%8;
	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1; 
}

uint8_t Check_Alarm_State_16(uint16_t Num,uint8_t ch)//报警返回1
{
	
	uint16_t temp,i,nbit;

	i = Num;
	temp=Alarm_Flag_16[i];
	nbit = ch%16;
	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1; 
	
}


void Set_Shield_Flag(uint16_t Num,uint8_t flag)//将屏蔽标志置1或清0
{
   uint8_t x,temp,i,nbit;
   
   i= Num/8;  //第Num路，判断在第几个字节中
   temp=Shield_Flag[i];
   nbit=Num%8; //判断在第几位中
    
    x= 1 << nbit; 
   
    if (flag==1)   //=1将相应的位置1
    {
     
       temp=temp | x;
    } 
   else 
    {  x=0xFF-x;
       temp=temp & x;
     }
   Shield_Flag[i]=temp;
}

void Set_World_Flag_Flag(uint8_t Num,uint8_t flag)
{
	uint16_t nbit;
	uint16_t x,temp2;

	temp2=World_Flag;
	nbit=Num; //判断在第几位中

	x= 1 << nbit; 
   
	if (flag==1)   //=1将相应的位置1
	{
		temp2=temp2 | x;
	} 
	else 
	{  
		x=0xFFFF-x;
		temp2=temp2 & x;
	}
	World_Flag=temp2;
}


void Save_Event_Record(uint8_t type)
{
	uint8_t DataBuff[12];
	uint32_t Addr;

	if (SDRecount<99)SDRecount++; 
	else SDRecount=1;
	DataBuff[0]=SDRecount;
	Addr=0x1A;
	Delay1ms(1); 
	RW24XX(DataBuff,1,Addr,0xA0);
	Delay1ms(1);  

	DataBuff[1]=type;    

	DataBuff[2]= Real_Time.year%2000;//：年月日时分－－[5]..[9]?
	DataBuff[3]= Real_Time.month;//月
	DataBuff[4]= Real_Time.day;//日
	DataBuff[5]= Real_Time.hour;//时
	DataBuff[6]= Real_Time.min;//分

	Addr= 0x141 + (SDRecount-1) * 8;
	Delay1ms(1); 
	RW24XX(DataBuff,7,Addr,0xA0);
	Delay1ms(1); 
/*
	if (SDRecount<500){SDRecount ++;}//
	else  SDRecount=1;////故障记录总数
	
	DataBuff[0]=SDRecount/256;//高位  
	DataBuff[1]=SDRecount%256;//低位 
	Addr=0x1A;
	RW24XX(DataBuff,2,Addr,0xA0);//上电次数
	Delay1ms(2);  

	DataBuff[0]=type;    //1:代表开机上电  2：代表关机   3：复位   4：清除记录   5：初始化
	 
	DataBuff[3]= Real_Time.year%2000;//：年月日时分－－[5]..[9]?
	DataBuff[4]= Real_Time.month;//月
	DataBuff[5]= Real_Time.day;//日
	DataBuff[6]= Real_Time.hour;//时
	DataBuff[7]= Real_Time.min;//分
	//计算地址
	Addr= 0x18000 + (SDRecount-1) * 8;
	RW24XX(DataBuff,8,Addr,0xA0);
	Delay1ms(1); 
*/
}

//总报警 总故障 主电正常 主电故障  备电正常  备电故障 馈电指示 充电故障
//第7位   6        5        4        3          2        1       0
uint8_t Check_World_Flag_State(uint8_t nbit)//总标志返回1
{
		uint16_t temp;

		temp=World_Flag;
		temp =temp & (1 << nbit);
		if (temp==0) return 0;
		else return 1;  
}

void Save_Alarm_Record(uint8_t TCQ_ID,uint16_t Alarm_State,uint16_t type)
{
	uint8_t DataBuff[12],i,j;
	uint16_t Addr,temp2;
	uint8_t AlarmM[]={"512-16超限报警!"};
	uint8_t DtM[]={"2014-02-13 15:32"};
	
	DataBuff[2]=TCQ_ID/256;//地址高
	DataBuff[3]=TCQ_ID%256;//地址低

	DataBuff[5]= Real_Time.year%2000;//:年月日时分--[5]..[9]
	DataBuff[6]= Real_Time.month;
	DataBuff[7]= Real_Time.day;
	DataBuff[8]= Real_Time.hour;
	DataBuff[9]= Real_Time.min;


	
 for(i=0;i<16;i++)//每一通道
 {
		temp2=Alarm_State;

		if((temp2& (1<<i))==0) 
		{
			continue;
		}
		else
		{  
			if (AlarmRecount<999)//报警记录999条
			{
				AlarmRecount++;
			}
			else  
			{
				AlarmRecount=1;
			}
			//	AlarmRecount=1;	 
			DataBuff[0]=AlarmRecount/256;
			DataBuff[1]=AlarmRecount%256;; 
			Addr=0x18;
			Delay1ms(1);
			RW24XX(DataBuff,2,Addr,0xA0);
			Delay1ms(1);
			if((type& (1<<i))==0)  DataBuff[4]=0;
			else DataBuff[4]=i+1; 
			
			Addr= 0x502 + (AlarmRecount-1) * 16;
			DataBuff[10]=0x5A;
			Delay1ms(1);
			RW24XX(DataBuff,11,Addr,0xA0); 
			Delay1ms(1);
		}	
	}
 
	//------------------打印机功能--------------------------
		if(Print_State==0xAA)//打印机开启
		{
			temp2=DataBuff[2]*256+DataBuff[3];//探测器ID
			AlarmM[0]=temp2/100+0x30;
			AlarmM[1]=temp2%100/10+0x30;
			AlarmM[2]=temp2%10+0x30;
			AlarmM[4]= DataBuff[4]/10+0x30;	//回路号
			AlarmM[5]= DataBuff[4]%10+0x30;
			/*if(DataBuff[4]==0)
			{
				AlarmM[6]= 0xCE;
				AlarmM[7]= 0xC2;
				AlarmM[8]= 0xB6;
				AlarmM[9]= 0xC8;
			}
			else
			{
				AlarmM[6]= 0xC2;
				AlarmM[7]= 0xA9;
				AlarmM[8]= 0xB5;
				AlarmM[9]= 0xE7;
			}*/
			for (i=0;i<5;i++) //日期的转换
			{ 
				DtM[2+3*i]=DataBuff[5+i]/10+0x30;  //年
				DtM[3+3*i]=DataBuff[5+i]%10+0x30;  
			}
			PrintID++;		
			Begin_Print(PrintID,AlarmM,DtM);
			
	
		}

}

void Save_Fault_Record(uint16_t tcID,uint8_t type)
{
		unsigned char hz5[]={"主电故障"};
		unsigned char hz6[]={"备电故障"};
		unsigned char hz7[]={"充电故障"};
		//unsigned char DtM[]={"2014-02-13 15:32"};
		unsigned char DataBuff[12];//,i;
		unsigned int temp;
		unsigned int Addr;
		//uint8_t i=0;
		
		temp=FaultRecount;//故障记录总数
		DataBuff[0]=temp/256;//高位  
		DataBuff[1]=temp%256;//低位 
		Addr=0x1C;
		Delay1ms(1);
		RW24XX(DataBuff,2,Addr,0xA0);
		Delay1ms(5);
		DataBuff[2]=tcID/256;//故障类型
		DataBuff[3]=tcID%256;

		DataBuff[4]=type;	//故障类型 0 通讯故障1-16 回路故障 F0主电故障 F1备电故障 F2充电故障

		Read_RTC();
		DataBuff[4+1]= Real_Time.year%2000;//年--[5]..[9]?
    DataBuff[5+1]= Real_Time.month;
	  DataBuff[6+1]= Real_Time.day;
	  DataBuff[7+1]= Real_Time.hour;
	  DataBuff[8+1]= Real_Time.min;
	 
		//计算地址
		Addr= 0x4602 + (FaultRecount-1) * 16;
		Delay1ms(1);
		RW24XX(DataBuff,9+1,Addr,0xA0);
		// 数据长度 地址 功能码(01) 数据区(报警路数+报警浓度值+年月日时分)
		Delay1ms(1);

 /*
		if(Print_State==0xAA)//开启打印机功能
		{	
			for (i=0;i<5;i++) //日期的转换
			{ 
				DtM[2+3*i]=DataBuff[4+i]/10+0x30;  //年
				DtM[3+3*i]=DataBuff[4+i]%10+0x30;  
			}
			if (type==0xF0) //打印主电故障
			{
				PrintID++;
				Begin_Print(PrintID,hz5,DtM);
			}
			else if(type==0xF1)//打印备电故障
			{
				PrintID++; 
				Begin_Print(PrintID,hz6,DtM);
			}
		}
*/	
/*
   pn=Fault_Rec_Position;//故障部位总数
                     
   if (pn>10) pn=10;  
              
   Fault_Position[pn]=tcID;
              
   flag=0;
   for(k=0;k<(pn);k++)
    {
        if (Fault_Position[k]==tcID)
        {
            for(m=k;m<(pn);m++) Fault_Position[m]=Fault_Position[m+1];//相同的左移
            flag=1;
            break;
          }
                  
       }
    if (flag==1) Fault_RecP++;//有重复的不处理
    else 
    {
         Fault_Rec_Position++;
         if (pn==10)
         for(m=0;m<10;m++) Fault_Position[m]=Fault_Position[m+1];//相同的左移
      }
*/            
            

}

void Check_Fault_Alarm(void)//故障总数判断
{   
		uint16_t j,temp,cTemp;
		uint16_t i,pn;
//主机回路0~EndAddr
    for (i=0;i<End_Addr;i++)
    {
        if (Check_Shield_State(i))  continue;//被屏蔽,继续
       
				if(!Check_Fault_State(i))  //之前没有故障报警 
				{  
					if( End_Addr > 256 )
						cTemp = Max_Uart/2;
					else
						cTemp = Max_Uart;

					if ( Uart_Fault_Timer(i)>=cTemp )  //判断此时是否有故障了
					{   
						Set_Fault_Flag(i,1); //通讯故障置故障标志
						
						SendFunction[SendPtr.LoadCnt].Command = 1;
						SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
						SendFunction[SendPtr.LoadCnt].TDH = 1;
						SendFunction[SendPtr.LoadCnt].type = 0x41;
						SendPtr.LoadCnt++;
		
						//SendToPC1(1,i+1,1,0x41);//发送通讯故障到主机
						
						Set_Alarm_Flag(i,0);
						Beep_Alarm_Fault=2; //开中断
						
						Set_World_Flag_Flag(7,0);//消音灯关闭
						Beep_ON();
						if (FaultRecount<500) //故障记录总数500条
						{
							FaultRecount++;
						}
						else 
						{
							FaultRecount=1;//报警记录总数加1
						}
						Save_Fault_Record(i+1,0);//探测器通讯故障     
					}
				}
				else   ///已处于故障报警状态
				{            
					if( End_Addr > 256 )
						cTemp = Max_Uart/2;
					else
						cTemp = Max_Uart;
					
					if (Uart_Fault_Timer(i)<cTemp) //故障清除了
					{           
						Set_Fault_Flag(i,0);//故障清除
						
						SendFunction[SendPtr.LoadCnt].Command = 2;
						SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
						SendFunction[SendPtr.LoadCnt].TDH = 1;
						SendFunction[SendPtr.LoadCnt].type = 0x41;
						SendPtr.LoadCnt++;	

						//SendToPC1(2,i+1,1,0x41);//发送通讯故障到主机
						
						// Clear_Fault_Record(i+1);//取消显示这回路                
					}          
				}       
     }  
//---探测器故障部位总数加-------
    
		pn=0;

		for (j=0;j<((End_Addr-1)/8+1);j++)//
		{   
			temp=Fault_Flag[j];
			for (i=0;i<8;i++)
			{ 
				if( temp&0x80 ) //判断最高位状态=1报警 ，计数加1
				{
					pn++;
				}
				temp=temp<<1;
			}
		}
		
		if(LoopOpenFlag==1)//开启辅助回路
		{
			for (i=LoopStart-1;i<LoopEnd;i++)
			{
					if (Check_Shield_State(i))  continue;//被屏蔽,继续
				 
					if(!Check_Fault_State(i))  //之前没有故障报警 
					{  
						if( LoopEnd > 256 )
							cTemp = Max_Uart/2;
						else
							cTemp = Max_Uart;

						if ( Uart_Fault_Timer(i)>=cTemp )  //判断此时是否有故障了
						{   
							Set_Fault_Flag(i,1); //通讯故障置故障标志
							
							SendFunction[SendPtr.LoadCnt].Command = 1;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x41;
							SendPtr.LoadCnt++;

							//SendToPC1(1,i+1,1,0x41);//发送通讯故障到主机
							
							Set_Alarm_Flag(i,0);
							Beep_Alarm_Fault=2; //开中断
							
							Set_World_Flag_Flag(7,0);//消音灯关闭
							Beep_ON();
							if (FaultRecount<500) //故障记录总数
							{
								FaultRecount++;
							}
							else 
							{
								FaultRecount=1;//报警记录总数加1
							}
							Save_Fault_Record(i+1,0);//探测器通讯故障                          
						}
					}
					else   ///已处于故障报警状态
					{            
						if( LoopEnd > 256 )
							cTemp = Max_Uart/2;
						else
							cTemp = Max_Uart;
						
						if (Uart_Fault_Timer(i)<cTemp) //故障清除了
						{           
							Set_Fault_Flag(i,0);//故障清除
							
							SendFunction[SendPtr.LoadCnt].Command = 2;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x41;
							SendPtr.LoadCnt++;

							//SendToPC1(2,i+1,1,0x41);//发送通讯故障到主机
							// Clear_Fault_Record(i+1);//取消显示这回路                
						}          
					}       
			}  			
			
			pn=0;		
			for (j=0;j<((LoopEnd-1)/8+1);j++)//
			{   
				temp=Fault_Flag[j];
				for (i=0;i<8;i++)
				{ 
					if( temp&0x80 ) //判断最高位状态=1报警 ，计数加1
					{
						pn++;
					}
					temp=temp<<1;
				}
			}
			
		}
		
	if(pn > 0)
	{
		Set_World_Flag_Flag(5,1);  //通讯故障
	}
	else
	{
		Set_World_Flag_Flag(5,0);  //通讯故障
	}
		
	cTemp=0;	
		
  //--------------- 判断总故障--------------------
	if (Check_World_Flag_State(11))
	{
		pn++;//主电
		cTemp++;
	}
	
	if (Check_World_Flag_State(13))
	{
		pn++;//备电
		cTemp++;
	}
	
	if(cTemp != 0)
	{
		Set_World_Flag_Flag(3,1);  //判断系统故障
	}
	else
	{
		Set_World_Flag_Flag(3,0);  
	}
	
	Fault_Rec_Position=pn;
		
	//检查互感器回路故障
	//互感器故障计数Fault_Rec
  //--------------- 判断总故障--------------------
	if ((pn!=0)||(Fault_Rec !=0))
	{
		Set_World_Flag_Flag(1,1);  //判断总故障
	}
	else  
	{
		Set_World_Flag_Flag(1,0);//消除总故障报警灯
		if(Beep_Alarm_Fault==2)//关闭蜂鸣器
		{
			Beep_Alarm_Fault=0; 
			Beep_OFF();
		}
	}

}


void Check_Feel_Alarm(void)//检测探测器报警
{
	uint16_t i,j,pn;
	
	//-------报警部位总数------------------------
	pn=0;
	for (i=0;i<End_Addr;i++)//
	{  
		if (Check_Shield_State(i))  continue;//被屏蔽,继续
		
		for(j=0;j<16;j++)
		{
			if(Check_Alarm_State_16(i,j))
			{
				pn++;
			}
		}
		//if(Check_Alarm_State(i))pn++;//启动

	}
	
	if(LoopOpenFlag ==1)
	{
		for (i=LoopStart-1;i<LoopEnd;i++)//
		{  
			if (Check_Shield_State(i))  continue;//被屏蔽,继续
			
			for(j=0;j<16;j++)
			{
				if(Check_Alarm_State_16(i,j))
				{
					pn++;
				}
			}
			//if(Check_Alarm_State(i))pn++;//启动
		}
	}

	Alarm_Rec_Position=pn;	
   
	
	
}


void Set_Uart_Fault_Timer0(unsigned int Num)//将故障清0
{
   unsigned  char temp;

     //第Num路，判断在第几个字节中
   temp=Uart_Err_Timer[Num/2];
   
   if ((Num%2)==1) 
      temp=temp&0x0F;   //高半字节
   else temp=temp&0xF0;

   Uart_Err_Timer[Num/2]=temp;
 
}

void Set_Fault_Flag(unsigned int Num,unsigned char  flag)//将报警标志置1或清0
{
   unsigned char x,temp,i,nbit;
   
   i= Num/8;  //第Num路，判断在第几个字节中
   temp=Fault_Flag[i];
   nbit=Num%8; //判断在第几位中
    
    x= 1 << nbit; 
   
    if (flag==1)   //=1将相应的位置1
    {
     
       temp=temp | x;
    } 
   else 
    {  x=0xFF-x;
       temp=temp & x;
     }
   Fault_Flag[i]=temp;
}


void Set_Alarm_Flag(unsigned int Num,unsigned char flag)//将报警标志置1或清0
{
	unsigned char x,temp,i,nbit;

	i= Num/8;  //第Num路，判断在第几个字节中
	temp=Alarm_Flag[i];
	nbit=Num%8; //判断在第几位中

	x= 1 << nbit; 

	if (flag==1)   //=1将相应的位置1
	{
		temp=temp | x;
	} 
	else 
	{  
		x=0xFF-x;
		temp=temp & x;
	}
	
	Alarm_Flag[i]=temp;
}

void Set_Alarm_Flag_16(unsigned int Num,unsigned char ch,unsigned char flag)//将报警标志置1或清0
{
	uint16_t x,temp,i,nbit;

	i= Num;  //第Num路，判断在第几个字节中
	temp=Alarm_Flag_16[i];
	nbit=ch; //判断在第几位中

	x= 1 << nbit; 

	if (flag==1)   //=1将相应的位置1
	{
		temp=temp | x;
	} 
	else 
	{  
		x=0xFFFF-x;
		temp=temp & x;
	}
	
	Alarm_Flag_16[i]=temp;
	
}
