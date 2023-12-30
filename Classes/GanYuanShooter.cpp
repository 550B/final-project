#include "GanYuanShooter.h"
#include "GameManager.h"

USING_NS_CC;
//����
bool GanYuanShooter::init()
{
    if (!Sprite::initWithFile("Pictures/GanYuanShooter.png")) {
        return false;
    }
    //���������һЩ�����������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShooter���������Ժ���Ϊ
    this->setPosition(Vec2(visibleSize.width / 2-200, 75));//����Shield��Ƴ���x���ķ�֮һ����y��
    this->setScale(0.32);
  
    initial();
    return true;

    
}
void GanYuanShooter::initial()
{
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
    firstInteract();//��ʼ����
    //castBigMove();
}
void GanYuanShooter::setDefaultData() {
  
    // �趨��װĬ����ֵ
    setType(SHOOTER_TYPE);
    scope = ShooterScope;
    setPrice(ShieldPrice);
    setLethality(ShooterLethality);   // ɱ����
    setHp(ShooterHp);  // ���Ѫ��
    setHealth(ShooterHp);  // ��ǰѪ��
    setBlock(ShooterBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShooterDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShooterIntervalTime);//�������ʱ��
    setCoolTime(ShooterCoolTime);//������ȴʱ��;
    setFirstPose(Vec2(getPosition()));
    setweapon_Price(ShooterWeapon);

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(false);
}


//���λ�úϷ�
void GanYuanShooter::positionLegal(bool& state, Vec2& p) {
    GameManager* instance = GameManager::getInstance();
    for (int i = 0; i < instance->towersPosition.size(); i++) {
        //(road_path[i - 1] - road_path[i]).getLength()
        if ((this->getPosition()).distance(instance->towersPosition[i]) < 50.f)//ȷ������װ�ɵ���λ��
        {
            state = true;
            p = instance->towersPosition[i];
            return;
        }
    }
    return;
}

//void GanYuanShooter::moveToPosition() {
//    auto listener1 = EventListenerTouchOneByOne::create();
//    listener1->setSwallowTouches(true);
//    //ͨ�� lambda ����ʽ ֱ��ʵ�ִ����¼��Ļص�����
//    listener1->onTouchBegan = [](Touch* touch, Event* event) {
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
//        Size s = target->getContentSize();
//        Rect rect = Rect(0, 0, s.width, s.height);
//
//        if (rect.containsPoint(locationInNode))
//        {
//            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
//            target->setOpacity(180);//�����ʱ������ɫ�䰵��255Ϊ���ֵ��9��Сreturn true;
//            return true;
//        }
//        return false;
//        };
//    listener1->onTouchMoved = [=](Touch* touch, Event* event) {
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        target->setPosition(target->getPosition() + touch->getDelta());
//        //this->curRoadSp = this->getCurRoadSp(touch->getLocation());
//        this->curTowerRect = this->getCurTowerRect(touch->getLocation());
//        };
//    listener1->onTouchEnded = [&](Touch* touch, Event* event) {
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
//        log("sprite onTouchesEnded..");
//        target->setOpacity(255);//�����ɿ�ʱʹ����ָ�ԭ������ɫ
//        if (this->curTowerRect.getMinX()!= 0) {
//            target->setPosition(this->curTowerRect.getMidX(), this->curTowerRect.getMidY());
//        }
//        else {
//            target->setPosition(this->originPos);
//        }
//        this->curTowerRect = Rect(0, 0, 0, 0);
//        };
//    //�������¼��󶨵���������
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
//}


Rect GanYuanShooter::getCurTowerRect(Point touchP) {
    Rect rec(0, 0, 0, 0);
    for (Rect rect : this->towerRectVec) {
        if (rect.containsPoint(touchP)) {
            rec = rect;
            break;
        }
    }
    return rec;
}

void GanYuanShooter::castBigMove() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* sprite = Sprite::create();
    this->addChild(sprite);
    sprite->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));

    std::string frameNamePrefix = "Pictures/ShooterBigMove/";
    int numFrames = 9;

    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= numFrames; i++) {
        std::string frameFileName = frameNamePrefix + std::to_string(i) + ".png";
        Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(frameFileName);
        if (texture) {
            Size frameSize = texture->getContentSize();
            Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
            SpriteFrame* frame = SpriteFrame::createWithTexture(texture, frameRect);
            frames.pushBack(frame);
        }
    }
    int opacity = this->getOpacity();
    if (!frames.empty()) {
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
        Animate* animate = Animate::create(animation);
        RepeatForever* repeat = RepeatForever::create(animate);
        this->setOpacity(0);
        sprite->runAction(repeat);
    }

    DelayTime* delay = DelayTime::create(3.0f);
    CallFunc* stopAnimation = CallFunc::create([=]() {
        sprite->stopAllActions();
        sprite->removeFromParent();
        this->setOpacity(opacity);
        });

    Sequence* sequence = Sequence::create(delay, stopAnimation, nullptr);
    this->runAction(sequence);
}
void GanYuanShooter::weaponCallback(Ref* sender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    GameManager* instance = GameManager::getInstance();
    if (instance->getMoney() > weapon_price) {
        instance->setMoney(instance->getMoney() - weapon_price);
        castBigMove();
    }
    else {
        Label* label = Label::createWithTTF("MONEY NOT ENOUGH!", "fonts/arial.ttf", 200);
        label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        label->setColor(Color3B::RED);
        this->addChild(label);

        DelayTime* delay = DelayTime::create(1.0f);
        CallFunc* removeLabel = CallFunc::create([label]() {
            label->removeFromParent();
            });
        label->runAction(Sequence::create(delay, removeLabel, nullptr));
    }
}
