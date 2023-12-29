#ifndef _WAVE_H_
#define _WAVE_H_

#include <iostream>
#include "cocos2d.h"
#include "Const.h"
#include "EnemyBase.h"

class Wave : public cocos2d::Node
{
public:

    Wave();

    virtual bool init();

    CREATE_FUNC(Wave);

    // 按索引设置波次敌人，
    // 第一个参数：添加敌人的种类，
    // 第二个参数：添加的个数
    // 第三个参数：走哪条路
    void addEnemy(int type, int road);

    // 获取这波敌人数量
    int getEnemyCount();

    // 加完调用这个推入waveVector
    void finishAdd(Wave* w);

    // 波次索引
    CC_SYNTHESIZE(int, index, Index);

    // 是否添加成功
    CC_SYNTHESIZE(bool, isFinished, IsFinished);

    // 出现时间
    CC_SYNTHESIZE(float, showTime, ShowTime);

    // 波里的敌人数组
    // 调用示例：waves.push_back({源石虫的代号,1})
    // 解释：在本波的最后一个添加一只源石虫
    std::vector<EnemyType> enemies;

};
#endif /* defined(_WAVE_H_) */