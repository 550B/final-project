#ifndef _GAN_YUAN_BASE_H_
#define _GAN_YUAN_BASE_H_

#include <iostream>
#include "cocos2d.h"

#include "EnemyBase.h"


USING_NS_CC;

class GanYuanBase : public Sprite
{
public:

    GanYuanBase();

    virtual bool init();

    CREATE_FUNC(GanYuanBase);

    // 给重装
    void checkBlock();

    // 给射手
    void checkNearestEnemy();

    // 给医疗
    void checkInjuredGanYuan();

    void sortInjuredGanYuan();

    CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
    CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
    CC_SYNTHESIZE(float, hp, Hp);  // 最大血量
    CC_SYNTHESIZE(float, health, Health);  // 当前血量
    CC_SYNTHESIZE(int, block, Block);  //阻挡数
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //已经阻挡数
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //
    CC_SYNTHESIZE(float, rate, Rate);  //

protected:

    EnemyBase* nearestEnemy;    // 塔子视野内最近的敌人

    Vector<EnemyBase*> blockedEnemy;    // 被阻挡的敌人

    // 受伤的干员
    Vector<GanYuanBase*> injuredGanYuan;

};


#endif /* defined(_GAN_YUAN_BASE_H_) */