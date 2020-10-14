/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:             KeyFunc.c
** Latest modified date:  2019-07-09
** Latest version:        V1.0.1
** Description:           KEY Run
**
**------------------------------------------------------------
** Created by:
** Created date:          2019-06-13
** Version:               V1.0.0
** Descriptions:          KEY Run
**
*************************************************************/
#include "KeyFunc.h"
#include "KEYGPIO.h"
#include "LEDConfig.h"
#include "WS2812Config.h"
/*************************************************************
** Function name:       KEY_Press
** Descriptions:        按键按下
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void KEY_Press(PKeyFrame_ToUserPARM pToUser)
{
    SetLEDFlashing(100);
    return;
}
/*************************************************************
** Function name:       KEY_UP
** Descriptions:        按键弹起
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void KEY_UP(PKeyFrame_ToUserPARM pToUser)
{
    SetLEDFlashing(1000);
	WS2812ConfigChangeEffect();
    return;
}


/* 定义按键框架 */
KeyFrame_FRAME_EXPORT(KEY_FRAME,10,200,500,1,1)
/* 定义按键链路 */
KeyFrame_LINK_EXPORT(LINK_Key,GetKeyLeave,0)
/* 定义按键功能 */
KeyFrame_FUNC_EXPORT(KEY_FUNCLIST,KEY_Press,
                     1,0,0,0,KEY_UP)







/*************************************************************
** Function name:       KeyFunc_Init
** Descriptions:        初始化
** Input parameters:    no
** Output parameters:   no
** Returned             no
*************************************************************/
void KeyFunc_Init(void)
{
    /* 链接按键框架，链路，功能 */
    KeyFrame_LINK_AND_FUNC(KEY_FRAME,LINK_Key,KEY_FUNCLIST);
}

/*************************************************************
** Function name:       KeyFunc_Exec
** Descriptions:        执行函数
** Input parameters:    no
** Output parameters:   no
** Returned             no
*************************************************************/
inline void KeyFunc_Exec(void)
{
    KeyFrame_Exec(&KEY_FRAME);
}



