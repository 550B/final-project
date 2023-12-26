#pragma once

#ifndef _NORMALMAP1SCENE_H__
#define __NORMALMAP1SCENE_H__

#include "cocos2d.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GameManager.h"
#include "GameLayer.h"
#include <vector>

//class NormalMap1 : public cocos2d::Layer
class NormalMap1 : public GameLayer
{
public:
    //创建场景
    static cocos2d::Scene* createScene();

    //创建瓦片地图
    static cocos2d::TMXTiledMap* createMap();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(NormalMap1);

    TMXObjectGroup* road;
    TMXObjectGroup* towers;
    TMXObjectGroup* grounds;
    std::vector<Vec2> road_path;
    std::vector<Vec2> towers_path;
    std::vector<Vec2> grounds_path;

};

#endif // _NORMALMAP1SCENE_H__
