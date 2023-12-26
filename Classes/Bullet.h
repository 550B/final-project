#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Actor;

class Bullet :public Sprite
{
	CC_SYNTHESIZE(float, damage, Damage);
	CC_SYNTHESIZE(float, velo, Velo);
	CC_SYNTHESIZE(Actor*, from, From);
	CC_SYNTHESIZE(Actor*, target, Target);

public:

	virtual bool init(const std::string& filename, float damage, float velo, Actor* from, Actor* target);

	static Bullet* create(const std::string& filename, float damage, float velo, Actor* from, Actor* target);

	void calculatePosition();

	float calculateDistance() const;

	void removeBullet(Node* pSender);

};

#endif // !_BULLET_H_