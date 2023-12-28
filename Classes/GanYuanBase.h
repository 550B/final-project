#ifndef _GAN_YUAN_BASE_H_
#define _GAN_YUAN_BASE_H_

#include <iostream>
#include<string>
#include<time.h>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "Const.h"//xjy
#include "Bar.h"
#include "Actor.h" //zmz
#include "Bullet.h"//zmz
USING_NS_CC;
class GanYuanBase : public Actor
{
public:
    GanYuanBase();
    virtual bool init(const std::string &filename);

    static GanYuanBase* create(const std::string& filename);

    // 赵明泽注释的，理由：放Actor里了
    //CC_SYNTHESIZE(int, scope, Scope);
    //CC_SYNTHESIZE(int, lethality, Lethality);
    //CC_SYNTHESIZE(float, hp, Hp);
    //CC_SYNTHESIZE(float, health, Health);
    //CC_SYNTHESIZE(float, defence, Defence);
    CC_SYNTHESIZE(bool, selected, Selected);
    //CC_SYNTHESIZE(bool, alive, Alive);
    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);
    CC_SYNTHESIZE(Vec2, pose, Pose);
    CC_SYNTHESIZE(int, price, Price);//干员的购买价格
    //CC_SYNTHESIZE(float, intervalTime, IntervalTime);
    CC_SYNTHESIZE(float, coolTime, CoolTime);

    virtual void firstInteract();
    virtual void selectCallback(Ref* sender);
    virtual void unselectCallback(Ref* sender);
    virtual void ifmove();
    virtual void moveToPosition();
    virtual void positionLegal(bool& state, Vec2& p);
    //xjy新增，为了使得选择干员按钮能够在回调函数中被删除
    MenuItemImage*m_selectMenu;
    Menu*m_menuSelect;



};
#endif /* defined(_GAN_YUAN_BASE_H_) */