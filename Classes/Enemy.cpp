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
    setLethality(Enemy1Lethality);   // 杀伤力
    setHp(Enemy1Hp);  // 最大血量
    setHealth(Enemy1Hp);  // 当前血量
    setDefence(Enemy1Defence);  // 防御力
    setRunSpeed(Enemy1RunSpeed);
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsGround(true);

}
void Enemy1::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}

// 地面1
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
    setLethality(Enemy2Lethality);   // 杀伤力
    setHp(Enemy2Hp);  // 最大血量
    setHealth(Enemy2Hp);  // 当前血量
    setDefence(Enemy2Defence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(Enemy2IntervalTime);//攻击间隔时间
    setRunSpeed(Enemy2RunSpeed);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

}
void Enemy2::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}

// 地面2
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
    setLethality(Enemy3Lethality);   // 杀伤力
    setHp(Enemy3Hp);  // 最大血量
    setHealth(Enemy3Hp);  // 当前血量
    setDefence(Enemy3Defence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(Enemy3IntervalTime);//攻击间隔时间
    setRunSpeed(Enemy3RunSpeed);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);
}

void Enemy3::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}
