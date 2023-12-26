#include "GanYuanShield.h"
#include "GameManager.h"

USING_NS_CC;
//����һ����װ
bool GanYuanShield::init()
{
    if (!GanYuanBase::init("Pictures/snake.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShield���������Ժ���Ϊ
    this->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));//����Shield��Ƴ���x���ķ�֮һ����y��
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
    // �趨��װĬ����ֵ
    scope = ShieldScope;
    setLethality(ShieldLethality);   // ɱ����
    setHp(ShieldHp);  // ���Ѫ��
    setHealth(ShieldHp);  // ��ǰѪ��
    setBlock(ShieldBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShieldDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��
    setCoolTime(ShieldCoolTime);//������ȴʱ��;
    setFirstPose(Vec2(getPosition()));
<<<<<<< HEAD
=======

    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);

>>>>>>> refs/remotes/origin/main
    //���¿�ʼ��ʼ��Ѫ��
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
    //�����Ļ�ĳ�ʼ��
    setDefaultData();//����Ĭ��ֵ
    moveToPosition();//��Ա�ƶ�
    castBigMove();
}
//���λ�úϷ�
void GanYuanShield:: positionLegal(bool& state, Vec2& p) {
    GameManager* instance = GameManager::getInstance();
    for (int i = 0; i < instance->groundPosition.at(0).size(); i++) {
        //(road_path[i - 1] - road_path[i]).getLength()
        if ((this->getPosition()).distance(instance->groundPosition.at(0)[i]) < 50.f)//ȷ������װ�ɵ���λ��
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
}//�Ƿ�ﵽ����

void GanYuanShield::shoot()
{

}

