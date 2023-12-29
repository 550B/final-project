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
	float actualDefence = damage < 0 ? 1 - defence : 1;

	INT32 actualDamage = static_cast<INT32>(actualDefence * damage * -1);

	// 公式
	this->setHealth(getHealth() - actualDamage <= 0 ? 0 : getHealth() - actualDamage >= getHp() ? getHp() : getHealth() - actualDamage);
	healthBar->changeStateBy(-actualDamage);//更新血条
	if (!health)
		die();
	if (getHealth() <= 0)
	{
		die();
	}
}

bool Actor::attack(Actor* target)
{
	GameManager* instance = GameManager::getInstance();

	auto nowTime = GetCurrentTime() / 1000.f;

	if (nowTime - lastAttackTime < intervalTime)
	{
		return false;
	}
	else
	{
		lastAttackTime = nowTime;
		std::string tmpPath;

		switch (target->getType())
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

		auto bullet = Bullet::create(tmpPath, this->getLethality(), 100, this, target);
		bullet->setPosition(this->getPosition());
		bullet->setScale(2);
		instance->gameScene->addChild(bullet);
		instance->bulletVector.pushBack(bullet);

		return true;
	}
	return false;
}

void Actor::die()
{}
