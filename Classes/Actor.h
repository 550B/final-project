#pragma once
#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "Const.h"

USING_NS_CC;

class Actor : public cocos2d::Sprite
{

protected:

	CC_SYNTHESIZE(int, type, Type);

	CC_SYNTHESIZE(int, scope, Scope);

	CC_SYNTHESIZE(int, lethality, Lethality);

	CC_SYNTHESIZE(float, hp, Hp);

	CC_SYNTHESIZE(float, health, Health);

	CC_SYNTHESIZE(float, defence, Defence);

	CC_SYNTHESIZE(bool, alive, Alive);

	CC_SYNTHESIZE(float, intervalTime, IntervalTime);

	CC_SYNTHESIZE(float, lastAttackTime, LastAttackTime);

	CC_SYNTHESIZE(bool, isBlock, IsBlock);  //�Ƿ��赲

	CC_SYNTHESIZE(int, block, Block);  //�赲��

	CC_SYNTHESIZE(int, curBlock, CurBlock);  //�Ѿ��赲��

	CC_SYNTHESIZE(bool, isGround, IsGround);  // �Ƿ����

public:

	virtual void die();

	virtual bool attack(Actor* target);

	virtual void takeDamage(INT32 damge);

	virtual bool init();
	//
	static Actor* create();

};

#endif // !_ACTOR_H_