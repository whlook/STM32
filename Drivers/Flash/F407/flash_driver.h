#pragma ONCE

#include "stm32f4xx.h"


// ������һ��ҳ����������128K�ֽڵ�����
#define START_ADDR 0x080E0000

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth);

void flash_read(u16 *read_data,u8 lenth);