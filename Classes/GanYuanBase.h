#ifndef _GAN_YUAN_BASE_H_
#define _GAN_YUAN_BASE_H_

#include <iostream>
#include<string>
#include<time.h>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "Const.h"
#include "Bar.h"
#include "Actor.h"
#include "Bullet.h"
USING_NS_CC;
class GanYuanBase : public Actor
{
public:
    GanYuanBase();
    virtual bool init(const std::string &filename);

    static GanYuanBase* create(const std::string& filename);


    //CC_SYNTHESIZE(int, scope, Scope);
    //CC_SYNTHESIZE(int, lethality, Lethality);
    //CC_SYNTHESIZE(float, hp, Hp);
    //CC_SYNTHESIZE(float, health, Health);
    //CC_SYNTHESIZE(float, defence, Defence);
    //CC_SYNTHESIZE(bool, selected, Selected);
    //CC_SYNTHESIZE(bool, alive, Alive);
    //CC_SYNTHESIZE(float, intervalTime, IntervalTime);
    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);
    CC_SYNTHESIZE(Vec2, pose, Pose);
    CC_SYNTHESIZE(int, price, Price);//��Ա�Ĺ���۸�
    CC_SYNTHESIZE(float, coolTime, CoolTime);
    CC_SYNTHESIZE(int, weapon_price, weapon_Price);

    //EnemyBase* nearestEnemy;

    virtual void setDefaultData() {};
    virtual void ganYuanController();
    virtual void firstInteract();
    virtual void selectCallback(Ref* sender);
    virtual void moveToPosition();
    virtual void positionLegal(bool& state, Vec2& p); 
    virtual void weaponCallback(Ref* sender);
    virtual void castBigMove() {};
    virtual void die();
    virtual bool attack(Actor* target);
    virtual void reborn() {};
    virtual void cleanDie();
  
    MenuItemImage*m_selectMenu;
    Menu*m_menuSelect;
    MenuItemImage* weapon;
    // ����װ
    void checkBlock();

    // ������
    void checkNearestEnemy();

    // ��ҽ��
    void checkInjuredGanYuan();

    void sortInjuredGanYuan();


};
#endif /* defined(_GAN_YUAN_BASE_H_) */