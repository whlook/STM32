/*
1. ���ļ���Ӧ�ó�����ÿ������а������


*/


#ifndef _KEY_DRIVER_H_
#define _KEY_DRIVER_H_

#include "stm32f10x.h"

void KEY_Init();

u8 KEY1_Scan(); // ��ҡ�˰���

u8 KEY2_Scan(); // �����ϵİ���

u8 KEY3_Scan(); // �Ҳ࿪��

u8 KEY4_Scan(); // ��ҡ�˰���

#endif