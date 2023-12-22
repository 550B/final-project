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

    // �����е�λ
    // ���������Ա
    void checkNearestGanYuan();


    // ÿdelta֡����
    virtual void update(float delta);

    // �������о�һ�£�ʵ�ڲ���ɾ��
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);

    // ת��dt����û��
    //virtual void changeDirection(float dt) {};

    // ������
    virtual void enemyExpload() {};

    // ѭ���ж�С�ɻ�����
    virtual void flyAndShoot(float dt) {};

    virtual void shoot() {};

    virtual void removeBullet(Node* pSender) {};

    // ��������ж��赲
    virtual void attack(float dt) {};

    // ���ص�ǰ��
    Node* currPoint();

    // ������һ��
    Node* nextPoint();

    // ������һ�㣬���������Լ�A*Ѱ·�㷨
    void runFollowPoint();

    // ���Ѫ��
    Sprite* getHpBarBg();

    // ��������
    void setPointsVector(Vector<Node*> points);

    // ����������Ѫ��
    void createAndSetHpBar();

private:

    // ����㼯
    Vector<Node*> pointsVector;

protected:

    // �����ָ��
    int pointCounter;

    // ���Ҷ���
    Animation* animationRight;

    // ���󶯻�
    Animation* animationLeft;

    // ���˶���
    Animation* animationExplode;

    // ������Щ���ǿ�������{get();set();}��
    // ˵�˻����Ƕ���ɶ���д������,
    // �мǣ�
    // ����CC_SYNTHESIZEֵʱ��ֻ����set����������ֱ��=��ֵ��
    // ����CC_SYNTHESIZEֵʱ��ֻ����set����������ֱ��=��ֵ��
    // ����CC_SYNTHESIZEֵʱ��ֻ����set����������ֱ��=��ֵ��
    // ����
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);

    // Ѫ��
    CC_SYNTHESIZE(float, maxHp, MaxHp);

    // ���赲
    CC_SYNTHESIZE(bool, beBlocked, BeBlocked);

    // �жϿ��е���
    CC_SYNTHESIZE(bool, isGround, IsGround);

    // ���˻�������Χ
    CC_SYNTHESIZE(int, scope, Scope);

    // һ��ֵ
    CC_SYNTHESIZE(float, value, Value);

    // �ܶ�ֵ...

    // ������
    CC_SYNTHESIZE(float, atk, Atk);

    // ������
    CC_SYNTHESIZE(float, defense, Defense);

    // ��ǰѪ
    CC_SYNTHESIZE(float, currHp, CurrHp);

    // Ѫ�ٷֱ�
    CC_SYNTHESIZE(float, hpPercentage, HpPercentage);

    // ֻ���Ľ��������͵�Ѫ��
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);

    // �����߽�����
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);

    Sprite* sprite;

    Sprite* hpBgSprite;

    // ����ĸ�Ա
    GanYuanBase* nearestGanYuan;

    // �赲�ĸ�Ա
    GanYuanBase* blockGanYuan;

};



#endif /* defined(_ENEMY_BASE_H_) *///;