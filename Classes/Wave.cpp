#include "Wave.h"
#include "GameManager.h"

USING_NS_CC;


Wave::Wave()
	: index(0)
	, isFinished(false)
	, showTime(0)
{

}

bool Wave::init()
{
    if (!Node::init())
    {
        return false;
    }
    return true;
}

void Wave::addEnemy(int type, int road)
{
	EnemyType tmp;
	tmp.type = type;
	tmp.road = road;
    enemies.push_back(tmp);
}

void Wave::finishAdd()
{
	GameManager* instance = GameManager::getInstance();

	instance->waveVector.push_back(this);

	this->setIsFinished(true);
	this->setIndex(instance->waveVector.size());

	int tmp = instance->getWaveIndex();
	instance->setWaveIndex(++tmp);
}

// 获取全部敌人个数，而不是结构体个数
int Wave::getEnemyCount()
{
	return enemies.size();
}

//Wave* Wave::initWave(EnemyWave w)
//{
//    this->type1Total = type1Total;
//    this->type2Total = type2Total;
//    this->type3Total = type3Total;
//    this->type1Hp = type1Hp;
//    this->type2Hp = type2Hp;
//    this->type3Hp = type3Hp;
//    this->enemyTotal = type1Total + type2Total + type3Total;
//    this->isFinishedAddGroup = false;
//    return this;
//}

//// 获取当前波次
//Wave* GameLayer::currentWave()
//{
//	Wave* groupEnemy;
//	if (!instance->waveVector.empty())
//	{
//		groupEnemy = (Wave*)instance->waveVector.at(waveCounter);
//	}
//	else {
//		groupEnemy = NULL;
//	}
//	return groupEnemy;
//}
//
//// 获取下一波
//Wave* GameLayer::nextWave()
//{
//	if (instance->waveVector.empty())
//	{
//		return NULL;
//	}
//
//	if (waveCounter < instance->getGroupNum() - 1)
//	{
//		waveCounter++;
//	}
//	else {
//		isSuccessful = true;
//	}
//	Wave* groupEnemy = (Wave*)instance->waveVector.at(waveCounter);
//	return groupEnemy;
//
//}
//
//// 加入敌人
//void GameLayer::addEnemy()
//{
//	GameManager* instance = GameManager::getInstance();
//
//	Wave* groupEnemy = this->currentWave();
//	if (groupEnemy == NULL)
//	{
//		return;
//	}
//	auto restEnemyNum = groupEnemy->getEnemyTotal();
//	if (restEnemyNum <= 0) {
//		groupEnemy->setIsFinishedAddGroup(true);
//		return;
//	}
//
//	restEnemyNum--;
//	groupEnemy->setEnemyTotal(restEnemyNum);
//
//	EnemyBase* enemy = NULL;
//
//	if (groupEnemy->getType1Total() > 0) {
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		enemy = Enemy1::createEnemy1(pointsVector, groupEnemy->getType1Hp());
//		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
//	}
//	else if (groupEnemy->getType2Total() > 0) {
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		enemy = Enemy2::createEnemy2(pointsVector, groupEnemy->getType2Hp());
//		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
//	}
//	else if (groupEnemy->getType3Total() > 0) {
//		enemy = Enemy3::createEnemy3(pointsVector, groupEnemy->getType3Hp());
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
//	}
//
//	this->addChild(enemy, 10);
//	this->addChild(enemy->getHpBarBg(), 1000);
//	instance->enemyVector.pushBack(enemy);
//}

