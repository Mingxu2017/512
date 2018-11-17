#include "stm32f10x.h"
#include "declare.h"
#include  "string.h"
 const int8_t crc_table[512]=
{
	0x00,0x00,0x10,0x21,0x20,0x42,0x30,0x63,0x40,0x84,0x50,0xA5,0x60,0xC6,0x70,0xE7,
	0x81,0x08,0x91,0x29,0xA1,0x4A,0xB1,0x6B,0xC1,0x8C,0xD1,0xAD,0xE1,0xCE,0xF1,0xEF,
	0x12,0x31,0x02,0x10,0x32,0x73,0x22,0x52,0x52,0xB5,0x42,0x94,0x72,0xF7,0x62,0xD6,
	0x93,0x39,0x83,0x18,0xB3,0x7B,0xA3,0x5A,0xD3,0xBD,0xC3,0x9C,0xF3,0xFF,0xE3,0xDE,
	0x24,0x62,0x34,0x43,0x04,0x20,0x14,0x01,0x64,0xE6,0x74,0xC7,0x44,0xA4,0x54,0x85,
	0xA5,0x6A,0xB5,0x4B,0x85,0x28,0x95,0x09,0xE5,0xEE,0xF5,0xCF,0xC5,0xAC,0xD5,0x8D,
	0x36,0x53,0x26,0x72,0x16,0x11,0x06,0x30,0x76,0xD7,0x66,0xF6,0x56,0x95,0x46,0xB4,
	0xB7,0x5B,0xA7,0x7A,0x97,0x19,0x87,0x38,0xF7,0xDF,0xE7,0xFE,0xD7,0x9D,0xC7,0xBC,
	0x48,0xC4,0x58,0xE5,0x68,0x86,0x78,0xA7,0x08,0x40,0x18,0x61,0x28,0x02,0x38,0x23,
	0xC9,0xCC,0xD9,0xED,0xE9,0x8E,0xF9,0xAF,0x89,0x48,0x99,0x69,0xA9,0x0A,0xB9,0x2B,
	0x5A,0xF5,0x4A,0xD4,0x7A,0xB7,0x6A,0x96,0x1A,0x71,0x0A,0x50,0x3A,0x33,0x2A,0x12,
	0xDB,0xFD,0xCB,0xDC,0xFB,0xBF,0xEB,0x9E,0x9B,0x79,0x8B,0x58,0xBB,0x3B,0xAB,0x1A,
	0x6C,0xA6,0x7C,0x87,0x4C,0xE4,0x5C,0xC5,0x2C,0x22,0x3C,0x03,0x0C,0x60,0x1C,0x41,
	0xED,0xAE,0xFD,0x8F,0xCD,0xEC,0xDD,0xCD,0xAD,0x2A,0xBD,0x0B,0x8D,0x68,0x9D,0x49,
	0x7E,0x97,0x6E,0xB6,0x5E,0xD5,0x4E,0xF4,0x3E,0x13,0x2E,0x32,0x1E,0x51,0x0E,0x70,
	0xFF,0x9F,0xEF,0xBE,0xDF,0xDD,0xCF,0xFC,0xBF,0x1B,0xAF,0x3A,0x9F,0x59,0x8F,0x78,

	0x91,0x88,0x81,0xA9,0xB1,0xCA,0xA1,0xEB,0xD1,0x0C,0xC1,0x2D,0xF1,0x4E,0xE1,0x6F,
	0x10,0x80,0x00,0xA1,0x30,0xC2,0x20,0xE3,0x50,0x04,0x40,0x25,0x70,0x46,0x60,0x67,
	0x83,0xB9,0x93,0x98,0xA3,0xFB,0xB3,0xDA,0xC3,0x3D,0xD3,0x1C,0xE3,0x7F,0xF3,0x5E,
	0x02,0xB1,0x12,0x90,0x22,0xF3,0x32,0xD2,0x42,0x35,0x52,0x14,0x62,0x77,0x72,0x56,
	0xB5,0xEA,0xA5,0xCB,0x95,0xA8,0x85,0x89,0xF5,0x6E,0xE5,0x4F,0xD5,0x2C,0xC5,0x0D,
	0x34,0xE2,0x24,0xC3,0x14,0xA0,0x04,0x81,0x74,0x66,0x64,0x47,0x54,0x24,0x44,0x05,
	0xA7,0xDB,0xB7,0xFA,0x87,0x99,0x97,0xB8,0xE7,0x5F,0xF7,0x7E,0xC7,0x1D,0xD7,0x3C,
	0x26,0xD3,0x36,0xF2,0x06,0x91,0x16,0xB0,0x66,0x57,0x76,0x76,0x46,0x15,0x56,0x34,
	0xD9,0x4C,0xC9,0x6D,0xF9,0x0E,0xE9,0x2F,0x99,0xC8,0x89,0xE9,0xB9,0x8A,0xA9,0xAB,
	0x58,0x44,0x48,0x65,0x78,0x06,0x68,0x27,0x18,0xC0,0x08,0xE1,0x38,0x82,0x28,0xA3,
	0xCB,0x7D,0xDB,0x5C,0xEB,0x3F,0xFB,0x1E,0x8B,0xF9,0x9B,0xD8,0xAB,0xBB,0xBB,0x9A,
	0x4A,0x75,0x5A,0x54,0x6A,0x37,0x7A,0x16,0x0A,0xF1,0x1A,0xD0,0x2A,0xB3,0x3A,0x92,
	0xFD,0x2E,0xED,0x0F,0xDD,0x6C,0xCD,0x4D,0xBD,0xAA,0xAD,0x8B,0x9D,0xE8,0x8D,0xC9,
	0x7C,0x26,0x6C,0x07,0x5C,0x64,0x4C,0x45,0x3C,0xA2,0x2C,0x83,0x1C,0xE0,0x0C,0xC1,
	0xEF,0x1F,0xFF,0x3E,0xCF,0x5D,0xDF,0x7C,0xAF,0x9B,0xBF,0xBA,0x8F,0xD9,0x9F,0xF8,
	0x6E,0x17,0x7E,0x36,0x4E,0x55,0x5E,0x74,0x2E,0x93,0x3E,0xB2,0x0E,0xD1,0x1E,0xF0
};    



