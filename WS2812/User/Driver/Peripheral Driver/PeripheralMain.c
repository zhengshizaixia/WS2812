/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               PeripheralMain.c
** Latest modified date:    2019-11-22
** Latest version:          V1.0.0
** Description:             外设驱动主文件
**
**------------------------------------------------------------
** Created by:              Chen JunTong
** Created date:            2019-11-22
** Version:                 V1.0.0
** Descriptions:            外设驱动主文件
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "PeripheralMain.h"
#include "main.h"

#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"
#include "stdio.h"

#include "WS2812Config.h"

#include "SPI2.h"
#include "math.h"
#include "LEDConfig.h"
/*************************************************************
** Function name:       PeripheralMain_Init
** Descriptions:        外设驱动初始化
** Input parameters:    no
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/
void PeripheralMain_Init(void)
{
	WS2812ConfigSetByUser(ALL_LED,WS2812Config_Breath,255,255,255,1.0);
	SetLEDFlashing(1000);
}
/*************************************************************
** Function name:       PeripheralMain_Loop
** Descriptions:        外设驱动循环函数
** Input parameters:    no
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/

void PeripheralMain_Loop(void)
{
	WS2812Config_Loop();
	LEDConfig_Loop();
}



