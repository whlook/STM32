/*
1. ����Ƭ��flash��д��ʱ�������ǹرյģ�������Ҫ��HSI��Ĭ���ǿ��ģ�
2. д����������£�
	- ������ʹ�ÿ⺯������
	- �����־λ
	- �����趨����ʼ��ַ����һҳ
	- ѭ��д�����ݣ���С��16λ�ģ���ÿ��ѭ����ַ��Ҫ+2
	- ����
	
	- д�����ý��ж�ȡУ��
3. ��ȡֱ��ʹ�õ�ַ��ȡ �� data = *(u16 *)ADDRESS; // ADDRESS��Ҫ��ȡ�ĵ�ַ












*/
#pragma ONCE

#include "stm32f10x.h"


// �����ڶ���ҳ����������2K�ֽڵ�����
#define START_ADDR 0x0801F800

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth);

void flash_read(u16 *read_data,u8 lenth);

