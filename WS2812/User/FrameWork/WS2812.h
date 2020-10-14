/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               WS2812.h
** Latest modified date:    2020-05-27
** Latest version:          V1.0.0
** Description:             WS2812彩灯驱动
**
**------------------------------------------------------------
** Created by:              liu xiang
** Created date:            2020-05-27
** Version:                 V1.0.0
** Descriptions:            WS2812彩灯驱动
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/


#ifndef __WS2812__H
#define __WS2812__H
#include "stdint.h"



enum {
    Ws2812_Normal = 0,  //正常模式
    Ws2812_OnWithTime,  //定时熄灭
    Ws2812_Breath,      //呼吸模式
    Ws2812_Flashing,    //闪烁模式
	Ws2812_RainBow,     //彩虹变换
    Ws2812_Surround,    //流水
    Ws2812_Police,      //红蓝交替
};

struct SSetNormal_Struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct SSetNormal_Struct SetNormal_Struct; /* WS2812_Struct 类型 */
typedef SetNormal_Struct *PSetNormal_Struct;      /* PWS2812_Struct 指针类型 */

struct SSetOnTime_Struct {
    uint8_t isON;
    float cycle;            //点亮时间
    float cnt;              //当前时间
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct SSetOnTime_Struct SetOnTime_Struct; /* WS2812_Struct 类型 */
typedef SetOnTime_Struct *PSetOnTime_Struct;      /* PWS2812_Struct 指针类型 */

struct SRainBowBreath_Struct {
    uint16_t ledIndex;
    uint8_t colorIndex;     //颜色索引
    uint8_t breathFlag;     //呼气和吸气
    float cycle;            //单位秒
    float cnt;
};
typedef struct SRainBowBreath_Struct RainBowBreath_Struct; /* WS2812_Struct 类型 */
typedef RainBowBreath_Struct *PRainBowBreath_Struct;      /* PWS2812_Struct 指针类型 */

struct SSurround_Struct {
    uint8_t surroundIndex;
    float cycle;            //循环周期
    float cnt;              //时间计数Cnt 单位秒
    uint8_t id;
    uint8_t num;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct SSurround_Struct Surround_Struct; /* WS2812_Struct 类型 */
typedef Surround_Struct *PSurround_Struct;      /* PWS2812_Struct 指针类型 */

struct SFlashing_Struct {
    uint8_t ledStatus;
    float cycle;          //闪烁周期   单位秒
    float cnt;          //时间计数Cnt 单位秒
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct SFlashing_Struct Flashing_Struct; /* WS2812_Struct 类型 */
typedef Flashing_Struct *PFlashing_Struct;      /* PWS2812_Struct 指针类型 */

struct SBreath_Struct {
    uint8_t breathFlag; //呼气和吸气
    int breathCounts; //呼气和吸气次数
    float cycle;   //单位秒
    float cnt;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct SBreath_Struct Breath_Struct; /* WS2812_Struct 类型 */
typedef Breath_Struct *PBreath_Struct;      /* PWS2812_Struct 指针类型 */

struct SPolice_Struct {
    uint8_t ledStatus;
    float cycle;          //闪烁周期   单位秒
    float cnt;          //时间计数Cnt 单位秒
};
typedef struct SPolice_Struct Police_Struct; /* WS2812_Struct 类型 */
typedef Police_Struct *PPolice_Struct;      /* PWS2812_Struct 指针类型 */

struct SWS2812B_Struct{
    uint8_t effectFlag;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    SetNormal_Struct gNormal;
    Breath_Struct gBreath;
    Flashing_Struct gFlashing;
    RainBowBreath_Struct gRainBow;
    SetOnTime_Struct gSetOnTime;
    Surround_Struct gSurround;
    Police_Struct gPolice;
};
typedef struct SWS2812B_Struct WS2812B_Struct;
typedef WS2812B_Struct *PWS2812B_Struct;

struct SWS2812BGroup_Struct{
	float cycle;         //循环函数执行周期单位秒 建议0.01
    uint32_t startTime;  //记录系统时间，判断是否到达新的周期
    uint8_t ledNum;      //LED数量
    PWS2812B_Struct LED; //LED数组
    uint16_t *buffer;    //存放数据的数组
    void (*TransmitData)(uint16_t *buf,uint16_t length); //数据传输函数
};
typedef struct SWS2812BGroup_Struct WS2812BGroup_Struct;
typedef WS2812BGroup_Struct *PWS2812BGroup_Struct;


/*************************************************************
** Function name:       WS2812B_EXPORT
** Descriptions:        WS2812实例化
**                      x:对象名字
**                      xNum:LED数量
**                      xTransmitData：SPI传输函数 16位数据 9MHz MSBFirst CPOL:LoW CPHA 1Edge
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define WS2812B_EXPORT(x,xNum,xTransmitData)            \
uint16_t xWS2812BBuffer [24*xNum] = {0};                \
WS2812B_Struct xWS2812BLED [xNum] = {0};                \
WS2812BGroup_Struct x = {                               \
	.cycle = 0.01,                                      \
    .startTime = 0,                                     \
    .ledNum = xNum,                                     \
    .LED = xWS2812BLED,                                 \
    .buffer = xWS2812BBuffer,                           \
    .TransmitData = xTransmitData,                      \
};



extern volatile uint32_t gWS2812_TimeCNT;

/*************************************************************
** Function name:       WS2812_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
#define WS2812_TIMEBASE(ms)                \
        gWS2812_TimeCNT+= ms

/*************************************************************
** Function name:       WS2812_GETTIME
** Descriptions:        获取起始时间
** Input parameters:    None
** Output parameters:   None
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define WS2812_GETTIME(void)                        \
    gWS2812_TimeCNT

/*************************************************************
** Function name:       WS2812_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Output parameters:   None
** Returned value:      false,未超时，true，超时
*************************************************************/
#define WS2812_TIMEOUT(timeOut,startTime)                \
    ((gWS2812_TimeCNT - startTime) >= timeOut ? 1 : 0)


void WS2812StartNormalDisplay(PWS2812BGroup_Struct gWS2812,uint16_t index, uint8_t r,uint8_t g,uint8_t b);
void WS2812StartSurround(PWS2812BGroup_Struct gWS2812,uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812SetOnTimeDisplay(PWS2812BGroup_Struct gWS2812,uint16_t index, uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812StartRainBowBreathe(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,float cycle);
void WS2812StartBreathe(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle,uint8_t breathFlag,int breathCounts);
void WS2812StartFlashing(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle);
void WS2812StartPolice(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,float cycle);
void WS2812Cycle(PWS2812BGroup_Struct gWS2812);




#endif







