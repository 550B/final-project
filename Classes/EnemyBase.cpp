#include "EnemyBase.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
// 赋初始值
    : runSpeed(0)
    , entered(false)
    , firstPose(NULL)
    , lastPose(NULL)
    , curPose(NULL)
    , nextPose(NULL)
    , blocked(false)//xjy
    , ptr(0)
{

}

EnemyBase* EnemyBase::create(const std::string& filename)
{
    EnemyBase* Base = new(std::nothrow)EnemyBase;
    if (Base && Base->init(filename))
    {
        Base->autorelease();
        return Base;
    }
    CC_SAFE_DELETE(Base);
    return nullptr;
}

bool EnemyBase::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    return true;
}

// 跑到下一个点去
void EnemyBase::runToFollowPoint()
{
    //auto temp = currPoint();
    //sprite->setPosition(temp->getPosition());
    //auto point = nextPoint();

    //if (point != NULL) {
    //    auto duration = temp->getPosition().getDistance(point->getPosition()) / getRunSpeed();
    //    sprite->runAction(Sequence::create(MoveTo::create(duration, point->getPosition())
    //        , CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFollowPoint, this))
    //        , NULL));
    //}
    GameManager* instance = GameManager::getInstance();
    // complicated... tomorrow
}

Actor* EnemyBase::checkNearestGanYuan()
{
    GameManager* instance = GameManager::getInstance();
    auto ganyuanVector = instance->ganyuanVector;

    auto currMinDistant = this->scope;

    Actor* ganyuanTemp = NULL;
    for (int i = 0; i < ganyuanVector.size(); i++)
    {
        auto ganyuan = ganyuanVector.at(i);
        double distance = this->getPosition().getDistance(ganyuan->getPosition());

        if (distance < currMinDistant) {
            currMinDistant = distance;
            ganyuanTemp = ganyuan;
        }
    }
    return ganyuanTemp;
}

bool EnemyBase::lookAround()
{
    return false;
}
