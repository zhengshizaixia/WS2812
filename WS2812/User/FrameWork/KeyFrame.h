/********************** Copyright(c)***************************
** Shenzhen Yuejiang Technology Co., Ltd.
**
** http:// www.dobot.cc
**
**------File Info----------------------------------------------
** File name:               KeyFrame.h
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

#ifndef KeyFrame_H
#define KeyFrame_H

#include "stdint.h"
#include "stdbool.h"

#define KeyFrame_DEFAULTVALUE 0xFF

typedef enum{
   KeyFrame_STATUS_END = 0,            /* 结束 */
   KeyFrame_STATUS_FIRST,              /* 首次执行 */
   KeyFrame_STATUS_REPEAT,             /* 重复执行 */
   KeyFrame_STATUS_LOCKREPEAT,         /* 锁定重复执行，新的指令会被丢弃，不能覆盖当前指令 */
}KeyFrame_StatusList;

#pragma pack(1)

typedef struct KeyFrame_LinkParm KeyFrame_LinkPARM;               /* 结构体类型*/
typedef KeyFrame_LinkPARM *PKeyFrame_LinkPARM;                    /* 结构体指针类型*/

typedef struct KeyFrame_FuncParm KeyFrame_FuncPARM;               /* 功能结构体类型*/
typedef KeyFrame_FuncPARM *PKeyFrame_FuncPARM;                    /* 功能结构体指针类型*/


/* 传递给用户参数 */
struct KeyFrame_ToUserParm {
    uint8_t status;                     /* 按键状态 */
    uint8_t num;                        /* 按键生效次数 */
    uint32_t scanTime;                  /* 按键生效时间 */
    uint8_t isExitReleaseCB:1;          /* 是否退出松开回调函数，只作用在按键松开时调用回调的时候 */
};
typedef struct KeyFrame_ToUserParm KeyFrame_ToUserPARM;               /* 结构体类型*/
typedef KeyFrame_ToUserPARM *PKeyFrame_ToUserPARM;                    /* 结构体指针类型*/

/* 功能用户参数 */
struct KeyFrame_FuncUserParm {
    uint8_t index;                  /* 名称索引 */
    uint8_t num;
    uint16_t timeMin;
    uint16_t timeMax;
/*************************************************************
** Function name:       CallBack
** Descriptions:        回调函数
** Input parameters:    pToUser:传递给用户的参数指针
** Output parameters:   no
** Returned             no
*************************************************************/
    void (*CallBack)(PKeyFrame_ToUserPARM pToUser);
};
typedef struct KeyFrame_FuncUserParm KeyFrame_FuncUserPARM;               /* 结构体类型*/
typedef KeyFrame_FuncUserPARM *PKeyFrame_FuncUserPARM;                    /* 结构体指针类型*/

/* 功能状态参数 */
struct KeyFrame_FuncStatusParm {
    uint8_t enable:1;
    uint8_t status:7;
};
typedef struct KeyFrame_FuncStatusParm KeyFrame_FuncStatusPARM;               /* 结构体类型*/
typedef KeyFrame_FuncStatusPARM *PKeyFrame_FuncStatusPARM;                    /* 结构体指针类型*/

/* 功能参数 */
struct KeyFrame_FuncParm {
/*************************************************************
** Function name:       PressCallBack
** Descriptions:        按键按下回调函数
** Input parameters:    pToUser:传递给用户的参数指针
** Output parameters:   no
** Returned             no
*************************************************************/
    void (*PressCallBack)(PKeyFrame_ToUserPARM pToUser);
    uint8_t pressStatus;
    PKeyFrame_FuncUserPARM pUser;
    PKeyFrame_FuncStatusPARM pStatus;
    uint8_t funcNum;
};

/* 按键状态参数 */
struct KeyFrame_LinkParm {
/*************************************************************
** Function name:       ReadKey
** Descriptions:        读取按键状态
** Input parameters:    no
** Output parameters:   no
** Returned             按键状态
*************************************************************/
    uint8_t (*ReadKey)(void);
    uint8_t effectStatus:1;          /* 按压状态 */

    uint8_t status:1;               /* 按键状态 */
    uint8_t lastStatus:1;           /* 按键上一次状态 */
    uint8_t scanMark:1;             /* 按键扫描标记 */
    uint8_t lastScanMark:1;         /* 按键上一次扫描标记 */
    uint8_t trembleMark:1;          /* 消抖标记 */
    uint8_t isExitReleaseCB:1;      /* 是否退出松开回调函数，只作用在按键松开时调用回调的时候 */
    uint8_t isEnable:1;             /* 是否使能 */

