/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:
** Latest modified date:
** Latest version:
** Description:
**
**------------------------------------------------------------
** Created by:
** Created date:
** Version:
** Descriptions:
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "ApplicationMain.h"

#include "PeripheralMain.h"
#include "FunctionMain.h"
/*************************************************************
** Function name:       ApplicationMain_Init
** Descriptions:        应用初始化函数
** Input parameters:    no
** Output parameters:   no
** Returned value:      no
*************************************************************/
void ApplicationMain_Init(void)
{
	PeripheralMain_Init();
	FunctionMain_Init();
}


/*************************************************************
** Function name:       ApplicationMain_Loop
** Descriptions:        应用循环函数
** Input parameters:    no
** Output parameters:   no
** Returned value:      no
*************************************************************/
void ApplicationMain_Loop(void)
{
	PeripheralMain_Loop();
	FunctionMain_Loop();
}






