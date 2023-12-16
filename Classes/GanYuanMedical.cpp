#include "GanYuanMedical.h"
#include "GameManager.h"

bool GanYuanMedical::init()
{
    if (!GanYuanMedical::init())
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

    ganyuanMedical = Sprite::createWithSpriteFrameName("arrow.png");
    ganyuanMedical->setPosition(0, baseplate->getContentSize().height / 4);
    addChild(ganyuanMedical);

    schedule(CC_SCHEDULE_SELECTOR(GanYuanMedical::rotateAndShoot), 0.8f);
    return true;
}


Sprite* GanYuanMedical::MedicalBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    bullet->setPosition(ganyuanMedical->getPosition());
    bullet->setRotation(ganyuanMedical->getRotation());
    addChild(bullet);

    return bullet;
}

void GanYuanMedical::rotateAndShoot(float dt)
{
    checkInjuredGanYuan();

    if (!injuredGanYuan.empty())
    {
        // 旋转的逻辑
        // 暂时先不要
        /*auto rotateVector = nearestEnemy->sprite->getPosition() - this->getPosition();
        auto rotateRadians = rotateVector.getAngle();
        auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);

        auto speed = 0.5 / M_PI;
        auto rotateDuration = fabs(rotateRadians * speed);
        */

        ganyuanMedical->runAction(Sequence::create(
            CallFunc::create(CC_CALLBACK_0(GanYuanMedical::shoot, this)),
            NULL));
    }
}

void GanYuanMedical::shoot()
{
    GameManager* instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;

    sortInjuredGanYuan();
    auto temp = injuredGanYuan.at(0);  //血量最低的干员
    injuredGanYuan.clear();

    if (!injuredGanYuan.empty())
    {
        // 这段代码是发射治疗弹的
        auto currBullet = MedicalBullet();
        instance->bulletVector.pushBack(currBullet);

        auto moveDuration = getRate();

        // 这里改成干员位置
        Point shootVector = temp->getPosition() - this->getPosition();

        shootVector.normalize();
        Point normalizedShootVector = -shootVector;

        auto farthestDistance = Director::getInstance()->getWinSize().width;
        Point overshotVector = normalizedShootVector * farthestDistance;
        Point offscreenPoint = (ganyuanMedical->getPosition() - overshotVector);

        currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
            CallFuncN::create(CC_CALLBACK_1(GanYuanMedical::removeBullet, this)),
            NULL));
        currBullet = NULL;


        ////////////////////////////////
        // 下面注释都废了

        // 创建同时执行动作范例
        /*
        //创建一个移动动作
        MoveBy * moveby = MoveBy::create(2.2f, Point(40, 20));
        //创建一个弹跳的动作
        JumpBy * jumpby = JumpBy::create(3.0f, Point(50,1),100,1);
        //创建一个旋转动作
        RotateBy * rotateby = RotateBy::create(2.5f, 220, 10);
        ///创建组合动作将动作组合起来

        //顺序执行

        Action * action = Sequence::create(moveby, jumpby, rotateby, NULL);

        //一起执行

        Action * action = Spawn::create(moveby, jumpby, rotateby, NULL);
        sp->runAction(action);
        */


        // 群奶的一种思路是
        // 治疗的时候，给每个人身边加个特效
        
        // 加血
        // 这里可以写血量判断
        // 比如低于某个阈值才治疗
        /*temp1->setHealth(temp1->getHealth() + this->getLethality() >= temp1->getHp() ? temp1->getHp() : temp1->getHealth() + this->getLethality());
        injuredGanYuan.popBack();*/
        // 1的特效跟上（创建）
        // 参考EnemyBase加动画
        // implement here!
        ///////////////////////////

        // 特判
        //if (injuredGanYuan.size() - 1 >= 0) {
        //    auto temp2 = injuredGanYuan.at(injuredGanYuan.size() - 1);  //血量次低的干员
        //    // 加血
        //    temp2->setHealth(temp2->getHealth() + this->getLethality() >= temp2->getHp() ? temp2->getHp() : temp2->getHealth() + this->getLethality());
        //    injuredGanYuan.popBack();
        //    // 2的特效跟上
        //    // 参考EnemyBase加动画
        //    // implement here!
        //    ///////////////////////////
        //}

        //// 特判2
        //if (injuredGanYuan.size() - 1 >= 0) {
        //    auto temp3 = injuredGanYuan.at(injuredGanYuan.size() - 1);  //血量第三低的干员
        //    // 加血
        //    temp3->setHealth(temp3->getHealth() + this->getLethality() >= temp3->getHp() ? temp3->getHp() : temp3->getHealth() + this->getLethality());
        //    injuredGanYuan.popBack();
        //    // 3的特效跟上
        //    // 参考EnemyBase加动画
        //    // implement here!
        //    ///////////////////////////
        //}

        /*
        // 一起执行
        // 
        Action * action = Spawn::create(moveby, jumpby, rotateby, NULL);
        sp->runAction(action);
        */

    }
}

void GanYuanMedical::removeBullet(Node* pSender)
{
    GameManager* instance = GameManager::getInstance();

    auto bulletVector = instance->bulletVector;

    Sprite* sprite = (Sprite*)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}

