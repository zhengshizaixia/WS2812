/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               FunctionMain.c
** Latest modified date:    2019-11-22
** Latest version:          V1.0.0
** Description:             功能主文件
**
**------------------------------------------------------------
** Created by:              Chen JunTong
** Created date:            2019-11-22
** Version:                 V1.0.0
** Descriptions:            功能主文件
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "FunctionMain.h"


#include "KeyFunc.h"



/*************************************************************
** Function name:       FunctionMain_Init
** Descriptions:        功能初始化
** Input parameters:    no
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/
void FunctionMain_Init(void)
{
    KeyFunc_Init();
}


/*************************************************************
** Function name:       FunctionMain_Loop
** Descriptions:        功能循环执行
** Input parameters:    no
** Output parameters:   no
** min：                no
** Returned             no
*************************************************************/
void FunctionMain_Loop(void)
{
    KeyFunc_Exec();
}







