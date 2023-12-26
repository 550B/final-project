#pragma once
#ifndef _NORMALMAPCHOOSE_H_
#define _NORMALMAPCHOOSE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;
#include <string.h>
#include "GanYuanShield.h"
#include "GameManager.h"
using namespace cocos2d::ui;
using namespace std;
#include "Menu.h"
#include "NormalMap1Scene.h"
#include "NormalMap2Scene.h"
#include "NormalMap3Scene.h"
class MapChoose : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //������ͼ����
    void ChooseMap(ScrollView* scrollView);

    //ѡ��ؿ�
    void ChooseNmap(ScrollView* scrollView);


    //�������˵�
    void reMenu();

    //��������
    void  MenuMusicCallBack(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MapChoose);

};

#endif //_NORMALMAPCHOOSE_H_