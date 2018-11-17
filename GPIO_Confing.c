#include "stm32f10x.h"
#include "Declare.h"
void GPIO_Confing(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//可以设置为浮空输入、上拉输入、下拉输入、推挽输出、
	//开漏输出等多种工作模式，
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);/* 打开GPIOF的时钟 */

		 
//电源指示灯LED PE14
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* 输出推挽模式, */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* 设置GPIO工作的最大频率，降低速度可以抑制GPIO信号跳变沿的振铃现象 */
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//-------------------------------------------------------------	

//状态指示灯 SCLK2=PE11 SLCK2=PE12 SDA=PE13
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
//-----------------------------------------------------------------
 //WDOG=PE10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 设置为输出推挽模式, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//----------------------------------------------------------		
//显示屏

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	// 设置为开漏极输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
//显示屏的背光控制 BACK = PC8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 设置为输出推挽模式, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
//打印机c10 c11 a15
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //输出信号
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //打印机输入，未用
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //打印机忙
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
//------------------------------------------------------------------
//CS1  RD2
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;///
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//-------------------------------------------------------------	
//按键 PA4 PA5 PA6 PA7 PC4 PC5
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //外部设置了上拉电阻，所以选浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	 //外部设置了上拉电阻，所以选浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
//-----------------------------------------------------------------
 	
  //蜂鸣器＝PB1  喇叭＝PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// 设置为输出推挽模式, 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//------------------------------------------------------------------
//PB3=ZD   BDKC CDKC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//禁止SW+JTAG  PA15\PB4\PB3

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//ZD检测，上拉输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//BDKC CDKC
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// GPIO_Mode_AF_PP;//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	
	CDK_OFF();//默认充电关闭
//------------------------------------------------------------------
//PA0 作为模拟通道输入引脚,检测备电电压
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 //------------------------------------------------------------

//256 PE9=I2C_SCL  PE8=I2C_SDA 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出，外部需要加上拉电阻 GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

//--------------------------------------
//PD3 PD4 PD5  继电器控制
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;///
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	KC1_OFF();
	KC2_OFF();
	Set_World_Flag_Flag(2,0);//输出指示灯灭
	Dis_State_LED();//状态指示灯显示	
//-----------------------------------------------------------------

//------PA9_TXD  PA10_RXD---UART1-------------------------------------------
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx的GPIO配置为推挽复用模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//都是浮空输入模式
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx的GPIO配置为推挽复用模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置RXD浮空输入模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//设置RXD浮空输入模式
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

//CS1 = PA13 复用输出脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//CS1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 //复用输出脚
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//Tx的GPIO配置为推挽复用模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//都是浮空输入模式
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
	//TREN_PE15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//-----------------------------------------------------------------------------------
  //CAN通讯端口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	  // can选的是PA11和PA12口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//-----------------------------------------------------------
}
