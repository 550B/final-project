#ifndef _GAN_YUAN_SHOOTER_H_
#define _GAN_YUAN_SHOOTER_H_

#include "cocos2d.h"
USING_NS_CC;

class GanYuanShooter :public cocos2d::Sprite
{
public:
    CREATE_FUNC(GanYuanShooter); 
    CC_SYNTHESIZE(int, block, Block);  //阻挡数
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //已经阻挡数
    //base中已有
    
    //完成初始化
    //开始攻击
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//攻击时的动画
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//大招时的动画

    
    void initial();
    bool init();
    void setDefaultData();//设置默认数值
    void firstInteract();//初始交互（包括选择及拖拽去部署位置部署）
    void moveToPosition();//初始拖拽
    
    //完成初始化，包括内置数值初始化以及动画初始化
    bool attack();//攻击
    bool bigMove();//是否达到大招

    void castBigMove();//开放大招
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