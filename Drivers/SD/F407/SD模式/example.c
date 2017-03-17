#include "sdio_sd_driver.h"

void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
    printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	// 制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								// 卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	// 显示容量
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			// 显示块大小
}


int main()
{
	SD_Error err = SD_OK;
	u8 data[512];
	
	while(SD_Init())
		printf("Init Error");
	show_sdcard_info();
	
	err = SD_WriteMultiBlocks(data,0x0000,512,2);
	
}