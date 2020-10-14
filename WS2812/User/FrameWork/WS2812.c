/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               WS2812.c
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

#include "WS2812.h"
#include "SPI2.h"


//低电平时间
#define ZERO 0x7000
// 高电平时间
#define ONE 0x7F00

//彩虹灯对应RGB值，赤橙黄绿青蓝紫
uint32_t RainBow[7] = {0xFF0000,0xFFA500,0xFFFF00,0x00FF00,0x007FFF,0x0000FF,0x8B00FF};
volatile uint32_t gWS2812_TimeCNT;
/*************************************************************
** Function name:       LEDTransmitData
** Descriptions:        将计算好的LED数组通过SPI发送给灯带
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void LEDTransmitData(PWS2812BGroup_Struct gWS2812)
{
    gWS2812->TransmitData(gWS2812->buffer,gWS2812->ledNum*24);
}
/*************************************************************
** Function name:       SetLEDValue
** Descriptions:        计算LED亮度值对应的数据
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED
**                      r: 红色值
**                      g: 绿色值
**                      b: 蓝色值
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetLEDValue(PWS2812BGroup_Struct gWS2812,uint16_t index, uint8_t r,uint8_t g,uint8_t b)
{
	uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        if (g >> i & 0x01) {
            gWS2812->buffer[index*24+7-i] = ONE;
        } else {
            gWS2812->buffer[index*24+7-i] = ZERO;
        }
    }
    for (i = 0; i < 8; i++) {
        if (r >> i & 0x01) {
            gWS2812->buffer[index*24+15-i] = ONE;
        } else {
            gWS2812->buffer[index*24+15-i] = ZERO;
        }
    }
    for (i = 0; i < 8; i++) {
        if (b >> i & 0x01) {
            gWS2812->buffer[index*24+23-i] = ONE;
        } else {
            gWS2812->buffer[index*24+23-i] = ZERO;
        }
    }
}

/*************************************************************
** Function name:       WS2812StartNormalDisplay
** Descriptions:        设置普通模式下灯的颜色
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      r: 红色值
**                      g: 绿色值
**                      b: 蓝色值
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812StartNormalDisplay(PWS2812BGroup_Struct gWS2812,uint16_t index, uint8_t r,uint8_t g,uint8_t b)
{
	uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((index >> j) & 0x01) {
            gWS2812->LED[j].effectFlag = Ws2812_Normal;
            gWS2812->LED[j].gNormal.r = r;
            gWS2812->LED[j].gNormal.g = g;
            gWS2812->LED[j].gNormal.b = b;
        }
    }
}
/*************************************************************
** Function name:       WS2812StartNormalDisplayCycle
** Descriptions:        普通模式循环(自用)
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812StartNormalDisplayCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    gWS2812->LED[index].r =  gWS2812->LED[index].gNormal.r;
    gWS2812->LED[index].g =  gWS2812->LED[index].gNormal.g;
    gWS2812->LED[index].b =  gWS2812->LED[index].gNormal.b;
}
/*************************************************************
** Function name:       WS2812SetOnTimeDisplay
** Descriptions:        设置普通模式下灯亮的时间
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      r: 红色值
**                      g: 绿色值
**                      b: 蓝色值
**                      cycle: 定时时间 单位秒
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812SetOnTimeDisplay(PWS2812BGroup_Struct gWS2812,uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((index >> j) & 0x01) {
            gWS2812->LED[j].effectFlag = Ws2812_OnWithTime;
            gWS2812->LED[j].gSetOnTime.isON = 1;
            gWS2812->LED[j].gSetOnTime.cycle = cycle;
            gWS2812->LED[j].gSetOnTime.cnt = 0;
            gWS2812->LED[j].gSetOnTime.r = r;
            gWS2812->LED[j].gSetOnTime.g = g;
            gWS2812->LED[j].gSetOnTime.b = b;
        }
    }
}
/*************************************************************
** Function name:       WS2812SetOnTimeDisplayCycle
** Descriptions:        定时熄灭循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812SetOnTimeDisplayCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    if (gWS2812->LED[index].gSetOnTime.isON) {
        gWS2812->LED[index].gSetOnTime.cnt += gWS2812->cycle;
        if (gWS2812->LED[index].gSetOnTime.cnt >= gWS2812->LED[index].gSetOnTime.cycle) {
            gWS2812->LED[index].gSetOnTime.r = 0;
            gWS2812->LED[index].gSetOnTime.g = 0;
            gWS2812->LED[index].gSetOnTime.b = 0;
        }
    }
    gWS2812->LED[index].r =  gWS2812->LED[index].gSetOnTime.r;
    gWS2812->LED[index].g =  gWS2812->LED[index].gSetOnTime.g;
    gWS2812->LED[index].b =  gWS2812->LED[index].gSetOnTime.b;
}
/*************************************************************
** Function name:       WS2812StartSurround
** Descriptions:        设置流水模式
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      r: 红色值
**                      g: 绿色值
**                      b: 蓝色值
**                      cycle: 所有灯流水总时间 单位秒
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812StartSurround(PWS2812BGroup_Struct gWS2812,uint16_t index,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    uint8_t j = 0;
    uint8_t id = 0;
    uint8_t num = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((index >> j) & 0x01) {
            num ++;
        }
    }
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((index >> j) & 0x01) {

            if(gWS2812->LED[j].effectFlag  == Ws2812_Surround &&
                gWS2812->LED[j].gSurround.r == r &&
                gWS2812->LED[j].gSurround.g == g &&
                gWS2812->LED[j].gSurround.b == b &&
                gWS2812->LED[j].gSurround.cycle == cycle ) {
                continue;
            }
            gWS2812->LED[j].effectFlag = Ws2812_Surround;
            gWS2812->LED[j].gSurround.cycle = cycle;
            gWS2812->LED[j].gSurround.surroundIndex = 0;
            gWS2812->LED[j].gSurround.cnt = 0;
            gWS2812->LED[j].gSurround.id = id;
            gWS2812->LED[j].gSurround.r = r;
            gWS2812->LED[j].gSurround.g = g;
            gWS2812->LED[j].gSurround.b = b;
            gWS2812->LED[j].gSurround.num = num;
            id ++;
        }
    }
}
/*************************************************************
** Function name:       WS2812SurroundCycle
** Descriptions:        LED流水模式循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812SurroundCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    gWS2812->LED[index].gSurround.cnt += gWS2812->cycle;
    if (gWS2812->LED[index].gSurround.cnt >= gWS2812->LED[index].gSurround.cycle / gWS2812->LED[index].gSurround.num) {
        gWS2812->LED[index].gSurround.cnt = 0;
        if (gWS2812->LED[index].gSurround.id == gWS2812->LED[index].gSurround.surroundIndex) {
            gWS2812->LED[index].r =  gWS2812->LED[index].gSurround.r;
            gWS2812->LED[index].g =  gWS2812->LED[index].gSurround.g;
            gWS2812->LED[index].b =  gWS2812->LED[index].gSurround.b;
        } else {
            gWS2812->LED[index].r = 0;
            gWS2812->LED[index].g = 0;
            gWS2812->LED[index].b = 0;
        }
        gWS2812->LED[index].gSurround.surroundIndex = (gWS2812->LED[index].gSurround.surroundIndex + 1) % gWS2812->LED[index].gSurround.num;
    }
}
/*************************************************************
** Function name:       WS2812StartFlashing
** Descriptions:        设置闪烁模式
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      r: 红色值
**                      g: 绿色值
**                      b: 蓝色值
**                      cycle: 闪烁（亮灭）一次的时间 单位秒
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void WS2812StartFlashing(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((ledIndex >> j) & 0x01) {
            if(gWS2812->LED[j].effectFlag == Ws2812_Flashing &&
                gWS2812->LED[j].gFlashing.r == r &&
                gWS2812->LED[j].gFlashing.g == g &&
                gWS2812->LED[j].gFlashing.b == b &&
				gWS2812->LED[j].gFlashing.cycle == cycle) {
                continue;
            }
            gWS2812->LED[j].effectFlag = Ws2812_Flashing;
            gWS2812->LED[j].gFlashing.cycle = cycle;
            gWS2812->LED[j].gFlashing.ledStatus = 0;
            gWS2812->LED[j].gFlashing.cnt = 0;
            gWS2812->LED[j].gFlashing.r = r;
            gWS2812->LED[j].gFlashing.g = g;
            gWS2812->LED[j].gFlashing.b = b;
        }
    }
}

/*************************************************************
** Function name:       WS2812FlashingCycle
** Descriptions:        WS2812闪烁循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812FlashingCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    gWS2812->LED[index].gFlashing.cnt += gWS2812->cycle;
    if (gWS2812->LED[index].gFlashing.cnt >= gWS2812->LED[index].gFlashing.cycle/2) {
        gWS2812->LED[index].gFlashing.cnt = 0;
        if(gWS2812->LED[index].gFlashing.ledStatus == 1) {
            gWS2812->LED[index].gFlashing.ledStatus = 0;
            gWS2812->LED[index].r = 0;
            gWS2812->LED[index].g = 0;
            gWS2812->LED[index].b = 0;
        } else {
            gWS2812->LED[index].gFlashing.ledStatus = 1;
            gWS2812->LED[index].r = gWS2812->LED[index].gFlashing.r;
            gWS2812->LED[index].g = gWS2812->LED[index].gFlashing.g;
            gWS2812->LED[index].b = gWS2812->LED[index].gFlashing.b;
        }
    }
}
/*************************************************************
** Function name:       WS2812StartBreathe
** Descriptions:        启动呼吸灯
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      r:红色值
**                      g:绿色值
**                      b:蓝色值
**                      cycle：最暗->最亮 或 最亮->最暗 需要的时间
**                      breathFlag：起始状态 0：最暗->最亮 1：最亮->最暗
**                      breathCounts: 次数
** Output parameters:   None
** Returned value:      None
*************************************************************/
void WS2812StartBreathe(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,uint8_t r,uint8_t g,uint8_t b,float cycle,uint8_t breathFlag,int breathCounts)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((ledIndex >> j) & 0x01) {
            if(gWS2812->LED[j].effectFlag == Ws2812_Breath &&
                gWS2812->LED[j].gBreath.r == r &&
                gWS2812->LED[j].gBreath.g == g &&
                gWS2812->LED[j].gBreath.b == b &&
                gWS2812->LED[j].gBreath.breathCounts == breathCounts) {
                continue;
            }
            gWS2812->LED[j].effectFlag = Ws2812_Breath;
            gWS2812->LED[j].gBreath.cycle = cycle;
            gWS2812->LED[j].gBreath.breathFlag = breathFlag;
            gWS2812->LED[j].gBreath.breathCounts = breathCounts;
            if (breathFlag) {
                gWS2812->LED[j].gBreath.cnt = 250;
            } else {
                gWS2812->LED[j].gBreath.cnt = 0;
            }
            gWS2812->LED[j].gBreath.r = r;
            gWS2812->LED[j].gBreath.g = g;
            gWS2812->LED[j].gBreath.b = b;
        }
    }
}
/*************************************************************
** Function name:       WS2812BreathCycle
** Descriptions:        WS2812呼吸模式循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812BreathCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
	float rValue = 0.0;
	float gValue = 0.0;
	float bValue = 0.0;
    if (gWS2812->LED[index].gBreath.breathCounts != 0) {
        if (gWS2812->LED[index].gBreath.breathFlag == 0) {
            gWS2812->LED[index].gBreath.cnt += gWS2812->cycle * 1000 / gWS2812->LED[index].gBreath.cycle / 2 / 2;
        }else if (gWS2812->LED[index].gBreath.breathFlag == 1) {
            gWS2812->LED[index].gBreath.cnt -= gWS2812->cycle * 1000 / gWS2812->LED[index].gBreath.cycle / 2 / 2;
        }
    }

    if(gWS2812->LED[index].gBreath.cnt >= 250) {
        gWS2812->LED[index].gBreath.breathFlag = 1;
        if (gWS2812->LED[index].gBreath.breathCounts > 0) {
            gWS2812->LED[index].gBreath.breathCounts --;
        }

    } else if (gWS2812->LED[index].gBreath.cnt <= 0) {
        gWS2812->LED[index].gBreath.breathFlag = 0;
        if (gWS2812->LED[index].gBreath.breathCounts > 0) {
            gWS2812->LED[index].gBreath.breathCounts --;
        }
    }
    rValue = gWS2812->LED[index].gBreath.r*gWS2812->LED[index].gBreath.cnt/250;
    gValue = gWS2812->LED[index].gBreath.g*gWS2812->LED[index].gBreath.cnt/250;
    bValue = gWS2812->LED[index].gBreath.b*gWS2812->LED[index].gBreath.cnt/250;

    gWS2812->LED[index].r = rValue;
    gWS2812->LED[index].g = gValue;
    gWS2812->LED[index].b = bValue;
}

/*************************************************************
** Function name:       WS2812StartRainBowBreathe
** Descriptions:        启动彩虹呼吸灯
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      cycle：彩虹切换一次颜色需要的时间 单位秒 总共7种颜色
** Output parameters:   None
** Returned value:      None
*************************************************************/
void WS2812StartRainBowBreathe(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,float cycle)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((ledIndex >> j) & 0x01) {
            if(gWS2812->LED[j].effectFlag == Ws2812_RainBow &&
              gWS2812->LED[j].gRainBow.cycle == cycle) {
                continue;
            }
            gWS2812->LED[j].effectFlag = Ws2812_RainBow;
            gWS2812->LED[j].gRainBow.cycle = cycle;
            gWS2812->LED[j].gRainBow.breathFlag = 0;
            gWS2812->LED[j].gRainBow.cnt = 0;
            gWS2812->LED[j].gRainBow.colorIndex = 0;
        }
    }
}
/*************************************************************
** Function name:       WS2812RainBowBreathCycle
** Descriptions:        WS2812彩虹呼吸渐变循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812RainBowBreathCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    float rValue = 0.0;
	float gValue = 0.0;
	float bValue = 0.0;

    if (gWS2812->LED[index].gRainBow.breathFlag == 0) {
        gWS2812->LED[index].gRainBow.cnt += gWS2812->cycle * 1000 / gWS2812->LED[index].gRainBow.cycle / 2;
    }else if (gWS2812->LED[index].gRainBow.breathFlag == 1) {
        gWS2812->LED[index].gRainBow.cnt -= gWS2812->cycle * 1000 / gWS2812->LED[index].gRainBow.cycle / 2;
    }

    if(gWS2812->LED[index].gRainBow.cnt >= 250) {
        gWS2812->LED[index].gRainBow.breathFlag = 1;
    } else if (gWS2812->LED[index].gRainBow.cnt <= 0) {
        gWS2812->LED[index].gRainBow.breathFlag = 0;
		gWS2812->LED[index].gRainBow.colorIndex++;
    }

    rValue = ((RainBow[gWS2812->LED[index].gRainBow.colorIndex]>>16) & 0xFF) * gWS2812->LED[index].gRainBow.cnt/255;
    gValue = ((RainBow[gWS2812->LED[index].gRainBow.colorIndex]>>8) & 0xFF) * gWS2812->LED[index].gRainBow.cnt/255;
    bValue = ((RainBow[gWS2812->LED[index].gRainBow.colorIndex]) & 0xFF) * gWS2812->LED[index].gRainBow.cnt/255;

    gWS2812->LED[index].r = rValue;
    gWS2812->LED[index].g = gValue;
    gWS2812->LED[index].b = bValue;

    if (gWS2812->LED[index].gRainBow.colorIndex >= 7) {
        gWS2812->LED[index].gRainBow.colorIndex = 0;
    }
}
/*************************************************************
** Function name:       WS2812StartPolice
** Descriptions:        启动闪烁功能
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 每一bit代表一个LED 0x01:第一颗LED 0x04:第三颗LED
**                      cycle: 红蓝闪烁一次需要的周期值 单位秒
** Output parameters:   None
** Returned value:      None
*************************************************************/
void WS2812StartPolice(PWS2812BGroup_Struct gWS2812,uint16_t ledIndex,float cycle)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        if ((ledIndex >> j) & 0x01) {
            if(gWS2812->LED[j].effectFlag == Ws2812_Police &&
              gWS2812->LED[j].gPolice.cycle == cycle) {
                continue;
            }
            gWS2812->LED[j].effectFlag = Ws2812_Police;
            gWS2812->LED[j].gPolice.cycle = cycle;
            gWS2812->LED[j].gPolice.ledStatus = 0;
            gWS2812->LED[j].gPolice.cnt = 0;
        }
    }
}

