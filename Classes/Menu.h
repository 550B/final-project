#pragma once
#ifndef _MENU_H__
#define __MENU_H__

#include "cocos2d.h"
#include "Const.h"
#include"editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;

//Emode mode;//模式
//Scene* gameScene;//当前场景（hard/normal地图）
//bool gameStart = false;//是否游戏已经开始运行,如果已经运行则干员选择是不能继续的，初始想法是设计按钮可决定开始

class Menusys : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //开关音乐
    void MenuMusicCallBack(Ref* pSender);

    //跳转普通关卡
    void NormalMap(Ref* pSender);

    //跳转剿灭作战
    void HardMap(Ref* pSender);

    //跳转干员编队
    void OperatorFormation(Ref* pSender);

    //按键声音
    void onButtonEffect();

    // implement the "static create()" method manually
    CREATE_FUNC(Menusys);

};

#endif // _MENU_H__
