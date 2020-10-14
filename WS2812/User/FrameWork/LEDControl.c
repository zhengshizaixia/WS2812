/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDControl.c
** Latest modified date:    2020-07-20
** Latest version:          V1.0.0
** Description:             LED控制函数
**
**------------------------------------------------------------
** Created by:              liuxiang
** Created date:            2020-07-20
** Version:                 V1.0.0
** Descriptions:            LED控制函数
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "LEDControl.h"

volatile uint32_t gLED_TimeCNT;

/*************************************************************
** Function name:       LEDON
** Descriptions:        LED常亮
** Input parameters:    gLED:SLEDControl_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDON(PLEDControl_Struct gLED)
{
    gLED->state = LEDState_ON;
    gLED->SetLEDLeave(gLED->onLeave);
}
/*************************************************************
** Function name:       LEDFF
** Descriptions:        LED常灭
** Input parameters:    gLED:SLEDControl_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDOFF(PLEDControl_Struct gLED)
{
    gLED->state = LEDState_OFF;
    gLED->SetLEDLeave(!(gLED->onLeave));
}
/*************************************************************
** Function name:       LEDToggle
** Descriptions:        LED闪烁
** Input parameters:    gLED:SLEDControl_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDToggle(PLEDControl_Struct gLED)
{
    gLED->onoff = !gLED->onoff;
    gLED->SetLEDLeave(gLED->onoff);
}
/*************************************************************
** Function name:       LEdRunCycle
** Descriptions:        LED周期执行函数
** Input parameters:    gLED:SLEDControl_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEdRunCycle(PLEDControl_Struct gLED)
{
    if(LED_TIMEOUT(gLED->cycle,gLED->startTime)) {
        gLED->startTime = LED_GETTIME();
        if(gLED->state == LEDState_Toggle) {
            LEDToggle(gLED);
        }
    }
}
/*************************************************************
** Function name:       LEDFlashing
** Descriptions:        LED闪烁
** Input parameters:    gLED:SLEDControl_Struct结构体指针
**                      cycle:闪烁周期(单位ms)
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDFlashing(PLEDControl_Struct gLED,uint16_t cycle)
{
    gLED->state = LEDState_Toggle;
    gLED->cycle = cycle;
}


















