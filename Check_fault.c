#include "stm32f10x.h"		/* ���Ҫ��ST�Ĺ̼��⣬�����������ļ� */
#include "Declare.h"
uint8_t Bat_Low_Flag=0;
uint8_t CD_Flag=0;//����־

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

//Num��0--63֮��
uint8_t Check_Shield_State(uint16_t Num)//���κ󷵻�1�����򷵻�0
{
   uint8_t temp,i,nbit;
  
   i= Num/8;  //��Num·���ж��ڵڼ����ֽ���
   temp=Shield_Flag[i];
   nbit=Num%8; //�ж��ڵڼ�λ��
   temp =temp & (1 << nbit);
   if (temp==0) return 0;
   else return 1; 
   
}

uint8_t Check_Fault_State(uint16_t Num)//��������1
{
		uint8_t temp,i,nbit;

		i= Num/8;  //��Num·���ж��ڵڼ����ֽ���
		temp=Fault_Flag[i];
		nbit=Num%8; //�ж��ڵڼ�λ��
		temp =temp & (1 << nbit);
		if (temp==0) return 0;
		else return 1; 
}
void Add_Uart_Fault_Timer(unsigned int Num,unsigned char m)//���ϴ�����1
{
    unsigned  char temp;

   temp=Uart_Err_Timer[Num/2];
   
   if ((Num%2)==1) 
      temp+=(m<<4);  
   else temp+=m;

   Uart_Err_Timer[Num/2]=temp;
}
//-------------------------------------------------
uint8_t  Uart_Fault_Timer(uint16_t Num)//������ϴ���
{
	unsigned  char temp;
	//��Num·���ж��ڵڼ����ֽ���
	temp=Uart_Err_Timer[Num/2];

	if ((Num%2)==1) 
		temp=temp>>4;   //�߰��ֽ�

	temp=temp&0x0F;   
	return temp;
}

uint8_t Check_Alarm_State(uint16_t Num)//��������1
{
	uint8_t temp,i,nbit;

	i = Num/8;
	temp=Alarm_Flag[i];
	nbit = Num%8;
	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1; 
}

uint8_t Check_Alarm_State_16(uint16_t Num,uint8_t ch)//��������1
{
	
	uint16_t temp,i,nbit;

	i = Num;
	temp=Alarm_Flag_16[i];
	nbit = ch%16;
	temp =temp & (1 << nbit);
	if (temp==0) return 0;
	else return 1; 
	
}


void Set_Shield_Flag(uint16_t Num,uint8_t flag)//�����α�־��1����0
{
   uint8_t x,temp,i,nbit;
   
   i= Num/8;  //��Num·���ж��ڵڼ����ֽ���
   temp=Shield_Flag[i];
   nbit=Num%8; //�ж��ڵڼ�λ��
    
    x= 1 << nbit; 
   
    if (flag==1)   //=1����Ӧ��λ��1
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
	nbit=Num; //�ж��ڵڼ�λ��

	x= 1 << nbit; 
   
	if (flag==1)   //=1����Ӧ��λ��1
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

	DataBuff[2]= Real_Time.year%2000;//��������ʱ�֣���[5]..[9]?
	DataBuff[3]= Real_Time.month;//��
	DataBuff[4]= Real_Time.day;//��
	DataBuff[5]= Real_Time.hour;//ʱ
	DataBuff[6]= Real_Time.min;//��

	Addr= 0x141 + (SDRecount-1) * 8;
	Delay1ms(1); 
	RW24XX(DataBuff,7,Addr,0xA0);
	Delay1ms(1); 
/*
	if (SDRecount<500){SDRecount ++;}//
	else  SDRecount=1;////���ϼ�¼����
	
	DataBuff[0]=SDRecount/256;//��λ  
	DataBuff[1]=SDRecount%256;//��λ 
	Addr=0x1A;
	RW24XX(DataBuff,2,Addr,0xA0);//�ϵ����
	Delay1ms(2);  

	DataBuff[0]=type;    //1:�������ϵ�  2������ػ�   3����λ   4�������¼   5����ʼ��
	 
	DataBuff[3]= Real_Time.year%2000;//��������ʱ�֣���[5]..[9]?
	DataBuff[4]= Real_Time.month;//��
	DataBuff[5]= Real_Time.day;//��
	DataBuff[6]= Real_Time.hour;//ʱ
	DataBuff[7]= Real_Time.min;//��
	//�����ַ
	Addr= 0x18000 + (SDRecount-1) * 8;
	RW24XX(DataBuff,8,Addr,0xA0);
	Delay1ms(1); 
*/
}

