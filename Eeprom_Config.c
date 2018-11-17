#include "stm32f10x.h"
#include "declare.h"

#define  ERRORCOUNT 10

#define I2C_SDA_1()  GPIO_SetBits(GPIOE,GPIO_Pin_8) 
#define I2C_SDA_0()  GPIO_ResetBits(GPIOE,GPIO_Pin_8) 

#define I2C_SCL_1()  GPIO_SetBits(GPIOE,GPIO_Pin_9) 
#define I2C_SCL_0()  GPIO_ResetBits(GPIOE,GPIO_Pin_9) 

#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)	/* 读SDA口线状态 */

T_Struct1 System;

/**********************************************************************************************************
*	函 数 名: i2c_Delay
*	功能说明: I2C总线位延迟，最快400KHz
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Delay(void)
{
	uint8_t i;
  for (i = 0; i < 10; i++);
	/*　
	 	下面的时间是通过安富莱AX-Pro逻辑分析仪测试得到的。
		CPU主频72MHz时，在内部Flash运行, MDK工程不优化
		循环次数为10时，SCL频率 = 205KHz 
		循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
	 	循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 
    IAR工程编译效率高，不能设置为7
	*/
	
	}


//DataBuff为读写数据输入／输出缓冲区的首址
//ByteQuantity 为要读写数据的字节数量
//Address 为EEPROM的片内地址
//ControlByte 为EEPROM的控制字节，具体形式为(1)(0)(1)(0)(A2)(A1)(A0)(R/W),其中R/W=1,
//表示读操作,R/W=0为写操作,A2,A1,A0为EEPROM的页选或片选地址;
//EepromType为枚举变量,需为M2401至M24256中的一种,分别对应24C01至24C256;
//函数返回值为一个位变量，若返回1表示此次操作失效，0表示操作成功;
//ERRORCOUNT为允许最大次数，若出现ERRORCOUNT次操作失效后，则函数中止操作，并返回1
//SDA和SCL由用户自定义，这里暂定义为P0^0和P0^1;
//其余的用户不用管，只要把只子程序放在你的程序中并调用它就可以了;


/***********************************************************************************/
uint8_t RW24XX(uint8_t *DataBuff,uint8_t ByteQuantity,uint32_t Address,uint8_t ControlByte)//,enum eepromtype EepromType)
{

void IICStart(void);
void IICStop(void);
uint8_t  IICRecAck(void);
void IICNoAck(void);
void IICAck(void);
uint8_t IICReceiveByte(void);
void IICSendByte(unsigned char sendbyte);
uint8_t j,i=ERRORCOUNT;
uint8_t      errorflag=1;

while(i--)
   {
		 
   IICStart();
   IICSendByte((ControlByte&0xfe)|(Address&0x060000));
   if(IICRecAck())
       continue;
 //  if(EepromType>M2416)
   //   {
      IICSendByte((unsigned char)(Address>>8));
      if(IICRecAck())
         continue;
  //    }
   IICSendByte((unsigned char)Address);
   if(IICRecAck())
       continue;
   if(!(ControlByte&0x01))
      {
      j=ByteQuantity;
      errorflag=0;                      //********clr errorflag
      while(j--)
        {
        IICSendByte(*DataBuff++);
        if(!IICRecAck())
           continue;
        errorflag=1;
        break;
        }
      if(errorflag==1)
        continue;
      break;
      }
   else
     {
     IICStart();
     IICSendByte(ControlByte);
     if(IICRecAck())
       continue;
     while(--ByteQuantity)
       {
       *DataBuff++=IICReceiveByte();
       IICAck();
       }
     *DataBuff=IICReceiveByte();        //read last byte data
     IICNoAck();
     errorflag=0;
     break;
     }
  }
IICStop();


if(!(ControlByte&0x01))
  {
  Delay1us(255);
  Delay1us(255);
  Delay1us(255);
  Delay1us(255);
  }

return(errorflag);

}
/***********************************************************************************/
uint8_t RW24XX_1(uint8_t *DataBuff,uint8_t ByteQuantity,uint32_t Address,uint8_t ControlByte)//,enum eepromtype EepromType)
{
//void Delay1(unsigned char DelayCount);
void IICStart(void);
void IICStop(void);
uint8_t  IICRecAck(void);
void IICNoAck(void);
void IICAck(void);
unsigned char IICReceiveByte(void);
void IICSendByte(unsigned char sendbyte);
uint8_t j,i=ERRORCOUNT;
uint8_t      errorflag=1;

while(i--)
   {
   IICStart();
   IICSendByte(ControlByte&0xfe);
   if(IICRecAck())
       continue;
 //  if(EepromType>M2416)
   //   {
      IICSendByte((unsigned char)(Address>>8));
      if(IICRecAck())
         continue;
  //    }
   IICSendByte((unsigned char)Address);
   if(IICRecAck())
       continue;
   if(!(ControlByte&0x01))
      {
      j=ByteQuantity;
      errorflag=0;                      //********clr errorflag
      while(j--)
        {
        IICSendByte(*DataBuff++);
        if(!IICRecAck())
           continue;
        errorflag=1;
        break;
        }
      if(errorflag==1)
        continue;
      break;
      }
   else
     {
     IICStart();
     IICSendByte(ControlByte);
     if(IICRecAck())
       continue;
     while(--ByteQuantity)
       {
       *DataBuff++=IICReceiveByte();
       IICAck();
       }
     *DataBuff=IICReceiveByte();        //read last byte data
     IICNoAck();
     errorflag=0;
     break;
     }
  }
	IICStop();

	if(!(ControlByte&0x01))
	{
		Delay1us(255);
		Delay1us(255);
		Delay1us(255);
		Delay1us(255);
	}

return(errorflag);

}


/*****************以下是对IIC总线的操作子程序***/
/*****************启动总线**********************/
void IICStart(void)
{
 	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();       //
}

/*****************停止IIC总线****************/
void IICStop(void)
{
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_0();
}
void IICAck(void)
{
    I2C_SDA_0();	/* CPU驱动SDA = 0 */
		i2c_Delay();
		I2C_SCL_1();	/* CPU产生1个时钟 */
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
		I2C_SDA_1();	/* CPU释放SDA总线 */
}
/**************检查应答位*******************/
uint8_t IICRecAck(void)
{
	uint8_t RValue;

	I2C_SDA_1();	/* CPU释放SDA总线 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
	RValue=I2C_SDA_READ();	/* CPU读取SDA口线状态 */
	
	I2C_SCL_0();
  i2c_Delay();
	return RValue;
	
}

/***************对IIC总线产生应答*******************/
void IICACK(void)
{

	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();
}

/*****************不对IIC总线产生应答***************/
void IICNoAck(void)
{
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*******************向IIC总线写数据*********************/
void IICSendByte(unsigned char sendbyte)
{
	 uint8_t i;

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (sendbyte & 0x80)
		{
			I2C_SDA_1();
			}
		else
		{
			I2C_SDA_0();
			}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if (i == 7)
		{
			 I2C_SDA_1(); // 释放总线
			}
		sendbyte <<= 1;	/* 左移一个bit */
		i2c_Delay();
	}

}


/**********************从IIC总线上读数据子程序**********/
uint8_t IICReceiveByte(void)
{
	 
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return value;
}


