/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               LEDConfig.c
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

#include "LEDConfig.h"
#include "main.h"
#include "LEDControl.h"
#include "LEDGPIO.h"

LED_EXPORT(gDebugLED,1,SetDebugLEDLeave);



/*************************************************************
** Function name:       LEDConfig_Init
** Descriptions:        LED初始化函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDConfig_Init(void)
{
    LEDOFF(&gDebugLED);
}
/*************************************************************
** Function name:       LEDConfig_loop
** Descriptions:        LED循环函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDConfig_Loop(void)
{
    LEdRunCycle(&gDebugLED);

}
/*************************************************************
** Function name:       LEDConfig_DeInit
** Descriptions:        LEDConfig反初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDConfig_DeInit(void)
{
    LEDOFF(&gDebugLED);
}

/*************************************************************
** Function name:       设置LED亮灭状态
** Descriptions:        SetLEDStatus
** Input parameters:    index:LED索引
**                      status:亮灭
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetLEDStatus(uint8_t status)
{
    if (LED_ON == status) {
		LEDON(&gDebugLED);        
    } else if (LED_OFF == status) {
		LEDOFF(&gDebugLED);
	}         
}

/*************************************************************
** Function name:       设置LED闪烁
** Descriptions:        SetLEDFlashing
** Input parameters:    index:LED索引
**                      cycle:闪烁周期单位(ms)
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetLEDFlashing(uint16_t cycle)
{
	LEDFlashing(&gDebugLED,cycle);     
}
