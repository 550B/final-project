#include "GanYuanShield.h"
#include "GameManager.h"

bool GanYuanShield::init()
{
    if (!GanYuanShield::init())
    {
        return false;
    }

    // 设定数值
    setScope(90);
    setLethality(2);
    setTowerValue(250);
    setRate(2);

    curBlockedEnemy = NULL;

    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
    addChild(baseplate);

    ganyuanShield = Sprite::createWithSpriteFrameName("arrow.png");
    ganyuanShield->setPosition(0, baseplate->getContentSize().height / 4);
    addChild(ganyuanShield);

    schedule(CC_SCHEDULE_SELECTOR(GanYuanShield::attack), 2.0f);
    return true;
}

void GanYuanShield::attack(float dt)
{
    this->checkBlock();

    if (!blockedEnemy.empty())
    {
        if (curBlockedEnemy == NULL)
        {
            curBlockedEnemy = blockedEnemy.at(blockedEnemy.size() - 1);
        }

        float blood = curBlockedEnemy->getCurrHp();
        float dfs = curBlockedEnemy->getDefense();
        float atk = this->getLethality();

        if (blood > 0)
        {
            curBlockedEnemy->setCurrHp(blood - atk * (1 - dfs) <= 0 ? 0 : blood - atk * (1 - dfs));

            // 攻击动画
            // 在这实现

        }

        /*if (curBlockedEnemy->getCurrHp() <= 0)
        {
            if (blockedEnemy.contains(curBlockedEnemy))
                blockedEnemy.eraseObject(curBlockedEnemy);
        }*/
    }
}

void GanYuanShield::ganyuanDie()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();

    unschedule(CC_SCHEDULE_SELECTOR(GanYuanShield::attack));

    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->removeFromParent();
}

