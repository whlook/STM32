#include "stm32f10x.h"
#include "init.h"
#include "time.h"
#include "stm32f10x_gpio.h"

int main()
{
	restart:
	
	Init_all();
	
	while(1)
	{
		if(Flag_restart>3)
		{
			Flag_restart = 0;
			goto restart;
		}
	}
	
	return 0;
}