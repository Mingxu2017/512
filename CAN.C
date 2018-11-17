#include "stm32f10x.h"
#include "declare.h"
CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;

CanTxMsg TxMessage;
CanRxMsg RxMessage;

CanTxMsg CanSendData[8];
CanRxMsg CanRecData[8];

void CAN_Config(void)
{
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	NVIC_InitTypeDef  		NVIC_InitStructure;
  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  /* CANx Periph clock enable */
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			//txd
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��ʼ��IO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		//rxd
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//��ʼ��IO
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//APB1=36M
  
	/* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;;//=0��ֹʱ�䴥��ͨѶģʽ
  CAN_InitStructure.CAN_ABOM = ENABLE;//DISABLE;; //=1�����Զ��ָ�ģʽ
  CAN_InitStructure.CAN_AWUM = DISABLE;;///=0��ֹ�Զ�����ģʽ
  CAN_InitStructure.CAN_NART = ENABLE;//DISABLE;;//=1��ֹ�Զ��ش�ģʽ
  CAN_InitStructure.CAN_RFLM = DISABLE;;//��ֹ����FIFO����ģʽ
  CAN_InitStructure.CAN_TXFP = DISABLE;; //��ֹ����FIFO���ȼ�
	
  //���� �ػ�ģʽ
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_Normal;//CAN_Mode_LoopBack;////CANӲ������������ģʽ 
  
	/* CAN Baudrate = 1MBps  CAN������=APB1����Ƶ��/BRP��Ƶ��/(1+tBS1+tBS2)
       baud=(36/4)/(3+5+1)
  һλ��ʱ��bitTime��CAN_SJW_1tq+CAN_BS1_3tq+CAN_BS2_5tq=(1+3+5)tq
	 tq=1/TFCAN  ---
   ����ע����ǲ��õ��λ��,Ҳ��ʱBS1,BS2����������
   1Mbps �����£����õ��λ����6tqλ�ô���BS1=5, BS2=2
   500kbps �����£����õ��λ����8tqλ�ô���BS1=7, BS2=3
   250kbps �����£����õ��λ����14tqλ�ô���BS1=13, BS2=2
   125k, 100k, 50k, 20k, 10k �Ĳ��õ�λ���� 250K ��ͬ��

	�������ñ���tBS1>=tBS2 tBS2>=1��CANʱ������  tBS2>=2tSJW*/
	/* CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;;//ͬ��ʱ��Ρ���������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥Ԫ�����ޡ���ֵ���Ա��Ϊ1��4��ʱ�䵥Ԫ��
	CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;;//ʱ���1  1-16���� 
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;//1-8���� 
	CAN_InitStructure.CAN_Prescaler = 4; //
	CAN_Init(CAN1, &CAN_InitStructure);//1M	
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;;//����ͬ����Ծ����(SJW)����������ÿλ�п����ӳ������̶��ٸ�ʱ�䵥Ԫ�����ޡ���ֵ���Ա��Ϊ1��4��ʱ�䵥Ԫ��
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;;//ʱ���1Ϊ3��ʱ�䵥λ1-16���� 
	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;//1-8���� 
	CAN_InitStructure.CAN_Prescaler = 90;//25K
  /*     225;//10K
         90;//25K;
         45;//50K
         30;//75K;
         25 ;//90K;
         18 ;125K;
         9 ;250K;*/
	CAN_Init(CAN1, &CAN_InitStructure);//50K   9=250K
	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;//�������� 0~13
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//��ʶ������λģʽ����CAN_FilterMode_IdList��ʶ���б���
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;   //��������λ��Ϊ����32λ
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;  //��ʶ���Ĵ�����16λ
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//���μĴ�����16λ
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&CAN_FilterInitStructure);
  
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//��ʼ��CAN�жϽ���
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//FIFO0��Ϣ�Һ��ж�����.	
}

u8 Can_Send_Msg(uint16_t id,u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;

	TxMessage.StdId=id;			// ��׼��ʶ�� 
	TxMessage.ExtId=0x12;			// ������չ��ʾ�� 
	TxMessage.IDE=CAN_Id_Standard; 	// ��׼֡
	TxMessage.RTR=CAN_RTR_Data;		// ����֡
	TxMessage.DLC=len;				// Ҫ���͵����ݳ���
	
	for(i=0;i<len;i++)
		TxMessage.Data[i]=msg[i];			          
	
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
	if(i>=0XFFF)return 1;
	return 0;	 
}

