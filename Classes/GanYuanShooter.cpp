#include "GanYuanShooter.h"
#include "GameManager.h"

bool GanYuanShooter::init()
{
    if (!GanYuanShooter::init())
    {
        return false;
    }

    // 设定数值
    setScope(90);
    setLethality(2);
    setTowerValue(250);
    setRate(2);

    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);

    ganyuanShooter = Sprite::createWithSpriteFrameName("arrow.png");
    ganyuanShooter->setPosition(0, baseplate->getContentSize().height / 4);
    addChild(ganyuanShooter);

    schedule(CC_SCHEDULE_SELECTOR(GanYuanShooter::rotateAndShoot), 0.8f);
    return true;
}


Sprite* GanYuanShooter::ShooterBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(ganyuanShooter->getPosition());
    bullet->setRotation(ganyuanShooter->getRotation());
    addChild(bullet);

    return bullet;
}

void GanYuanShooter::rotateAndShoot(float dt)
{
    checkNearestEnemy();

    if (nearestEnemy != NULL)
    {
        ganyuanShooter->runAction(Sequence::create(
            CallFunc::create(CC_CALLBACK_0(GanYuanShooter::shoot, this)),
            NULL));
    }
}

void GanYuanShooter::shoot()
{
    GameManager* instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

    if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
    {
        auto currBullet = ShooterBullet();
        instance->bulletVector.pushBack(currBullet);

        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
        shootVector.normalize();
        Point normalizedShootVector = -shootVector;

        auto farthestDistance = Director::getInstance()->getWinSize().width;
        Point overshotVector = normalizedShootVector * farthestDistance;
        Point offscreenPoint = (ganyuanShooter->getPosition() - overshotVector);

        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
            CallFuncN::create(CC_CALLBACK_1(GanYuanShooter::removeBullet, this)),
            NULL));
        currBullet = NULL;
    }
}

void GanYuanShooter::removeBullet(Node* pSender)
{
    GameManager* instance = GameManager::getInstance();

    auto bulletVector = instance->bulletVector;

    Sprite* sprite = (Sprite*)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

