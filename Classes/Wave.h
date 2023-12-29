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

    // ���������ò��ε��ˣ�
    // ��һ����������ӵ��˵����࣬
    // �ڶ�����������ӵĸ���
    // ������������������·
    void addEnemy(int type, int road);

    // ��ȡ�Ⲩ��������
    int getEnemyCount();

    // ��������������waveVector
    void finishAdd(Wave* w);

    // ��������
    CC_SYNTHESIZE(int, index, Index);

    // �Ƿ���ӳɹ�
    CC_SYNTHESIZE(bool, isFinished, IsFinished);

    // ����ʱ��
    CC_SYNTHESIZE(float, showTime, ShowTime);

    // ����ĵ�������
    // ����ʾ����waves.push_back({Դʯ��Ĵ���,1})
    // ���ͣ��ڱ��������һ�����һֻԴʯ��
    std::vector<EnemyType> enemies;

};
#endif /* defined(_WAVE_H_) */