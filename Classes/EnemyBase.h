#pragma once
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
//#include "GanYuanBase.h"
#include "Const.h"//xjy
#include "Bar.h"
#include "Actor.h" //zmz
#include "Bullet.h"//zmz

USING_NS_CC;

class EnemyBase : public Actor
{
public:

	EnemyBase();

    virtual bool init(const std::string& filename);

    static EnemyBase* create(const std::string& filename);

    // �Ƿ����
    CC_SYNTHESIZE(bool, entered, Entered);

    // ���
    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);

    // �յ�
    CC_SYNTHESIZE(Vec2, lastPose, LastPose);

    // ��ǰ�㣨�ܵ���·�ǻ�û�ܵ��ĵ㣩
    CC_SYNTHESIZE(Vec2, curPose, CurPose);

    // ·������ָ��
    CC_SYNTHESIZE(int, ptr, Ptr);

    // ��Manager�������һ��
    CC_SYNTHESIZE(Vec2, nextPose, NextPose);

    // ����
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);




    // �����е�λ
    // ���������Ա
    virtual Actor* checkNearestGanYuan();

    // �ж��赲
    virtual bool lookAround();

    // �ܵ���һ��
    virtual void runToFollowPoint();

};



#endif /* defined(_ENEMY_BASE_H_) *///