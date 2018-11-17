#include "stm32f10x.h"


	
void IWDG_Configuration(void)
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);     /* Register write functions allow dogs*/
  IWDG_SetPrescaler(IWDG_Prescaler_256);            /*  40K/256=156HZ(6.4ms) */ 

  IWDG_SetReload(781);               /* ι��ʱ�� 5s/6.4mS=781 */
  IWDG_ReloadCounter();               /* ι��*/
  IWDG_Enable();                      /* ʹ��*/
}


