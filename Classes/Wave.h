#ifndef _WAVE_H_
#define _WAVE_H_

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"

// �������࣬���ֵ��˵�����
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

    // ���������ò��ε��ˣ�
    // ��һ����������ӵ��˵����࣬
    // �ڶ�����������ӵĸ���
    void addEnemy(int type, int cnt);

    // ��ȡ�Ⲩ��������
    int getEnemyCount();

    // ��������������waveVector
    void finishAdd();

    // ��������
    CC_SYNTHESIZE(int, index, Index);

    // �Ƿ���ӳɹ�
    CC_SYNTHESIZE(bool, isFinished, IsFinished);

    // ����ĵ�������
    // ����ʾ����waves.push_back({Դʯ��Ĵ���,1})
    // ���ͣ��ڱ��������һ�����һֻԴʯ��
    Vector<EnemyType> enemies;

};
#endif /* defined(_WAVE_H_) */