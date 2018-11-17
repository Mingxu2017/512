#include "stm32f10x.h"
#include "Declare.h"
void GPIO_Confing(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��������Ϊ�������롢�������롢�������롢���������
	//��©����ȶ��ֹ���ģʽ��
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);/* ��GPIOF��ʱ�� */

		 
//��Դָʾ��LED PE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* �������ģʽ, */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* ����GPIO���������Ƶ�ʣ������ٶȿ�������GPIO�ź������ص��������� */
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//-------------------------------------------------------------	

//״ָ̬ʾ�� SCLK2=PE11 SLCK2=PE12 SDA=PE13
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
//-----------------------------------------------------------------
 //WDOG=PE10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ����Ϊ�������ģʽ, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//----------------------------------------------------------		
//��ʾ��

//RST= PD8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//RST
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//RS= PB14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//RS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//WR = PB12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//WR
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//RD = PB13
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//A0 = PB15  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//DB0~DB6 = PD9~PD15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//DB7 = PC6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	// ����Ϊ��©�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
//��ʾ���ı������ BACK = PC8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ����Ϊ�������ģʽ, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
//��ӡ��c10 c11 a15
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //����ź�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //��ӡ�����룬δ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //��ӡ��æ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//------------------------------------------------------------------
//CS1  RD2
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;///
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//-------------------------------------------------------------	
//���� PA4 PA5 PA6 PA7 PC4 PC5
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //�ⲿ�������������裬����ѡ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //�ⲿ�������������裬����ѡ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
//-----------------------------------------------------------------
 	
  //��������PB1  ���ȣ�PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// ����Ϊ�������ģʽ, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//------------------------------------------------------------------
//PB3=ZD   BDKC CDKC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//��ֹSW+JTAG  PA15\PB4\PB3

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//ZD��⣬��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//BDKC CDKC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// GPIO_Mode_AF_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	CDK_OFF();//Ĭ�ϳ��ر�
//------------------------------------------------------------------
//PA0 ��Ϊģ��ͨ����������,��ⱸ���ѹ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 //------------------------------------------------------------

//256 PE9=I2C_SCL  PE8=I2C_SDA 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//��©������ⲿ��Ҫ���������� GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

//--------------------------------------
//PD3 PD4 PD5  �̵�������
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;///
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	KC1_OFF();
	KC2_OFF();
	Set_World_Flag_Flag(2,0);//���ָʾ����
	Dis_State_LED();//״ָ̬ʾ����ʾ	
//-----------------------------------------------------------------

//------PA9_TXD  PA10_RXD---UART1-------------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//���Ǹ�������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//485_EN
	GPIO_Init(GPIOE, &GPIO_InitStructure);
//-------PA8=RX----PA9=TX ------UART1---------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//------PA2_TXD  PA3_RXD-----------UART2-----------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//����RXD��������ģʽ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����RXD��������ģʽ
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

//CS1 = PA13 ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//CS1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

//TREN_PA1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
//------PB10_TXD  PB11_RXD-----------UART3-----------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//���Ǹ�������ģʽ
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	//TREN_PE15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//-----------------------------------------------------------------------------------
  //CANͨѶ�˿�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	  // canѡ����PA11��PA12��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//-----------------------------------------------------------
}