void UART1Init(void)	//485与回路板通讯
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	//使能串口的RCC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE, ENABLE);//使能GPIOA,D时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//------PA9_TXD  PA10_RXD---UART1-------------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx的GPIO配置为推挽复用模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//都是浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//485_EN
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1,ENABLE);//复位串口1
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1,DISABLE);//停止复位

	//配置串口
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;//USART_Parity_Even;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);//配置串口1
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //使能串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
   
  USART_Cmd(USART1, ENABLE);                    //使能串口 

  RS485_TX_EN_0;			//默认为接收模式
}

void UART2Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	//使能串口的RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//|RCC_APB2Periph_GPIOA

	//配置串口
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);//配置串口2

	// Enable USART1 Receive interrupts 使能串口接收中断
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//串口发送中断在发送数据时开启
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
	// Enable the USART2 
	USART_Cmd(USART2, ENABLE);//使能串口1
}

void UART3Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//使能串口的RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//|RCC_APB2Periph_GPIOA
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3,ENABLE);//复位串口1
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3,DISABLE);//停止复位
	//配置串口
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);//配置串口3

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //使能串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
   
  USART_Cmd(USART3, ENABLE);                    //使能串口 

  TREN_PC_OFF();			//默认为接收模式
}

void UART4Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	//使能串口的RCC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//|RCC_APB2Periph_GPIOA
	//配置串口
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);//配置串口2

	// Enable USART1 Receive interrupts 使能串口接收中断
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	//串口发送中断在发送数据时开启
	USART_Cmd(UART4, ENABLE);//使能串口1
}
 
void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN_1;			//设置为发送模式
	Delay1ms(1);
	for(t=0;t<len;t++)		//循环发送数据
	{		   
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	  
		USART_SendData(USART1,buf[t]);
	}	 

	Delay1ms(1);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	RS485_TX_EN_0;				//设置为接收模式	
}


