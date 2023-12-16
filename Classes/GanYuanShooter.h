#ifndef _GAN_YUAN_SHOOTER_H_
#define _GAN_YUAN_SHOOTER_H_

#include "GanYuanBase.h"


class GanYuanShooter :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanShooter);

    void rotateAndShoot(float dt);

    void shoot();

    void removeBullet(Node* pSender);

    Sprite* ShooterBullet();

private:

    Sprite* ganyuanShooter;

};

#endif /* defined(_GAN_YUAN_SHOOTER_H_) */