    uint8_t num;                    /* 按键生效次数 */
    uint8_t funcInTable;            /* 功能在表的位置 */
    uint32_t scanTime;              /* 按键生效时间 */
    uint32_t jumpTime;              /* 按键跳转时间 */
};

/* 按键参数 */
struct KeyFrameParm {

    uint16_t trembleTime;       /* 消抖时间 */
    uint16_t dPressTime;        /* 连按间隔 */
    uint16_t blockInvalidTime;  /* 程序阻塞时按键检测失效时间 */

    PKeyFrame_LinkPARM *pLinkTable;
    uint8_t LinkMaxNum;                                      /* 链路最大个数 */
    uint8_t LinkNum;                                         /* 已注册链路个数 */
    PKeyFrame_FuncPARM *pFuncTable;
    uint8_t FuncMaxNum;                                      /* 功能最大个数 */
    uint8_t FuncNum;                                         /* 已注册功能个数 */

    uint32_t blockTime;         /* 阻塞时间 */
    KeyFrame_ToUserPARM toUser;
};
typedef struct KeyFrameParm KeyFramePARM;               /* 结构体类型*/
typedef KeyFramePARM *PKeyFramePARM;                    /* 结构体指针类型*/

#pragma pack()

extern uint32_t gKeyFrame_TimeCNT;

/*************************************************************
** Function name:       KeyFrame_TIMEBASE
** Descriptions:        时基,放在周期为1ms的函数里面执行
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
#define KeyFrame_TIMEBASE(ms)                \
        gKeyFrame_TimeCNT += ms

/*************************************************************
** Function name:       KeyFrame_GETTIME
** Descriptions:        获取起始时间
** Input parameters:    None
** Output parameters:   None
** Returned value:      (uint32_t)起始时间
*************************************************************/
#define KeyFrame_GETTIME(void)                        \
    gKeyFrame_TimeCNT

/*************************************************************
** Function name:       KeyFrame_TIMEOUT
** Descriptions:        检查超时
** Input parameters:    timeOut：(uint32_t)超时时间
**                      startTime:(uint32_t)开始的时间
** Output parameters:   None
** Returned value:      false,未超时，true，超时
*************************************************************/
#define KeyFrame_TIMEOUT(timeOut,startTime)                \
    ((gKeyFrame_TimeCNT - startTime) > timeOut ? true : false)

