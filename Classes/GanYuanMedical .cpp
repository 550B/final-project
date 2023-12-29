#include "GanYuanMedical.h"

USING_NS_CC;
//医疗
bool GanYuanMedical::init()
{
    if (!Sprite::initWithFile("Pictures/GanYuanMedical.png")) {
        return false;
    }
    //在这里进行一些精灵类的设置
    auto visibleSize = Director::getInstance()->getVisibleSize();

    this->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));
    this->setScale(0.3);

    initial();
    return true;


}
void GanYuanMedical::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
    firstInteract();//初始交互
    castBigMove();
}

void GanYuanMedical::setDefaultData() {

    /*
    setLethality(MedicalLethality);   // 杀伤力
    setHp(MedicalHp);  // 最大血量
    setHealth(MedicalHp);  // 当前血量*/
}
void GanYuanMedical::firstInteract() {

    if (1) {
        moveToPosition();
    }
}
void GanYuanMedical::moveToPosition() {
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    //通过 lambda 表达式 直接实现触摸事件的回掉方法
    listener1->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);

        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);//点击的时候精灵颜色变暗，255为最大值，9最小return true;
            return true;
        }
        return false;
        };
    listener1->onTouchMoved = [=](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
        //this->curRoadSp = this->getCurRoadSp(touch->getLocation());
        this->curTowerRect = this->getCurTowerRect(touch->getLocation());
        };
    listener1->onTouchEnded = [&](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        log("sprite onTouchesEnded..");
        target->setOpacity(255);//手势松开时使精灵恢复原来的颜色
        if (this->curTowerRect.getMinX() != 0) {
            target->setPosition(this->curTowerRect.getMidX(), this->curTowerRect.getMidY());
        }
        else {
            target->setPosition(this->originPos);
        }
        this->curTowerRect = Rect(0, 0, 0, 0);
        };
    //将触摸事件绑定到精灵身上
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
}


Rect GanYuanMedical::getCurTowerRect(Point touchP) {
    Rect rec(0, 0, 0, 0);
    for (Rect rect : this->towerRectVec) {
        if (rect.containsPoint(touchP)) {
            rec = rect;
            break;
        }
    }
    return rec;
}

void GanYuanMedical::castBigMove() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* sprite = Sprite::create();
    this->addChild(sprite);
    sprite->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));

    std::string frameNamePrefix = "Pictures/MedicalBigMove/";
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

