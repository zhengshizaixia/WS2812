/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               SPI2.c
** Latest modified date:    2020-05-27
** Latest version:          V1.0.0
** Description:             SPI2驱动
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-05-27
** Version:                 V1.0.0
** Descriptions:            SPI2驱动
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#include "SPI2.h"

extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_tx;

/*************************************************************
** Function name:       SPI2TransmitData
** Descriptions:        SPI发送数据
** Input parameters:    buffer: 数据存放首地址,length：数据长度
** Output parameters:   None
** Returned value:      None
*************************************************************/
void SPI2TransmitData(uint16_t *buffer,uint16_t length)
{
    HAL_SPI_Transmit_DMA(&hspi2,(uint8_t *)buffer,length);
}














