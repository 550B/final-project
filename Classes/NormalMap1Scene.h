#pragma once

#ifndef _NORMALMAP1SCENE_H__
#define __NORMALMAP1SCENE_H__

#include "cocos2d.h"
#include "GanYuanShooter.h"
//#include"GanYuanMedical.h"

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
    GanYuanShooter* ganyuanShooter;
    TMXLayer* mapLayer;
    TMXTiledMap* map;
    void initGanyuanRoadSp();
};

#endif // _NORMALMAP1SCENE_H__
