#pragma once
#ifndef _NORMALMAPCHOOSE_H_
#define _NORMALMAPCHOOSE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include "GanYuanShield.h"
#include "GameManager.h"
using namespace cocos2d::ui;
using namespace std;
class MapChoose : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //滚动地图背景
    void ChooseMap(ScrollView* scrollView);

    //选择关卡
    void ChooseNmap(ScrollView* scrollView);


    //返回主菜单
    void reMenu();

    // implement the "static create()" method manually
    CREATE_FUNC(MapChoose);

};

#endif //_NORMALMAPCHOOSE_H_