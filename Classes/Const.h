#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include "cocos2d.h"
USING_NS_CC;

#define FRAMES_PER_SECOND 60

#define ShieldScope 50
#define ShieldLethality 193
#define ShieldHp 1221
#define ShieldBlock 3
#define ShieldDefence 249
#define ShieldIntervalTime 1.2
#define ShieldCoolTime 60
#define ShieldPrice 10//开局可买干员

#define ShooterScope 50
#define ShooterLethality 337
#define ShooterHp 709
#define ShooterBlock 0
#define ShooterDefence 79
#define ShooterIntervalTime 1.6
#define ShooterCoolTime 70

// types of GanYuans
#define SHIELD_TYPE 1
#define SHOOTER_TYPE 2
#define MEDICAL_TYPE 3

// types of Enemies
#define ENEMY1_TYPE 4
#define ENEMY2_TYPE 5
#define ENEMY3_TYPE 6

// pathes of bullets
const std::string SHIELD_PATH = "Pictures/HelloWorld.png";
const std::string SHOOTER_PATH = "Pictures/HelloWorld.png";
const std::string MEDICAL_PATH = "Pictures/HelloWorld.png";

const std::string ENEMY1_PATH = "Pictures/HelloWorld.png";
const std::string ENEMY2_PATH = "Pictures/HelloWorld.png";
const std::string ENEMY3_PATH = "Pictures/HelloWorld.png";

const float MAX_GAME_DURATION = 9999.f;

// types of roads
#define AROAD 1
#define BROAD 2
#define CROAD 3
#define DROAD 4

enum Emode
{
	normal,
	hard,
	biandui,
};

// 敌人种类，这种敌人的数量
struct EnemyType
{
	int type;
	int road;
};

#endif // !Constant_H