#pragma once
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
//#include "GanYuanBase.h"
#include "Const.h"//xjy
#include "Bar.h"
#include "Actor.h" //zmz
#include "Bullet.h"//zmz

USING_NS_CC;

class EnemyBase : public Actor
{
public:

	EnemyBase();

    virtual bool init(const std::string& filename);

    static EnemyBase* create(const std::string& filename);

    // 是否进屋
    CC_SYNTHESIZE(bool, entered, Entered);

    // 起点
    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);

    // 终点
    CC_SYNTHESIZE(Vec2, lastPose, LastPose);

    // 移速
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);




    // 给空中单位
    // 查找最近干员
    virtual Actor* checkNearestGanYuan();

    // 判断阻挡
    virtual bool lookAround();

    // 跑到下一点
    virtual void runToFollowPoint();

};



#endif /* defined(_ENEMY_BASE_H_) *///