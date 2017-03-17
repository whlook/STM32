#include "time.h"
#include "stm32f10x_it.h"
#include "duty.h"

 u32 SysTick_cnt = 0;
 
 u8 Flag_restart = 0;


void sysTick_Init()
{
	while(SysTick_Config(SystemCoreClock/1000));
	
}

void delay_ms(u16 ms)
{
	u32 temp = SysTick_cnt;
	while((SysTick_cnt - temp)<ms);
}

void delay_s(u8 s)
{
	delay_ms(s*1000);
}


void duty()
{
	static u16 duty_cnt_1ms = 0;
	static u16 duty_cnt_2ms = 0;
	static u16 duty_cnt_5ms = 0;
	static u16 duty_cnt_10ms = 0;
	static u16 duty_cnt_20ms = 0;
	static u16 duty_cnt_1s = 0;
	
	duty_cnt_1ms++;
	duty_cnt_2ms++;
	duty_cnt_5ms++;
	duty_cnt_10ms++;
	duty_cnt_20ms++;
	duty_cnt_1s++;
	
	if(duty_cnt_1ms >2000 ||duty_cnt_2ms >2000 ||duty_cnt_5ms >2000 ||duty_cnt_10ms >2000 ||duty_cnt_20ms >2000 ||duty_cnt_1s >2000 )
	{
		duty_cnt_1ms = 0;
		duty_cnt_2ms = 0;
		duty_cnt_5ms = 0;
		duty_cnt_10ms = 0;
		duty_cnt_20ms = 0;
		duty_cnt_1s = 0;
		
		Flag_restart++;
	}
	
	if(duty_cnt_1ms == 1)
	{
		duty_cnt_1ms = 0;
//==================================//run every 1ms
		duty_1ms();
		
	}
	
		if(duty_cnt_2ms == 2)
	{
		duty_cnt_2ms = 0;
//==================================//run every 2ms
		duty_2ms();
		
	}
	
		if(duty_cnt_5ms == 5)
	{
		duty_cnt_5ms = 0;
//==================================//run every 5ms
		duty_5ms();
		
	}
	
		if(duty_cnt_10ms == 10)
	{
		duty_cnt_10ms = 0;
//==================================//run every 10ms
		duty_10ms();
	}
	
		if(duty_cnt_20ms == 20)
	{
		duty_cnt_20ms = 0;
//==================================//run every 20ms
		duty_20ms();
		
	}
	
		if(duty_cnt_1s == 1000 )
	{
		duty_cnt_1s = 0;
//==================================// run every 1s
		duty_1s();
	}
	
}


