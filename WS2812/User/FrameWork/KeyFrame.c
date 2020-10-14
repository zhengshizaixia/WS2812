/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               KeyFrame.c
** Latest modified date:    2019-11-08
** Latest version:          V1.0.0
** Description:             KEY Frame
**
**------------------------------------------------------------
** Created by:              Chen JunTong
** Created date:            2019-11-08
** Version:                 V1.0.0
** Descriptions:            KEY Frame
**
**------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Description:
**
*************************************************************/
#include "KeyFrame.h"
#include "stddef.h"

uint32_t gKeyFrame_TimeCNT = 0;

/*************************************************************
** Function name:       KeyFrame_ToUserDataFill
** Descriptions:        传递给用户的数据赋值
** Input parameters:    p:参数结构体指针
**                      status：状态
**                      num：按下次数
**                      scanTime：扫描时间
**                      isExitReleaseCB:退出松开回调
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_ToUserDataFill(PKeyFramePARM p, uint8_t status, uint8_t num, uint32_t scanTime, uint8_t isExitReleaseCB)
{
    p->toUser.status = status;
    p->toUser.num = num;
    p->toUser.scanTime = scanTime;
    p->toUser.isExitReleaseCB = isExitReleaseCB;
}

/*************************************************************
** Function name:       KeyFrame_FuncDisableExcept
** Descriptions:        禁用除exceptName外的所有功能
** Input parameters:    pFunc:功能参数指针
**                      exceptIndex:除外的索引名称
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncDisableExcept(PKeyFrame_FuncPARM pFunc, uint8_t exceptIndex)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        if(pFunc->pUser[cir].index != exceptIndex) {
            pFunc->pStatus[cir].enable = false;
        }
    }
}

/*************************************************************
** Function name:       KeyFrame_FuncDisable
** Descriptions:        功能禁用
** Input parameters:    pFunc:功能参数指针
**                      index：功能索引
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncDisable(PKeyFrame_FuncPARM pFunc, uint8_t index)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        if(pFunc->pUser[cir].index == index) {
            pFunc->pStatus[cir].enable = false;
            break;
        }
    }
}

/*************************************************************
** Function name:       KeyFrame_FuncEnable
** Descriptions:        功能开启
** Input parameters:    pFunc:功能参数指针
**                      index：功能索引
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncEnable(PKeyFrame_FuncPARM pFunc, uint8_t index)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        if(pFunc->pUser[cir].index == index) {
            pFunc->pStatus[cir].enable = true;
            break;
        }
    }
}

/*************************************************************
** Function name:       KeyFrame_FuncEnable
** Descriptions:        功能开启
** Input parameters:    pFunc:功能参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncEnableAll(PKeyFrame_FuncPARM pFunc)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        pFunc->pStatus[cir].enable = true;
    }
}

/*************************************************************
** Function name:       KeyFrame_FuncStatusClearAll
** Descriptions:        清除所有功能状态
** Input parameters:    pFunc:功能参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncStatusClearAll(PKeyFrame_FuncPARM pFunc)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        pFunc->pStatus[cir].status = KeyFrame_STATUS_END;
    }
}

/*************************************************************
** Function name:       KeyFrame_FuncStatusClear
** Descriptions:        清除功能状态
** Input parameters:    pFunc:功能参数指针
**                      index：功能索引
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncStatusClear(PKeyFrame_FuncPARM pFunc, uint8_t index)
{
    uint8_t cir = 0;
    for(cir = 0; cir < pFunc->funcNum; cir ++) {
        if(pFunc->pUser[cir].index == index) {
            pFunc->pStatus[cir].status = KeyFrame_STATUS_END;
            break;
        }
    }
}


/*************************************************************
** Function name:       KeyFrame_KeyReleaseHandle
** Descriptions:        按键松开处理
** Input parameters:    p:参数结构体指针
**                      pLink:链路指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_KeyReleaseHandle(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    PKeyFrame_FuncPARM pFunc = p->pFuncTable[pLink->funcInTable];
    uint8_t cir = 0;
    if(pLink->funcInTable == KeyFrame_DEFAULTVALUE) {
        return;
    }
    for(cir = 0; cir < pFunc->funcNum; cir++) {
        if(pFunc->pStatus[cir].enable == true
                && pFunc->pStatus[cir].status != KeyFrame_STATUS_LOCKREPEAT
                && (pFunc->pUser[cir].num == pLink->num || pFunc->pUser[cir].num == 0)
                && pLink->scanTime >= pFunc->pUser[cir].timeMin
                && (pLink->scanTime < pFunc->pUser[cir].timeMax || pFunc->pUser[cir].timeMax == 0)
                && pFunc->pUser[cir].CallBack != NULL) {
            if(pLink->isExitReleaseCB == false) {
                pLink->isExitReleaseCB = true;
                KeyFrame_ToUserDataFill(p, KeyFrame_STATUS_FIRST, pLink->num, pLink->scanTime, pLink->isExitReleaseCB);
                pFunc->pUser[cir].CallBack(&p->toUser);
                pFunc->pStatus[cir].status = p->toUser.status;
                pLink->isExitReleaseCB = p->toUser.isExitReleaseCB;
            }
            if(pLink->isExitReleaseCB == true) {
                return;
            }
        }
    }
}

/*************************************************************
** Function name:       KeyFrame_KeyPressHandle
** Descriptions:        按键按下处理
** Input parameters:    p:参数结构体指针
**                      pLink:链路指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_KeyPressHandle(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    PKeyFrame_FuncPARM pFunc = p->pFuncTable[pLink->funcInTable];
    uint8_t status = KeyFrame_STATUS_FIRST;
    /* 判断功能表是否存在 */
    if(pLink->funcInTable == KeyFrame_DEFAULTVALUE) {
        return;
    }
    /* 设置状态 */
    if(pLink->scanMark == pLink->lastScanMark) {
        status = KeyFrame_STATUS_REPEAT;
    } else {
        pLink->isExitReleaseCB = false;
    }
    if(pFunc->pressStatus == KeyFrame_STATUS_LOCKREPEAT) {
        status = KeyFrame_STATUS_LOCKREPEAT;
    }
    /* 判断按键回调是否存在 */
    if(p->pFuncTable[pLink->funcInTable]->PressCallBack == NULL) {
        return;
    }
    KeyFrame_ToUserDataFill(p, status, pLink->num, KeyFrame_GETTIME() - pLink->scanTime, pLink->isExitReleaseCB);
    pFunc->PressCallBack(&p->toUser);
    pFunc->pressStatus = p->toUser.status;
    pLink->isExitReleaseCB = p->toUser.isExitReleaseCB;
}

