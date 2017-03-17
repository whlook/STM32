#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "flash.h"

//void flash_init();

u8 flash_write(u16 *write_data,u8 lenth)
{
	u16 cnt = 0;
	// ����HSI��Ĭ�Ͽ����ģ��Է���һ
	RCC_HSICmd(ENABLE);
	
	// ����
	FLASH_Unlock();
	
	// ���flag
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
	// ������ҳ
	FLASH_ErasePage(START_ADDR);
	
	// д������
	do
	{
		FLASH_ProgramHalfWord((START_ADDR + cnt*2),write_data[cnt]);
		
		cnt++;
		
	}while(cnt != lenth);
	
	// ����
	FLASH_Lock();
	
// ���ж�ȡУ��
	
	u32 addr = START_ADDR;
	
	cnt = 0;
	
	u8 read_err_cnt = 0;
	
	u16 buf;
	
	while(cnt<lenth)
	{
		buf = *(u16 *)addr;
		if(buf!=write_data[cnt])
			read_err_cnt++;
		addr = addr+2;
		cnt++;
	}
	
	return read_err_cnt;
	
	
	
	
	
}

void flash_read(u16 *read_data,u8 lenth)
{
	u16 cnt = 0;
	
	u32 addr = START_ADDR;
	do
	{
		read_data[cnt] = *(u16 *)addr;
		addr+=2;
		cnt++;
	}while(cnt!=lenth);
}