/*************************************************************
** Function name:       KeyFrame_FRAME_EXPORT
** Descriptions:        定义按键框架
** Input parameters:    name：(KeyFramePARM)需符合变量命名规范
**                      trembleTime：(uint16_t)消抖时间
**                      dPressTime：(uint16_t)连按间隔
**                      blockInvalidTime：(uint16_t) 程序阻塞时按键检测失效时间,即超过该时间按键循环函数未被执行，则清空之前的所有按键检测状态
**                      linkNum：(uint8_t)链路最大个数
**                      funcNum：(uint8_t)功能列表最大个数
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_FRAME_EXPORT(name,trembleTime,dPressTime,blockInvalidTime,linkNum,funcNum) \
        PKeyFrame_LinkPARM KeyFrame_LinkInTable##name[linkNum];                             \
        PKeyFrame_FuncPARM KeyFrame_FuncInTable##name[funcNum];                             \
        KeyFramePARM name =                                                                 \
        {                                                                                   \
            trembleTime,                                                                    \
            dPressTime,                                                                     \
            blockInvalidTime,                                                               \
            KeyFrame_LinkInTable##name,                                                     \
            linkNum,                                                                        \
            0,                                                                              \
            KeyFrame_FuncInTable##name,                                                     \
            funcNum,                                                                        \
            0,                                                                              \
            0,                                                                              \
        };

/*************************************************************
** Function name:       KeyFrame_FRAME_EXTERN
** Descriptions:        声明按键框架
** Input parameters:    name：(KeyFramePARM)需符合变量命名规范
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_FRAME_EXTERN(name)             \
        extern KeyFramePARM name;

/*************************************************************
** Function name:       KeyFrame_LINK_EXPORT
** Descriptions:        定义按键链路
** Input parameters:    name：(KeyFrame_LinkPARM)需符合变量命名规范
**                      ReadKey：读取按键状态回调函数，具体接口类型查看 KeyFrame_LinkParm
**                      effectStatus：(uint8_t)按键生效的状态
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_LINK_EXPORT(name,ReadKey,effectStatus)                                     \
        KeyFrame_LinkPARM name =                                                            \
        {                                                                                   \
            ReadKey,                                                                        \
            effectStatus,                                                                   \
            !effectStatus,                                                                  \
            !effectStatus,                                                                  \
            false,                                                                          \
            false,                                                                          \
            false,                                                                          \
            false,                                                                          \
            true,                                                                           \
            0,                                                                              \
            KeyFrame_DEFAULTVALUE,                                                          \
            0,                                                                              \
            0,                                                                              \
        };

/*************************************************************
** Function name:       KeyFrame_LINK_EXPORT
** Descriptions:        声明按键链路
** Input parameters:    name：(KeyFrame_LinkPARM)需符合变量命名规范
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_LINK_EXTERN(name)
        extern KeyFrame_LinkPARM name;

/*************************************************************
** Function name:       KeyFrame_FUNC_EXPORT
** Descriptions:        定义按键功能列表
** Input parameters:    name：(KeyFrame_FuncPARM)需符合变量命名规范、
**                      PressCallBack：按键按下的回调函数，具体类型查看 KeyFrame_FuncParm
**                      FuncList:(KeyFrame_FuncUserPARM)功能列表
**                              index：(uint8_t)名称索引
**                              num：(uint8_t)按键生效次数
**                              timeMin：(uint16_t)按键生效的最短时间
**                              timeMax：(uint16_t)按键生效的最大时间
**                              CallBack：按键功能回调函数，具体查看 KeyFrame_FuncUserParm
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_FUNC_EXPORT(name,PressCallBack,FuncList...)                                    \
        KeyFrame_FuncUserPARM PKeyFrame_FuncUser##name[] =                                      \
        {                                                                                       \
            FuncList                                                                            \
        };                                                                                      \
        KeyFrame_FuncStatusPARM KeyFrame_FuncStatus##name[sizeof(PKeyFrame_FuncUser##name)      \
                                                          / sizeof(KeyFrame_FuncUserPARM)];     \
        KeyFrame_FuncPARM name =                                                                \
        {                                                                                       \
            PressCallBack,                                                                      \
            KeyFrame_STATUS_FIRST,                                                              \
            PKeyFrame_FuncUser##name,                                                           \
            KeyFrame_FuncStatus##name,                                                          \
            sizeof(PKeyFrame_FuncUser##name) / sizeof(KeyFrame_FuncUserPARM),                   \
        };

/*************************************************************
** Function name:       KeyFrame_FUNC_EXTERN
** Descriptions:        声明按键功能列表
** Input parameters:    name：(KeyFrame_FuncPARM)需符合变量命名规范、
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_FUNC_EXTERN(name)      \
        extern KeyFrame_FuncPARM name;


/*************************************************************
** Function name:       KeyFrame_LINK_AND_FUNC
** Descriptions:        链接按键框架，链路和功能列表
** Input parameters:    frameName：(KeyFramePARM)按键框架参数
**                      linkName：(KeyFrame_LinkPARM)链路参数
**                      funcName：(KeyFrame_FuncPARM)功能列表参数
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
#define KeyFrame_LINK_AND_FUNC(frameName,linkName,funcName)                                             \
        KeyFrame_RegisterFunc(&frameName,&funcName);                                                      \
        KeyFrame_FuncEnableAll(&funcName);                                                               \
        linkName.funcInTable = KeyFrame_SearchFuncInTable(&frameName,&funcName);                          \
        KeyFrame_RegisterLink(&frameName,&linkName)


extern void KeyFrame_Exec(PKeyFramePARM p);
extern void KeyFrame_FuncDisableExcept(PKeyFrame_FuncPARM pFunc,uint8_t exceptIndex);
extern void KeyFrame_FuncDisable(PKeyFrame_FuncPARM pFunc,uint8_t index);
extern void KeyFrame_FuncEnable(PKeyFrame_FuncPARM pFunc,uint8_t index);
extern void KeyFrame_FuncEnableAll(PKeyFrame_FuncPARM pFunc);
extern void KeyFrame_FuncStatusClearAll(PKeyFrame_FuncPARM pFunc);
extern void KeyFrame_FuncStatusClear(PKeyFrame_FuncPARM pFunc,uint8_t index);
extern void KeyFrame_LinkIsEnable(PKeyFrame_LinkPARM pLink,uint8_t isEnable);

/* 内部使用接口 */
extern uint8_t KeyFrame_RegisterLink(PKeyFramePARM p, PKeyFrame_LinkPARM pLink);
extern uint8_t KeyFrame_SearchFuncInTable(PKeyFramePARM p, PKeyFrame_FuncPARM pFunc);
extern uint8_t KeyFrame_RegisterFunc(PKeyFramePARM p, PKeyFrame_FuncPARM pFunc);
#endif /* KeyFrame_H */





