/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDGPIO.h
** Latest modified date:    2020-05-28
** Latest version:          V1.0.0
** Description:             LED引脚初始化
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-05-28
** Version:                 V1.0.0
** Descriptions:            LED引脚初始化
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#ifndef __LEDGPIO__H
#define __LEDGPIO__H
#include "stdint.h"

void SetDebugLEDLeave(uint8_t leave);
void SetBlueLED1Leave(uint8_t leave);
void SetBlueLED2Leave(uint8_t leave);
void SetBlueLED3Leave(uint8_t leave);
void SetBlueLED4Leave(uint8_t leave);

#endif

