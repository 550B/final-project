#pragma once
#ifndef _NORMALMAP2SCENE_H__
#define __NORMALMAP2SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
class NormalMap2 : public GameLayer
{
public:
    //创建场景
    static cocos2d::Scene* createScene();

    //创建瓦片地图
    static cocos2d::TMXTiledMap* createMap();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(NormalMap2);

    TMXObjectGroup* aroad = {};
    TMXObjectGroup* broad = {};
    std::vector<Vec2> aroad_path = {};
    std::vector<Vec2> broad_path = {};
};

#endif // _NORMALMAP2SCENE_H__