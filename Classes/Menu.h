#pragma once
#ifndef _MENU_H__
#define __MENU_H__

#include "cocos2d.h"
#include "Const.h"
#include"editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;

class Menusys : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void MenuMusicCallBack(Ref* pSender);

    void NormalMap(Ref* pSender);

    void HardMap(Ref* pSender);

    void OperatorFormation(Ref* pSender);

    void onButtonEffect();

    // implement the "static create()" method manually
    CREATE_FUNC(Menusys);
};

#endif // _MENU_H__
