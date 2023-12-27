#include "Actor.h"
#include "Bullet.h"
#include "GameManager.h"

//Actor::Actor()
//	: scope(0)
//	, lethality(0)   // 杀伤力
//	, hp(0)  // 最大血量
//	, health(0) // 当前血量
//	, defence(0)  // 防御力
//	, alive(true)//是否仍然活着 
//	, intervalTime(0)//攻击间隔时间
//	, lastAttackTime(0)//上一次攻击的时间
//	, isBlock(false)//是否阻挡
//	, isGround(false)// 是否地面
//	, curBlock(0)//已经阻挡数
//	, block(0)//阻挡数
//{
//
//}

Actor* Actor::create()
{
	Actor* sprite = new (std::nothrow) Actor();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Actor::init()
{
	if (Sprite::init())
	{
		return true;
	}
	return false;
}

void Actor::takeDamage(INT32 damage)
{
	INT32 actualDamage = static_cast<INT32>((1 - defence) * damage);

	this->setHealth(getHealth() - actualDamage <= 0 ? 0 : getHealth() - actualDamage);

	if (getHealth() <= 0)
	{
		die();
	}
}

bool Actor::attack()
{
	auto nowTime = GetCurrentTime() / 1000.f;

	if (nowTime - lastAttackTime < intervalTime)
	{
		return false;
	}
	else
	{
		lastAttackTime = nowTime;

		//auto projectile = Projectile::create("pictures/others/bullet.png", _attack, SPEED_FLY, this, _attackTarget);
		//projectile->setPosition(getPosition());
		//projectile->setScale(2);
		//_combatScene->getMap()->addChild(projectile);
		//_combatScene->_bullets.pushBack(projectile);

		return true;
	}
	return false;
}

void Actor::die()
{
	this->setAlive(false);
}
