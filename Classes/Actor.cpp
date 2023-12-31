#include "Actor.h"
#include "Bullet.h"
#include "GameManager.h"


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
	float actualDefence = damage < 0 ? 1 - defence : 1;

	INT32 actualDamage = static_cast<INT32>(actualDefence * damage * -1);

	// 公式
	int a = getHealth() - actualDamage <= 0 ? 0 : getHealth() - actualDamage >= getHp() ? getHp() : getHealth() - actualDamage;
	this->setHealth(getHealth() + actualDamage <= 0 ? 0 : getHealth() + actualDamage >= getHp() ? getHp() : getHealth() + actualDamage);
	if (this->healthBar != NULL)
		healthBar->ifRecover(actualDamage);//更新血条 打架是-医疗为正
	//if (!health)
	//	die();
	if (getHealth() <= 0)
	{
		die();
	}
}

bool Actor::attack(Actor* target)
{
	GameManager* instance = GameManager::getInstance();

	auto nowTime = GetCurrentTime() / 1000.f;

	if (nowTime - getLastAttackTime() <= getIntervalTime())
	{
		return false;
	}
	else if(target == nullptr){
		return false;
	}
	else
	{
		setLastAttackTime(nowTime);
		std::string tmpPath;

		switch (this->getType())
		{
		case SHIELD_TYPE:
			tmpPath = SHIELD_PATH;
			break;
		case SHOOTER_TYPE:
			tmpPath = SHOOTER_PATH;
			break;
		case MEDICAL_TYPE:
			tmpPath = MEDICAL_PATH;
			break;
		case ENEMY1_TYPE:
			tmpPath = ENEMY1_PATH;
			break;
		case ENEMY2_TYPE:
			tmpPath = ENEMY2_PATH;
			break;
		case ENEMY3_TYPE:
			tmpPath = ENEMY3_PATH;
			break;
		}

		auto bullet = Bullet::create(tmpPath, this->getLethality(), 3000, this, target);
		bullet->setPosition(this->getPosition());
		bullet->setScale(0.12);
		instance->gameScene->addChild(bullet);
		instance->bulletVector.pushBack(bullet);

		return true;
	}
	return false;
}

void Actor::die()
{
	this->setAlive(false);
}
