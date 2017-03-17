/*
1. 该文件的应用场景是每毫秒进行按键检测


*/


#ifndef _KEY_DRIVER_H_
#define _KEY_DRIVER_H_

#include "stm32f10x.h"

void KEY_Init();

u8 KEY1_Scan(); // 左摇杆按键

u8 KEY2_Scan(); // 板子上的按键

u8 KEY3_Scan(); // 右侧开关

u8 KEY4_Scan(); // 右摇杆按键

#endif