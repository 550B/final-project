#pragma once

#ifndef _NORMALMAP1SCENE_H__
#define __NORMALMAP1SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
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

    TMXObjectGroup* road = {};
    std::vector<Vec2> road_path = {};
};

#endif // _NORMALMAP1SCENE_H__
