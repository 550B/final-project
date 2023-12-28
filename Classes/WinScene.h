#pragma once
#ifndef __Win__H__
#define __Win__H__
#include "cocos2d.h"
#include "Menu.h"
USING_NS_CC;
class Win: public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene(RenderTexture* sqr);
    CREATE_FUNC(Win);

    //回主界面
    void menuLogin(Ref* pSender);

private:

};

#endif // __Win_H__