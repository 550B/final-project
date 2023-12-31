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

    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);

    
    void initial();
    bool init();
    virtual void setDefaultData();

    virtual void positionLegal(bool& state, Vec2& p);;
    void castBigMove();
    void setTowerRect(std::vector<Rect> vec) {
        this->towerRectVec = vec;
    }
    virtual void reborn();
private:

    Rect getCurTowerRect(Point touchP);
    std::vector<Rect> towerRectVec;
    Rect curTowerRect;
    Point originPos;

};

#endif 