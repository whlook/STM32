#ifndef _TIME_DRIVER_H_
#define _TIME_DRIVER_H_
#include "stm32f4xx.h"

//��ʱ�����ʱ����㷽����Tout = ((reload_value+1)*(psc+1))/Ft  us. Ft�Ƕ�ʱ������Ƶ�� Mhz
void TIM3_Init(u16 reload_value_us);
void TIM2_Init(u16 reload_value_us);


#endif