/*************************************************************
** Function name:       KeyFrame_EliminationTremble
** Descriptions:        消抖
** Input parameters:    p:参数结构体指针
**                      pKeyStatus：按键状态参数指针
**                      pUserKey：按键用户参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_EliminationTremble(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    if(pLink->status != pLink->ReadKey()
            || (pLink->status == pLink->effectStatus && pLink->scanMark == false)) {
        if(pLink->trembleMark == false) {
            pLink->jumpTime = KeyFrame_GETTIME();
        }
        if(KeyFrame_TIMEOUT(pLink->jumpTime, p->trembleTime) == true) {
            pLink->trembleMark = false;
            pLink->status = pLink->ReadKey();
        } else {
            pLink->trembleMark = true;
        }
    } else {
        pLink->trembleMark = false;
    }
}

/*************************************************************
** Function name:       KeyFrame_Scan
** Descriptions:        按键扫描
** Input parameters:    p:参数结构体指针
**                      pKeyStatus：按键状态参数指针
**                      pUserKey：按键用户参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_Scan(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    if(pLink->status == pLink->effectStatus) {
        if(pLink->scanMark == false) {
            pLink->scanTime = pLink->jumpTime;
            pLink->scanMark = true;
        }
        if(pLink->lastStatus != pLink->status) {
            pLink->num++;
        }
        KeyFrame_KeyPressHandle(p, pLink);
    } else {
        if(KeyFrame_TIMEOUT(pLink->jumpTime, p->dPressTime) == true) {
            if(pLink->scanMark == true) {
                pLink->scanTime = KeyFrame_GETTIME() - pLink->scanTime - p->dPressTime;
                KeyFrame_KeyReleaseHandle(p, pLink);
                pLink->scanMark = false;
                pLink->num = 0;
            }
        }
    }
    pLink->lastScanMark = pLink->scanMark;
    pLink->lastStatus = pLink->status;
}

/*************************************************************
** Function name:       KeyFrame_CLEAR_LINK
** Descriptions:        清除链路检测
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_CLEAR_LINK(pLink)          \
        pLink->scanMark = false;            \
        pLink->num = 0;                     \
        pLink->trembleMark = false

/*************************************************************
** Function name:       KeyFrame_Clear
** Descriptions:        清空按键状态
** Input parameters:    p:参数结构体指针
**                      pKeyStatus：按键状态参数指针
**                      pUserKey：按键用户参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
inline void KeyFrame_Clear(PKeyFramePARM p)
{
    uint8_t cir = 0;
    for(cir = 0; cir < p->LinkNum; cir++) {
        KeyFrame_CLEAR_LINK(p->pLinkTable[cir]);
    }
}

/*************************************************************
** Function name:       KeyFrame_SearchLinkInTable
** Descriptions:        查找链路在表的位置
** Input parameters:    p：参数结构体指针
**                      pLink:查找的链路指针
** Output parameters:   no
** min：                no
** Returned             KeyFrame_DEFAULTVALUE，没有注册项
**                      其它：链路在表的位置
*************************************************************/
uint8_t KeyFrame_SearchLinkInTable(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    uint16_t cirNum = p->LinkNum;
    while(cirNum) {
        cirNum--;
        if(p->pLinkTable[cirNum] == pLink) {
            return cirNum;
        }
    }
    return KeyFrame_DEFAULTVALUE;
}

