#include "Bullet.h"
#include "Actor.h"
#include "GameManager.h"
#include "math.h"

#define PI 3.1415926

Bullet* Bullet::create(const std::string& filename, float damge, float velo, Actor* from, Actor* target)
{
	Bullet* bullet = new(std::nothrow)Bullet;
	if (bullet && bullet->init(filename, damge, velo, from, target))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}


bool Bullet::init(const std::string& filename, float damage, float velo, Actor* from, Actor* target)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture(filename);
	setPosition(from->getPosition());
	setScale(0.5);

	this->setDamage(damage);
	this->setVelo(velo);
	this->setFrom(from);
	this->setTarget(target);

	return true;
}

void Bullet::calculatePosition()
{
	// Ðý×ªµÄÂß¼­
	if (target != NULL)
	{
		auto delta = target->getPosition() - this->getPosition();

		auto distance = delta.length();
		auto dx = delta.x;
		auto dy = delta.y;

		auto rotateRadians = delta.getAngle();
		auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);

		auto speed = 0.5 / M_PI;
		auto rotateDuration = fabs(rotateRadians * speed);

		//setRotation(360 - getRad(getPosition(), target->getPosition()) / M_PI * 180);
		setRotation(rotateDegrees);
		setPosition(getPosition() + Vec2(dx / distance * velo / FRAMES_PER_SECOND, dy / distance * velo / FRAMES_PER_SECOND));
	}
}

float Bullet::calculateDistance() const
{
	if (target != NULL)
	{
		auto delta = target->getPosition() - this->getPosition();

		return delta.getLength();
	}
	else
	{
		return 0;
	}
}

