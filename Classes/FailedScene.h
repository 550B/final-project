#pragma once
#ifndef __Failed__H__
#define __Failed__H__
#include "cocos2d.h"
#include "Menu.h"
USING_NS_CC;
class Failed : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* scene(RenderTexture* sqr);
    CREATE_FUNC(Failed);

    //回主界面
    void menuLogin(Ref* pSender);

private:

};

#endif // __Failed_H__