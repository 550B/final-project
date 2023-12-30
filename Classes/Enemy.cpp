#include "Enemy.h"
#include "GameManager.h"

USING_NS_CC;

// ����
bool Enemy1::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShield���������Ժ���Ϊ
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    this->setPosition(Vec2(visibleSize.width / 2, 75));//����Shield��Ƴ���x���ķ�֮һ����y��
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
    // �趨��װĬ����ֵ
    setType(ENEMY1_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // ɱ����
    setHp(ShieldHp);  // ���Ѫ��
    setHealth(ShieldHp);  // ��ǰѪ��
    setBlock(ShieldBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShieldDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��
    //setCoolTime(ShieldCoolTime);//������ȴʱ��;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //���¿�ʼ��ʼ��Ѫ��
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
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}

// ����1
bool Enemy2::init()
{
    if (!EnemyBase::init("Pictures/enemy_air.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShield���������Ժ���Ϊ
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    //this->setPosition(Vec2(visibleSize.width / 2, 75));//����Shield��Ƴ���x���ķ�֮һ����y��
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
    // �趨��װĬ����ֵ
    setType(ENEMY2_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // ɱ����
    setHp(ShieldHp);  // ���Ѫ��
    setHealth(ShieldHp);  // ��ǰѪ��
    setBlock(ShieldBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShieldDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��
    //setCoolTime(ShieldCoolTime);//������ȴʱ��;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //���¿�ʼ��ʼ��Ѫ��
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
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}

// ����2
bool Enemy3::init()
{
    if (!EnemyBase::init("Pictures/enemy_ground.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShield���������Ժ���Ϊ
    //this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    //this->setPosition(Vec2(visibleSize.width / 2, 75));//����Shield��Ƴ���x���ķ�֮һ����y��
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
    // �趨��װĬ����ֵ
    setType(ENEMY3_TYPE);
    //setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);   // ɱ����
    setHp(ShieldHp);  // ���Ѫ��
    setHealth(ShieldHp);  // ��ǰѪ��
    setBlock(ShieldBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShieldDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��
    //setCoolTime(ShieldCoolTime);//������ȴʱ��;
    //setFirstPose(Vec2(getPosition()));

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

    //���¿�ʼ��ʼ��Ѫ��
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
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
}
