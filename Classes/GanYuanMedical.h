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


    //完成初始化
       //开始攻击
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//攻击时的动画
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//大招时的动画


    void initial();
    virtual void setDefaultData();//设置默认数值

    virtual void positionLegal(bool& state, Vec2& p);;//当前位置是否合法

    //void firstInteract();//初始交互（包括选择及拖拽去部署位置部署）
    //virtual void moveToPosition();//初始拖拽

    //完成初始化，包括内置数值初始化以及动画初始化

    void castBigMove();//开放大招
    void weaponCallback(Ref* sender);

    //冷却状态
    bool beingCool();//冷却状态动画显示及自己退出冷却状态
    //reset
    bool reset();//冷却后重启

    void setTowerRect(std::vector<Rect> vec) {
        this->towerRectVec = vec;
    }

private:
    void updateHealth(float delta);//更新血条
    void updateLethality(float delta);//更新杀伤力（大招释放）
    void updatDefence(float delta);//更新防御力（技能加成）

    Rect getCurTowerRect(Point touchP);

    std::vector<Rect> towerRectVec;
    Rect curTowerRect;
    Point originPos;

};

#endif 