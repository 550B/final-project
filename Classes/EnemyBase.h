#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include <iostream>
#include "cocos2d.h"

#include "GanYuanBase.h"

USING_NS_CC;

class EnemyBase : public Sprite
{
public:

    EnemyBase();

    ~EnemyBase();

    virtual bool init() override;

    CREATE_FUNC(EnemyBase);

    // 给空中单位
    // 查找最近干员
    void checkNearestGanYuan();

    // 打
    void attack(float dt);


    // 每delta帧更新
    virtual void update(float delta);

    // 动画，研究一下，实在不行删掉
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);

    // 转身，dt好像没用
    virtual void changeDirection(float dt) {};

    // 敌人死
    virtual void enemyExpload() {};

    // 返回当前点
    Node* currPoint();

    // 返回下一点
    Node* nextPoint();

    // 计算下一点，这里后面可以加A*寻路算法
    void runFollowPoint();

    // 获得血条
    Sprite* getHpBarBg();

    // 设置坐标
    void setPointsVector(Vector<Node*> points);

    // 创建并设置血条
    void createAndSetHpBar();

private:

    // 坐标点集
    Vector<Node*> pointsVector;

protected:

    // 坐标点指针
    int pointCounter;

    // 向右动画
    Animation* animationRight;

    // 向左动画
    Animation* animationLeft;

    // 寄了动画
    Animation* animationExplode;

    // 下面这些都是快速设置{get();set();}，
    // 说人话就是定义可读可写的属性,
    // 切记！
    // 设置CC_SYNTHESIZE值时，只能用set方法，不能直接=赋值！
    // 设置CC_SYNTHESIZE值时，只能用set方法，不能直接=赋值！
    // 设置CC_SYNTHESIZE值时，只能用set方法，不能直接=赋值！
    // 移速
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);

    // 血量
    CC_SYNTHESIZE(float, maxHp, MaxHp);

    // 被阻挡
    CC_SYNTHESIZE(bool, beBlocked, BeBlocked);

    // 判断空中地上
    CC_SYNTHESIZE(bool, isFly, IsFly);

    // 无人机攻击范围
    CC_SYNTHESIZE(int, scope, Scope);

    // 一个值
    CC_SYNTHESIZE(float, value, Value);

    // 很多值...

    // 防御力
    CC_SYNTHESIZE(float, defense, Defense);

    // 当前血
    CC_SYNTHESIZE(float, currHp, CurrHp);

    // 血百分比
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);

    // 只读的进度条类型的血条
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);

    // 敌人生成成功？
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);

    Sprite* sprite;

    Sprite* hpBgSprite;

    // 最近的干员
    GanYuanBase* nearestGanYuan;

};



#endif /* defined(_ENEMY_BASE_H_) *///;