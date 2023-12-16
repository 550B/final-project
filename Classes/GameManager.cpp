#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

void GameManager::clear()
{
	enemyVector.clear();
	bulletVector.clear();
	//ganyuanVector.clear();	// 他想结束时保留场上干员阵型
	waveVector.clear();
}
