#ifndef _GAN_YUAN_MEDICAL_H_
#define _GAN_YUAN_MEDICAL_H_

#include "GanYuanBase.h"


class GanYuanMedical :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanMedical);

    // ��ת���������Ƶ�
    void rotateAndShoot(float dt);

    void shoot();

    void removeBullet(Node* pSender);

    virtual void ganyuanDie();

    Sprite* MedicalBullet();

private:

    Sprite* ganyuanMedical;

};

#endif /* defined(_GAN_YUAN_MEDICAL_H_) */