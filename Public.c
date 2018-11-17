#include "stm32f10x.h"	
#include "Declare.h"

const uint8_t ChCode[] = {'0','1','2','3','4','5','6','7','8','9','*',' '};
const uint8_t Hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

uint8_t SuperPassFlag=0;
uint8_t testled=0;

uint8_t  dis_buff[30];
uint8_t GC_Name[22];//8个汉字+５个时间字节
uint8_t Door_Addr=1;//门注册的起始地址

//uint16_t Zero[256];
//uint16_t Fac[256];
uint16_t World_Flag=0x1400;//系统状态指示灯标志 

uint8_t uart_cnt=0;
//备电正常12  主电正常10 　 解锁8 自动6  总反馈4　  总启动2　 火警0
//备电故障13　主电故障11    自检9 消音7  总故障5   门关闭3   门开启1
uint8_t Function_Flag=1;
uint8_t canflag=0;
uint8_t Pass1[4]={1,0,0,0},Pass2[4]={2,0,0,0};//保存1级2级密码
uint16_t AlarmRecount=0;
uint16_t FaultRecount=0;
uint16_t SDRecount=0;
uint8_t Self_Addr=1;
//uint8_t ShowFrq=1;//刷新频率，每屏显示的时间间隔
uint16_t  PrintID=0;
//uint8_t Bat_ON_Flag;

//接收到的数据长度
//uint8_t RS485_RX_CNT=0;  

//uint8_t Door[256][24];//2944字节
//uint8_t DoorFault[512];// 7门磁短路 6门磁断路 5闭门器短路 4闭门器断路 3常闭门故障  2常开故障   1门通讯故障　0未用
//uint8_t DoorBackTimer[256];
//uint8_t SendNum[512];
uint32_t address[512][3];
uint8_t RS485_RX_BUF[256];  	//接收缓冲,最大64个字节.
uint8_t ReceivePoint=0;
uint8_t ReceiveFlag=0;

uint8_t RS485_RX_BUF2[256];  	//接收缓冲,最大64个字节.
uint8_t ReceivePoint2=0;
uint8_t ReceiveFlag2=0;
uint8_t Display_Flag=1;
uint16_t Fault_Position[24];
uint16_t Alarm_Position[11];
uint16_t Alarm_Data[11];
uint8_t AlarmNum=0;
uint8_t DisplayAddr=0;
uint16_t InstallAddr=1;
uint16_t FAlarm_Rec_Position=0;//火警报警部位总数
uint16_t Alarm_Rec_Position=0;//报警部位总数
uint16_t XAlarm_Rec_Position=0;//未反馈总数
uint16_t RAlarm_Rec_Position=0;
uint8_t Flash_Flag;

uint16_t Alarm_RecP;
uint16_t Fault_Rec_Position=0;//故障部位总数
uint16_t Fault_Rec=0;
uint16_t Fault_RecP=0;
uint16_t Fault_Num=0;
uint16_t First_Alarm=0;
uint8_t Dis_Alarm_Fault_Flag=0;//1显示报警　２显示故障
uint8_t ARec_Position;//,FRec_Position;

uint16_t Shiled_Rec_Position;
uint8_t Flicker_Timer;

uint16_t End_Addr=1;
uint16_t LoopStart=1;
uint16_t LoopEnd=1;

uint16_t TCQ_ID_CAN=1;
uint16_t TCQ_ID_485=1;

uint8_t Shield_Flag[64];//8..1路显示标志位　　=1显示，＝0屏蔽不显示
uint8_t Fault_Flag[64];

uint8_t KEY_Uart_Fault_Flag;//按键板通讯故障


uint8_t Alarm_Flag[64];
uint16_t Alarm_Flag_16[512];
uint16_t Sensor_Fault0_Flag[512];
/*uint8_t RAlarm_Flag[32];//=1接收反馈标识
uint8_t XAlarm_Flag[32];//＝１未反馈标识
uint8_t NXAlarm_Flag[32];//＝１未反馈时间到但未发送标识
*/
uint8_t SendToPC_Flag;
uint8_t LoopOpenFlag;

uint8_t Uart_Err_Timer[256];
uint8_t NOBack_Flag;
uint16_t TCDID,State1,State2,temp1,temp2,Alarm_State,Fault_State;

//uint16_t PB_State,Type_State,SKC_State;
uint8_t LDK[2];//LDK[1]=Ｋ１输出　１代表火警输出　２故障输出　３火警与故障均输出 ０时都不输出




uint16_t  Dis_Num=0;        //显示路数
uint16_t TCQ_Addr=0;
uint8_t DateTimer[8]={12,7,23,1,16,15,10,9};   // 依次为：  年月日周时分秒，输出控制
uint16_t Power_Check_Timer=0;

//uint8_t TCQ_Return_OK=0; //探测器返回正确标志



uint16_t Bat_Power=0;
uint8_t Sound_Flag=1;


uint8_t  Key_Down_Flag=0;
uint8_t  Key_Up_Flag=0;
uint8_t  Dis_Key_Buff_Flag=0;//=1显示按銉操作信息
uint16_t Key_Input_Value=0;
uint8_t Flicker_Position=0,Flicker_Position1=0;//闪烁的位置
uint8_t Beep_Alarm_Fault=0;//=1alarm;;=2fault
uint8_t Self_Check_Flag;//自检标志
uint8_t KEY_LOCK_Flag;
uint8_t KEY_LOCK_Timer1S;
uint8_t KEYDoor_Flag,HMDoor_Flag;
uint8_t SendKEY_TCQ_Flag=0;//读按键与模块交替

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
uint8_t Print_State;//打印机配置状态

uint8_t TCQ_Return_Length;
uint8_t TCQ_Return_Timer=0;
uint8_t TCQ_Return_OK;

uint8_t TCQ_485Return_Length;
uint8_t TCQ_485Return_Timer=0;
uint8_t TCQ_485Return_OK;
T_SendPtr SendPtr;
T_SendFunction SendFunction[16];
uint8_t PC_AN_Flag=0;


uint8_t ShowFrq=1;//刷新频率，每屏显示的时间间隔


uint8_t Type_State,PB_State,SKC_State;
uint16_t Low_Feel[20],Feel[20];
u8 rs485buf[20];
uint8_t rr[100];
uint8_t rr_cnt;