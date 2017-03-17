/***********************************************

	Fly2017  < 2017-1-13 >
	USART 驱动程序 库函数版本

************************************************/
#include "usart_driver.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"

static unsigned char usart1_rx_flag = 0xff;
static unsigned char usart2_rx_flag = 0xff;
static unsigned char usart1_com_data = 0x00;
static unsigned char usart2_com_data = 0x00;

static unsigned char usart1_rec_buf[100];
static unsigned char usart1_rec_count = 0;

static unsigned char usart2_rec_buf[100];
static unsigned char usart2_rec_count = 0;

//重定义 printf ，可以直接用printf 发串口数据
int fputc(int ch, FILE *f)
{ 	
	USART_SendData(USART1,(u8)ch);
	while(!(USART1->SR&USART_FLAG_TXE));
	return ch;
}


/*======================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *=====================================================================================================*/
void USART1_Init(int baud)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; // tx rx
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate = baud;    
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1,ENABLE);
	
}
void USART2_Init(int baud)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; // tx rx
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate = baud;    
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2,&USART_InitStruct);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_Cmd(USART2,ENABLE);
}

/*========================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 

 *========================================================================================================*/
void USART1_sendData(unsigned char * tx_data_buf,unsigned char length)
{
	int i;
	USART_ITConfig(USART1,USART_IT_TXE,DISABLE); // disable tx interrupt
	for(i = 0;i<length;i++)
	{
		USART_SendData(USART1,tx_data_buf[i]);
		while(!(USART1->SR&USART_FLAG_TXE)); // wait for the tx reg empty
	}
}

/*============================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description:当有数据收到时（ usart1_rx_flag == 0x00 ），返回该数据，否则返回0xff，表示没有数据

 *===========================================================================================================*/
unsigned char USART1_recData(unsigned char *get_buf)
{
	int i = 0;
	for(;i<100;i++)
		get_buf[i] = usart1_rec_buf[i];
	if(usart1_rx_flag == 0x00)
	{
		usart1_rx_flag = 0xff;
		return usart1_com_data;
	}
	else
	{
		return 0xff;
	}
}

void USART2_sendData(unsigned char * tx_data_buf,unsigned char length)
{
		int i;
	USART_ITConfig(USART2,USART_IT_TXE,DISABLE); // disable tx interrupt
	for(i = 0;i<length;i++)
	{
		USART_SendData(USART2,tx_data_buf[i]);
		while(!(USART2->SR&USART_FLAG_TXE)); // wait for the tx reg empty
	}
}
unsigned char USART2_recData(unsigned char *get_buf)
{
	int i = 0;
	for(;i<100;i++)
		get_buf[i] = usart2_rec_buf[i];
	if(usart2_rx_flag == 0x00)
	{
		usart2_rx_flag = 0xff;
		return usart2_com_data;
	}
	else
	{
		return 0xff;
	}
}

/*========================================================================================================

	author: wuhui
	version: 2017.1.13
	input: 
	output: 
	description: 当产生了RX中断的时候，数据接收标志usart1_rx_flag变成 0x00

 *========================================================================================================*/
void USART1_IRQHandler(void)  
{
	if(USART1->SR & USART_SR_ORE)
	{
		usart1_com_data = USART1->DR;
	}
	
	//+-------RX-中断--------+
	if( USART_GetITStatus(USART1,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); // clear interrupt flag
		if(usart1_rx_flag == 0xff)
		{
			usart1_com_data = USART1->DR;
			usart1_rec_buf[usart1_rec_count++] = usart1_com_data;
			if(usart1_rec_count>99) 
				usart1_rec_count = 0;
			usart1_rx_flag =0x00;
		}
		
	}
	//+-------TX-中断--------+
	if( USART_GetITStatus(USART1,USART_IT_TXE ) )
	{
			USART1->DR = 0x00; // write DR to clear interrupt flag
			USART1->CR1 &= ~USART_CR1_TXEIE; // close TXE
	}
	
}

void USART2_IRQHandler(void)
{
	if(USART2->SR & USART_SR_ORE)
	{
		usart2_com_data = USART2->DR;
	}
	
	
	if( USART_GetITStatus(USART2,USART_IT_RXNE) )
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); // clear interrupt flag
		if(usart2_rx_flag == 0xff)
		{
			usart2_com_data = USART2->DR;
			usart2_rec_buf[usart2_rec_count++] = usart2_com_data;
		if(usart2_rec_count>99) 
			usart2_rec_count = 0;
			usart2_rx_flag =0x00;
		}
		
	}
	
	if( USART_GetITStatus(USART2,USART_IT_TXE ) )
	{
			USART2->DR = 0x00; // write DR to clear interrupt flag
			USART2->CR1 &= ~USART_CR1_TXEIE; // close TXE
	}
	
}

