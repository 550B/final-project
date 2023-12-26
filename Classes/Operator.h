#pragma once
#ifndef _OPERATOR_H_
#define _OPERATOR_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <string.h>
using namespace cocos2d::ui;
using namespace std;
#include "Menu.h"
class OperatorFormation : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //�������˵�
    void reMenu();

    //��������
    void  MenuMusicCallBack(Ref* pSender);

    //��װ
    void Shield(Ref* pSender);

    //����
    void Shooter(Ref* pSender);

    //ҽ��
    void Medical(Ref* pSender);

    //
    void onButtonEffect();

    //չʾ��ͬ��ɫ
    void Role();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // implement the "static create()" method manually
    CREATE_FUNC(OperatorFormation);

};

#endif //_OPERATOR_H_