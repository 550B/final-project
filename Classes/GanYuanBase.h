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

    ~GanYuanBase();

    virtual bool init();

    CREATE_FUNC(GanYuanBase);

    // 给重装
    void checkBlock();

    // 给射手
    void checkNearestEnemy();

    // 给医疗
    void checkInjuredGanYuan();

    void sortInjuredGanYuan();

    // 干员死
    virtual void ganyuanDie() {};

    // 获得血条
    Sprite* getHpBarBg();

    // 创建并设置血条
    void createAndSetHpBar();

    CC_SYNTHESIZE(float, scope, Scope);  // 塔的视线范围
    CC_SYNTHESIZE(float, lethality, Lethality);   // 杀伤力
    CC_SYNTHESIZE(float, defense, Defense);   // 防御力
    CC_SYNTHESIZE(float, hp, Hp);  // 最大血量
    CC_SYNTHESIZE(float, health, Health);  // 当前血量
    CC_SYNTHESIZE(int, block, Block);  //阻挡数
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //已经阻挡数
    CC_SYNTHESIZE(bool, isGround, IsGround);  // 是否地面
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //
    CC_SYNTHESIZE(float, rate, Rate);  //

    // 血百分比
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);

    // 只读的进度条类型的血条
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);

protected:

    Sprite* sprite;

    Sprite* hpBgSprite;

    EnemyBase* nearestEnemy;    // 塔子视野内最近的敌人

    Vector<EnemyBase*> blockedEnemy;    // 被阻挡的敌人

    // 受伤的干员
    Vector<GanYuanBase*> injuredGanYuan;

};


#endif /* defined(_GAN_YUAN_BASE_H_) */