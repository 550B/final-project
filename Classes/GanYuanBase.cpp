#include "GanYuanBase.h"
#include "GameManager.h"

GanYuanBase::GanYuanBase()
	:scope(0)
	, towerValue(0)
	, lethality(0)
	, hp(0)
	, health(0)
	, block(0)
	, curBlock(0)
	, rate(0)
	, nearestEnemy(NULL)
{

}

bool GanYuanBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}


void GanYuanBase::checkNearestEnemy()
{
	GameManager* instance = GameManager::getInstance();
	auto enemyVector = instance->enemyVector;

	auto currMinDistant = this->scope;

	EnemyBase* enemyTemp = NULL;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->sprite->getPosition());

		if (distance < currMinDistant) {
			currMinDistant = distance;
			enemyTemp = enemy;
		}
	}
	nearestEnemy = enemyTemp;
}

// 单体奶检查血量最低干员
void GanYuanBase::checkInjuredGanYuan()
{
	GameManager* instance = GameManager::getInstance();

	auto ganyaunVector = instance->ganyuanVector;

	GanYuanBase* ganyuanTemp = NULL;

	for (int i = 0; i < ganyaunVector.size(); i++)
	{
		auto ganyuan = ganyaunVector.at(i);

		if (ganyuan->getHealth() < hp * 1.0 && ganyuan->getHealth() > 0)
		{
			injuredGanYuan.pushBack(ganyuan);
		}
	}
}

void GanYuanBase::sortInjuredGanYuan()
{
	// 快排筛出血量最低的干员
	qSort(injuredGanYuan, 0, injuredGanYuan.size() - 1);

}


void qSort(Vector<GanYuanBase*>array, int low, int high) {
	int i = low;
	int j = high;
	if(i >= j) {
		return;
	}

	int temp = array.at(low)->getHealth();
	while(i != j) {
		while(array.at(j)->getHealth() >= temp && i < j) {
			j--;
		}
	while(array.at(i)->getHealth() <= temp && i < j) {
			i++;
		}
	if(i < j) {
			//swap(array[i], array[j]);
			array.swap(i, j);
		}
	}

	//将基准temp放于自己的位置，（第i个位置）
	array.swap(low, i);
	qSort(array, low, i - 1);
	qSort(array, i + 1, high);
}

void GanYuanBase::checkBlock()
{
	// 先找到最近的敌人(废
	//checkNearestEnemy();

	GameManager* instance = GameManager::getInstance();
	auto enemyVector = instance->enemyVector;

	// 判断是否贴贴
	for (int i = 0; i < enemyVector.size() && curBlock < block; i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->sprite->getPosition());

		if (distance < 0.1 /*这个数举个例子，后面微调*/)
		{
			// 加入阻挡队列
			blockedEnemy.pushBack(enemy);

			enemy->setBeBlocked(true);

			curBlock++;

			this->setCurBlock(curBlock);
		}
	}


}


