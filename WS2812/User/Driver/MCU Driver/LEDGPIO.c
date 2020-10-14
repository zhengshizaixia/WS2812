/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDGPIO.c
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

#include "LEDGPIO.h"
#include "main.h"

/*************************************************************
** Function name:       SetDebugLEDLeave
** Descriptions:        设置Debug_LED引脚电平
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetDebugLEDLeave(uint8_t leave)
{
    HAL_GPIO_WritePin(Debug_LED_GPIO_Port, Debug_LED_Pin, (GPIO_PinState)leave);
}
