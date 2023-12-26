#include "GanYuanShield.h"
#include "GameManager.h"

USING_NS_CC;
//创建一个重装
bool GanYuanShield::init()
{
    if (!GanYuanBase::init("Pictures/snake.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 初始化GanYuanShield的其他属性和行为
    this->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));//对于Shield设计成在x的四分之一处，y的
    this->setScale(0.3);
    initial();
    return true;
}


GanYuanShield* GanYuanShield::create()
{
    GanYuanShield* shield = new GanYuanShield();
    if (shield && shield->init())
    {
        shield->autorelease();
        return shield;
    }
    CC_SAFE_DELETE(shield);
    return nullptr;
}

void GanYuanShield::setDefaultData() {
    // 设定重装默认数值
    scope = ShieldScope;
    setLethality(ShieldLethality);   // 杀伤力
    setHp(ShieldHp);  // 最大血量
    setHealth(ShieldHp);  // 当前血量
    setBlock(ShieldBlock);  //阻挡数
    setCurBlock(0);  //已经阻挡数*/
    setDefence(ShieldDefence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间
    setCoolTime(ShieldCoolTime);//死亡冷却时间;
    setFirstPose(Vec2(getPosition()));
<<<<<<< HEAD
=======

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

>>>>>>> refs/remotes/origin/main
    //以下开始初始化血条
    auto lethalityBar = Bar::create(EStateType::Lethality, lethality);
    auto healthBar = Bar::create(EStateType::Health, Health);
    auto defenceBar = Bar::create(EStateType::Defence, defence);
    auto position = getPosition();
    auto size = getBoundingBox().size;
    lethalityBar->setScaleX(0.5);
    lethalityBar->setScaleY(0.7);
    lethalityBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lethalityBar->setPosition(position + Vec2(size.width / 2+80, size.height + 35));
    addChild(lethalityBar);
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(position + Vec2(size.width / 2 + 80, size.height));
    addChild(healthBar);
    defenceBar->setScaleX(0.5);
    defenceBar->setScaleY(0.7);
    defenceBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    defenceBar->setPosition(position + Vec2(size.width / 2 + 80, size.height-35));
    addChild(defenceBar);

}
void GanYuanShield::initial()
{
    //完成屏幕的初始化
    setDefaultData();//设置默认值
    moveToPosition();//干员移动
    castBigMove();
}
//检查位置合法
void GanYuanShield:: positionLegal(bool& state, Vec2& p) {
    GameManager* instance = GameManager::getInstance();
    for (int i = 0; i < instance->groundPosition.at(0).size(); i++) {
        //(road_path[i - 1] - road_path[i]).getLength()
        if ((this->getPosition()).distance(instance->groundPosition.at(0)[i]) < 50.f)//确定是重装可到达位置
        {
            state = true;
            p = instance->groundPosition.at(0)[i];
            return;
        }
    }
<<<<<<< HEAD
    state=true;
=======
    //state=true;//?
    //state = false;
    return;
>>>>>>> refs/remotes/origin/main
}
void GanYuanShield::castBigMove() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* sprite = Sprite::create();
    this->addChild(sprite);
    sprite->setPosition(Vec2(this->getPosition().x-70, this->getPosition().y+160));


    std::string frameNamePrefix = "Pictures/snakeBigMove/";
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
    int opacity= this->getOpacity();
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



void GanYuanShield::bigMove() {
    /*
    if (Director::getInstance()->getDeltaTime() == ShieldIntervalTime && health > 0)
        castBigMove();*/
}//是否达到大招

void GanYuanShield::shoot()
{

}

