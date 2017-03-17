/*
1. 进行片内flash读写的时候总线是关闭的，并且需要打开HSI（默认是开的）
2. 写入的流程如下：
	- 解锁，使用库函数即可
	- 清除标志位
	- 擦除设定的起始地址的那一页
	- 循环写入数据（最小是16位的），每次循环地址需要+2
	- 加锁
	
	- 写完后最好进行读取校验
3. 读取直接使用地址读取 如 data = *(u16 *)ADDRESS; // ADDRESS是要读取的地址












*/
#pragma ONCE

#include "stm32f10x.h"


// 倒数第二个页，到结束共2K字节的容量
#define START_ADDR 0x0801F800

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth);

void flash_read(u16 *read_data,u8 lenth);

