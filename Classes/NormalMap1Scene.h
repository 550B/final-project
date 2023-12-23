#pragma once

#ifndef _NORMALMAP1SCENE_H__
#define __NORMALMAP1SCENE_H__

#include "cocos2d.h"
#include "GanYuanShield.h"
#include "GameManager.h"

class NormalMap1 : public cocos2d::Layer
{
public:
    //��������
    static cocos2d::Scene* createScene();

    //������Ƭ��ͼ
    static cocos2d::TMXTiledMap* createMap();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(NormalMap1);

};

#endif // _NORMALMAP1SCENE_H__
