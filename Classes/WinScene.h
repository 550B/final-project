#pragma once
#ifndef _WIN_SCENE_H_
#define _WIN_SCENE_H_

#include "cocos2d.h"

class WinScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //��ת��ͨ�ؿ�
    void NormalMap(Ref* pSender);

    //��ת������ս
    void HardMap(Ref* pSender);

    //��ת��Ա���
    void OperatorFormation(Ref* pSender);

    //��������
    void onButtonEffect();

    // implement the "static create()" method manually
    CREATE_FUNC(WinScene);
};

#endif // _WIN_SCENE_H_
