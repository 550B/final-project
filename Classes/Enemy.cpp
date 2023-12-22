#include "Enemy.h"
#include "GameManager.h"

// 空中
bool Enemy1::init()
{
    /////////////////////////
    // 1.super init
    if (!Sprite::init())
    {
        return false;
    }

    // 设置敌人值
    setRunSpeed(25);
    setValue(10);
    // setValue

    sprite = Sprite::create("orc.c3b");
    this->addChild(sprite);
    sprite->setScale(2.0);
    sprite->setAnchorPoint(Vec2(0, 0));

    // 3D动画，无法企及，
    // 看看能不能换成2D动画
    // 调用EnemyBase里面的createAnimation方法
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

    // 设置间隔为0的转向调度，
    // 不确定是不是这么写，
    // 请测试一下！
    //schedule(schedule_selector(EnemyBase::changeDirection), 0);
    // 
    // 先不要转了
    //schedule(CC_SCHEDULE_SELECTOR(Enemy1::changeDirection), 0);
    schedule(CC_SCHEDULE_SELECTOR(Enemy1::flyAndShoot), 2.0f);

    return true;

}

Sprite* Enemy1::FlyBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(enemyFly->getPosition());
    bullet->setRotation(enemyFly->getRotation());
    addChild(bullet);

    return bullet;
}

void Enemy1::removeBullet(Node* pSender)
{
    GameManager* instance = GameManager::getInstance();

    auto bulletVector = instance->bulletVector;

    Sprite* sprite = (Sprite*)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

void Enemy1::flyAndShoot(float dt)
{
    checkNearestGanYuan();

    if (nearestGanYuan != NULL)
    {
        enemyFly->runAction(Sequence::create(
            CallFunc::create(CC_CALLBACK_0(Enemy1::shoot, this)),
            NULL));
    }
}

void Enemy1::shoot()
{
    GameManager* instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

    if (nearestGanYuan != NULL && nearestGanYuan->getHealth() > 0)
    {
        // 发射子弹
        auto currBullet = FlyBullet();
        instance->bulletVector.pushBack(currBullet);

        auto moveDuration = nearestGanYuan->getRate();

        Point shootVector = nearestGanYuan->getPosition() - this->getPosition();
        shootVector.normalize();
        Point normalizedShootVector = -shootVector;

        auto farthestDistance = Director::getInstance()->getWinSize().width;
        Point overshotVector = normalizedShootVector * farthestDistance;
        Point offscreenPoint = (enemyFly->getPosition() - overshotVector);

        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
            CallFuncN::create(CC_CALLBACK_1(Enemy1::removeBullet, this)),
            NULL));
        currBullet = NULL;
    }
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
        // 看一下这里，转向是不是这样的？
        sprite->setRotation(-90);

        // 这个旋转可能会比较尴尬
        // 猜测他的敌人是俯瞰类型的
        // 但是咱们的是人形，还是纸片人
        // 按照他这种转法，会出现前倾后仰甚至倒立
        // 请改一下！

    }
    else 
    {
        // 还有这里？
        sprite->setRotation(90);
    }
}

void Enemy1::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();

    // 设置间隔为0的转向调度，
    // 不确定是不是这么写，
    // 请测试一下！
    //unschedule(schedule_selector(Enemy1::changeDirection));
    //unschedule(CC_SCHEDULE_SELECTOR(Enemy1::changeDirection));
    unschedule(CC_SCHEDULE_SELECTOR(Enemy1::flyAndShoot));

    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

// 地面
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

    schedule(CC_SCHEDULE_SELECTOR(Enemy2::changeDirection, Enemy2::attack), 0);

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

void Enemy2::attack(float dt)
{
    if (getBeBlocked())
    {
        if (blockGanYuan == NULL)
        {
            return;
        }

        float blood = blockGanYuan->getHealth();
        float dfs = blockGanYuan->getDefense();
        float atk = this->getAtk();

        if (blood > 0)
        {
            blockGanYuan->setHealth(blood - atk * (1 - dfs) <= 0 ? 0 : blood - atk * (1 - dfs));

            // 攻击动画
            // 在这实现

        }
    }
}

void Enemy2::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(CC_SCHEDULE_SELECTOR(Enemy2::changeDirection, Enemy2::attack));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

// 地面
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

void Enemy3::attack(float dt)
{
    if (getBeBlocked())
    {
        if (blockGanYuan == NULL)
        {
            return;
        }

        float blood = blockGanYuan->getHealth();
        float dfs = blockGanYuan->getDefense();
        float atk = this->getAtk();

        if (blood > 0)
        {
            blockGanYuan->setHealth(blood - atk * (1 - dfs) <= 0 ? 0 : blood - atk * (1 - dfs));

            // 攻击动画
            // 在这实现

        }
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

