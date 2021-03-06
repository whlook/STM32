#ifndef _TIME_DRIVER_H_
#define _TIME_DRIVER_H_
#include "stm32f4xx.h"

//定时器溢出时间计算方法：Tout = ((reload_value+1)*(psc+1))/Ft  us. Ft是定时器工作频率 Mhz
void TIM3_Init(u16 reload_value_us);
void TIM2_Init(u16 reload_value_us);


#endif