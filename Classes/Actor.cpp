#include "Actor.h"
#include "Bullet.h"
#include "GameManager.h"

//Actor::Actor()
//	: scope(0)
//	, lethality(0)   // ɱ����
//	, hp(0)  // ���Ѫ��
//	, health(0) // ��ǰѪ��
//	, defence(0)  // ������
//	, alive(true)//�Ƿ���Ȼ����
//	, intervalTime(0)//�������ʱ��
//	, lastAttackTime(0)//��һ�ι�����ʱ��
//	, isBlock(false)//�Ƿ��赲
//	, isGround(false)// �Ƿ����
//	, curBlock(0)//�Ѿ��赲��
//	, block(0)//�赲��
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