/*************************************************************
** Function name:       KeyFrame_RegisterLink
** Descriptions:        注册链路
** Input parameters:    p：参数结构体指针
**                      pLink：注册的链路指针
** Output parameters:   no
** min：                no
** Returned             0，成功
**                      1，注册地址超出格式表范围，更多格式修改KeyFrame_EXPORT的linkNum个数
**                      2，pLink为NULL
*************************************************************/
uint8_t KeyFrame_RegisterLink(PKeyFramePARM p, PKeyFrame_LinkPARM pLink)
{
    /* 检查格式是否已经注册 */
    if(KeyFrame_SearchLinkInTable(p, pLink) != KeyFrame_DEFAULTVALUE) {
        return 0;
    }
    if(p->LinkNum >= p->LinkMaxNum) {
        return 1;
    }
    if(pLink == NULL) {
        return 2;
    } else {
        p->pLinkTable[p->LinkNum] = pLink;
        p->LinkNum++;
        return 0;
    }
}

/*************************************************************
** Function name:       KeyFrame_SearchFuncInTable
** Descriptions:        查找功能在表的位置
** Input parameters:    p：参数结构体指针
**                      pFunc:查找的链路指针
** Output parameters:   no
** min：                no
** Returned             KeyFrame_DEFAULTVALUE，没有注册项
**                      其它：功能在表的位置
*************************************************************/
uint8_t KeyFrame_SearchFuncInTable(PKeyFramePARM p, PKeyFrame_FuncPARM pFunc)
{
    uint16_t cirNum = p->FuncNum;
    while(cirNum) {
        cirNum--;
        if(p->pFuncTable[cirNum] == pFunc) {
            return cirNum;
        }
    }
    return KeyFrame_DEFAULTVALUE;
}

