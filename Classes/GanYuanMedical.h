#ifndef _GAN_YUAN_MEDICAL_H_
#define _GAN_YUAN_MEDICAL_H_

#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
USING_NS_CC;
class GanYuanBase;

class GanYuanMedical :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanMedical);



    void initial();
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