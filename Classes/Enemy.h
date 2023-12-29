#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>
#include "EnemyBase.h"
#include "Const.h"
#include "Bar.h"
#include "cocos2d.h"

USING_NS_CC;

//class EnemyBase;

// 这里类名起敌人名字
// 飞行类
class Enemy1 : public EnemyBase
{
public:

    bool init();

    static Enemy1* create();//创建静态create方法

    virtual void setDefaultData();//设置默认数值

    virtual void initial();//初始化

};

// 第二种敌人
// 地面类
class Enemy2 : public EnemyBase
{
public:

    bool init();

    static Enemy2* create();//创建静态create方法

    virtual void setDefaultData();//设置默认数值

    virtual void initial();//初始化

};

// 第三种敌人
// 地面类
class Enemy3 : public EnemyBase
{
public:

    bool init();

    static Enemy3* create();//创建静态create方法

    virtual void setDefaultData();//设置默认数值

    virtual void initial();//初始化

};


#endif /* defined(_ENEMY_H_) */