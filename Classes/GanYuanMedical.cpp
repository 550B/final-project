#include "GanYuanMedical.h"
#include "GameManager.h"

bool GanYuanMedical::init()
{
    if (!GanYuanMedical::init())
    {
        return false;
    }

    // �趨��ֵ
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
        // ��ת���߼�
        // ��ʱ�Ȳ�Ҫ
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
    auto temp = injuredGanYuan.at(0);  //Ѫ����͵ĸ�Ա
    injuredGanYuan.clear();

    if (!injuredGanYuan.empty())
    {
        // ��δ����Ƿ������Ƶ���
        auto currBullet = MedicalBullet();
        instance->bulletVector.pushBack(currBullet);

        auto moveDuration = getRate();

        // ����ĳɸ�Աλ��
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
        // ����ע�Ͷ�����

        // ����ͬʱִ�ж�������
        /*
        //����һ���ƶ�����
        MoveBy * moveby = MoveBy::create(2.2f, Point(40, 20));
        //����һ�������Ķ���
        JumpBy * jumpby = JumpBy::create(3.0f, Point(50,1),100,1);
        //����һ����ת����
        RotateBy * rotateby = RotateBy::create(2.5f, 220, 10);
        ///������϶����������������

        //˳��ִ��

        Action * action = Sequence::create(moveby, jumpby, rotateby, NULL);

        //һ��ִ��

        Action * action = Spawn::create(moveby, jumpby, rotateby, NULL);
        sp->runAction(action);
        */


        // Ⱥ�̵�һ��˼·��
        // ���Ƶ�ʱ�򣬸�ÿ������߼Ӹ���Ч
        
        // ��Ѫ
        // �������дѪ���ж�
        // �������ĳ����ֵ������
        /*temp1->setHealth(temp1->getHealth() + this->getLethality() >= temp1->getHp() ? temp1->getHp() : temp1->getHealth() + this->getLethality());
        injuredGanYuan.popBack();*/
        // 1����Ч���ϣ�������
        // �ο�EnemyBase�Ӷ���
        // implement here!
        ///////////////////////////

        // ����
        //if (injuredGanYuan.size() - 1 >= 0) {
        //    auto temp2 = injuredGanYuan.at(injuredGanYuan.size() - 1);  //Ѫ���ε͵ĸ�Ա
        //    // ��Ѫ
        //    temp2->setHealth(temp2->getHealth() + this->getLethality() >= temp2->getHp() ? temp2->getHp() : temp2->getHealth() + this->getLethality());
        //    injuredGanYuan.popBack();
        //    // 2����Ч����
        //    // �ο�EnemyBase�Ӷ���
        //    // implement here!
        //    ///////////////////////////
        //}

        //// ����2
        //if (injuredGanYuan.size() - 1 >= 0) {
        //    auto temp3 = injuredGanYuan.at(injuredGanYuan.size() - 1);  //Ѫ�������͵ĸ�Ա
        //    // ��Ѫ
        //    temp3->setHealth(temp3->getHealth() + this->getLethality() >= temp3->getHp() ? temp3->getHp() : temp3->getHealth() + this->getLethality());
        //    injuredGanYuan.popBack();
        //    // 3����Ч����
        //    // �ο�EnemyBase�Ӷ���
        //    // implement here!
        //    ///////////////////////////
        //}

        /*
        // һ��ִ��
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

