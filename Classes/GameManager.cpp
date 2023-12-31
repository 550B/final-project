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
	towersPosition.clear();
	groundsPosition.clear();
	roadsPosition.clear();
	ganyuanVector.clear();
	waveVector.clear();
	occupied.clear();
}