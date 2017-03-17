#pragma ONCE
#include "stm32f10x.h"

extern u32 SysTick_cnt;

extern u8 Flag_restart;
 
//------------------------------+

void sysTick_Init();

void delay_ms(u16 ms);

void delay_s(u8 s);

void duty();