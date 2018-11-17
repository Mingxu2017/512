#include "stm32f10x.h"	
#include "Declare.h"

const uint8_t ChCode[] = {'0','1','2','3','4','5','6','7','8','9','*',' '};
const uint8_t Hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

uint8_t SuperPassFlag=0;
uint8_t testled=0;

uint8_t  dis_buff[30];
uint8_t GC_Name[22];//8������+����ʱ���ֽ�
uint8_t Door_Addr=1;//��ע�����ʼ��ַ

//uint16_t Zero[256];
//uint16_t Fac[256];
uint16_t World_Flag=0x1400;//ϵͳ״ָ̬ʾ�Ʊ�־ 

uint8_t uart_cnt=0;
//��������12  ��������10 �� ����8 �Զ�6  �ܷ���4��  ������2�� ��0
//�������13���������11    �Լ�9 ����7  �ܹ���5   �Źر�3   �ſ���1
uint8_t Function_Flag=1;
uint8_t canflag=0;
uint8_t Pass1[4]={1,0,0,0},Pass2[4]={2,0,0,0};//����1��2������
uint16_t AlarmRecount=0;
uint16_t FaultRecount=0;
uint16_t SDRecount=0;
uint8_t Self_Addr=1;
//uint8_t ShowFrq=1;//ˢ��Ƶ�ʣ�ÿ����ʾ��ʱ����
uint16_t  PrintID=0;
//uint8_t Bat_ON_Flag;

//���յ������ݳ���
//uint8_t RS485_RX_CNT=0;  

//uint8_t Door[256][24];//2944�ֽ�
//uint8_t DoorFault[512];// 7�ŴŶ�· 6�ŴŶ�· 5��������· 4��������· 3�����Ź���  2��������   1��ͨѶ���ϡ�0δ��
//uint8_t DoorBackTimer[256];
//uint8_t SendNum[512];
uint32_t address[512][3];
uint8_t RS485_RX_BUF[256];  	//���ջ���,���64���ֽ�.
uint8_t ReceivePoint=0;
uint8_t ReceiveFlag=0;

uint8_t RS485_RX_BUF2[256];  	//���ջ���,���64���ֽ�.
uint8_t ReceivePoint2=0;
uint8_t ReceiveFlag2=0;
uint8_t Display_Flag=1;
uint16_t Fault_Position[24];
uint16_t Alarm_Position[11];
uint16_t Alarm_Data[11];
uint8_t AlarmNum=0;
uint8_t DisplayAddr=0;
uint16_t InstallAddr=1;
uint16_t FAlarm_Rec_Position=0;//�𾯱�����λ����
uint16_t Alarm_Rec_Position=0;//������λ����
uint16_t XAlarm_Rec_Position=0;//δ��������
uint16_t RAlarm_Rec_Position=0;
uint8_t Flash_Flag;

uint16_t Alarm_RecP;
uint16_t Fault_Rec_Position=0;//���ϲ�λ����
uint16_t Fault_Rec=0;
uint16_t Fault_RecP=0;
uint16_t Fault_Num=0;
uint16_t First_Alarm=0;
uint8_t Dis_Alarm_Fault_Flag=0;//1��ʾ����������ʾ����
uint8_t ARec_Position;//,FRec_Position;

uint16_t Shiled_Rec_Position;
uint8_t Flicker_Timer;

uint16_t End_Addr=1;
uint16_t LoopStart=1;
uint16_t LoopEnd=1;

uint16_t TCQ_ID_CAN=1;
uint16_t TCQ_ID_485=1;

uint8_t Shield_Flag[64];//8..1·��ʾ��־λ����=1��ʾ����0���β���ʾ
uint8_t Fault_Flag[64];

uint8_t KEY_Uart_Fault_Flag;//������ͨѶ����


uint8_t Alarm_Flag[64];
uint16_t Alarm_Flag_16[512];
uint16_t Sensor_Fault0_Flag[512];
/*uint8_t RAlarm_Flag[32];//=1���շ�����ʶ
uint8_t XAlarm_Flag[32];//����δ������ʶ
uint8_t NXAlarm_Flag[32];//����δ����ʱ�䵽��δ���ͱ�ʶ
*/
uint8_t SendToPC_Flag;
uint8_t LoopOpenFlag;

uint8_t Uart_Err_Timer[256];
uint8_t NOBack_Flag;
uint16_t TCDID,State1,State2,temp1,temp2,Alarm_State,Fault_State;

//uint16_t PB_State,Type_State,SKC_State;
uint8_t LDK[2];//LDK[1]=�ˣ�������������������������������������Ͼ���� ��ʱ�������




uint16_t  Dis_Num=0;        //��ʾ·��
uint16_t TCQ_Addr=0;
uint8_t DateTimer[8]={12,7,23,1,16,15,10,9};   // ����Ϊ��  ��������ʱ���룬�������
uint16_t Power_Check_Timer=0;

//uint8_t TCQ_Return_OK=0; //̽����������ȷ��־



uint16_t Bat_Power=0;
uint8_t Sound_Flag=1;


uint8_t  Key_Down_Flag=0;
uint8_t  Key_Up_Flag=0;
uint8_t  Dis_Key_Buff_Flag=0;//=1��ʾ��ヲ�����Ϣ
uint16_t Key_Input_Value=0;
uint8_t Flicker_Position=0,Flicker_Position1=0;//��˸��λ��
uint8_t Beep_Alarm_Fault=0;//=1alarm;;=2fault
uint8_t Self_Check_Flag;//�Լ��־
uint8_t KEY_LOCK_Flag;
uint8_t KEY_LOCK_Timer1S;
uint8_t KEYDoor_Flag,HMDoor_Flag;
uint8_t SendKEY_TCQ_Flag=0;//��������ģ�齻��

uint8_t SD_Loop_Flag=0;
uint8_t Alarm_Loop_Flag=0;
uint8_t Fault_Loop_Flag=0;




uint8_t RecPCCnt;
uint8_t RecPC_Begin_Flag;
uint8_t ReceiveFromPC_Flag;
uint8_t PCFunction_Flag;
//uint8_t Re_SendTCQ_Addr;
uint8_t SendPC_Buff[100],RecPC_Buff[100];//20
uint8_t Buff[100];
uint8_t Send_Buff[20],Rec_Buff[100];
uint8_t RecCnt,Rec_Begin_Flag;
uint8_t Rec_Flag;

uint8_t SendKEY_Buff[20],RecKEY_Buff[20];
uint8_t KEY_RecCnt,KEY_Rec_Begin_Flag;

uint8_t KEY_Uart_Err_Timer=0;

uint8_t KEY_Return_Timer=0;

uint8_t PCQueryT;
uint8_t Print_State;//��ӡ������״̬

uint8_t TCQ_Return_Length;
uint8_t TCQ_Return_Timer=0;
uint8_t TCQ_Return_OK;

uint8_t TCQ_485Return_Length;
uint8_t TCQ_485Return_Timer=0;
uint8_t TCQ_485Return_OK;
T_SendPtr SendPtr;
T_SendFunction SendFunction[16];
uint8_t PC_AN_Flag=0;


uint8_t ShowFrq=1;//ˢ��Ƶ�ʣ�ÿ����ʾ��ʱ����


uint8_t Type_State,PB_State,SKC_State;
uint16_t Low_Feel[20],Feel[20];
u8 rs485buf[20];
uint8_t rr[100];
uint8_t rr_cnt;