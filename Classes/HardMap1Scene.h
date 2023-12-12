#pragma once

#ifndef _HARDMAP1SCENE_H__
#define __HARDMAP1SCENE_H__

#include "cocos2d.h"


class HardMap1 : public cocos2d::Layer
{
public:
    //��������
    static cocos2d::Scene* createScene();

    //������Ƭ��ͼ
    static cocos2d::TMXTiledMap* createMap();

    virtual bool init();



    // implement the "static create()" method manually
    CREATE_FUNC(HardMap1);
};

#endif // _HARDMAP1SCENE_H__
