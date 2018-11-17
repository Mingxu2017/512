#include "stm32f10x.h"



const uint8_t ChCode[] = {'0','1','2','3','4','5','6','7','8','9'};

uint8_t Pass1[4]={1,0,0,0},Pass2[4]={2,0,0,0};//����1��2������
uint8_t Self_Addr=1;
uint16_t AlarmRecount=0;
uint16_t FaultRecount=0;
uint16_t SDRecount=0;
uint8_t ShowFrq=1;//ˢ��Ƶ�ʣ�ÿ����ʾ��ʱ����

uint16_t Alarm_Rec_Position;//������λ����
uint16_t Alarm_RecP;
uint16_t Fault_Rec_Position;//���ϲ�λ����
//extern uint16_t Fault_RecP;

uint16_t Alarm_Position[11];
uint16_t Fault_Position[11];


//uint8_t End_Addr=1;


//uint8_t Shield_Flag[16];//8..1·��ʾ��־λ����=1��ʾ����0���β���ʾ
//uint8_t Fault_Flag[16];
//uint8_t Alarm_Flag[16];
//uint8_t Uart_Err_Timer[64];


uint8_t World_Flag=0x2A;//ϵͳ״ָ̬ʾ�Ʊ�־
// ��7λ     6       5       4         3         2         1        0
// �ܹ���  �ܱ��� ����ָʾ ������  �������� �������  �������� �������

uint8_t Function_Flag=1;

uint16_t Dis_Num=0;        //��ʾ·��
uint8_t DateTimer[8]={12,7,23,1,16,15,10,9};   // ����Ϊ��  ��������ʱ���룬�������


uint8_t TCQ_Return_OK=0; //̽����������ȷ��־
uint8_t TCQ_Return_Timer=0;


//uint8_t Send_Buff[50],Rec_Buff[100];
uint8_t RecCnt;
uint8_t Rec_Begin_Flag=0;

uint16_t Bat_Power=0;
uint8_t Sound_Flag=1;

uint16_t Back_Led_Timer=0;
uint8_t Back_Led_Flag=1;

uint8_t  Key_Down_Flag=0;
uint8_t  Key_Up_Flag=0;
uint8_t  Dis_Key_Buff_Flag=0;//=1��ʾ��ヲ�����Ϣ
uint8_t Key_Input_Value=0;
uint8_t Flicker_Position=0;//��˸��λ��
uint8_t Beep_Alarm_Fault=0;//=1alarm;;=2fault

uint8_t SD_Loop_Flag=0;
uint8_t Alarm_Loop_Flag=0;
uint8_t Fault_Loop_Flag=0;

uint8_t  dis_buff[8];
/*
void Delay1us(uint16_t n)
{
    while(n>0)
	{
	    n--;
	}
}

void Delay1ms(uint16_t ms)        		//��ʱms����
{
    uint16_t  i;
    ms=ms*10; 
    for(i = 0;i<ms;i++)                        
    { 
	  Delay1us(80);           		//100us
    }
  //  WDOG();
}

void Delay1s(uint16_t s)        		//��ʱms����
{
    uint16_t  i;
    for(i = 0;i<s;i++)                        
    { WDOG();
	  Delay1ms(1000);           	
    }
}*/
