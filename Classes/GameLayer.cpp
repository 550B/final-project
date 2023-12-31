#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "GameLayer.h"
#include "WinScene.h"
#include "FailedScene.h"
//#include "LevelScene.h"

#include <ctime>
#include <sstream>

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}


USING_NS_CC_EXT;
using namespace CocosDenshion;

GameLayer::GameLayer()
	:isTouchEnable(false)
	, spriteSheet(NULL)
	, map(NULL)
	, waveCounter(0)
	, moneyL(8)
	, moneyLabel(NULL)
	, groupLabel(NULL)
	, groupTotalLabel(NULL)
	, interval(0)
	, startTime(0)
	, totalEnemies(0)
	, mapType(0)
	, star(3)
{

}
Scene* GameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	// record start time first
	this->startTime = GetCurrentTime() / 1000.f;

	srand((unsigned int)(time(0)));

	interval = 4.0f;

	Size winSize = Director::getInstance()->getWinSize();
	GameManager* instance = GameManager::getInstance();

	mapType = instance->levelType;

	instance->towersPosition = towers_path;
	instance->groundsPosition = grounds_path;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/battle.mp3");
	auto audio_battle = SimpleAudioEngine::getInstance();
	if (!audio_battle->isBackgroundMusicPlaying()) {
		audio_battle->playBackgroundMusic("Music/battle.mp3", true);
	}

	shield= GanYuanShield::create();
	this->addChild(shield);
	shooter = GanYuanShooter::create();
	this->addChild(shooter);
	medical = GanYuanMedical::create();
	this->addChild(medical);

	initToolLayer();

	// initialize waves
	initWave();

	schedule(CC_SCHEDULE_SELECTOR(GameLayer::addSceneEnemy), interval);
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::bulletFlying), 0.1f);
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::updatemoney), 1.0f);

	scheduleUpdate();

	int arraySize = sizeof(GanYuanBase*) * MAP_WIDTH * MAP_HEIGHT;

	return true;
}

void GameLayer::initToolLayer()
{
	GameManager* instance = GameManager::getInstance();
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	addChild(toolLayer, 10);
	

	moneyL = 8;
	instance->setMoney(moneyL);
	auto moneyText = patch::to_string(moneyL);
	moneyLabel = Label::createWithSystemFont(moneyText, "fonts/arial.ttf", 50);
	moneyLabel->setColor(Color3B(255, 215, 0));
	moneyLabel->setAnchorPoint(Point(1, 1));
	moneyLabel->setPosition(Point(Director::getInstance()->getVisibleSize().width - 20, Director::getInstance()->getVisibleSize().height));
	toolLayer->addChild(moneyLabel);

	sprite_money = Sprite::create("Pictures/money.png");
	sprite_money->setAnchorPoint(Point(1, 1));
	sprite_money->setScale(2);//32*32
	sprite_money->setPosition(Point(Director::getInstance()->getVisibleSize().width-100, Director::getInstance()->getVisibleSize().height));
	toolLayer->addChild(sprite_money);


	//3
	star3 = Sprite::create("Pictures/star3.png");
	star3->setScale(0.5);
	star3->setAnchorPoint(Point(0.5f, 1));
	star3->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
	star3->setTag(333);
	toolLayer->addChild(star3);

	/*
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupLabel->setPosition(Point(spritetool->getContentSize().width / 8 * 3, spritetool->getContentSize().height / 2));
	groupLabel->setAnchorPoint(Point(0.5f, 0.5f));
	auto groupInfoText = patch::to_string(waveCounter + 1);
	groupLabel->setString(groupInfoText);
	spritetool->addChild(groupLabel);

	groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2, spritetool->getContentSize().height / 2));
	groupTotalLabel->setAnchorPoint(Point(0.5f, 0.5f));
	auto groupTotalText = patch::to_string(groupTotal);
	groupTotalLabel->setString(groupTotalText);
	spritetool->addChild(groupTotalLabel);*/

	// back
	Button* back = Button::create("Pictures/pause.png", "Pictures/pause.png", "");
	back->setScale(2);
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
	back->setPressedActionEnabled(true);
	toolLayer->addChild(back);
	back->addTouchEventListener(CC_CALLBACK_1(GameLayer::menuBackCallback, this));
}

