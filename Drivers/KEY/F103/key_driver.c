#include "key_driver.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

static u8 key1_cnt = 0; //¼ÆÊ±
static u8 key2_cnt = 0;
static u8 key3_cnt = 0;
static u8 key4_cnt = 0;

#define KEY_ON  1

#define KEY_OFF 0

void KEY_Init()
{
	GPIO_InitTypeDef GPIO_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	
	/* key1 init */
	GPIO_Struct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	/* key2 init */
	GPIO_Struct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	/* key3 init */
	GPIO_Struct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);
	
	/* key4 init */
	GPIO_Struct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_Struct);
}

u8 KEY1_Scan()
{
	static u8 key_up = 1;
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==KEY_ON)
	{
		key1_cnt++;
		if(key1_cnt>20)
		{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==KEY_ON)
		{
			key1_cnt = 0;
			return KEY_ON;
		}
		else
			return KEY_OFF;
		}
		else
			return 3;
	}
	else
		return KEY_OFF;
		
}

u8 KEY2_Scan()
{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==KEY_ON)
	{
		key2_cnt++;
		if(key2_cnt>20)
		{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==KEY_ON)
		{
			key2_cnt = 0;
			return KEY_ON;
		}
		else
			return KEY_OFF;
		}
		else
			return 3;
	}
	else
		return KEY_OFF;
		
}

u8 KEY3_Scan()
{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==KEY_ON)
	{
		key3_cnt++;
		if(key3_cnt>20)
		{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==KEY_ON)
		{
			key3_cnt = 0;
			return KEY_ON;
		}
		else
			return KEY_OFF;
		}
		else
			return 3;
	}
	else
		return KEY_OFF;
		
}

u8 KEY4_Scan()
{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==KEY_ON)
	{
		key4_cnt++;
		if(key4_cnt>20)
		{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)==KEY_ON)
		{
			key4_cnt = 0;
			return KEY_ON;
		}
		else
			return KEY_OFF;
		}
		else
			return 3;
	}
	else
		return KEY_OFF;
		
}