#include "init.h"
#include "time.h"
#include "led.h"

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"



void Init_all()
{
	led_init();
	
	sysTick_Init();
}