#ifndef _GAN_YUAN_MEDICAL_H_
#define _GAN_YUAN_MEDICAL_H_

#include "cocos2d.h"
USING_NS_CC;

class GanYuanMedical :public cocos2d::Sprite
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanMedical);



    void initial();
 
    void setDefaultData();//设置默认数值
    void firstInteract();//初始交互（包括选择及拖拽去部署位置部署）
    void moveToPosition();//初始拖拽
    void castBigMove();//开放大招

    void shoot();

    //void removeBullet(Node* pSender);

    //Sprite* MedicalBullet();

private:
    Rect getCurTowerRect(Point touchP);

    std::vector<Rect> towerRectVec;
    Rect curTowerRect;
    Point originPos;
    Sprite* ganyuanMedical;

};

#endif 