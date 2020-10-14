/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               KeyGPIO.c
** Latest modified date:    2020-05-28
** Latest version:          V1.0.0
** Description:             Key引脚初始化
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-05-28
** Version:                 V1.0.0
** Descriptions:            Key引脚初始化
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#include "KEYGPIO.h"
#include "main.h"

/*************************************************************
** Function name:       GetKeyLeave
** Descriptions:        获取按键引脚电平
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
uint8_t GetKeyLeave(void)
{
    return HAL_GPIO_ReadPin(Key_GPIO_Port,Key_Pin);
}