void CAN_SendData(void)
{
	u8 TransmitMailbox=0;
	uint16_t CRC16;
	uint8_t j,length;
	
	uint16_t i;
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE); 
	
  TxMessage.StdId = Send_Buff[0]*256+Send_Buff[1]; //�趨��׼��ʶ��

	TxMessage.ExtId = 0x01;  //�趨��չ��ʶ��
	TxMessage.RTR = CAN_RTR_DATA; //�趨��������Ϣ��֡����Ϊ����֡
	TxMessage.IDE = CAN_ID_STD;//�趨��Ϣ��ʶ��������Ϊ�ñ�׼��ʶ��
	TxMessage.DLC = 8;//�趨��������Ϣ��֡����
		
	//��ַ	���ݳ���	������	������	У��
	length=Send_Buff[2];
	
	CRC16=CRC_16(&Send_Buff[0],length+3);
	Send_Buff[length+3]=CRC16/256;
	Send_Buff[length+4]=CRC16%256;

	for(j=0;j<((length+4)/8+1);j++)
	{
	  if(j==((length+4)/8))//���һ֡Send_Buff[j*8+i];
	  {
	     for(i=0;i<((length+4)%8+1);i++) 
			{
				TxMessage.Data[i] =Send_Buff[j*8+i]; 
				//SendPC_Buff[j*8+i+1]=TxMessage.Data[i];
			}
			 TransmitMailbox =CAN_Transmit(CAN1, &TxMessage);
			
		}	
    else
    {
			for(i=0;i<8;i++) 
			{ 
				TxMessage.Data[i] = Send_Buff[j*8+i]; 
				//SendPC_Buff[j*8+i+1]=TxMessage.Data[i];
			}
			TransmitMailbox =CAN_Transmit(CAN1, &TxMessage);
			Delay1ms(20);//10K�ٶ�Ϊ15MS,50K�ٶ�Ϊ3MS

    }			
	 
	}

 	 //memcpy(TxMessage.Data, data_buf, len);

	 i = 0xFFFF;	// ���ڼ����Ϣ�����Ƿ����� //����Ƿ��ͳɹ�
	 while(i--)
	 { 
		 if (CAN_TransmitStatus(CAN1, TransmitMailbox) == CANTXOK) break;
	 }
   
 // Alarm_Rec_Position=CAN_TransmitStatus( CAN1, TransmitMailbox);
		 
		 
	 CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	 RecCnt=0;	//������׼������
   Rec_Flag=0;
}

void CanCmdPro(void)
{
 //��ַ	���ݳ���	������	������	У��
	uint8_t i=0;
	uint16_t CRCR,CRC16;
	uint16_t IDType,Channal;
	if(RecCnt==0)//Rec_Buff[2]=0x0A;}//�������ݳ���
	{
		Rec_Buff[2]=RxMessage.Data[2];
	}

	for(i=0;i<8;i++)
	{
		if(RecCnt<(Rec_Buff[2]+5))//Rec_Buff[2] = 0x0A,���ݳ���Ϊ10
		{
			Rec_Buff[RecCnt]=RxMessage.Data[i];//��ַ
			RecCnt++;
		}
		
		if(RecCnt==(Rec_Buff[2]+5))//���ս��� Rec_Buff[2]��ʾ���ݳ���
		{
			CRCR=Rec_Buff[RecCnt-2]<<8;
			CRCR=(CRCR&0xFF00)|Rec_Buff[RecCnt-1];//����У����
			CRC16=CRC_16(&Rec_Buff[0],(Rec_Buff[2]+3));//У��
			
			if (CRCR==CRC16) 
			{ 
				Rec_Flag=1; //���ճɹ�			
				if(Rec_Buff[3]==0x01)//��
				{  
					if(Rec_Buff[4]==0)//ƫ�Ƶ�ַΪ0��״̬
					{
						//TCQ_Return_OK=1;//=1������ʾ��·ֵ
						TCQ_Return_Length = Rec_Buff[2];	//ceshi ��Ҫȷ��
	
						TCQ_Data_Control();  //ƫ�Ƶ�ַΪ0��״̬���Ǳ����趨ֵ ����ֵ
					}
					else if(Rec_Buff[4]==80)//��ȡ�������ֵ
					{
						for(i=0;i<7;i++)
						{
							IDType = Rec_Buff[0]*256+Rec_Buff[1];	//�豸��
							if(IDType == (Alarm_Position[i]&0x7FF))
							{
									Channal = (Alarm_Position[i]/4096);//1-16��ʾ16��·  0 ��ʾ�¶�
								
									if( (Channal > 0)&&(Channal < 16) )
									{
										Alarm_Data[i] = (Rec_Buff[5+(Channal-1)*2]&0x7F)*256+Rec_Buff[6+(Channal-1)*2];	
										Function_Flag =1;
									}				
							}			
						}
					}
					else if(Rec_Buff[4]==40) 
					{
						Read_TCQ_Data();
					}//�����У׼ֵ
				}  	
				else if(Rec_Buff[3]==0x06)//������06 д����ظ�
				{
					TCQ_Return_OK=1;//д�ɹ�        
				}
				
				//�����ϴ�������
//				SendPC_Buff[0]=Rec_Buff[2]+5;
//				for(i=0;i<(Rec_Buff[2]+5);i++) 
//				{
//					SendPC_Buff[i+1]=Rec_Buff[i];
//				}
//				SendToPC_Flag = 1;
//				//SendToPC();		
			}
			break;				
		}				
	}	
}	

