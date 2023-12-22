#ifndef _GAN_YUAN_MEDICAL_H_
#define _GAN_YUAN_MEDICAL_H_

#include "GanYuanBase.h"


class GanYuanMedical :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanMedical);

    // 旋转并发射治疗弹
    void rotateAndShoot(float dt);

    void shoot();

    void removeBullet(Node* pSender);

    virtual void ganyuanDie();

    Sprite* MedicalBullet();

private:

    Sprite* ganyuanMedical;

};

#endif /* defined(_GAN_YUAN_MEDICAL_H_) */