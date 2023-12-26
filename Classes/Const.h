#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include "cocos2d.h"
#include "HardMap1Scene.h"
USING_NS_CC;

#define FRAMES_PER_SECOND 60

<<<<<<< HEAD
#define ShieldScope 50
=======
// 地面没有scope？吧
#define ShieldScope 0
>>>>>>> refs/remotes/origin/main
#define ShieldLethality 193
#define ShieldHp 1221
#define ShieldBlock 3
#define ShieldDefence 249
#define ShieldIntervalTime 1.2
#define ShieldCoolTime 60

#define ShooterScope 50
#define ShooterLethality 337
#define ShooterHp 709
#define ShooterBlock 0
#define ShooterDefence 79
#define ShooterIntervalTime 1.6
#define ShooterCoolTime 70

//class GanYuanBase;

enum Emode
{
	normal,
	hard,
	biandui,
};

//一些全局变量。声明成全局可操控的
//Emode mode;//模式
//Scene* gameScene;//当前场景（hard/normal地图）
//bool gameStart = false;//是否游戏已经开始运行,如果已经运行则干员选择是不能继续的，初始想法是设计按钮可决定开始

#endif // !Constant_H