void PC485DataPro(void)//PC���ݴ���
{
	if( RS485_RX_BUF2[0] == '@' )
	{
			ReceivePoint2 = 0;
	}
}



void RS485DataPro(void)
{
	uint16_t CRCR,CRC16;
	uint8_t i,j,k,m,pn;
	uint8_t flag=0,cTemp;
	uint8_t len;
	uint16_t lTemp = 0;
	uint16_t IDType,Channal;
	if( RS485_RX_BUF[0] == 0x5A )	//���ݻظ�
	{
		//if( RS485_RX_BUF[4]+5 < 100 )
		{
			for(i=0;i<RS485_RX_BUF[4]+5;i++)
			{
				Buff[i] = RS485_RX_BUF[i+2];		
				Rec_Buff[i] = RS485_RX_BUF[i+2];
			}	
		}
	}

	for(i=0;i<8;i++)
	{
		if(ReceiveFlag == 2)//���ս��� 
		{
			cTemp = Buff[2]+3;
			CRCR=Buff[cTemp]<<8;
			CRCR=(CRCR&0xFF00)|Buff[cTemp+1];//����У����
			CRC16=CRC_16(&Buff[0],(Buff[2]+3));//У��
			
			if(CRCR==CRC16)
			{ 
				Rec_Flag=1; //���ճɹ�			
				if(Buff[3]==0x01)//��
				{  
					if(Buff[4]==0)//ƫ�Ƶ�ַΪ0��״̬
					{
						//TCQ_Return_OK=1;//=1������ʾ��·ֵ	
						TCQ_Return_Length = Buff[2];		//���ݳ���
	
						TCDID=Buff[0]*256+Buff[1];			//�豸ID��
						Type_State=Buff[5]*256+Buff[6];	//�������=1���� =0�¶�
						PB_State =Buff[7]*256+Buff[8];	//����״̬=1���� =0����
						State1=Buff[9]*256+Buff[10];		//����״̬�͹���״̬��λ
						State2=Buff[11]*256+Buff[12];		//����״̬�͹���״̬��λ
						SKC_State=Buff[13]*256+Buff[14];//�ѿ�״̬=1���� =0����
						//MKC_State=Buff[15]*256+Buff[16];
	
						Alarm_State=0;
						Fault_State=0;
							
						Set_Uart_Fault_Timer0(TCDID-1);//Uart_Err_Timer[TCDID-1]=0;
							
						if((Function_Flag==7)||(Function_Flag==6))//д״̬����ֵ
						{
							TCQ_Return_OK=1;
						
							for(i=0;i<16;i++)
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
								else if((temp1^temp2)!=0) //����
								{
									if(!Check_Sensor_Fault0_State(TCDID-1,i))
									{
										Fault_State=Fault_State|(1<<i);
										Set_Sensor_Fault0_Flag(TCDID-1,i,1);
									}
								}			
							}
							return;
						}	
						//�����ж�
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
								if((Type_State& (1<<i))==0) //�������=1���� =0�¶�
									Alarm_Position[pn]=0*4096+TCDID;
								else 
									Alarm_Position[pn]=(i+1)*4096+TCDID; 

								flag=0;
								for(k=0;k<pn;k++)
								{
									if (Alarm_Position[k]==Alarm_Position[pn])//(i+1)*4096+TCDID) 
									{
										for(m=k;m<(pn+1);m++)
										{										
											Alarm_Position[m]=Alarm_Position[m+1];
											Alarm_Data[m]=Alarm_Data[m+1];
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
							for(i=0;i<(Buff[2]+3);i++)
							{
								Send_Buff[i]=Buff[i];
							}
							Send_Buff[3]=0x08;//������08 ����״̬��У��
							
							len=Send_Buff[2];		
							CRC16=CRC_16(&Send_Buff[0],len+3);
							Send_Buff[len+3]=CRC16/256;
							Send_Buff[len+4]=CRC16%256;
										
							rs485buf[0]=0xA5;
							rs485buf[1]=0x01;		//��·�� Ĭ��01
						
							for(i=0;i<len+5;i++)
							{
								rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
							}	
							
							RS485_Send_Data(rs485buf,len+7);//����8���ֽ� 	
							
							Save_Alarm_Record(TCDID,Alarm_State,Type_State);	
							
							SendFunction[SendPtr.LoadCnt].Command = 4;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = TCDID;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x31;
							SendPtr.LoadCnt++;
							//SendToPC1(4,TCDID,1,0x31);//���ͱ�����Ϣ������			
						}

						if(Fault_State!=0)
						{		
							//Save_Fault_Record(TCDID,Fault_State,Type_State);
							//Save_Fault_Record(TCDID);				
						}
					}
					else if(Buff[4]==80)	//���ձ������ֵ
					{
						for(i=0;i<7;i++)
						{
							IDType = Buff[0]*256+Buff[1];	//�豸��
							if(IDType == (Alarm_Position[i]&0x7FF))
							{
									Channal = (Alarm_Position[i]/4096);//1-16��ʾ16��·  0 ��ʾ�¶�
								
									if( (Channal > 0)&&(Channal < 16) )
									{
										Alarm_Data[i] = (Buff[5+(Channal-1)*2]&0x7F)*256+Buff[6+(Channal-1)*2];	
										Function_Flag =1;
									}				
							}			
						}
					}
					else if(Buff[4]==40) 
					{
						//Read_TCQ_Data();
					}//�����У׼ֵ
				}  	
				else if(Buff[3]==0x06)//������06 д����ظ�
				{
					TCQ_Return_OK=1;//д�ɹ�        
				}
			}
			
			//���͵��������ƽ̨
			//SendToPC1(1,TCDID,01,0x31);

			//���͵�������������
			//A5 0F 00 0C 0A 01 00 00 07 FF F6 00 00 00 00 C9 3C 00 00 
//			SendPC_Buff[0]=Buff[2]+5;	//���ݳ���
//			for(i=0;i<(Buff[2]+5);i++) 
//			{
//				SendPC_Buff[i+1]=Buff[i];//��������
//			}
//			SendToPC_Flag = 1;
//			//SendToPC();
	
			ReceiveFlag = 0;
			ReceivePoint = 0;
			break;							
		}
		
	
	}	
}

void RS485SendWork(u8 id)//���·��id��������
{
	uint8_t i;
	u16 CRC16=0;
	u8 length=0;
	
	if (Function_Flag==1) //Ѳ��
	{
			if(TCQ_ID_485 == 0)//��ֹ����0�����
			{
				TCQ_ID_485 =LoopStart;
			}
				
			while (Check_Shield_State(TCQ_ID_485-1))//ֱ��û�����κ��˳�ѭ�������κ󷵻�0 ���򷵻�1
			{
				
				if (TCQ_ID_485<LoopEnd) 
					TCQ_ID_485++;
				else 
				{
					TCQ_ID_485=LoopStart; 
				}					
			}
			
					
			Send_Buff[0]=TCQ_ID_485/256;
			Send_Buff[1]=TCQ_ID_485%256;
			Send_Buff[2]=0x03;//����
			Send_Buff[3]=0x01;//����
			Send_Buff[4]=0x00;//ƫ�Ƶ�ַ
			Send_Buff[5]=0x04;//����

			length=Send_Buff[2];
			CRC16=CRC_16(&Send_Buff[0],length+3);
			Send_Buff[length+3]=CRC16/256;
			Send_Buff[length+4]=CRC16%256;
						
			//ÿһ��Uart_Err_Timer��ʾ��·		
			if ( Uart_Fault_Timer(TCQ_ID_485-1) < Max_Uart )  
			{
				Add_Uart_Fault_Timer(TCQ_ID_485-1,1);//���ϴ�����1
			}

			if (TCQ_ID_485<LoopEnd) 
			{
				TCQ_ID_485++;// 
			}				
			else 
			{
				TCQ_ID_485=LoopStart; 
//				if(Alarm_Rec_Position!=0)//Ѳ��һ�κ��ѯ�������ֵ
//				{
//						Function_Flag = 12;	
//				}
			}
		
			rs485buf[0]=0xA5;
			rs485buf[1]=id;		//��·�� Ĭ��01
			
			for(i=0;i<8;i++)
			{
				rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
			}
		
			RS485_Send_Data(rs485buf,10);//����8���ֽ� 	

	}

	ReceivePoint = 0;
	ReceiveFlag = 0;
}

void CanSendWork(void)
{
		uint16_t temp2,iTemp;
		uint8_t pn;
		uint8_t i;
		static uint16_t LastAlarm=0;
		if (Function_Flag==4)  //����
		{ 
			//Uart_Timer=0;
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//����
			Send_Buff[3]=0x05;//����

			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//��·�� Ĭ��01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
				}	
				
				RS485_Send_Data(rs485buf,10);//����8���ֽ� 
			}
					
			Function_Flag=1;
		}//------------------------------
		else if (Function_Flag==3)//��λ ͬʱ��λ������
		{ 
			//Uart_Timer=0;  
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//����
			Send_Buff[3]=0x04;//����
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//��·�� Ĭ��01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
				}	
				
				RS485_Send_Data(rs485buf,10);//����8���ֽ� 		
			}
			
			Function_Flag=1;
		}  //------------------------------
		else if (Function_Flag==2) //�Լ�
		{ 
			//Uart_Timer=0; 
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//����
			Send_Buff[3]=0x03;//����
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//��·�� Ĭ��01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
				}	
				
				RS485_Send_Data(rs485buf,10);//����8���ֽ� 	
			}
			
			Function_Flag=1;
		}  
		//------------------------------
		/* 
		else if (Function_Flag==9) //�������趨ֵ
		else if (Function_Flag==10) //���ñ���ֵ
		*/
		else if (Function_Flag==1)  //10
		{ 
			//Uart_Timer=0; //����Ѳ�� ��״̬   
			
			if(TCQ_ID_CAN == 0)//��ֹ����0�����
			{
				TCQ_ID_CAN =1;
			}
			
			while (Check_Shield_State(TCQ_ID_CAN-1))//ֱ��û�����κ��˳�ѭ�������κ󷵻�0 ���򷵻�1
			{
				if (TCQ_ID_CAN<End_Addr) 
					TCQ_ID_CAN++;//  
				else 
				{
					TCQ_ID_CAN=1;    //1-32
				}
			}
					
			Send_Buff[0]=TCQ_ID_CAN/256;
			Send_Buff[1]=TCQ_ID_CAN%256;
			Send_Buff[2]=0x03;//����
			Send_Buff[3]=0x01;//����
			Send_Buff[4]=0x00;//ƫ�Ƶ�ַ
			Send_Buff[5]=0x04;//����
			
			CAN_SendData();
				
			//ÿһ��Uart_Err_Timer��ʾ��·		
			if ( Uart_Fault_Timer(TCQ_ID_CAN-1) < Max_Uart )  
			{
				Add_Uart_Fault_Timer(TCQ_ID_CAN-1,1);//���ϴ�����1
			}

			if (TCQ_ID_CAN<End_Addr) 
			{
				TCQ_ID_CAN++;
			}				
			else 
			{
				TCQ_ID_CAN=1; 
			}
		
		}//------------------------------------
		else if (Function_Flag==5)   //�������
		{   
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x04;//����
			Send_Buff[3]=0x02;//����
			Send_Buff[4]=0x05;//ƫ�Ƶ�ַ
			if (Key_Input_Value==0) 
			{
				Send_Buff[5]=0xFF;
				Send_Buff[6]=0xFF;
			}
			else 
			{
				Send_Buff[5]=0;
				Send_Buff[6]=0;
			}
			
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				if( temp2 >= LoopStart )
				{
					rs485buf[0]=0xA5;
					rs485buf[1]=0x01;		//��·�� Ĭ��01
				
					for(i=0;i<8;i++)
					{
						rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
					}	
					
					RS485_Send_Data(rs485buf,10);//����8���ֽ� 
				}
			}
		}  
		else if ((Function_Flag==6)||(Function_Flag==7)) //ʵʱ�������//��һ��״̬������ֵ
		{ 
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x03;//����
			Send_Buff[3]=0x01;//����
			Send_Buff[4]=0x00;//ƫ�Ƶ�ַ
			Send_Buff[5]=17;//����
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{	
				if( temp2 >= LoopStart )
				{
					rs485buf[0]=0xA5;
					rs485buf[1]=0x01;		//��·�� Ĭ��01
				
					for(i=0;i<8;i++)
					{
						rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
					}	
					
					RS485_Send_Data(rs485buf,10);//����8���ֽ� 
				}
				
			}
		}
		else if (Function_Flag==8)//д����ֵ    			  
		{	 
			//Uart_Timer=0;

			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=66;//����
			Send_Buff[3]=0x02;//����
			Send_Buff[4]=6;//ƫ�Ƶ�ַ
//			for(i=0;i<16;i++)
//			{
//				Send_Buff[5+4*i]=Low_Feel[i]/256;
//				Send_Buff[6+4*i]=Low_Feel[i]%256;
//			} 
			CAN_SendData();
		}			
	//----------------------------------------------------------------------			
		else if (Function_Flag==9)//�����У׼ֵ
		{
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x03;//����
			Send_Buff[3]=0x01;//����
			Send_Buff[4]=0x00;//ƫ�Ƶ�ַ
			Send_Buff[5]=0x04;//����
			CAN_SendData();
			Function_Flag=10;
		}	 
		else  if (Function_Flag==10)//�����У׼ֵ
		{
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=3;//����
			Send_Buff[3]=0x01;//����
			Send_Buff[4]=40;//ƫ�Ƶ�ַ
			Send_Buff[5]=32;//����
			CAN_SendData();
		}		
		else if (Function_Flag==11)//д���У׼ֵ
		{	  
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=18;//66;//����
			Send_Buff[3]=0x02;//����
			Send_Buff[4]=40;//ƫ�Ƶ�ַ
//			for(i=0;i<16;i++)
//			{
//				Send_Buff[5+4*i]=Zero[i]/256;
//				Send_Buff[6+4*i]=Zero[i]%256;
//				temp2=Fac[i]*10;
//				Send_Buff[7+4*i]=temp2/256;
//				Send_Buff[8+4*i]=temp2%256;
//			} 
			CAN_SendData();
		}	
		else if( (Function_Flag >= 12 )&&(Function_Flag <=15) )//����·�ı������ֵ
		{
			if(Alarm_Rec_Position>0)
			{
				pn=Alarm_Rec_Position-1;
				if (pn>6) 
				{
					pn=6;			//ˢ����������  
				}
				
				temp2=Alarm_Position[pn]&0x3FF;//���±���
				
//				for(i=AlarmNum;i<=pn;i++)
//				{
//					iTemp = Alarm_Position[i]&0x3FF;
//					if(LastAlarm != iTemp )
//					{
//						LastAlarm = iTemp;
//						temp2 = iTemp;	
//						break;
//					}		
//				}
//				
//				if( AlarmNum < pn )
//					AlarmNum++;
//				else
//					AlarmNum = 0;						
					
				Send_Buff[0]=temp2/256;
				Send_Buff[1]=temp2%256;
				Send_Buff[2]=3;		//����ȳ���
				Send_Buff[3]=0x01;//����
				Send_Buff[4]=80;//ƫ�Ƶ�ַ
				Send_Buff[5]=4;//���ݳ���
				CAN_SendData();
					
				if(LoopOpenFlag == 1)
				{
					if( temp2 >= LoopStart )
					{
						rs485buf[0]=0xA5;
						rs485buf[1]=0x01;		//��·�� Ĭ��01
					
						for(i=0;i<8;i++)
						{
							rs485buf[i+2]=Send_Buff[i];	//CAN���ݸ�ʽ
						}	
						
						RS485_Send_Data(rs485buf,10);//����8���ֽ� 
					}
				}
				
				if(Function_Flag >12)
				{
					Function_Flag--;
				}
				else
				{
					Function_Flag = 1;
				}
			}
			else
			{
				Function_Flag = 1;
			}
		
		}
}

