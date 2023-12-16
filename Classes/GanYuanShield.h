#ifndef _GAN_YUAN_SHIELD_H_
#define _GAN_YUAN_SHIELD_H_

#include "GanYuanBase.h"


class GanYuanShield :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanShield);

    void attack(float dt);

private:

    Sprite* ganyuanShield;

    EnemyBase* curBlockedEnemy;

};

#endif /* defined(_GAN_YUAN_SHIELD_H_) */