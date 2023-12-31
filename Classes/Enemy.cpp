#include "Enemy.h"
#include "GameManager.h"

USING_NS_CC;

// air
bool Enemy1::init()
{
    if (!EnemyBase::init("Pictures/enemy_air.png"))
    {
        return false;
    }
    initial();
    return true;
}

Enemy1* Enemy1::create()
{
    Enemy1* e1 = new Enemy1();
    if (e1 && e1->init())
    {
        e1->autorelease();
        return e1;
    }
    CC_SAFE_DELETE(e1);
    return nullptr;
}

void Enemy1::setDefaultData() {
    setType(ENEMY1_TYPE);
    scope = Enemy1Scope;
    setLethality(Enemy1Lethality);   // ɱ����
    setHp(Enemy1Hp);  // ���Ѫ��
    setHealth(Enemy1Hp);  // ��ǰѪ��
    setDefence(Enemy1Defence);  // ������
    setRunSpeed(Enemy1RunSpeed);
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsGround(true);

}
void Enemy1::initial()
{
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}

// ����1
bool Enemy2::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground1.png"))
    {
        return false;
    }
    initial();
    return true;
}

Enemy2* Enemy2::create()
{
    Enemy2* e2 = new Enemy2();
    if (e2 && e2->init())
    {
        e2->autorelease();
        return e2;
    }
    CC_SAFE_DELETE(e2);
    return nullptr;
}

void Enemy2::setDefaultData() {
    setType(ENEMY2_TYPE);

    scope = (Enemy2Scope);
    setLethality(Enemy2Lethality);   // ɱ����
    setHp(Enemy2Hp);  // ���Ѫ��
    setHealth(Enemy2Hp);  // ��ǰѪ��
    setDefence(Enemy2Defence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(Enemy2IntervalTime);//�������ʱ��
    setRunSpeed(Enemy2RunSpeed);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

}
void Enemy2::initial()
{
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}

// ����2
bool Enemy3::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground2.png"))
    {
        return false;
    }
    initial();
    return true;
}

Enemy3* Enemy3::create()
{
    Enemy3* e3 = new Enemy3();
    if (e3 && e3->init())
    {
        e3->autorelease();
        return e3;
    }
    CC_SAFE_DELETE(e3);
    return nullptr;
}

void Enemy3::setDefaultData() {
    setType(ENEMY3_TYPE);
    scope = Enemy3Scope;
    setLethality(Enemy3Lethality);   // ɱ����
    setHp(Enemy3Hp);  // ���Ѫ��
    setHealth(Enemy3Hp);  // ��ǰѪ��
    setDefence(Enemy3Defence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(Enemy3IntervalTime);//�������ʱ��
    setRunSpeed(Enemy3RunSpeed);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);
}

void Enemy3::initial()
{
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}