void GameLayer::updatemoney(float dt)
{
	GameManager* instance = GameManager::getInstance();
	if (moneyL - instance->getMoney() == 1) {
		moneyL += 1;
		instance->setMoney(moneyL);
	}
	else {
		moneyL= instance->getMoney() + 1;
	}
	auto moneyText = patch::to_string(moneyL);
	moneyLabel->setString(moneyText);
}

//�˵���ť
void GameLayer::menuBackCallback(Ref* pSender)
{
	// ������Ч
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("Music/button.mp3").c_str(), false);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	// ������ʵ���ļ���ȡ������ؿ�?

	//instance->clear();
	//�õ����ڵĴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	//������ǰ��������ӽڵ����?������renderTexture�С�
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����
	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

// return a float value of current time in a formal way
float GameLayer::getNowTime() const
{
	return GetCurrentTime() / 1000.f;
}

// calculate the interval between two parameters
float GameLayer::getInterval(float a, float b) const
{
	return a - b;
}

// give you the earliest showed wave
Wave* GameLayer::findEarliestWave()
{
	GameManager* instance = GameManager::getInstance();
	Wave* w = NULL;
	if (!instance->waveVector.empty() && this->allWavesSuccessful())
	{
		/*w = (Wave*)instance->waveVector.at(instance->waveVector.size() - 1);*/
		float minShowTime = MAX_GAME_DURATION;

		for(int i = 0; i < instance->waveVector.size(); i++)
		{
			auto tmp = instance->waveVector.at(i);

			if (tmp->getShowTime() < minShowTime/*tmp->getShowTime() > 5.f*/)
			{
				minShowTime = tmp->getShowTime();
				w = tmp;
			}
		}
	}
	else
	{
		w = NULL;
	}
	return w;
}

// example codes below
void GameLayer::addWaveEnemy(float showtime, std::initializer_list<EnemyType> il)
{
	GameManager* instance = GameManager::getInstance();

	Wave* curWave = Wave::create();

	if (curWave->init())
	{
		curWave->setShowTime(showtime);

		for (auto ene : il)
		{
			curWave->addEnemy(ene.type, ene.road);
		}

		curWave->finishAdd(curWave);
	}
}

// initiate it in each Scene!
void GameLayer::initWave()
{
	switch (mapType)
	{
	case NORMAL_MAP1:
		GameLayer::addWaveEnemy(5.f, { {5,AROAD}/*,{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD}*/ });
		GameLayer::addWaveEnemy(10.f, { {6,AROAD}/*,{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} */});
		GameLayer::addWaveEnemy(15.f, { {4,AROAD}/*, {ENEMY2_TYPE,AROAD}, {ENEMY3_TYPE,AROAD}*/ });
		break;
	case NORMAL_MAP2:
		GameLayer::addWaveEnemy(10.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} });
		GameLayer::addWaveEnemy(20.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} });
		GameLayer::addWaveEnemy(30.f, { {4,AROAD}, {5,AROAD}, {6,AROAD} });
		break;
	case NORMAL_MAP3:
		GameLayer::addWaveEnemy(10.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} });
		GameLayer::addWaveEnemy(20.f, { {rand() % 2 + 5,BROAD},{rand() % 2 + 5,BROAD}, {rand() % 2 + 5,BROAD} });
		GameLayer::addWaveEnemy(30.f, { {4,AROAD}, {5,BROAD}, {6,AROAD} });
		break;
	case HARD_MAP:
		GameLayer::addWaveEnemy(10.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,BROAD}, {rand() % 2 + 5,CROAD} });
		GameLayer::addWaveEnemy(20.f, { {rand() % 2 + 5,DROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,BROAD} });
		GameLayer::addWaveEnemy(30.f, { {4,CROAD}, {5,DROAD}, {6,AROAD} });
		break;
	}
}

