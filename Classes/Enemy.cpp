#include "Enemy.h"
#include "GameManager.h"

USING_NS_CC;

// 空中
bool Enemy1::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 初始化GanYuanShield的其他属性和行为
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    this->setPosition(Vec2(visibleSize.width / 2, 75));//对于Shield设计成在x的四分之一处，y的
    this->setScale(0.3);
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
    // 设定重装默认数值
    setType(ENEMY1_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // 杀伤力
    setHp(ShieldHp);  // 最大血量
    setHealth(ShieldHp);  // 当前血量
    setBlock(ShieldBlock);  //阻挡数
    setCurBlock(0);  //已经阻挡数*/
    setDefence(ShieldDefence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间
    //setCoolTime(ShieldCoolTime);//死亡冷却时间;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //以下开始初始化血条
    auto lethalityBar = Bar::create(EStateType::Lethality, lethality);
    auto healthBar = Bar::create(EStateType::Health, Health);
    auto defenceBar = Bar::create(EStateType::Defence, defence);
    //auto position = getPosition();
    auto size = getBoundingBox().size;
    lethalityBar->setScaleX(0.5);
    lethalityBar->setScaleY(0.7);
    lethalityBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lethalityBar->setPosition(Vec2(200, 450 + 70));
    addChild(lethalityBar);
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450 + 35));
    addChild(healthBar);
    defenceBar->setScaleX(0.5);
    defenceBar->setScaleY(0.7);
    defenceBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    defenceBar->setPosition(Vec2(200, 450));
    addChild(defenceBar);

}
void Enemy1::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}

// 地面1
bool Enemy2::init()
{
    if (!EnemyBase::init("Pictures/enemy_air.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 初始化GanYuanShield的其他属性和行为
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    //this->setPosition(Vec2(visibleSize.width / 2, 75));//对于Shield设计成在x的四分之一处，y的
    this->setScale(0.3);
    //initial();
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
    // 设定重装默认数值
    setType(ENEMY2_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // 杀伤力
    setHp(ShieldHp);  // 最大血量
    setHealth(ShieldHp);  // 当前血量
    setBlock(ShieldBlock);  //阻挡数
    setCurBlock(0);  //已经阻挡数*/
    setDefence(ShieldDefence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间
    //setCoolTime(ShieldCoolTime);//死亡冷却时间;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //以下开始初始化血条
    auto lethalityBar = Bar::create(EStateType::Lethality, lethality);
    auto healthBar = Bar::create(EStateType::Health, Health);
    auto defenceBar = Bar::create(EStateType::Defence, defence);
    //auto position = getPosition();
    auto size = getBoundingBox().size;
    lethalityBar->setScaleX(0.5);
    lethalityBar->setScaleY(0.7);
    lethalityBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lethalityBar->setPosition(Vec2(200, 450 + 70));
    addChild(lethalityBar);
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450 + 35));
    addChild(healthBar);
    defenceBar->setScaleX(0.5);
    defenceBar->setScaleY(0.7);
    defenceBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    defenceBar->setPosition(Vec2(200, 450));
    addChild(defenceBar);

}
void Enemy2::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}

// 地面2
bool Enemy3::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 初始化GanYuanShield的其他属性和行为
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    //this->setPosition(Vec2(visibleSize.width / 2, 75));//对于Shield设计成在x的四分之一处，y的
    this->setScale(0.3);
    //initial();
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
    // 设定重装默认数值
    setType(ENEMY3_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // 杀伤力
    setHp(ShieldHp);  // 最大血量
    setHealth(ShieldHp);  // 当前血量
    setBlock(ShieldBlock);  //阻挡数
    setCurBlock(0);  //已经阻挡数*/
    setDefence(ShieldDefence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间
    //setCoolTime(ShieldCoolTime);//死亡冷却时间;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //以下开始初始化血条
    auto lethalityBar = Bar::create(EStateType::Lethality, lethality);
    auto healthBar = Bar::create(EStateType::Health, Health);
    auto defenceBar = Bar::create(EStateType::Defence, defence);
    //auto position = getPosition();
    auto size = getBoundingBox().size;
    lethalityBar->setScaleX(0.5);
    lethalityBar->setScaleY(0.7);
    lethalityBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lethalityBar->setPosition(Vec2(200, 450 + 70));
    addChild(lethalityBar);
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450 + 35));
    addChild(healthBar);
    defenceBar->setScaleX(0.5);
    defenceBar->setScaleY(0.7);
    defenceBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    defenceBar->setPosition(Vec2(200, 450));
    addChild(defenceBar);

}
void Enemy3::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
}