/*************************************************************
** Function name:       KeyFrame_RegisterFunc
** Descriptions:        注册功能
** Input parameters:    p：参数结构体指针
**                      pFunc：注册的链路指针
** Output parameters:   no
** min：                no
** Returned             0，成功
**                      1，注册地址超出格式表范围，更多格式修改KeyFrame_EXPORT的funcNum个数
**                      2，pFunc为NULL
*************************************************************/
uint8_t KeyFrame_RegisterFunc(PKeyFramePARM p, PKeyFrame_FuncPARM pFunc)
{
    /* 检查格式是否已经注册 */
    if(KeyFrame_SearchFuncInTable(p, pFunc) != KeyFrame_DEFAULTVALUE) {
        return 0;
    }
    if(p->FuncNum >= p->FuncMaxNum) {
        return 1;
    }
    if(pFunc == NULL) {
        return 2;
    } else {
        p->pFuncTable[p->FuncNum] = pFunc;
        p->FuncNum++;
        return 0;
    }
}

/*************************************************************
** Function name:       KeyFrame_LinkIsEnable
** Descriptions:        链路是否使能
** Input parameters:    pLink：链路指针
**                      isEnable：是否是能，true使能，false 禁能
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void KeyFrame_LinkIsEnable(PKeyFrame_LinkPARM pLink,uint8_t isEnable)
{
    pLink->isEnable = isEnable;
}

/*************************************************************
** Function name:       KeyFrame_ScanExec
** Descriptions:        按键扫描执行函数
** Input parameters:    p:参数结构体指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_ScanExec(PKeyFramePARM p)
{
    uint8_t cir = 0;
    PKeyFrame_LinkPARM pLink;
    if(KeyFrame_TIMEOUT(p->blockTime, p->blockInvalidTime) == true) {
        KeyFrame_Clear(p);
    }
    for(cir = 0; cir < p->LinkNum; cir++) {
        pLink = p->pLinkTable[cir];
        if(pLink->isEnable == false){
            KeyFrame_CLEAR_LINK(pLink);
        }
        KeyFrame_EliminationTremble(p, pLink);
        if(pLink->trembleMark == false || pLink->scanMark == true) {
            KeyFrame_Scan(p, pLink);
        }
    }
    p->blockTime = KeyFrame_GETTIME();
}

/*************************************************************
** Function name:       KeyFrame_RepeatExec
** Descriptions:        按键功能重复执行
** Input parameters:    p:参数结构体指针
**                      pKeyStatus：按键状态参数指针
**                      pUserKey：按键用户参数指针
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_FuncRepeatExec(PKeyFramePARM p)
{
    uint8_t cir1 = 0;
    uint8_t cir2 = 0;
    uint8_t cir2Num = 0;
    PKeyFrame_FuncStatusPARM pFuncStatus;
    for(cir1 = 0; cir1 < p->FuncNum; cir1++) {
        cir2Num = p->pFuncTable[cir1]->funcNum;
        if(p->pFuncTable[cir1]->pressStatus == KeyFrame_STATUS_LOCKREPEAT
                && p->pLinkTable[cir1]->scanMark == false) {
            KeyFrame_ToUserDataFill(p, KeyFrame_STATUS_LOCKREPEAT, 0, 0, false);
            p->pFuncTable[cir1]->PressCallBack(&p->toUser);
            p->pFuncTable[cir1]->pressStatus = p->toUser.status;
        }
        for(cir2 = 0; cir2 < cir2Num; cir2++) {
            pFuncStatus = &p->pFuncTable[cir1]->pStatus[cir2];
            if(pFuncStatus->enable == true
                    && (pFuncStatus->status == KeyFrame_STATUS_REPEAT
                        || pFuncStatus->status == KeyFrame_STATUS_LOCKREPEAT)) {
                KeyFrame_ToUserDataFill(p, pFuncStatus->status, 0, 0, false);
                p->pFuncTable[cir1]->pUser[cir2].CallBack(&p->toUser);
                pFuncStatus->status = p->toUser.status;
            }
        }
    }
}


/*************************************************************
** Function name:       KeyFrame_Scan
** Descriptions:        按键框架执行函数
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void KeyFrame_Exec(PKeyFramePARM p)
{
    KeyFrame_FuncRepeatExec(p);
    KeyFrame_ScanExec(p);
}