// handle enemies in waves waiting to be added in Scene
void GameLayer::addSceneEnemy(float dt)
{
	GameManager* instance = GameManager::getInstance();

	for (int i = 0; i < waveQ.size(); i++)
	{
		auto groupEnemy = waveQ.at(i);

		EnemyType et;

		if (groupEnemy == NULL)
		{
			return;
		}
		else if (!groupEnemy->enemies.empty())
		{
			et = groupEnemy->enemies.front();

			std::vector<Vec2> rd = instance->roadsPosition.at(et.road - 1);

			if (et.type == ENEMY1_TYPE) {
		
				//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
			

				auto enemy = Enemy1::create();
				enemy->setEntered(false);
				enemy->setLastAttackTime(this->getNowTime());
				enemy->setRoad(et.road);
				enemy->setFirstPose(rd.front());
				enemy->setLastPose(rd.back());
				enemy->setCurPose(rd.front());
				enemy->setNextPose(rd.at(1));
				enemy->setPtr(0);
				enemy->setPosition(rd.front());
				enemy->setScale(0.125);
				this->addChild(enemy, 10);
				instance->enemyVector.insert(0, enemy);

				//enemy = Enemy1::createEnemy1(pointsVector, 500);
				//groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
			/*	this->addChild(enemy, 10);
				instance->enemyVector.pushBack(enemy);*/
			}
			else if (et.type == ENEMY2_TYPE) {
				//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
				//enemy = Enemy2::createEnemy2(pointsVector, 700);
				//groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	/*			this->addChild(enemy, 10);
				instance->enemyVector.pushBack(enemy);*/

				auto enemy = Enemy2::create();
				enemy->setEntered(false);
				enemy->setLastAttackTime(this->getNowTime());
				enemy->setRoad(et.road);
				enemy->setFirstPose(rd.front());
				enemy->setLastPose(rd.back());
				enemy->setCurPose(rd.front());
				enemy->setNextPose(rd.at(1));
				enemy->setPtr(0);
				enemy->setPosition(rd.front());
				enemy->setScale(0.125);
				this->addChild(enemy, 10);
				instance->enemyVector.insert(0, enemy);

			}
			else if (et.type == ENEMY3_TYPE) {
				//enemy = Enemy3::createEnemy3(pointsVector, 900);
				//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
				//groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
				//this->addChild(enemy, 10);
				//instance->enemyVector.pushBack(enemy);

				auto enemy = Enemy3::create();
				enemy->setEntered(false);
				enemy->setLastAttackTime(this->getNowTime());
				enemy->setRoad(et.road);
				enemy->setFirstPose(rd.front());
				enemy->setLastPose(rd.back());
				enemy->setCurPose(rd.front());
				enemy->setNextPose(rd.at(1));
				enemy->setPtr(0);
				enemy->setPosition(rd.front());
				enemy->setScale(0.125);
				this->addChild(enemy, 10);
				instance->enemyVector.insert(0, enemy);

			}

			groupEnemy->enemies.erase(groupEnemy->enemies.begin());

		}
		else
		{
			waveQ.eraseObject(groupEnemy);
		}
	}
}

bool GameLayer::allWavesSuccessful()
{
	GameManager* instance = GameManager::getInstance();
	if (!instance->waveVector.empty())
	{
		for(int i = 0; i < instance->waveVector.size(); i++)
		{
			auto tmp = instance->waveVector.at(i);

			if (!tmp->getIsFinished())
			{
				return false;
			}
		}
	}
	return true;
}

void GameLayer::logic()
{
	GameManager* instance = GameManager::getInstance();
	Wave* groupEnemy = this->findEarliestWave();

	if (groupEnemy == NULL)
	{
		return;
	}
	else
	{
		if (groupEnemy->enemies.empty())
		{
			instance->waveVector.eraseObject(groupEnemy);
		}
		else
		{
			if (this->getInterval(this->getNowTime(), this->startTime) > groupEnemy->getShowTime())
			{
				if (!waveQ.contains(groupEnemy))
				{
					waveQ.pushBack(groupEnemy);
				}
				instance->waveVector.eraseObject(groupEnemy);
			}
		}
	}
}

