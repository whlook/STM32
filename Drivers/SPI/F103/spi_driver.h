#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_
#include "stm32f10x.h"

void SPI1_Init(void);
void SPI2_Init(void);

void SPI1_SetSpeed(u8 SpeedSet);
void SPI2_SetSpeed(u8 SpeedSet);

u8 SPI1_ReadWriteByte(u8 TxData);
u8 SPI2_ReadWriteByte(u8 TxData);


#endif