#ifndef _WAVE_H_
#define _WAVE_H_

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"

// 敌人种类，这种敌人的数量
struct EnemyType
{
    int type;
    int count;
};

class Wave : public cocos2d::Node
{
public:

    Wave();

    ~Wave();

    virtual bool init();

    CREATE_FUNC(Wave);

    // 按索引设置波次敌人，
    // 第一个参数：添加敌人的种类，
    // 第二个参数：添加的个数
    void addEnemy(int type, int cnt);

    // 获取这波敌人数量
    int getEnemyCount();

    // 加完调用这个推入waveVector
    void finishAdd();

    // 波次索引
    CC_SYNTHESIZE(int, index, Index);

    // 是否添加成功
    CC_SYNTHESIZE(bool, isFinished, IsFinished);

    // 波里的敌人数组
    // 调用示例：waves.push_back({源石虫的代号,1})
    // 解释：在本波的最后一个添加一只源石虫
    Vector<EnemyType> enemies;

};
#endif /* defined(_WAVE_H_) */