// lose
void GameLayer::lose()
{
	GameManager* instance = GameManager::getInstance();
	auto enemyVector = instance->enemyVector;

	if (!enemyVector.empty())
	{
		for (int i = 0; i < enemyVector.size(); i++)
		{
			auto enemy = enemyVector.at(i);

			if (!enemy->getAlive())
			{
				continue;
			}

			if (enemy->checkIsEntered(enemy)/* && enemy->getAlive()*/)
			{
				bool isAlive = enemy->getAlive();
				instance->enemyVector.eraseObject(enemy);
				enemy->removeFromParent();

				if (isAlive)
				{
					this->star--;

					// update star
					switch (star)
					{
					case 2:
						star2 = Sprite::create("Pictures/star2.png");
						star2->setScale(0.5);
						star2->setAnchorPoint(Point(0.5f, 1));
						star2->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
						toolLayer->addChild(star2, 200);
						break;
					case 1:
						star1 = Sprite::create("Pictures/star1.png");
						star1->setScale(0.5);
						star1->setAnchorPoint(Point(0.5f, 1));
						star1->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
						toolLayer->addChild(star1, 300);
						break;
					default:
						star0 = Sprite::create("Pictures/star0.png");
						star0->setScale(0.5);
						star0->setAnchorPoint(Point(0.5f, 1));
						star0->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
						toolLayer->addChild(star0, 400);
						break;
					}
				}
				if (star <= 0)
				{
					Size visibleSize = Director::getInstance()->getVisibleSize();
					RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
					renderTexture->begin();
					this->getParent()->visit();
					renderTexture->end();
					unscheduleUpdate();
					SimpleAudioEngine::getInstance()->stopBackgroundMusic();
					instance->clear();
					Director::getInstance()->replaceScene(TransitionFade::create(0.1f, Failed::scene(renderTexture)));
				}
			}
		}
	}
}


void GameLayer::win()
{
	GameManager* instance = GameManager::getInstance();

	bool condition1 = instance->waveVector.empty();
	bool condition2 = star > 0;
	bool condition3 = true;
	bool condition4 = waveQ.empty();
	
	for (int i = 0; i < instance->enemyVector.size(); i++)
	{
		if (instance->enemyVector.at(i)->getAlive())
		{
			condition3 = false;
			break;
		}
	}

	if (condition1 && condition2 && condition3 && condition4 )
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		this->getParent()->visit();
		renderTexture->end();
		unscheduleUpdate();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		instance->clear();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, Win::scene(renderTexture)));
	}

	return;
}


void GameLayer::removeBullet(Bullet* pSender)
{
	GameManager* instance = GameManager::getInstance();

	auto bulletVector = instance->bulletVector;

	//instance->bulletVector.eraseObject(pSender);

	//pSender->removeFromParent();

	instance->bulletVector.eraseObject(pSender, true);

	pSender->getParent()->removeChild(pSender, true);
}

void GameLayer::bulletFlying(float dt)
{
	GameManager* instance = GameManager::getInstance();

	if (!instance->bulletVector.empty())
	{
		/*for (auto bullet : instance->bulletVector)*/
		for(int i = 0; i < instance->bulletVector.size(); i++)
		{
			auto bullet = instance->bulletVector.at(i);
			if (bullet)
			{
				if (bullet && bullet->getTarget() != NULL)
				{
					bullet->calculatePosition();

					if (bullet->calculateDistance() < 20.f)
					{
						auto receiver = bullet->getTarget();

						if (receiver != NULL)
						{
							receiver->takeDamage(bullet->getDamage());
						}
						this->removeBullet(bullet);
					}
				}
				else
				{
					this->removeBullet(bullet);
				}
			}
		}
	}
}

void GameLayer::runEnemies()
{
	GameManager* instance = GameManager::getInstance();
	for (auto enemy : instance->enemyVector)
	{
		enemy->runToFollowPoint();
	}
}
void GameLayer::runmedical() {
	GameManager* instance = GameManager::getInstance();
	medical->checkInjuredGanYuan();
	if (!instance->injuredganyuan.empty()) {
		medical->sortInjuredGanYuan();
		int i;
		for (i = 0; i < instance->injuredganyuan.size(); i++)
		{
			if (instance->injuredganyuan.at(i)->getAlive())
			{
				break;
			}
		}
		if (instance->injuredganyuan.size() != 0)
		{
			medical->attack(instance->injuredganyuan.at(i));
			if (instance->injuredganyuan.at(i)->getHealth() == instance->injuredganyuan.at(i)->getHp()) {
				instance->injuredganyuan.erase(instance->injuredganyuan.begin() + i);
			}
		}
	}
	
}

// update runs every frame
void GameLayer::update(float dt)
{
	GameManager* instance = GameManager::getInstance();
	logic();
	for (int i = 0; i < instance->ganyuanVector.size(); i++) {
		if (instance->ganyuanVector.at(i)->getType() == 3) {
			runmedical();
		}
		else
			instance->ganyuanVector.at(i)->ganYuanController();
	}
	for (int i = 0; i < instance->enemyVector.size(); i++) {
		if (instance->enemyVector.at(i)->getType() == ENEMY1_TYPE)
		{
			instance->enemyVector.at(i)->enemyController();
		}
	}
	runEnemies();
	lose();
	win();
}

