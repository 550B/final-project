#ifndef _GAN_YUAN_SHOOTER_H_
#define _GAN_YUAN_SHOOTER_H_

#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"

USING_NS_CC;

class GanYuanShooter : public GanYuanBase
{
public:
    CREATE_FUNC(GanYuanShooter); 
    //base���
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//����ʱ�Ķ���
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//����ʱ�Ķ���

    
    void initial();
    bool init();
    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void positionLegal(bool& state, Vec2& p);;//��ǰλ���Ƿ�Ϸ�
    void castBigMove();//���Ŵ���
    void setTowerRect(std::vector<Rect> vec) {
        this->towerRectVec = vec;
    }

private:

    Rect getCurTowerRect(Point touchP);
    std::vector<Rect> towerRectVec;
    Rect curTowerRect;
    Point originPos;

};

#endif 