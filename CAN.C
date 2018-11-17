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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//初始化IO

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		//rxd
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);				//初始化IO
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//APB1=36M
  
	/* CAN register init */
  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;;//=0禁止时间触发通讯模式
  CAN_InitStructure.CAN_ABOM = ENABLE;//DISABLE;; //=1离线自动恢复模式
  CAN_InitStructure.CAN_AWUM = DISABLE;;///=0禁止自动唤醒模式
  CAN_InitStructure.CAN_NART = ENABLE;//DISABLE;;//=1禁止自动重传模式
  CAN_InitStructure.CAN_RFLM = DISABLE;;//禁止接收FIFO锁定模式
  CAN_InitStructure.CAN_TXFP = DISABLE;; //禁止发送FIFO优先级
	
  //测试 回环模式
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_Normal;//CAN_Mode_LoopBack;////CAN硬件工作在正常模式 
  
	/* CAN Baudrate = 1MBps  CAN波特率=APB1总线频率/BRP分频器/(1+tBS1+tBS2)
       baud=(36/4)/(3+5+1)
  一位的时间bitTime＝CAN_SJW_1tq+CAN_BS1_3tq+CAN_BS2_5tq=(1+3+5)tq
	 tq=1/TFCAN  ---
   这里注意的是采用点的位置,也就时BS1,BS2的设置问题
   1Mbps 速率下，采用点的位置在6tq位置处，BS1=5, BS2=2
   500kbps 速率下，采用点的位置在8tq位置处，BS1=7, BS2=3
   250kbps 速率下，采用点的位置在14tq位置处，BS1=13, BS2=2
   125k, 100k, 50k, 20k, 10k 的采用点位置与 250K 相同。

	总体配置保持tBS1>=tBS2 tBS2>=1个CAN时钟周期  tBS2>=2tSJW*/
	/* CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;;//同步时间段。定义了在每位中可以延长或缩短多少个时间单元的上限。其值可以编程为1到4个时间单元。
	CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;;//时间段1  1-16设置 
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;//1-8设置 
	CAN_InitStructure.CAN_Prescaler = 4; //
	CAN_Init(CAN1, &CAN_InitStructure);//1M	
	*/
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;;//重新同步跳跃宽度(SJW)：定义了在每位中可以延长或缩短多少个时间单元的上限。其值可以编程为1到4个时间单元。
	CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;;//时间段1为3个时间单位1-16设置 
	CAN_InitStructure.CAN_BS2 = CAN_BS2_7tq;//1-8设置 
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
	CAN_FilterInitStructure.CAN_FilterNumber = 0;//过滤器号 0~13
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//标识符屏蔽位模式，（CAN_FilterMode_IdList标识符列表）
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;   //过滤器组位宽为单个32位
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;  //标识符寄存器高16位
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;//屏蔽寄存器高16位
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	
	CAN_FilterInit(&CAN_FilterInitStructure);
  
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 主优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//初始化CAN中断接收
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//FIFO0消息挂号中断允许.	
}

u8 Can_Send_Msg(uint16_t id,u8* msg,u8 len)
{	
	u8 mbox;
	u16 i=0;

	TxMessage.StdId=id;			// 标准标识符 
	TxMessage.ExtId=0x12;			// 设置扩展标示符 
	TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=len;				// 要发送的数据长度
	
	for(i=0;i<len;i++)
		TxMessage.Data[i]=msg[i];			          
	
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
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
	
  TxMessage.StdId = Send_Buff[0]*256+Send_Buff[1]; //设定标准标识符

	TxMessage.ExtId = 0x01;  //设定扩展标识符
	TxMessage.RTR = CAN_RTR_DATA; //设定待传输消息的帧类型为数据帧
	TxMessage.IDE = CAN_ID_STD;//设定消息标识符的类型为用标准标识符
	TxMessage.DLC = 8;//设定待传输消息的帧长度
		
	//地址	数据长度	功能码	数据区	校验
	length=Send_Buff[2];
	
	CRC16=CRC_16(&Send_Buff[0],length+3);
	Send_Buff[length+3]=CRC16/256;
	Send_Buff[length+4]=CRC16%256;

	for(j=0;j<((length+4)/8+1);j++)
	{
	  if(j==((length+4)/8))//最后一帧Send_Buff[j*8+i];
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
			Delay1ms(20);//10K速度为15MS,50K速度为3MS

    }			
	 
	}

 	 //memcpy(TxMessage.Data, data_buf, len);

	 i = 0xFFFF;	// 用于检查消息传输是否正常 //检测是否发送成功
	 while(i--)
	 { 
		 if (CAN_TransmitStatus(CAN1, TransmitMailbox) == CANTXOK) break;
	 }
   
 // Alarm_Rec_Position=CAN_TransmitStatus( CAN1, TransmitMailbox);
		 
		 
	 CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	 RecCnt=0;	//发送完准备接收
   Rec_Flag=0;
}

