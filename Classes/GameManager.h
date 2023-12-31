#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <iostream>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "GanYuanBase.h"
#include "Bullet.h"
#include "Const.h"
#include "Wave.h"

USING_NS_CC;

class GameManager
{
public:

	int levelType;

	std::vector<Vec2> occupied;

	Scene* gameScene;
	Vector<EnemyBase*> enemyVector;
	Vector<Bullet*> bulletVector;
	Vector<GanYuanBase*> ganyuanVector;
	Vector<Wave*> waveVector;
	Vector<GanYuanBase*> injuredganyuan;
	std::vector<Vec2> towersPosition;
	std::vector<Vec2> groundsPosition;
	std::vector<std::vector<Vec2> > roadsPosition;

	CC_SYNTHESIZE(int, money, Money);

	CC_SYNTHESIZE(int, waveIndex, WaveIndex);
	//CC_SYNTHESIZE(int, groupNum, GroupNum);
	//CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);

	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);

	CC_SYNTHESIZE(std::string, curBgName, CurBgName);

	bool init();
	void clear();

	static GameManager* getInstance();

private:

	static GameManager* instance;

};
#endif /* defined(_GAME_MANAGER_H_) */

