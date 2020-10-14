/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               Ws2812Config.c
** Latest modified date:    2020-06-05
** Latest version:          V1.0.0
** Description:             Ws2812灯带驱动
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-06-05
** Version:                 V1.0.0
** Descriptions:            Ws2812灯带驱动
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/

#include "SPI2.h"
#include "WS2812.h"
#include "WS2812Config.h"

//1路RGB灯带初始化
WS2812B_EXPORT(gWs2812,6,SPI2TransmitData);
/*************************************************************
** Function name:       WS2812Config_Init
** Descriptions:        WS2812初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812Config_Init(void)
{
    
}
/*************************************************************
** Function name:       WS2812Config_DeInit
** Descriptions:        WS2812反初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812Config_Deinit(void)
{

}
/*************************************************************
** Function name:       WS2812Config_Loop
** Descriptions:        WS2812循环
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812Config_Loop(void)
{
    WS2812Cycle(&gWs2812);
}
/*************************************************************
** Function name:       WS2812ConfigBreath
** Descriptions:        WS2812呼吸
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigBreath(uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle,uint8_t breathFlag,int breathCounts)
{
    WS2812StartBreathe(&gWs2812,ledIndex,r,g,b,cycle,breathFlag,breathCounts);
}
/*************************************************************
** Function name:       WS2812ConfigFlashing
** Descriptions:        WS2812闪烁
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigFlashing(uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    WS2812StartFlashing(&gWs2812,ledIndex,r,g,b,cycle);
}
/*************************************************************
** Function name:       WS2812ConfigDisplayOne
** Descriptions:        WS2812显示
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigNormalDisplay(uint16_t index,uint8_t r,uint8_t g,uint8_t b)
{
    WS2812StartNormalDisplay(&gWs2812,index,r,g,b);
}
/*************************************************************
** Function name:       WS2812ConfigRainBowBreath
** Descriptions:        WS2812彩虹呼吸
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigRainBowBreath(uint16_t ledIndex,float cycle)
{
    WS2812StartRainBowBreathe(&gWs2812,ledIndex,cycle);
}

/*************************************************************
** Function name:       WS2812ConfigSetOnTime
** Descriptions:        WS2812定时熄灭
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigSetOnTime(uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    WS2812SetOnTimeDisplay(&gWs2812,index,r,g,b,cycle);
}
/*************************************************************
** Function name:       WS2812ConfigSurround
** Descriptions:        WS2812流水环绕
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigSurround(uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    WS2812StartSurround(&gWs2812,index,r,g,b,cycle);
}
/*************************************************************
** Function name:       WS2812ConfigPolice
** Descriptions:        WS2812闪烁
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigPolice(uint16_t ledIndex,float cycle)
{
    WS2812StartPolice(&gWs2812,ledIndex,cycle);
}
struct SWS2812Config_Struct {
    uint16_t ledIndex;
    uint8_t effectIndex;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    float cycle;
};
struct SWS2812Config_Struct gWS2812Config = {
    .ledIndex = ALL_LED,
    .effectIndex = WS2812Config_Breath,
    .r = 255,
    .g = 255,
    .b = 255,
    .cycle = 1.0,
};
struct SWS2812Config_Struct gDefaultWS2812 = {
    .ledIndex = ALL_LED,
    .effectIndex = WS2812Config_Breath,
    .r = 255,
    .g = 255,
    .b = 255,
    .cycle = 1.0,
};
/*************************************************************
** Function name:       WS2812ConfigChangeEffect
** Descriptions:        改变灯效
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigChangeEffect(void)
{
    gWS2812Config.effectIndex = (gWS2812Config.effectIndex + 1) % WS2812_EFFECT_NUM;
	WS2812ConfigUserFunc();
}
/*************************************************************
** Function name:       WS2812ConfigSetByUser
** Descriptions:        用户设置LED状态
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigSetByUser(uint16_t ledIndex,uint8_t effectIndex,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    gWS2812Config.ledIndex = ledIndex;
    gWS2812Config.effectIndex = effectIndex;
    gWS2812Config.r = r;
    gWS2812Config.g = g;
    gWS2812Config.b = b;
    gWS2812Config.cycle = cycle;
	WS2812ConfigUserFunc();
}
/*************************************************************
** Function name:       UserFunc
** Descriptions:        用户设置LED状态回调函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812ConfigUserFunc(void)
{
    switch (gWS2812Config.effectIndex) {
        case WS2812Config_Normal:
            WS2812ConfigNormalDisplay(gWS2812Config.ledIndex,gWS2812Config.r,gWS2812Config.g,gWS2812Config.b);
            break;
        case WS2812Config_SetOnTime:
            WS2812ConfigSetOnTime(gWS2812Config.ledIndex,gWS2812Config.r,gWS2812Config.g,gWS2812Config.b,gWS2812Config.cycle);
            break;
        case WS2812Config_Breath:
            WS2812ConfigBreath(gWS2812Config.ledIndex,gWS2812Config.r,gWS2812Config.g,gWS2812Config.b,gWS2812Config.cycle,0,-1);
            break;
        case WS2812Config_Flashing:
            WS2812ConfigFlashing(gWS2812Config.ledIndex,gWS2812Config.r,gWS2812Config.g,gWS2812Config.b,gWS2812Config.cycle);
            break;
        case WS2812Config_Rainbow:
            WS2812ConfigRainBowBreath(gWS2812Config.ledIndex,gWS2812Config.cycle);
            break;
        case WS2812Config_Surround:
            WS2812ConfigSurround(gWS2812Config.ledIndex,gWS2812Config.r,gWS2812Config.g,gWS2812Config.b,gWS2812Config.cycle);
            break;
        case WS2812Config_Police:
            WS2812ConfigPolice(gWS2812Config.ledIndex,gWS2812Config.cycle);
            break;
    }
}
/*************************************************************
** Function name:       WS2812SetDefaultCloar
** Descriptions:        用户设置LED默认颜色
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812SetDefaultCloar(uint16_t ledIndex,uint8_t effectIndex,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    gDefaultWS2812.ledIndex = ledIndex;
    gDefaultWS2812.effectIndex = effectIndex;
    gDefaultWS2812.r = r;
    gDefaultWS2812.g = g;
    gDefaultWS2812.b = b;
    gDefaultWS2812.cycle = cycle;
}
/*************************************************************
** Function name:       DisableUserColor
** Descriptions:        取消用户LED状态
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void DisableUserColor(void)
{
	switch (gDefaultWS2812.effectIndex) {
        case WS2812Config_Normal:
            WS2812ConfigNormalDisplay(gDefaultWS2812.ledIndex,gDefaultWS2812.r,gDefaultWS2812.g,gDefaultWS2812.b);
            break;
        case WS2812Config_SetOnTime:
            WS2812ConfigSetOnTime(gDefaultWS2812.ledIndex,gDefaultWS2812.r,gDefaultWS2812.g,gDefaultWS2812.b,gDefaultWS2812.cycle);
            break;
        case WS2812Config_Breath:
            WS2812ConfigBreath(gDefaultWS2812.ledIndex,gDefaultWS2812.r,gDefaultWS2812.g,gDefaultWS2812.b,gDefaultWS2812.cycle,0,-1);
            break;
        case WS2812Config_Flashing:
            WS2812ConfigFlashing(gDefaultWS2812.ledIndex,gDefaultWS2812.r,gDefaultWS2812.g,gDefaultWS2812.b,gDefaultWS2812.cycle);
            break;
        case WS2812Config_Rainbow:
            WS2812ConfigRainBowBreath(gDefaultWS2812.ledIndex,gDefaultWS2812.cycle);
            break;
        case WS2812Config_Surround:
            WS2812ConfigSurround(gDefaultWS2812.ledIndex,gDefaultWS2812.r,gDefaultWS2812.g,gDefaultWS2812.b,gDefaultWS2812.cycle);
            break;
        case WS2812Config_Police:
            WS2812ConfigPolice(gDefaultWS2812.ledIndex,gDefaultWS2812.cycle);
            break;
    }
}












