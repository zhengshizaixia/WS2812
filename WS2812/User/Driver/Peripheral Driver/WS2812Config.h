/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               Ws2812Config.h
** Latest modified date:    2020-06-05
** Latest version:          V1.0.0
** Description:             WS2812
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-06-05
** Version:                 V1.0.0
** Descriptions:            WS2812
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#ifndef Ws2812Config_h
#define Ws2812Config_h
#include "stdint.h"
#define WS2812_EFFECT_NUM 7
enum{
    LED_1 = 0x0001,
    LED_2 = 0x0002,
    LED_3 = 0x0004,
    LED_4 = 0x0008,
    LED_5 = 0x0010,
    LED_6 = 0x0020,
    ALL_LED = 0x003F,
};

enum {
    WS2812Config_Normal = 0,
    WS2812Config_SetOnTime,
    WS2812Config_Breath,
    WS2812Config_Flashing,
    WS2812Config_Rainbow,
    WS2812Config_Surround,
    WS2812Config_Police,
};

void WS2812Config_Init(void);
void WS2812Config_Loop(void);
void WS2812Config_Deinit(void);

void WS2812ConfigRainBowBreath(uint16_t ledIndex,float cycle);
void WS2812ConfigBreath(uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle,uint8_t breathFlag,int breathCounts);
void WS2812ConfigFlashing(uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812ConfigNormalDisplay(uint16_t index,uint8_t r,uint8_t g,uint8_t b);
void WS2812ConfigSurround(uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812ConfigPolice(uint16_t ledIndex,float cycle);

void WS2812ConfigChangeEffect(void);
void WS2812ConfigSetByUser(uint16_t ledIndex,uint8_t effectIndex,uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812ConfigUserFunc(void);

void WS2812SetDefaultCloar(uint16_t ledIndex,uint8_t effectIndex,uint8_t r,uint8_t g,uint8_t b,float cycle);
void DisableUserColor(void);
#endif /* Ws2812Config_h */
