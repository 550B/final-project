#pragma once
#ifndef __Gamepause__H__
#define __Gamepause__H__
#include "cocos2d.h"
#include "Menu.h"
USING_NS_CC;
class Gamepause : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene(RenderTexture* sqr);
    CREATE_FUNC(Gamepause);
    //继续游戏
    void menuContinueCallback(Ref* pSender);

    //回主界面
    void menuLogin(Ref* pSender);

private:

};

#endif // __Gamepause_H__