//�ܱ��� �ܹ��� �������� �������  ��������  ������� ����ָʾ ������
//��7λ   6        5        4        3          2        1       0
uint8_t Check_World_Flag_State(uint8_t nbit)//�ܱ�־����1
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
	uint8_t AlarmM[]={"512-16���ޱ���!"};
	uint8_t DtM[]={"2014-02-13 15:32"};
	
	DataBuff[2]=TCQ_ID/256;//��ַ��
	DataBuff[3]=TCQ_ID%256;//��ַ��

	DataBuff[5]= Real_Time.year%2000;//:������ʱ��--[5]..[9]
	DataBuff[6]= Real_Time.month;
	DataBuff[7]= Real_Time.day;
	DataBuff[8]= Real_Time.hour;
	DataBuff[9]= Real_Time.min;


	
 for(i=0;i<16;i++)//ÿһͨ��
 {
		temp2=Alarm_State;

		if((temp2& (1<<i))==0) 
		{
			continue;
		}
		else
		{  
			if (AlarmRecount<999)//������¼999��
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
 
	//------------------��ӡ������--------------------------
		if(Print_State==0xAA)//��ӡ������
		{
			temp2=DataBuff[2]*256+DataBuff[3];//̽����ID
			AlarmM[0]=temp2/100+0x30;
			AlarmM[1]=temp2%100/10+0x30;
			AlarmM[2]=temp2%10+0x30;
			AlarmM[4]= DataBuff[4]/10+0x30;	//��·��
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
			for (i=0;i<5;i++) //���ڵ�ת��
			{ 
				DtM[2+3*i]=DataBuff[5+i]/10+0x30;  //��
				DtM[3+3*i]=DataBuff[5+i]%10+0x30;  
			}
			PrintID++;		
			Begin_Print(PrintID,AlarmM,DtM);
			
	
		}

}

void Save_Fault_Record(uint16_t tcID,uint8_t type)
{
		unsigned char hz5[]={"�������"};
		unsigned char hz6[]={"�������"};
		unsigned char hz7[]={"������"};
		//unsigned char DtM[]={"2014-02-13 15:32"};
		unsigned char DataBuff[12];//,i;
		unsigned int temp;
		unsigned int Addr;
		//uint8_t i=0;
		
		temp=FaultRecount;//���ϼ�¼����
		DataBuff[0]=temp/256;//��λ  
		DataBuff[1]=temp%256;//��λ 
		Addr=0x1C;
		Delay1ms(1);
		RW24XX(DataBuff,2,Addr,0xA0);
		Delay1ms(5);
		DataBuff[2]=tcID/256;//��������
		DataBuff[3]=tcID%256;

		DataBuff[4]=type;	//�������� 0 ͨѶ����1-16 ��·���� F0������� F1������� F2������

		Read_RTC();
		DataBuff[4+1]= Real_Time.year%2000;//��--[5]..[9]?
    DataBuff[5+1]= Real_Time.month;
	  DataBuff[6+1]= Real_Time.day;
	  DataBuff[7+1]= Real_Time.hour;
	  DataBuff[8+1]= Real_Time.min;
	 
		//�����ַ
		Addr= 0x4602 + (FaultRecount-1) * 16;
		Delay1ms(1);
		RW24XX(DataBuff,9+1,Addr,0xA0);
		// ���ݳ��� ��ַ ������(01) ������(����·��+����Ũ��ֵ+������ʱ��)
		Delay1ms(1);

 /*
		if(Print_State==0xAA)//������ӡ������
		{	
			for (i=0;i<5;i++) //���ڵ�ת��
			{ 
				DtM[2+3*i]=DataBuff[4+i]/10+0x30;  //��
				DtM[3+3*i]=DataBuff[4+i]%10+0x30;  
			}
			if (type==0xF0) //��ӡ�������
			{
				PrintID++;
				Begin_Print(PrintID,hz5,DtM);
			}
			else if(type==0xF1)//��ӡ�������
			{
				PrintID++; 
				Begin_Print(PrintID,hz6,DtM);
			}
		}
*/	
/*
   pn=Fault_Rec_Position;//���ϲ�λ����
                     
   if (pn>10) pn=10;  
              
   Fault_Position[pn]=tcID;
              
   flag=0;
   for(k=0;k<(pn);k++)
    {
        if (Fault_Position[k]==tcID)
        {
            for(m=k;m<(pn);m++) Fault_Position[m]=Fault_Position[m+1];//��ͬ������
            flag=1;
            break;
          }
                  
       }
    if (flag==1) Fault_RecP++;//���ظ��Ĳ�����
    else 
    {
         Fault_Rec_Position++;
         if (pn==10)
         for(m=0;m<10;m++) Fault_Position[m]=Fault_Position[m+1];//��ͬ������
      }
*/            
            

}

void Check_Fault_Alarm(void)//���������ж�
{   
		uint16_t j,temp,cTemp;
		uint16_t i,pn;
//������·0~EndAddr
    for (i=0;i<End_Addr;i++)
    {
        if (Check_Shield_State(i))  continue;//������,����
       
				if(!Check_Fault_State(i))  //֮ǰû�й��ϱ��� 
				{  
					if( End_Addr > 256 )
						cTemp = Max_Uart/2;
					else
						cTemp = Max_Uart;

					if ( Uart_Fault_Timer(i)>=cTemp )  //�жϴ�ʱ�Ƿ��й�����
					{   
						Set_Fault_Flag(i,1); //ͨѶ�����ù��ϱ�־
						
						SendFunction[SendPtr.LoadCnt].Command = 1;
						SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
						SendFunction[SendPtr.LoadCnt].TDH = 1;
						SendFunction[SendPtr.LoadCnt].type = 0x41;
						SendPtr.LoadCnt++;
		
						//SendToPC1(1,i+1,1,0x41);//����ͨѶ���ϵ�����
						
						Set_Alarm_Flag(i,0);
						Beep_Alarm_Fault=2; //���ж�
						
						Set_World_Flag_Flag(7,0);//�����ƹر�
						Beep_ON();
						if (FaultRecount<500) //���ϼ�¼����500��
						{
							FaultRecount++;
						}
						else 
						{
							FaultRecount=1;//������¼������1
						}
						Save_Fault_Record(i+1,0);//̽����ͨѶ����     
					}
				}
				else   ///�Ѵ��ڹ��ϱ���״̬
				{            
					if( End_Addr > 256 )
						cTemp = Max_Uart/2;
					else
						cTemp = Max_Uart;
					
					if (Uart_Fault_Timer(i)<cTemp) //���������
					{           
						Set_Fault_Flag(i,0);//�������
						
						SendFunction[SendPtr.LoadCnt].Command = 2;
						SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
						SendFunction[SendPtr.LoadCnt].TDH = 1;
						SendFunction[SendPtr.LoadCnt].type = 0x41;
						SendPtr.LoadCnt++;	

						//SendToPC1(2,i+1,1,0x41);//����ͨѶ���ϵ�����
						
						// Clear_Fault_Record(i+1);//ȡ����ʾ���·                
					}          
				}       
     }  
//---̽�������ϲ�λ������-------
    
		pn=0;

		for (j=0;j<((End_Addr-1)/8+1);j++)//
		{   
			temp=Fault_Flag[j];
			for (i=0;i<8;i++)
			{ 
				if( temp&0x80 ) //�ж����λ״̬=1���� ��������1
				{
					pn++;
				}
				temp=temp<<1;
			}
		}
		
		if(LoopOpenFlag==1)//����������·
		{
			for (i=LoopStart-1;i<LoopEnd;i++)
			{
					if (Check_Shield_State(i))  continue;//������,����
				 
					if(!Check_Fault_State(i))  //֮ǰû�й��ϱ��� 
					{  
						if( LoopEnd > 256 )
							cTemp = Max_Uart/2;
						else
							cTemp = Max_Uart;

						if ( Uart_Fault_Timer(i)>=cTemp )  //�жϴ�ʱ�Ƿ��й�����
						{   
							Set_Fault_Flag(i,1); //ͨѶ�����ù��ϱ�־
							
							SendFunction[SendPtr.LoadCnt].Command = 1;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x41;
							SendPtr.LoadCnt++;

							//SendToPC1(1,i+1,1,0x41);//����ͨѶ���ϵ�����
							
							Set_Alarm_Flag(i,0);
							Beep_Alarm_Fault=2; //���ж�
							
							Set_World_Flag_Flag(7,0);//�����ƹر�
							Beep_ON();
							if (FaultRecount<500) //���ϼ�¼����
							{
								FaultRecount++;
							}
							else 
							{
								FaultRecount=1;//������¼������1
							}
							Save_Fault_Record(i+1,0);//̽����ͨѶ����                          
						}
					}
					else   ///�Ѵ��ڹ��ϱ���״̬
					{            
						if( LoopEnd > 256 )
							cTemp = Max_Uart/2;
						else
							cTemp = Max_Uart;
						
						if (Uart_Fault_Timer(i)<cTemp) //���������
						{           
							Set_Fault_Flag(i,0);//�������
							
							SendFunction[SendPtr.LoadCnt].Command = 2;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = i+1;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x41;
							SendPtr.LoadCnt++;

							//SendToPC1(2,i+1,1,0x41);//����ͨѶ���ϵ�����
							// Clear_Fault_Record(i+1);//ȡ����ʾ���·                
						}          
					}       
			}  			
			
			pn=0;		
			for (j=0;j<((LoopEnd-1)/8+1);j++)//
			{   
				temp=Fault_Flag[j];
				for (i=0;i<8;i++)
				{ 
					if( temp&0x80 ) //�ж����λ״̬=1���� ��������1
					{
						pn++;
					}
					temp=temp<<1;
				}
			}
			
		}
		
	if(pn > 0)
	{
		Set_World_Flag_Flag(5,1);  //ͨѶ����
	}
	else
	{
		Set_World_Flag_Flag(5,0);  //ͨѶ����
	}
		
	cTemp=0;	
		
  //--------------- �ж��ܹ���--------------------
	if (Check_World_Flag_State(11))
	{
		pn++;//����
		cTemp++;
	}
	
	if (Check_World_Flag_State(13))
	{
		pn++;//����
		cTemp++;
	}
	
	if(cTemp != 0)
	{
		Set_World_Flag_Flag(3,1);  //�ж�ϵͳ����
	}
	else
	{
		Set_World_Flag_Flag(3,0);  
	}
	
	Fault_Rec_Position=pn;
		
	//��黥������·����
	//���������ϼ���Fault_Rec
  //--------------- �ж��ܹ���--------------------
	if ((pn!=0)||(Fault_Rec !=0))
	{
		Set_World_Flag_Flag(1,1);  //�ж��ܹ���
	}
	else  
	{
		Set_World_Flag_Flag(1,0);//�����ܹ��ϱ�����
		if(Beep_Alarm_Fault==2)//�رշ�����
		{
			Beep_Alarm_Fault=0; 
			Beep_OFF();
		}
	}

}


void Check_Feel_Alarm(void)//���̽��������
{
	uint16_t i,j,pn;
	
	//-------������λ����------------------------
	pn=0;
	for (i=0;i<End_Addr;i++)//
	{  
		if (Check_Shield_State(i))  continue;//������,����
		
		for(j=0;j<16;j++)
		{
			if(Check_Alarm_State_16(i,j))
			{
				pn++;
			}
		}
		//if(Check_Alarm_State(i))pn++;//����

	}
	
	if(LoopOpenFlag ==1)
	{
		for (i=LoopStart-1;i<LoopEnd;i++)//
		{  
			if (Check_Shield_State(i))  continue;//������,����
			
			for(j=0;j<16;j++)
			{
				if(Check_Alarm_State_16(i,j))
				{
					pn++;
				}
			}
			//if(Check_Alarm_State(i))pn++;//����
		}
	}

	Alarm_Rec_Position=pn;	
   
	
	
}


void Set_Uart_Fault_Timer0(unsigned int Num)//��������0
{
   unsigned  char temp;

     //��Num·���ж��ڵڼ����ֽ���
   temp=Uart_Err_Timer[Num/2];
   
   if ((Num%2)==1) 
      temp=temp&0x0F;   //�߰��ֽ�
   else temp=temp&0xF0;

   Uart_Err_Timer[Num/2]=temp;
 
}

void Set_Fault_Flag(unsigned int Num,unsigned char  flag)//��������־��1����0
{
   unsigned char x,temp,i,nbit;
   
   i= Num/8;  //��Num·���ж��ڵڼ����ֽ���
   temp=Fault_Flag[i];
   nbit=Num%8; //�ж��ڵڼ�λ��
    
    x= 1 << nbit; 
   
    if (flag==1)   //=1����Ӧ��λ��1
    {
     
       temp=temp | x;
    } 
   else 
    {  x=0xFF-x;
       temp=temp & x;
     }
   Fault_Flag[i]=temp;
}


void Set_Alarm_Flag(unsigned int Num,unsigned char flag)//��������־��1����0
{
	unsigned char x,temp,i,nbit;

	i= Num/8;  //��Num·���ж��ڵڼ����ֽ���
	temp=Alarm_Flag[i];
	nbit=Num%8; //�ж��ڵڼ�λ��

	x= 1 << nbit; 

	if (flag==1)   //=1����Ӧ��λ��1
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

void Set_Alarm_Flag_16(unsigned int Num,unsigned char ch,unsigned char flag)//��������־��1����0
{
	uint16_t x,temp,i,nbit;

	i= Num;  //��Num·���ж��ڵڼ����ֽ���
	temp=Alarm_Flag_16[i];
	nbit=ch; //�ж��ڵڼ�λ��

	x= 1 << nbit; 

	if (flag==1)   //=1����Ӧ��λ��1
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