uint16_t CRC_16(uint8_t *dat,uint8_t lenth)//dat[]为接收校验数组的首地址，lenth进行校验数组的长度
{
   uint8_t i,j;
   uint16_t temp,CRCR=0x0FFFF;
	
   for(i=0;i<lenth;i++)
   {
      CRCR^=dat[i];

      for(j=0;j<=7;j++)  //8位
      {
         //LSB=(bit)(CRC & 0x0001 );
         if((CRCR & 0x0001 )==1)
				 {
					 CRCR=CRCR>>1;
           CRCR^=0xA001;
				 }
				 else CRCR=CRCR>>1;
         
       }
    }
    temp=CRCR;
    CRCR=((temp<<8)&0xFF00)|((temp>>8)&0X00FF);//高低字节交换
   return (CRCR);
}

//------------------------------------------------------
/*
void SendToDOOR(void)
{ 
   uint8_t i,length,temp;
   uint16_t CRC16;

   Power_LED_ON(); 
    length=Send_Buff[0];
  
    temp =0x5A;   //帧头        
    USART_SendData(USART1, temp);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}	//等待发送结束
		
    for (i=0;i<length+1;i++)
	  {
       temp =Send_Buff[i];        
       USART_SendData(USART1, temp);
       while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}	//等待发送结束 
		
     }
   
    CRC16=CRC_16(&Send_Buff[1],length);//校验
    temp =CRC16/256;        
    USART_SendData(USART1, temp);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}	//等待发送结束

    temp =CRC16%256;        
    USART_SendData(USART1, temp);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){}	//等待发送结束
		
    //发送完毕
    Power_LED_OFF();
 }
 */
