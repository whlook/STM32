#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_
#include "stm32f10x.h"

/* 引脚图

						ADC1      ADC2      ADC3
0  					PA0				PA0				PA0
1 					PA1				PA1				PA1
2						PA2				PA2				PA2
3   				PA3				PA3				PA3
4  					PA4				PA4				PF6
5	    			PA5				PA5				PF7
6						PA6				PA6				PF8
7						PA7				PA7				PF9
8						PB0				PB0				PF10
9						PB1				PB1
10					PC0				PC0				PC0
11					PC1				PC1				PC1
12					PC2				PC2				PC2
13					PC3				PC3				PC3
14					PC4				PC4
15					PC5				PC5
16					温度传感器
17					内部参照电压

*/





void ADC1_Init(void);

void get_adc1_value(u8 *buf);

#endif