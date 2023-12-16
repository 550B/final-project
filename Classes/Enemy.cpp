#include "Enemy.h"

// ����
bool Enemy1::init()
{
    /////////////////////////
    // 1.super init
    if (!Sprite::init())
    {
        return false;
    }

    // ���õ���ֵ
    setRunSpeed(25);
    setValue(10);
    // setValue

    sprite = Sprite::create("orc.c3b");
    this->addChild(sprite);
    sprite->setScale(2.0);
    sprite->setAnchorPoint(Vec2(0, 0));

    // 3D�������޷��󼰣�
    // �����ܲ��ܻ���2D����
    // ����EnemyBase�����createAnimation����
    /*auto animation = Animation3D::create("orc.c3b");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        bool inverse = (std::rand() % 3 == 0);

        int rand2 = std::rand();
        float speed = 1.0f;
        if (rand2 % 3 == 1)
        {
            speed = animate->getSpeed() + CCRANDOM_0_1();
        }
        else if (rand2 % 3 == 2)
        {
            speed = animate->getSpeed() - 0.5 * CCRANDOM_0_1();
        }
        animate->setSpeed(inverse ? -speed : speed);

        sprite->runAction(RepeatForever::create(animate));
    }*/


    createAndSetHpBar();

    // ���ü��Ϊ0��ת����ȣ�
    // ��ȷ���ǲ�����ôд��
    // �����һ�£�
    //schedule(schedule_selector(EnemyBase::changeDirection), 0);
    schedule(CC_SCHEDULE_SELECTOR(EnemyBase::changeDirection), 0);

    return true;

}

Enemy1* Enemy1::createEnemy1(Vector<Node*> points, int hp)
{
    Enemy1* pRet = new Enemy1();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFollowPoint();

        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void Enemy1::changeDirection(float dt)
{
    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height + 15) + sprite->getPosition());
    auto curr = currPoint();
    if (curr == NULL)
    {
        return;
    }
    if (curr->getPositionX() > sprite->getPosition().x)
    {
        // ��һ�����ת���ǲ��������ģ�
        sprite->setRotation(-90);

        // �����ת���ܻ�Ƚ�����
        // �²����ĵ����Ǹ�����͵�
        // �������ǵ������Σ�����ֽƬ��
        // ����������ת���������ǰ�������������
        // ���һ�£�

    }
    else 
    {
        // �������
        sprite->setRotation(90);
    }
}

void Enemy1::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();

    // ���ü��Ϊ0��ת����ȣ�
    // ��ȷ���ǲ�����ôд��
    // �����һ�£�
    //unschedule(schedule_selector(Enemy1::changeDirection));
    unschedule(CC_SCHEDULE_SELECTOR(Enemy1::changeDirection));

    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

// ����
bool Enemy2::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    setRunSpeed(50);
    setValue(20);

    sprite = Sprite::create("orc.c3b");
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setScale(2.0);
    this->addChild(sprite);

    animationRight = createAnimation("enemyRight2", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright2");
    animationLeft = createAnimation("enemyLeft2", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft2");
    animationExplode = createAnimation("explode2", 6, 0.15f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode2");

    createAndSetHpBar();

    schedule(CC_SCHEDULE_SELECTOR(Enemy2::changeDirection), 0);

    return true;
}

Enemy2* Enemy2::createEnemy2(Vector<Node*> points, int hp)
{
    Enemy2* pRet = new Enemy2();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFollowPoint();

        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void Enemy2::changeDirection(float dt)
{
    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height + 15) + sprite->getPosition());
    auto curr = currPoint();
    if (curr == NULL)
    {
        return;
    }
    if (curr->getPositionX() > sprite->getPosition().x)
    {
        sprite->setRotation3D(Vec3(0, -90, 0));
    }
    else {
        sprite->setRotation3D(Vec3(0, 90, 0));
    }
}

void Enemy2::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(CC_SCHEDULE_SELECTOR(Enemy2::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

// ����
bool Enemy3::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    setRunSpeed(70);
    setValue(30);
    sprite = Sprite::create("orc.c3b");
    sprite->setColor(Color3B(255, 255, 0));
    sprite->setAnchorPoint(Vec2(0, 0));
    this->addChild(sprite);
    sprite->setScale(2.0);
    animationRight = createAnimation("enemyRight3", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationRight, "runright3");
    animationLeft = createAnimation("enemyLeft3", 4, 0.1f);
    AnimationCache::getInstance()->addAnimation(animationLeft, "runleft3");
    animationExplode = createAnimation("explode3", 6, 0.15f);
    AnimationCache::getInstance()->addAnimation(animationExplode, "explode3");

    createAndSetHpBar();
    schedule(CC_SCHEDULE_SELECTOR(Enemy3::changeDirection), 0);
    return true;
}

Enemy3* Enemy3::createEnemy3(Vector<Node*> points, int hp)
{
    Enemy3* pRet = new Enemy3();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
        pRet->setMaxHp(hp);
        pRet->setCurrHp(hp);
        pRet->runFollowPoint();

        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void Enemy3::changeDirection(float dt)
{
    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height + 15) + sprite->getPosition());
    auto curr = currPoint();
    if (curr == NULL)
    {
        return;
    }
    if (curr->getPositionX() > sprite->getPosition().x)
    {
        sprite->setRotation3D(Vec3(0, -90, 0));
    }
    else {
        sprite->setRotation3D(Vec3(0, 90, 0));
    }
}
void Enemy3::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(CC_SCHEDULE_SELECTOR(Enemy3::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

