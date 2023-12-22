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

    // ����װ
    void checkBlock();

    // ������
    void checkNearestEnemy();

    // ��ҽ��
    void checkInjuredGanYuan();

    void sortInjuredGanYuan();

    // ��Ա��
    virtual void ganyuanDie() {};

    // ���Ѫ��
    Sprite* getHpBarBg();

    // ����������Ѫ��
    void createAndSetHpBar();

    CC_SYNTHESIZE(float, scope, Scope);  // �������߷�Χ
    CC_SYNTHESIZE(float, lethality, Lethality);   // ɱ����
    CC_SYNTHESIZE(float, defense, Defense);   // ������
    CC_SYNTHESIZE(float, hp, Hp);  // ���Ѫ��
    CC_SYNTHESIZE(float, health, Health);  // ��ǰѪ��
    CC_SYNTHESIZE(int, block, Block);  //�赲��
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //�Ѿ��赲��
    CC_SYNTHESIZE(bool, isGround, IsGround);  // �Ƿ����
    CC_SYNTHESIZE(int, towerValue, TowerValue);  //
    CC_SYNTHESIZE(float, rate, Rate);  //

    // Ѫ�ٷֱ�
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);

    // ֻ���Ľ��������͵�Ѫ��
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);

protected:

    Sprite* sprite;

    Sprite* hpBgSprite;

    EnemyBase* nearestEnemy;    // ������Ұ������ĵ���

    Vector<EnemyBase*> blockedEnemy;    // ���赲�ĵ���

    // ���˵ĸ�Ա
    Vector<GanYuanBase*> injuredGanYuan;

};


#endif /* defined(_GAN_YUAN_BASE_H_) */