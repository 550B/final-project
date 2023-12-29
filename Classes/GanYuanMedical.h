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
 
    void setDefaultData();//����Ĭ����ֵ
    void firstInteract();//��ʼ����������ѡ����קȥ����λ�ò���
    void moveToPosition();//��ʼ��ק
    void castBigMove();//���Ŵ���

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