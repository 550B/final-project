#ifndef _GAN_YUAN_SHIELD_H_
#define _GAN_YUAN_SHIELD_H_
/*
   CC_SYNTHESIZE(int, scope, Scope);  // 塔的视线范围
   CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
   CC_SYNTHESIZE(float, hp, Hp);  // 最大血量
   CC_SYNTHESIZE(float, health, Health);  // 当前血量*/
#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
class GanYuanBase;

class GanYuanShield : public GanYuanBase
{
public:

    CC_SYNTHESIZE(int, block, Block);  //阻挡数
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //已经阻挡数
    //base中已有
    
    //完成初始化
    //开始攻击
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//攻击时的动画
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//大招时的动画

    
    
    bool init();
    static GanYuanShield* create();//创建静态create方法
    virtual void setDefaultData();//设置默认数值
    //virtual void positionLegal(bool& state);;//当前位置是否合法
    virtual void initial();//初始化
    
    //完成初始化，包括内置数值初始化以及动画初始化
    void shoot();//攻击
    void bigMove();//是否达到大招
    void castBigMove();//开放大招
    //冷却状态
    bool beingCool();//冷却状态动画显示及自己退出冷却状态
    //reset
    bool reset();//冷却后重启

private:
    void updateHealth(float delta);//更新血条
    void updateLethality(float delta);//更新杀伤力（大招释放）
    void updatDefence(float delta);//更新防御力（技能加成）

    Sprite* ganyuanShield;

};

#endif /* defined(_GAN_YUAN_SHIELD_H_) */