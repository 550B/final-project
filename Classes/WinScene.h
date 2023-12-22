#pragma once
#ifndef _WIN_SCENE_H_
#define _WIN_SCENE_H_

#include "cocos2d.h"

class WinScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //跳转普通关卡
    void NormalMap(Ref* pSender);

    //跳转剿灭作战
    void HardMap(Ref* pSender);

    //跳转干员编队
    void OperatorFormation(Ref* pSender);

    //按键声音
    void onButtonEffect();

    // implement the "static create()" method manually
    CREATE_FUNC(WinScene);
};

#endif // _WIN_SCENE_H_
