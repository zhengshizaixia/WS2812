/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDConfig.h
** Latest modified date:    2020-07-21
** Latest version:          V1.0.0
** Description:             LED
**
**------------------------------------------------------------
** Created by:              liuxiang
** Created date:            2020-07-21
** Version:                 V1.0.0
** Descriptions:            LED
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#ifndef LEDConfig_h
#define LEDConfig_h

#include "stdint.h"



typedef enum {
    Debug_LED = 0,
    Blue_LED1,
    Blue_LED2,
    Blue_LED3,
    Blue_LED4,
} gSysLED;

typedef enum {
    LED_OFF = 0,
    LED_ON,
} gSysLEDStatus;

void LEDConfig_Init(void);
void LEDConfig_Loop(void);
void LEDConfig_DeInit(void);
void SetLEDStatus(uint8_t status);
void SetLEDFlashing(uint16_t cycle);


#endif /* LEDConfig_h */
