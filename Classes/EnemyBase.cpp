#include "EnemyBase.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
    // 赋初始值
    : runSpeed(0)
    , entered(false)
    //, firstPose(NULL)
    //, lastPose(NULL)
    //, curPose(NULL)
    //, nextPose(NULL)
    , ptr(0)
    , mov(STILL)
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
    //以下开始初始化血条
    healthBar = Bar::create(EStateType::Health, health);
    //auto position = getPosition();
    auto size = getBoundingBox().size;
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450));
    addChild(healthBar);
    return true;
}

void EnemyBase::checkNearestGanYuan()
{
    GameManager* instance = GameManager::getInstance();
    auto gyv = instance->ganyuanVector;

    auto currMinDistant = this->scope;

    GanYuanBase* ganyuanTemp = nullptr;
    for (int i = 0; i < gyv.size(); i++)
    {
        auto enemy = gyv.at(i);
        double distance = this->getPosition().getDistance(enemy->getPosition());

        if (distance < currMinDistant) {
            currMinDistant = distance;
            ganyuanTemp = enemy;
        }
    }
    attacking = ganyuanTemp;
}

void EnemyBase::enemyController()
{
    if (getAlive())
    {
        checkNearestGanYuan();//判断最近干员
        this->attack(attacking);
        if (health <= 0)
            this->die();
    }
}

void EnemyBase::cleanDie()
{
    GameManager* instance = GameManager::getInstance();

    for (int i = 0; i < instance->bulletVector.size(); i++)
    {
        if (instance->bulletVector.at(i)->getTarget() == this)
        {
            instance->bulletVector.eraseObject(instance->bulletVector.at(i), true);
        }
    }
}

void EnemyBase::die()
{
    GameManager* instance = GameManager::getInstance();

    for (int i = 0; i < instance->occupied.size(); i++)
    {
        if (instance->occupied.at(i).equals(this->getPosition()))
        {
            instance->occupied.erase(instance->occupied.begin() + i);
        }
    }
    this->setAlive(false);

    auto es = instance->enemyVector;
    es.eraseObject(this, true);
    healthBar->setOpacity(0);
    healthBar->background->setOpacity(0);
    this->setOpacity(0);

    cleanDie();
}

// 跑到下一个点去
void EnemyBase::runToFollowPoint()
{
    GameManager* instance = GameManager::getInstance();
    std::vector<Vec2> positions = instance->roadsPosition.at(this->getRoad() - 1);
    auto ocp = instance->occupied;

    if (getMov() == STILL)
    {
        if (ptr < positions.size() - 1)
        {
            for (auto p : ocp)
            {
                if (p.equals(positions.at(ptr + 1)))
                {
                    this->setMov(ATTACKING);
                }
            }
        }

        if (this->getMov() != ATTACKING)
        {
            if (ptr < positions.size() - 1)
            {
                Vector<FiniteTimeAction*> actions;
                float dis = (positions.at(ptr) - positions.at(ptr + 1)).getLength();
                MoveTo* moveTo = MoveTo::create(dis / this->getRunSpeed(), positions.at(ptr + 1));
                actions.pushBack(moveTo);
                Sequence* seqAct = Sequence::create(actions);
                this->runAction(seqAct);
                this->setMov(RUNNING);
            }
        }
    }

    if (getMov() == RUNNING)
    {
        if (this->getPosition().equals(positions.at(ptr + 1)))
        {
            this->setCurPose(positions.at(ptr + 1));
            this->setPtr(++ptr);
            if (!positions.at(ptr).equals(this->getLastPose()))
            {
                this->setNextPose(positions.at(ptr + 1));
            }

            this->setMov(STILL);
        }
    }

    if (this->getMov() == ATTACKING)
    {
        if (this->getType() == ENEMY3_TYPE || this->getType() == ENEMY2_TYPE)
        {
            auto gy = checkBlockedGanYuan(positions.at(ptr + 1));
            if (gy != NULL && gy->getAlive())
            {
                this->setAttacking(gy);
                this->attack(gy);
            }
            else
            {
                this->setMov(STILL);
            }
        }
    }
}

bool EnemyBase::attack(Actor* target)
{
    GameManager* instance = GameManager::getInstance();

    auto nowTime = GetCurrentTime() / 1000.f;

    if (nowTime - getLastAttackTime() <= getIntervalTime())
    {
        return false;
    }
    else
    {
        setLastAttackTime(nowTime);
        std::string tmpPath;

        switch (this->getType())
        {
        case SHIELD_TYPE:
            tmpPath = SHIELD_PATH;
            break;
        case SHOOTER_TYPE:
            tmpPath = SHOOTER_PATH;
            break;
        case MEDICAL_TYPE:
            tmpPath = MEDICAL_PATH;
            break;
        case ENEMY1_TYPE:
            tmpPath = ENEMY1_PATH;
            break;
        case ENEMY2_TYPE:
            tmpPath = ENEMY2_PATH;
            break;
        case ENEMY3_TYPE:
            tmpPath = ENEMY3_PATH;
            break;
        }

        if (this->getLethality() == 0)
        {
            return false;
        }

        auto bullet = Bullet::create(tmpPath, this->getLethality(), 2000, this, target);
        bullet->setPosition(this->getPosition());
        bullet->setScale(0.12);
        instance->gameScene->addChild(bullet);
        instance->bulletVector.pushBack(bullet);

        return true;
    }
    return false;
}

bool EnemyBase::checkIsEntered(EnemyBase* ttt) const
{
    /*if (this->getCurPose().equals(this->getLastPose()) && this->getPosition().distance(this->getLastPose()) < 1.f)
    {
        return true;
    }*/
    GameManager* instance = GameManager::getInstance();

    //for (int i = 0; i < instance->enemyVector.size(); i++)
    //{
    //    if (instance->enemyVector.at(i) != NULL)
    //    {
    //        if (!instance->enemyVector.at(i)->getAlive())
    //        {
    //            return false;
    //        }
    //        if (instance->enemyVector.at(i)->getCurPose().equals(instance->enemyVector.at(i)->getLastPose())
    //            && instance->enemyVector.at(i)->getPosition().distance(instance->enemyVector.at(i)->getLastPose()) < 0.1f)
    //        {
    //            return true;
    //        }
    //    }
    //}

        if (ttt != NULL)
        {
            if (!ttt->getAlive())
            {
                return false;
            }
            if (ttt->getCurPose().equals(ttt->getLastPose())
                && ttt->getPosition().distance(ttt->getLastPose()) < 0.1f)
            {
                return true;
            }
        }


    return false;
}

Actor* EnemyBase::checkBlockedGanYuan(Vec2 bp)
{
    GameManager* instance = GameManager::getInstance();
    auto ganyuanVector = instance->ganyuanVector;

    for (auto gy : ganyuanVector)
    {
        if (gy->getType() == SHIELD_TYPE) {
            if (gy->getPosition().equals(bp))
            {
                return gy;
            }
        }
    }
    return NULL;
}
