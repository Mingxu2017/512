#include "stm32f10x.h"
#include "declare.h"

#define  ERRORCOUNT 10

#define I2C_SDA_1()  GPIO_SetBits(GPIOE,GPIO_Pin_8) 
#define I2C_SDA_0()  GPIO_ResetBits(GPIOE,GPIO_Pin_8) 

#define I2C_SCL_1()  GPIO_SetBits(GPIOE,GPIO_Pin_9) 
#define I2C_SCL_0()  GPIO_ResetBits(GPIOE,GPIO_Pin_9) 

#define I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)	/* ��SDA����״̬ */

T_Struct1 System;

/**********************************************************************************************************
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Delay(void)
{
	uint8_t i;
  for (i = 0; i < 10; i++);
	/*��
	 	�����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
    IAR���̱���Ч�ʸߣ���������Ϊ7
	*/
	
	}


//DataBuffΪ��д�������룯�������������ַ
//ByteQuantity ΪҪ��д���ݵ��ֽ�����
//Address ΪEEPROM��Ƭ�ڵ�ַ
//ControlByte ΪEEPROM�Ŀ����ֽڣ�������ʽΪ(1)(0)(1)(0)(A2)(A1)(A0)(R/W),����R/W=1,
//��ʾ������,R/W=0Ϊд����,A2,A1,A0ΪEEPROM��ҳѡ��Ƭѡ��ַ;
//EepromTypeΪö�ٱ���,��ΪM2401��M24256�е�һ��,�ֱ��Ӧ24C01��24C256;
//��������ֵΪһ��λ������������1��ʾ�˴β���ʧЧ��0��ʾ�����ɹ�;
//ERRORCOUNTΪ������������������ERRORCOUNT�β���ʧЧ��������ֹ������������1
//SDA��SCL���û��Զ��壬�����ݶ���ΪP0^0��P0^1;
//������û����ùܣ�ֻҪ��ֻ�ӳ��������ĳ����в��������Ϳ�����;


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


/*****************�����Ƕ�IIC���ߵĲ����ӳ���***/
/*****************��������**********************/
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

/*****************ֹͣIIC����****************/
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
    I2C_SDA_0();	/* CPU����SDA = 0 */
		i2c_Delay();
		I2C_SCL_1();	/* CPU����1��ʱ�� */
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
		I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}
/**************���Ӧ��λ*******************/
uint8_t IICRecAck(void)
{
	uint8_t RValue;

	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	RValue=I2C_SDA_READ();	/* CPU��ȡSDA����״̬ */
	
	I2C_SCL_0();
  i2c_Delay();
	return RValue;
	
}

/***************��IIC���߲���Ӧ��*******************/
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

/*****************����IIC���߲���Ӧ��***************/
void IICNoAck(void)
{
	I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*******************��IIC����д����*********************/
void IICSendByte(unsigned char sendbyte)
{
	 uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
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
			 I2C_SDA_1(); // �ͷ�����
			}
		sendbyte <<= 1;	/* ����һ��bit */
		i2c_Delay();
	}

}


/**********************��IIC�����϶������ӳ���**********/
uint8_t IICReceiveByte(void)
{
	 
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
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