//--------------------------------------------------------------------------------
void SendToKEY(void)
{ 
		uint8_t i,length,temp;
		uint16_t CRC16;

		//TREN_KEY_ON();
		length=SendKEY_Buff[0];

		temp =0x5A;   //帧头        
		USART_SendData(USART2, temp);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		
		for (i=0;i<length+1;i++)
		{
			temp =SendKEY_Buff[i];        
			USART_SendData(USART2, temp);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		}
   
    CRC16=CRC_16(&SendKEY_Buff[1],length);//校验
    temp =CRC16/256;        
    USART_SendData(USART2, temp);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */

    temp =CRC16%256;        
    USART_SendData(USART2, temp);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		
    //发送完毕
    //TREN_KEY_OFF();
 }
 
 
 void ASCcrc(uint8_t num)					 // 实总数 补CRC码为ASC 和# 
{
	unsigned int i,tbdptr=0;
	unsigned char ascarr[4];
	unsigned char crc_h = 0xff,crc_l = 0xff;
	unsigned char carry = 0x00,worka,work5,work6;


	for ( i = 0; i < num; i++ )
	{
		crc_h = SendPC_Buff[i] ^ crc_h;
		carry = crc_h & 0x80;
		crc_h = crc_h << 1;
		worka = crc_h;

		if ( carry == 0x80 )
		{
			tbdptr=0x100;
		}
        else
		{
			tbdptr=0x00;
		}
		
    //work5 =pgm_read_byte(&crc_table[worka+tbdptr]);
		work5 = crc_table[worka + tbdptr];

		worka = crc_h;
		worka ++;
		//work6 =pgm_read_byte(&crc_table[worka+tbdptr]);
		work6 = crc_table[worka + tbdptr];

		crc_h = work5 ^ crc_l;
		crc_l = work6;
  }
  		
	crc_h = ~crc_h;
	crc_l = ~crc_l;		

 
//		 SBUF =  crc_h;//Uart1_state_check[i];                          //发送数据时子串口选择端输出选择子串口
       
//        while(TI == 0)
//	    {
//	    }
//		TI = 0; 

//	 SBUF =  crc_l;//Uart1_state_check[i];                          //发送数据时子串口选择端输出选择子串口
       
//        while(TI == 0)
//	    {
//	    }
//		TI = 0; 
		//2010/03/24  
//		ASCStr[num]     =  crc_h;
//		ASCStr[num + 1] =  crc_l;

		//worka=ASCStr[0];		   //实总数
		
	//	sprintf( ascarr, "%03d", crc_h );

    ascarr[0] = crc_h/100 + 0x30;
		ascarr[1] = crc_h%100/10 + 0x30;
		ascarr[2] = crc_h%100%10 + 0x30;

		SendPC_Buff[num] =  ascarr[0];//100;
//			 SBUF =  ascarr[0];//Uart1_state_check[i];                          //发送数据时子串口选择端输出选择子串口
       
  //      while(TI == 0)
	//    {
	  //  }
		//TI = 0; 
		SendPC_Buff[num + 1] =  ascarr[1];
	//		 SBUF =  ascarr[1];//Uart1_state_check[i];                          //发送数据时子串口选择端输出选择子串口
       
    //    while(TI == 0)
	  //  {
	    //}
		//TI = 0; 
		SendPC_Buff[num + 2] =  ascarr[2];
	//		 SBUF =  ascarr[2];//Uart1_state_check[i];                          //发送数据时子串口选择端输出选择子串口
       
      //  while(TI == 0)
	   // {
	    //}
	//	TI = 0; 
		
//		sprintf( ascarr, "%03d", crc_l );
    ascarr[0] = crc_l/100 + 0x30;
		ascarr[1] = crc_l%100/10 + 0x30;
		ascarr[2] = crc_l%100%10 + 0x30;
		SendPC_Buff[num + 3] = ascarr[0];
		SendPC_Buff[num + 4] = ascarr[1];
		SendPC_Buff[num + 5] = ascarr[2];

		//ASCStr[0]='@';
		SendPC_Buff[num + 6] =  '#';
	
}
void SendDataToPC(uint8_t length)//发送至PC机
{ 
	uint8_t i,temp;
	uint16_t WaitT;

	TREN_PC_ON();
	for (i=0;i<length;i++)
	{
		temp =SendPC_Buff[i];        
		USART_SendData(USART3, temp);

		WaitT=0;
		while ((USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	/* 等待发送结束 */
	}//发送完毕

	TREN_PC_OFF();
}    
/*****************************************************
报警类型
0x31 漏电报警
0x32 温度报警
0x33 电弧报警
0x34 过流报警
0x41 通讯故障
0x42 通道故障
*******************************************************/
void  SendToPC1(uint8_t Command,uint8_t TCQ_Num,uint8_t TDH,uint8_t type)//连接监控平台
{
	switch(Command)
	{
		case 1://故障
		{
			//	datalen = 27;//40 464952 303031 303135 3130 3034 3236 3130 3537  303033303837 23
			SendPC_Buff[0] = '@'; // 信息
			SendPC_Buff[1] = 'F';
			SendPC_Buff[2] = 'A';
			SendPC_Buff[3] = 'U';

			SendPC_Buff[4] = Self_Addr/100+0X30;// 回路号---主机机地址
			SendPC_Buff[5] = Self_Addr%100/10+0X30;
			SendPC_Buff[6] = Self_Addr%10+0X30;				

			SendPC_Buff[7] = TCQ_Num/100+0X30;// 地址号--探测器地址
			SendPC_Buff[8] = TCQ_Num%100/10+0X30;
			SendPC_Buff[9] = TCQ_Num%10+0x30;				

//		SendPC_Buff[10] = TDH/100+0X30;// 地址号--通道号
//		SendPC_Buff[11] = TDH%100/10+0X30;
//		SendPC_Buff[12] = TDH%10+0x30;				
//		SendPC_Buff[13] = type;	
			
			SendPC_Buff[10] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[11] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[12] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[13] = Real_Time.month%10+0X30;
			SendPC_Buff[14] = Real_Time.day/10+0X30;
			SendPC_Buff[15] = Real_Time.day%10+0X30;				
			SendPC_Buff[16] = Real_Time.hour/10+0X30;
			SendPC_Buff[17] = Real_Time.hour%10+0X30;
			SendPC_Buff[18] = Real_Time.min/10+0X30;				
			SendPC_Buff[19] = Real_Time.min%10+0X30;	
			ASCcrc(20);
			SendDataToPC(27);
			break;	
		}
		case 2:// 故障恢复
		{
			//datalen = 27;//40 464952 303031 303135 3130 3034 3236 3130 3537  303033303837 23
			SendPC_Buff[0] = '@';            // 信息

			SendPC_Buff[1] = 'F';
			SendPC_Buff[2] = 'A';
			SendPC_Buff[3] = 'R';

			SendPC_Buff[4] = Self_Addr/100+0X30;// 回路号---机地址
			SendPC_Buff[5] = Self_Addr%100/10+0X30;
			SendPC_Buff[6] = Self_Addr%10+0X30;		

			SendPC_Buff[7] = TCQ_Num/100+0X30;// 地址号--探测器地址
			SendPC_Buff[8] = TCQ_Num%100/10+0X30;
			SendPC_Buff[9] = TCQ_Num%10+0x30;				

//			SendPC_Buff[10] = TDH/100+0X30;// 地址号--通道号
//			SendPC_Buff[11] = TDH%100/10+0X30;
//			SendPC_Buff[12] = TDH%10+0x30;				
//			SendPC_Buff[13] = type;	

			SendPC_Buff[10] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[11] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[12] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[13] = Real_Time.month%10+0X30;
			SendPC_Buff[14] = Real_Time.day/10+0X30;
			SendPC_Buff[15] = Real_Time.day%10+0X30;				
			SendPC_Buff[16] = Real_Time.hour/10+0X30;
			SendPC_Buff[17] = Real_Time.hour%10+0X30;
			SendPC_Buff[18] = Real_Time.min/10+0X30;				
			SendPC_Buff[19] = Real_Time.min%10+0X30;	
			ASCcrc(20);
			SendDataToPC(27);
			break;	
		}
    case 3://启动
		{
			
			SendPC_Buff[0] = '@';            // 信息

			SendPC_Buff[1] = 'S';
			SendPC_Buff[2] = 'T';
			SendPC_Buff[3] = 'A';
			SendPC_Buff[4] = '/';                                                                                                                       
			SendPC_Buff[5] = 'S';
			SendPC_Buff[6] = 'T';
			SendPC_Buff[7] = 'I';

			SendPC_Buff[8] = Self_Addr/100+0X30;// 回路号---机地址
			SendPC_Buff[9] = Self_Addr%100/10+0X30;
			SendPC_Buff[10] = Self_Addr%10+0X30;		

			SendPC_Buff[11] = TCQ_Num/100+0X30;// 地址号--探测器地址
			SendPC_Buff[12] = TCQ_Num%100/10+0X30;
			SendPC_Buff[13] = TCQ_Num%10+0x30;				

			SendPC_Buff[14] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[15] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[16] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[17] = Real_Time.month%10+0X30;
			SendPC_Buff[18] = Real_Time.day/10+0X30;
			SendPC_Buff[19] = Real_Time.day%10+0X30;				
			SendPC_Buff[20] = Real_Time.hour/10+0X30;
			SendPC_Buff[21] = Real_Time.hour%10+0X30;
			SendPC_Buff[22] = Real_Time.min/10+0X30;				
			SendPC_Buff[23] = Real_Time.min%10+0X30;	
			ASCcrc(24);
			SendDataToPC(31);
			break;	
		}
		case 4://报警信息
		{
			SendPC_Buff[0] = '@'; // 报警信息
			SendPC_Buff[1] = 'F';
			SendPC_Buff[2] = 'I';
			SendPC_Buff[3] = 'R';

			SendPC_Buff[4] = Self_Addr/100+0X30;// 回路号---主机机地址
			SendPC_Buff[5] = Self_Addr%100/10+0X30;
			SendPC_Buff[6] = Self_Addr%10+0X30;				

			SendPC_Buff[7] = TCQ_Num/100+0X30;// 地址号--探测器地址
			SendPC_Buff[8] = TCQ_Num%100/10+0X30;
			SendPC_Buff[9] = TCQ_Num%10+0x30;				

//		SendPC_Buff[10] = TDH/100+0X30;// 地址号--通道号
//		SendPC_Buff[11] = TDH%100/10+0X30;
//		SendPC_Buff[12] = TDH%10+0x30;				
//		SendPC_Buff[13] = type;	
			
			SendPC_Buff[10] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[11] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[12] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[13] = Real_Time.month%10+0X30;
			SendPC_Buff[14] = Real_Time.day/10+0X30;
			SendPC_Buff[15] = Real_Time.day%10+0X30;				
			SendPC_Buff[16] = Real_Time.hour/10+0X30;
			SendPC_Buff[17] = Real_Time.hour%10+0X30;
			SendPC_Buff[18] = Real_Time.min/10+0X30;				
			SendPC_Buff[19] = Real_Time.min%10+0X30;	
			ASCcrc(20);
			SendDataToPC(27);
			
			break;
		}
		
		 case 5://反馈
		{
			
	        SendPC_Buff[0] = '@';            // 信息

	        SendPC_Buff[1] = 'F';
   	      SendPC_Buff[2] = 'E';
	        SendPC_Buff[3] = 'E';
			    SendPC_Buff[4] = '/';
          SendPC_Buff[5] = 'F';
   	      SendPC_Buff[6] = 'E';
	        SendPC_Buff[7] = 'I';
			
          SendPC_Buff[8] = Self_Addr/100+0X30;// 回路号---机地址
	        SendPC_Buff[9] = Self_Addr%100/10+0X30;
	        SendPC_Buff[10] = Self_Addr%10+0X30;		
            
	        SendPC_Buff[11] = TCQ_Num/100+0X30;// 地址号--探测器地址
	        SendPC_Buff[12] = TCQ_Num%100/10+0X30;
	        SendPC_Buff[13] = TCQ_Num%10+0x30;				
 
           SendPC_Buff[14] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
	        SendPC_Buff[15] = Real_Time.year%2000%10+0X30;
	         SendPC_Buff[16] = Real_Time.month/10+0X30;					//报文长度低字节
	        SendPC_Buff[17] = Real_Time.month%10+0X30;
	        SendPC_Buff[18] = Real_Time.day/10+0X30;
	        SendPC_Buff[19] = Real_Time.day%10+0X30;				
	        SendPC_Buff[20] = Real_Time.hour/10+0X30;
	        SendPC_Buff[21] = Real_Time.hour%10+0X30;
	        SendPC_Buff[22] = Real_Time.min/10+0X30;				
          SendPC_Buff[23] = Real_Time.min%10+0X30;	
          ASCcrc(24);
          SendDataToPC(31);
			     break;	
					
		}
		case 6://反馈恢复
		{
			SendPC_Buff[0] = '@';            // 信息

			SendPC_Buff[1] = 'F';
			SendPC_Buff[2] = 'E';
			SendPC_Buff[3] = 'R';

			SendPC_Buff[4] = Self_Addr/100+0X30;// 回路号---机地址
			SendPC_Buff[5] = Self_Addr%100/10+0X30;
			SendPC_Buff[6] = Self_Addr%10+0X30;		

			SendPC_Buff[7] = TCQ_Num/100+0X30;// 地址号--探测器地址
			SendPC_Buff[8] = TCQ_Num%100/10+0X30;
			SendPC_Buff[9] = TCQ_Num%10+0x30;				

			SendPC_Buff[10] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[11] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[12] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[13] = Real_Time.month%10+0X30;
			SendPC_Buff[14] = Real_Time.day/10+0X30;
			SendPC_Buff[15] = Real_Time.day%10+0X30;				
			SendPC_Buff[16] = Real_Time.hour/10+0X30;
			SendPC_Buff[17] = Real_Time.hour%10+0X30;
			SendPC_Buff[18] = Real_Time.min/10+0X30;				
			SendPC_Buff[19] = Real_Time.min%10+0X30;	
			ASCcrc(20);
			SendDataToPC(27);
			break;	
					
		}
		case 7://主电故障
		{
			SendPC_Buff[0] = '@'; // 报警信息
			SendPC_Buff[1] = 'A';
			SendPC_Buff[2] = 'C';
			SendPC_Buff[3] = 'F';
		
			SendPC_Buff[4] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[5] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[6] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[7] = Real_Time.month%10+0X30;
			SendPC_Buff[8] = Real_Time.day/10+0X30;
			SendPC_Buff[9] = Real_Time.day%10+0X30;				
			SendPC_Buff[10] = Real_Time.hour/10+0X30;
			SendPC_Buff[11] = Real_Time.hour%10+0X30;
			SendPC_Buff[12] = Real_Time.min/10+0X30;				
			SendPC_Buff[13] = Real_Time.min%10+0X30;	
			ASCcrc(14);
			SendDataToPC(21);
			break;
		}
		case 8://主电恢复
		{
			SendPC_Buff[0] = '@'; // 报警信息
			SendPC_Buff[1] = 'A';
			SendPC_Buff[2] = 'C';
			SendPC_Buff[3] = 'N';
		
			SendPC_Buff[4] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[5] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[6] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[7] = Real_Time.month%10+0X30;
			SendPC_Buff[8] = Real_Time.day/10+0X30;
			SendPC_Buff[9] = Real_Time.day%10+0X30;				
			SendPC_Buff[10] = Real_Time.hour/10+0X30;
			SendPC_Buff[11] = Real_Time.hour%10+0X30;
			SendPC_Buff[12] = Real_Time.min/10+0X30;				
			SendPC_Buff[13] = Real_Time.min%10+0X30;	
			ASCcrc(14);
			SendDataToPC(21);
			break;
		}
		case 9://备电故障
		{
			SendPC_Buff[0] = '@'; // 报警信息
			SendPC_Buff[1] = 'B';
			SendPC_Buff[2] = 'T';
			SendPC_Buff[3] = 'F';
		
			SendPC_Buff[4] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[5] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[6] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[7] = Real_Time.month%10+0X30;
			SendPC_Buff[8] = Real_Time.day/10+0X30;
			SendPC_Buff[9] = Real_Time.day%10+0X30;				
			SendPC_Buff[10] = Real_Time.hour/10+0X30;
			SendPC_Buff[11] = Real_Time.hour%10+0X30;
			SendPC_Buff[12] = Real_Time.min/10+0X30;				
			SendPC_Buff[13] = Real_Time.min%10+0X30;	
			ASCcrc(14);
			SendDataToPC(21);
			break;
		}
		case 10://备电恢复
		{
			SendPC_Buff[0] = '@'; // 报警信息
			SendPC_Buff[1] = 'B';
			SendPC_Buff[2] = 'T';
			SendPC_Buff[3] = 'N';
		
			SendPC_Buff[4] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[5] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[6] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[7] = Real_Time.month%10+0X30;
			SendPC_Buff[8] = Real_Time.day/10+0X30;
			SendPC_Buff[9] = Real_Time.day%10+0X30;				
			SendPC_Buff[10] = Real_Time.hour/10+0X30;
			SendPC_Buff[11] = Real_Time.hour%10+0X30;
			SendPC_Buff[12] = Real_Time.min/10+0X30;				
			SendPC_Buff[13] = Real_Time.min%10+0X30;	
			ASCcrc(14);
			SendDataToPC(21);
			break;
		}
		
    case 11:// 查询 40 494E51 3031 313634  303532 23
		{
			SendPC_Buff[0] = '@'; // 信息
			SendPC_Buff[1] = 'I';
			SendPC_Buff[2] = 'N';
			SendPC_Buff[3] = 'Q';
			// 控制号
			SendPC_Buff[4] = 0X30;// 
			SendPC_Buff[5] = 0X30;// 
			SendPC_Buff[6] = 0X31;
			ASCcrc(7);
			SendDataToPC(14);
			break;	
		}
		case 12:// 复位40 525354 3130 3034 3236 3130 3534  313836313034 23
		{
		//	datalen = 21;
			SendPC_Buff[0] = '@';
			SendPC_Buff[1] = 'R';
			SendPC_Buff[2] = 'S';
			SendPC_Buff[3] = 'T';

			SendPC_Buff[4] = Real_Time.year%2000/10+0X30;    //读时间：年月日时分－－[0]..[4]
			SendPC_Buff[5] = Real_Time.year%2000%10+0X30;
			SendPC_Buff[6] = Real_Time.month/10+0X30;					//报文长度低字节
			SendPC_Buff[7] = Real_Time.month%10+0X30;
			SendPC_Buff[8] = Real_Time.day/10+0X30;
			SendPC_Buff[9] = Real_Time.day%10+0X30;				
			SendPC_Buff[10] = Real_Time.hour/10+0X30;
			SendPC_Buff[11] = Real_Time.hour%10+0X30;
			SendPC_Buff[12] = Real_Time.min/10+0X30;				
			SendPC_Buff[13] = Real_Time.min%10+0X30;	
			ASCcrc(14);
			SendDataToPC(21);
			break;	
		}

		default:break;	
	
	}

}

void SendToPC(void)
{ 
   uint8_t i,length,temp;
   uint16_t CRC16;

    TREN_PC_ON();
    length=SendPC_Buff[0];
  
    temp =0xA5;   //帧头        
    USART_SendData(USART3, temp);
  	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		
    for (i=0;i<length+1;i++)
	  {
       temp =SendPC_Buff[i];        
       USART_SendData(USART3, temp);
      while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		
     }
   
    CRC16=CRC_16(&SendPC_Buff[1],length);//校验
    temp =CRC16/256;        
    USART_SendData(USART3, temp);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */

    temp =CRC16%256;        
    USART_SendData(USART3, temp);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){}	/* 等待发送结束 */
		TREN_PC_OFF();
    //发送完毕

 }

void Begin_Print(uint16_t Num,uint8_t *Mg,uint8_t *Dt)
{
		uint8_t i,temp;
		uint16_t WaitT=0;

    temp=0x1B;     //打印机初始化
	  USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

    temp=0x40;
    USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

//------------------------------
		for (i=0;i<8;i++)
		{ 
			 temp=0x20;    //' '
			 USART_SendData(UART4, temp);
			 WaitT=0;
			 while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

		 }
		 
    for (i=0;i<strlen(Dt);i++)
    { 
      temp=Dt[i];  //打印日期
			USART_SendData(UART4, temp);
      WaitT=0;
    	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	 
    }    
    
    temp=0x0A;   //打印并换行
		USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	


    temp=0x0D;
		USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	
//-------------------------------  
    temp=Num/10000+0x30;//序号
		USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	


    temp=Num%10000/1000+0x30;
		USART_SendData(UART4, temp);
     WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

    temp=Num%1000/100+0x30;
		USART_SendData(UART4, temp);
     WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	


    temp=Num%100/10+0x30;
		USART_SendData(UART4, temp);
     WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

    temp=Num%10+0x30;
		USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	


    for (i=0;i<3;i++)
    { 
       temp=0x20;//' '
			 USART_SendData(UART4, temp);
       WaitT=0;
  	   while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

     }

		for (i=0;i<(strlen(Mg));i++)
		{ 
			temp=Mg[i];//信息
			USART_SendData(UART4, temp);
			WaitT=0;
			while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	
		}
  
		temp=0x0A;   //打印并换行
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

		temp=0x0D;
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

//------------------------------
		temp=0x0A;   //打印并换行
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

		temp=0x0D;
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

		for (i=0;i<30;i++)
		{ 
			temp=0x3D;//=
			USART_SendData(UART4, temp);
			WaitT=0;
			while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	
		}
  
		temp =0x1B;         //打印并换行
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

    temp=0x64;
		USART_SendData(UART4, temp);
    WaitT=0;
  	while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	

		temp=0x1;
		USART_SendData(UART4, temp);
		WaitT=0;
		while ((USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)&&(WaitT<0xFFFF)){WDOG();WaitT++;}	
} 