void CanCmdPro(void)
{
 //地址	数据长度	功能码	数据区	校验
	uint8_t i=0;
	uint16_t CRCR,CRC16;
	uint16_t IDType,Channal;
	if(RecCnt==0)//Rec_Buff[2]=0x0A;}//接收数据长度
	{
		Rec_Buff[2]=RxMessage.Data[2];
	}

	for(i=0;i<8;i++)
	{
		if(RecCnt<(Rec_Buff[2]+5))//Rec_Buff[2] = 0x0A,数据长度为10
		{
			Rec_Buff[RecCnt]=RxMessage.Data[i];//地址
			RecCnt++;
		}
		
		if(RecCnt==(Rec_Buff[2]+5))//接收结束 Rec_Buff[2]表示数据长度
		{
			CRCR=Rec_Buff[RecCnt-2]<<8;
			CRCR=(CRCR&0xFF00)|Rec_Buff[RecCnt-1];//接收校验码
			CRC16=CRC_16(&Rec_Buff[0],(Rec_Buff[2]+3));//校验
			
			if (CRCR==CRC16) 
			{ 
				Rec_Flag=1; //接收成功			
				if(Rec_Buff[3]==0x01)//读
				{  
					if(Rec_Buff[4]==0)//偏移地址为0读状态
					{
						//TCQ_Return_OK=1;//=1才能显示回路值
						TCQ_Return_Length = Rec_Buff[2];	//ceshi 需要确认
	
						TCQ_Data_Control();  //偏移地址为0读状态或是报警设定值 报警值
					}
					else if(Rec_Buff[4]==80)//读取报警最大值
					{
						for(i=0;i<7;i++)
						{
							IDType = Rec_Buff[0]*256+Rec_Buff[1];	//设备号
							if(IDType == (Alarm_Position[i]&0x7FF))
							{
									Channal = (Alarm_Position[i]/4096);//1-16表示16回路  0 表示温度
								
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
					}//读零点校准值
				}  	
				else if(Rec_Buff[3]==0x06)//命令码06 写命令回复
				{
					TCQ_Return_OK=1;//写成功        
				}
				
				//数据上传到主机
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

void PC485DataPro(void)//PC数据处理
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
	if( RS485_RX_BUF[0] == 0x5A )	//数据回复
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
		if(ReceiveFlag == 2)//接收结束 
		{
			cTemp = Buff[2]+3;
			CRCR=Buff[cTemp]<<8;
			CRCR=(CRCR&0xFF00)|Buff[cTemp+1];//接收校验码
			CRC16=CRC_16(&Buff[0],(Buff[2]+3));//校验
			
			if(CRCR==CRC16)
			{ 
				Rec_Flag=1; //接收成功			
				if(Buff[3]==0x01)//读
				{  
					if(Buff[4]==0)//偏移地址为0读状态
					{
						//TCQ_Return_OK=1;//=1才能显示回路值	
						TCQ_Return_Length = Buff[2];		//数据长度
	
						TCDID=Buff[0]*256+Buff[1];			//设备ID号
						Type_State=Buff[5]*256+Buff[6];	//检测类型=1电流 =0温度
						PB_State =Buff[7]*256+Buff[8];	//屏蔽状态=1屏蔽 =0工作
						State1=Buff[9]*256+Buff[10];		//报警状态和故障状态高位
						State2=Buff[11]*256+Buff[12];		//报警状态和故障状态低位
						SKC_State=Buff[13]*256+Buff[14];//脱扣状态=1屏蔽 =0开启
						//MKC_State=Buff[15]*256+Buff[16];
	
						Alarm_State=0;
						Fault_State=0;
							
						Set_Uart_Fault_Timer0(TCDID-1);//Uart_Err_Timer[TCDID-1]=0;
							
						if((Function_Flag==7)||(Function_Flag==6))//写状态返回值
						{
							TCQ_Return_OK=1;
						
							for(i=0;i<16;i++)
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
								else if((temp1^temp2)!=0) //故障
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
						//报警判断
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
								if((Type_State& (1<<i))==0) //检测类型=1电流 =0温度
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
									Alarm_Rec_Position++;	//报警总数加1
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
							for(i=0;i<(Buff[2]+3);i++)
							{
								Send_Buff[i]=Buff[i];
							}
							Send_Buff[3]=0x08;//功能码08 接收状态字校对
							
							len=Send_Buff[2];		
							CRC16=CRC_16(&Send_Buff[0],len+3);
							Send_Buff[len+3]=CRC16/256;
							Send_Buff[len+4]=CRC16%256;
										
							rs485buf[0]=0xA5;
							rs485buf[1]=0x01;		//回路号 默认01
						
							for(i=0;i<len+5;i++)
							{
								rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
							}	
							
							RS485_Send_Data(rs485buf,len+7);//发送8个字节 	
							
							Save_Alarm_Record(TCDID,Alarm_State,Type_State);	
							
							SendFunction[SendPtr.LoadCnt].Command = 4;
							SendFunction[SendPtr.LoadCnt].TCQ_Num = TCDID;
							SendFunction[SendPtr.LoadCnt].TDH = 1;
							SendFunction[SendPtr.LoadCnt].type = 0x31;
							SendPtr.LoadCnt++;
							//SendToPC1(4,TCDID,1,0x31);//发送报警信息到主机			
						}

						if(Fault_State!=0)
						{		
							//Save_Fault_Record(TCDID,Fault_State,Type_State);
							//Save_Fault_Record(TCDID);				
						}
					}
					else if(Buff[4]==80)	//接收报警最大值
					{
						for(i=0;i<7;i++)
						{
							IDType = Buff[0]*256+Buff[1];	//设备号
							if(IDType == (Alarm_Position[i]&0x7FF))
							{
									Channal = (Alarm_Position[i]/4096);//1-16表示16回路  0 表示温度
								
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
					}//读零点校准值
				}  	
				else if(Buff[3]==0x06)//命令码06 写命令回复
				{
					TCQ_Return_OK=1;//写成功        
				}
			}
			
			//发送到消防监控平台
			//SendToPC1(1,TCDID,01,0x31);

			//发送到电脑数据中心
			//A5 0F 00 0C 0A 01 00 00 07 FF F6 00 00 00 00 C9 3C 00 00 
//			SendPC_Buff[0]=Buff[2]+5;	//数据长度
//			for(i=0;i<(Buff[2]+5);i++) 
//			{
//				SendPC_Buff[i+1]=Buff[i];//数据内容
//			}
//			SendToPC_Flag = 1;
//			//SendToPC();
	
			ReceiveFlag = 0;
			ReceivePoint = 0;
			break;							
		}
		
	
	}	
}

void RS485SendWork(u8 id)//向回路板id发送命令
{
	uint8_t i;
	u16 CRC16=0;
	u8 length=0;
	
	if (Function_Flag==1) //巡检
	{
			if(TCQ_ID_485 == 0)//防止出现0的情况
			{
				TCQ_ID_485 =LoopStart;
			}
				
			while (Check_Shield_State(TCQ_ID_485-1))//直到没有屏蔽后退出循环，屏蔽后返回0 否则返回1
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
			Send_Buff[2]=0x03;//长度
			Send_Buff[3]=0x01;//命令
			Send_Buff[4]=0x00;//偏移地址
			Send_Buff[5]=0x04;//长度

			length=Send_Buff[2];
			CRC16=CRC_16(&Send_Buff[0],length+3);
			Send_Buff[length+3]=CRC16/256;
			Send_Buff[length+4]=CRC16%256;
						
			//每一个Uart_Err_Timer表示两路		
			if ( Uart_Fault_Timer(TCQ_ID_485-1) < Max_Uart )  
			{
				Add_Uart_Fault_Timer(TCQ_ID_485-1,1);//故障次数加1
			}

			if (TCQ_ID_485<LoopEnd) 
			{
				TCQ_ID_485++;// 
			}				
			else 
			{
				TCQ_ID_485=LoopStart; 
//				if(Alarm_Rec_Position!=0)//巡检一次后查询报警最大值
//				{
//						Function_Flag = 12;	
//				}
			}
		
			rs485buf[0]=0xA5;
			rs485buf[1]=id;		//回路号 默认01
			
			for(i=0;i<8;i++)
			{
				rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
			}
		
			RS485_Send_Data(rs485buf,10);//发送8个字节 	

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
		if (Function_Flag==4)  //消音
		{ 
			//Uart_Timer=0;
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//长度
			Send_Buff[3]=0x05;//命令

			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//回路号 默认01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
				}	
				
				RS485_Send_Data(rs485buf,10);//发送8个字节 
			}
					
			Function_Flag=1;
		}//------------------------------
		else if (Function_Flag==3)//复位 同时复位联动箱
		{ 
			//Uart_Timer=0;  
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//长度
			Send_Buff[3]=0x04;//命令
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//回路号 默认01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
				}	
				
				RS485_Send_Data(rs485buf,10);//发送8个字节 		
			}
			
			Function_Flag=1;
		}  //------------------------------
		else if (Function_Flag==2) //自检
		{ 
			//Uart_Timer=0; 
			Send_Buff[0]=0x00;
			Send_Buff[1]=0x00;
			Send_Buff[2]=0x01;//长度
			Send_Buff[3]=0x03;//命令
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{
				rs485buf[0]=0xA5;
				rs485buf[1]=0x01;		//回路号 默认01
			
				for(i=0;i<8;i++)
				{
					rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
				}	
				
				RS485_Send_Data(rs485buf,10);//发送8个字节 	
			}
			
			Function_Flag=1;
		}  
		//------------------------------
		/* 
		else if (Function_Flag==9) //读报警设定值
		else if (Function_Flag==10) //设置报警值
		*/
		else if (Function_Flag==1)  //10
		{ 
			//Uart_Timer=0; //正常巡检 读状态   
			
			if(TCQ_ID_CAN == 0)//防止出现0的情况
			{
				TCQ_ID_CAN =1;
			}
			
			while (Check_Shield_State(TCQ_ID_CAN-1))//直到没有屏蔽后退出循环，屏蔽后返回0 否则返回1
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
			Send_Buff[2]=0x03;//长度
			Send_Buff[3]=0x01;//命令
			Send_Buff[4]=0x00;//偏移地址
			Send_Buff[5]=0x04;//长度
			
			CAN_SendData();
				
			//每一个Uart_Err_Timer表示两路		
			if ( Uart_Fault_Timer(TCQ_ID_CAN-1) < Max_Uart )  
			{
				Add_Uart_Fault_Timer(TCQ_ID_CAN-1,1);//故障次数加1
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
		else if (Function_Flag==5)   //控制输出
		{   
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x04;//长度
			Send_Buff[3]=0x02;//命令
			Send_Buff[4]=0x05;//偏移地址
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
					rs485buf[1]=0x01;		//回路号 默认01
				
					for(i=0;i<8;i++)
					{
						rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
					}	
					
					RS485_Send_Data(rs485buf,10);//发送8个字节 
				}
			}
		}  
		else if ((Function_Flag==6)||(Function_Flag==7)) //实时监测数据//读一下状态及报警值
		{ 
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x03;//长度
			Send_Buff[3]=0x01;//命令
			Send_Buff[4]=0x00;//偏移地址
			Send_Buff[5]=17;//长度
			CAN_SendData();
			
			if(LoopOpenFlag == 1)
			{	
				if( temp2 >= LoopStart )
				{
					rs485buf[0]=0xA5;
					rs485buf[1]=0x01;		//回路号 默认01
				
					for(i=0;i<8;i++)
					{
						rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
					}	
					
					RS485_Send_Data(rs485buf,10);//发送8个字节 
				}
				
			}
		}
		else if (Function_Flag==8)//写报警值    			  
		{	 
			//Uart_Timer=0;

			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=66;//长度
			Send_Buff[3]=0x02;//命令
			Send_Buff[4]=6;//偏移地址
//			for(i=0;i<16;i++)
//			{
//				Send_Buff[5+4*i]=Low_Feel[i]/256;
//				Send_Buff[6+4*i]=Low_Feel[i]%256;
//			} 
			CAN_SendData();
		}			
	//----------------------------------------------------------------------			
		else if (Function_Flag==9)//读零点校准值
		{
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=0x03;//长度
			Send_Buff[3]=0x01;//命令
			Send_Buff[4]=0x00;//偏移地址
			Send_Buff[5]=0x04;//长度
			CAN_SendData();
			Function_Flag=10;
		}	 
		else  if (Function_Flag==10)//读零点校准值
		{
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=3;//长度
			Send_Buff[3]=0x01;//命令
			Send_Buff[4]=40;//偏移地址
			Send_Buff[5]=32;//长度
			CAN_SendData();
		}		
		else if (Function_Flag==11)//写零点校准值
		{	  
			//Uart_Timer=0;
			temp2=dis_buff[0]*100+dis_buff[1]*10+dis_buff[2];
			Send_Buff[0]=temp2/256;
			Send_Buff[1]=temp2%256;
			Send_Buff[2]=18;//66;//长度
			Send_Buff[3]=0x02;//命令
			Send_Buff[4]=40;//偏移地址
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
		else if( (Function_Flag >= 12 )&&(Function_Flag <=15) )//读回路的报警最大值
		{
			if(Alarm_Rec_Position>0)
			{
				pn=Alarm_Rec_Position-1;
				if (pn>6) 
				{
					pn=6;			//刷新最新数据  
				}
				
				temp2=Alarm_Position[pn]&0x3FF;//最新报警
				
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
				Send_Buff[2]=3;		//命令长度长度
				Send_Buff[3]=0x01;//命令
				Send_Buff[4]=80;//偏移地址
				Send_Buff[5]=4;//数据长度
				CAN_SendData();
					
				if(LoopOpenFlag == 1)
				{
					if( temp2 >= LoopStart )
					{
						rs485buf[0]=0xA5;
						rs485buf[1]=0x01;		//回路号 默认01
					
						for(i=0;i<8;i++)
						{
							rs485buf[i+2]=Send_Buff[i];	//CAN数据格式
						}	
						
						RS485_Send_Data(rs485buf,10);//发送8个字节 
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