/*************************************************************
** Function name:       WS2812PoliceCycle
** Descriptions:        WS2812红蓝闪烁模式循环函数
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
**                      index：LED索引 0:第一颗LED 1:第二颗LED
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void WS2812PoliceCycle(PWS2812BGroup_Struct gWS2812,uint8_t index)
{
    gWS2812->LED[index].gPolice.cnt += gWS2812->cycle;
    if (gWS2812->LED[index].gPolice.cnt >= gWS2812->LED[index].gPolice.cycle/2) {
        gWS2812->LED[index].gPolice.cnt = 0;
        if(gWS2812->LED[index].gPolice.ledStatus == 1) {
            gWS2812->LED[index].gPolice.ledStatus = 0;
            gWS2812->LED[index].r = 255;
            gWS2812->LED[index].g = 0;
            gWS2812->LED[index].b = 0;
        } else {
            gWS2812->LED[index].gPolice.ledStatus = 1;
            gWS2812->LED[index].r = 0;
            gWS2812->LED[index].g = 0;
            gWS2812->LED[index].b = 255;
        }
    }
}
/*************************************************************
** Function name:       UpdateLED
** Descriptions:        扫描每一个LED,判断当前应有的颜色
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
static void UpdateLED(PWS2812BGroup_Struct gWS2812)
{
    uint8_t j = 0;
    for (j = 0; j < gWS2812->ledNum; j++) {
        switch(gWS2812->LED[j].effectFlag) {
            case Ws2812_Normal:
                WS2812StartNormalDisplayCycle(gWS2812,j);
                break;
            case Ws2812_OnWithTime:
                WS2812SetOnTimeDisplayCycle(gWS2812,j);
                break;
            case Ws2812_Breath:
                WS2812BreathCycle(gWS2812,j);
                break;
            case Ws2812_Flashing:
                WS2812FlashingCycle(gWS2812,j);
                break;
            case Ws2812_RainBow:
                WS2812RainBowBreathCycle(gWS2812,j);
                break;
            case Ws2812_Surround:
                WS2812SurroundCycle(gWS2812,j);
                break;
            case Ws2812_Police:
                WS2812PoliceCycle(gWS2812,j);
                break;
        }
        SetLEDValue(gWS2812,j,gWS2812->LED[j].r, gWS2812->LED[j].g, gWS2812->LED[j].b);
    }
    LEDTransmitData(gWS2812);
}
/*************************************************************
** Function name:       WS2812Cycle
** Descriptions:        呼吸灯后台执行程序, 主循环中一直调用
** Input parameters:    gWS2812：PWS2812BGroup_Struct结构体指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void WS2812Cycle(PWS2812BGroup_Struct gWS2812)
{
    if(WS2812_TIMEOUT(gWS2812->cycle * 1000,gWS2812->startTime)) {
        gWS2812->startTime = WS2812_GETTIME();
        UpdateLED(gWS2812);
    }
}
