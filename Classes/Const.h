#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include "cocos2d.h"
USING_NS_CC;

#define FRAMES_PER_SECOND 60

#define BigMoveTime 3

#define ShieldScope 50
#define ShieldLethality 193
#define ShieldHp 1221
#define ShieldBlock 3
#define ShieldDefence 0.249
#define ShieldIntervalTime 1.2
#define ShieldCoolTime 10
#define ShieldPrice 10
#define ShieldWeapon 9

#define MedicalScope 50
#define MedicalLethality 189
#define MedicalHp 1000
#define MedicalDefence 0.48
#define MedicalIntervalTime 2.8
#define MedicalCoolTime 20
#define MedicalPrice 15
#define MedicalWeapon 14

#define ShooterScope 50
#define ShooterLethality 337
#define ShooterHp 709
#define ShooterDefence 0.79
#define ShooterIntervalTime 1.6
#define ShooterCoolTime 15
#define ShooterPrice 12
#define ShooterWeapon 11

//air
#define Enemy1Scope 50
#define Enemy1Lethality 110
#define Enemy1Hp 500
#define Enemy1Defence 2.5
#define Enemy1IntervalTime 3.0
#define Enemy1RunSpeed 200

//ground1
#define Enemy2Scope 50
#define Enemy2Lethality 130
#define Enemy2Hp 550
#define Enemy2Defence 1.0
#define Enemy2IntervalTime 1.7
#define Enemy2RunSpeed 100

#define Enemy3Scope 50
#define Enemy3Lethality 240
#define Enemy3Hp 650
#define Enemy3Defence 0.8
#define Enemy3IntervalTime 2.4
#define Enemy3RunSpeed 90

// types of GanYuans
#define SHIELD_TYPE 1
#define SHOOTER_TYPE 2
#define MEDICAL_TYPE 3

// types of Enemies
#define ENEMY1_TYPE 4
#define ENEMY2_TYPE 5
#define ENEMY3_TYPE 6

// types of Maps
#define NORMAL_MAP1 1
#define NORMAL_MAP2 2
#define NORMAL_MAP3 3
#define HARD_MAP 4

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

struct EnemyType
{
	int type;
	int road;
};

enum Eface
{
	up,
	down,
	left,
	right
};

enum State
{
	RUNNING,
	STILL,
	ATTACKING
};

#endif // !Constant_H