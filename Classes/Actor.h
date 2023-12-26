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

	CC_SYNTHESIZE(int, scope, Scope);

	CC_SYNTHESIZE(int, lethality, Lethality);

	CC_SYNTHESIZE(float, hp, Hp);

	CC_SYNTHESIZE(float, health, Health);

	CC_SYNTHESIZE(float, defence, Defence);

	CC_SYNTHESIZE(bool, alive, Alive);

	CC_SYNTHESIZE(float, intervalTime, IntervalTime);

	CC_SYNTHESIZE(float, lastAttackTime, LastAttackTime);

	CC_SYNTHESIZE(bool, isBlock, IsBlock);  //是否阻挡

	CC_SYNTHESIZE(int, block, Block);  //阻挡数

	CC_SYNTHESIZE(int, curBlock, CurBlock);  //已经阻挡数

	CC_SYNTHESIZE(bool, isGround, IsGround);  // 是否地面

public:

	virtual void die();

	virtual bool attack();

	virtual void takeDamage(INT32 damge);

	virtual bool init();
	//
	static Actor* create();

	//GameManager* instance;

};

#endif // !_ACTOR_H_