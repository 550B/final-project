#include "EnemyBase.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
    : sprite(NULL)      // 赋初始值
    , hpBgSprite(NULL)
    , beBlocked(false)
    , isGround(false)
    , scope(0)
    , pointCounter(0)
    , animationRight(NULL)
    , animationLeft(NULL)
    , animationExplode(NULL)
    , pointsVector(NULL)
    , runSpeed(0)
    , atk(0)
    , defense(0)
    , maxHp(0)
    , currHp(0)
    , hpPercentage(100)
    , hpBar(NULL)
    , enemySuccessful(false)
{

}

EnemyBase::~EnemyBase()
{
    hpBgSprite->removeFromParent();
}

bool EnemyBase::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    return true;
}

Sprite* EnemyBase::getHpBarBg()
{
    return hpBgSprite;
}

void EnemyBase::update(float delta)
{
    // 源码这里注释了，
    // 大意是每delta帧更新血条
    // 请精灵同学测试一下
    //hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height )+sprite->getPosition());

}

void EnemyBase::createAndSetHpBar()
{
    // 添加血条边框帧
    hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png");

    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height));

    // 进度条，添加血条帧
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));

    hpBar->setType(ProgressTimer::Type::BAR);

    hpBar->setMidpoint(Point(0, 0.5f));

    hpBar->setBarChangeRate(Point(1, 0));

    hpBar->setPercentage(hpPercentage);

    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2));

    hpBgSprite->addChild(hpBar);

}

// 量力而行
Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> animFrames;

    // 这里以遍历的方式，把动画的每一帧推入栈
    // 使用TexturePacker或Photoshop抠出每一帧
    for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "_%i.png", i);
        std::string str = prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}

// 返回当前坐标
Node* EnemyBase::currPoint()
{
    if (pointsVector.size() > 0) {
        // 按照指针寻址
        return this->pointsVector.at(pointCounter);
    }
    else {
        return NULL;
    }
}

// 返回下一点坐标
Node* EnemyBase::nextPoint()
{
    // 被阻挡，静止
    if (beBlocked)
    {
        return NULL;
    }

    int maxCount = this->pointsVector.size();
    pointCounter++;
    if (pointCounter < maxCount) {
        auto node = this->pointsVector.at(pointCounter);
        return node;
    }
    else {
        setEnemySuccessful(true);
    }

    return NULL;
}

// 跑到下一个点去
void EnemyBase::runFollowPoint()
{
    auto temp = currPoint();
    sprite->setPosition(temp->getPosition());
    auto point = nextPoint();

    if (point != NULL) {
        auto duration = temp->getPosition().getDistance(point->getPosition()) / getRunSpeed();
        sprite->runAction(Sequence::create(MoveTo::create(duration, point->getPosition())
            , CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFollowPoint, this))
            , NULL));
    }
}


void EnemyBase::setPointsVector(Vector<Node*> points)
{
    this->pointsVector = points;
}

void EnemyBase::checkNearestGanYuan()
{
    GameManager* instance = GameManager::getInstance();
    auto ganyuanVector = instance->ganyuanVector;

    auto currMinDistant = this->scope;

    GanYuanBase* ganyuanTemp = NULL;
    for (int i = 0; i < ganyuanVector.size(); i++)
    {
        auto ganyuan = ganyuanVector.at(i);
        double distance = this->getPosition().getDistance(ganyuan->getPosition());

        if (distance < currMinDistant) {
            currMinDistant = distance;
            ganyuanTemp = ganyuan;
        }
    }
    nearestGanYuan = ganyuanTemp;
}

