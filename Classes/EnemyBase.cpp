#include "EnemyBase.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
    : sprite(NULL)      // ����ʼֵ
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
    // Դ������ע���ˣ�
    // ������ÿdelta֡����Ѫ��
    // �뾫��ͬѧ����һ��
    //hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height )+sprite->getPosition());

}

void EnemyBase::createAndSetHpBar()
{
    // ���Ѫ���߿�֡
    hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png");

    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height));

    // �����������Ѫ��֡
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));

    hpBar->setType(ProgressTimer::Type::BAR);

    hpBar->setMidpoint(Point(0, 0.5f));

    hpBar->setBarChangeRate(Point(1, 0));

    hpBar->setPercentage(hpPercentage);

    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2));

    hpBgSprite->addChild(hpBar);

}

// ��������
Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> animFrames;

    // �����Ա����ķ�ʽ���Ѷ�����ÿһ֡����ջ
    // ʹ��TexturePacker��Photoshop�ٳ�ÿһ֡
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

// ���ص�ǰ����
Node* EnemyBase::currPoint()
{
    if (pointsVector.size() > 0) {
        // ����ָ��Ѱַ
        return this->pointsVector.at(pointCounter);
    }
    else {
        return NULL;
    }
}

// ������һ������
Node* EnemyBase::nextPoint()
{
    // ���赲����ֹ
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

// �ܵ���һ����ȥ
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

