#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>
#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

// 这里类名起敌人名字
// 飞行类
class Enemy1 : public EnemyBase
{
public:

    virtual bool init() override;

    static Enemy1* createEnemy1(Vector<Node*> points, int hp);

    void changeDirection(float dt);

    void enemyExpload();

};

// 第二种敌人
// 地面类
class Enemy2 : public EnemyBase
{
public:

    virtual bool init() override;

    static Enemy2* createEnemy2(Vector<Node*> points, int hp);

    void changeDirection(float dt);

    void enemyExpload();

    // 地面敌人判断阻挡

};

// 第三种敌人
// 地面类
class Enemy3 : public EnemyBase
{
public:

    virtual bool init() override;

    static Enemy3* createEnemy3(Vector<Node*> points, int hp);

    void changeDirection(float dt);

    void enemyExpload();

};


#endif /* defined(_ENEMY_H_) */