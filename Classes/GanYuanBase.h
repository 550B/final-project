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

    // ����װ
    void checkBlock();

    // ������
    void checkNearestEnemy();

    // ��ҽ��
    void checkInjuredGanYuan();

    void sortInjuredGanYuan();

    CC_SYNTHESIZE(int, scope, Scope);  // �������߷�Χ
    CC_SYNTHESIZE(int, lethality, Lethality);   // ɱ����
    CC_SYNTHESIZE(float, hp, Hp);  // ���Ѫ��
    CC_SYNTHESIZE(float, health, Health);  // ��ǰѪ��
    CC_SYNTHESIZE(int, block, Block);  //�赲��
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //�Ѿ��赲��
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //
    CC_SYNTHESIZE(float, rate, Rate);  //

protected:

    EnemyBase* nearestEnemy;    // ������Ұ������ĵ���

    Vector<EnemyBase*> blockedEnemy;    // ���赲�ĵ���

    // ���˵ĸ�Ա
    Vector<GanYuanBase*> injuredGanYuan;

};


#endif /* defined(_GAN_YUAN_BASE_H_) */