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
	, money(8)
	, blue(3)
	, moneyLabel(NULL)
	, groupLabel(NULL)
	, groupTotalLabel(NULL)
	, isSuccessful(false)
	, interval(0)
	, startTime(0)
	, totalEnemies(0)
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

	// ���������
	srand((unsigned int)(time(0)));

	// ��ʼÿ��������һ��
	interval = 2.0f;

	// ��ȡ����
	Size winSize = Director::getInstance()->getWinSize();
	instance = GameManager::getInstance();

	//instance->towersPosition = towers_path;
	//instance->groundsPosition = grounds_path;
	//��������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/battle.mp3");
	auto audio_battle = SimpleAudioEngine::getInstance();
	if (!audio_battle->isBackgroundMusicPlaying()) {
		audio_battle->playBackgroundMusic("Music/battle.mp3", true);
	}

	shield= GanYuanShield::create();
	this->addChild(shield);
	instance->ganyuanVector.pushBack(shield);
	shooter = GanYuanShooter::create();
	this->addChild(shooter);
	instance->ganyuanVector.pushBack(shooter);
	// ���Ӱ�ť
	initToolLayer();


	// ÿ������һ����Ϸ�߼�
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::addSceneEnemy), interval);
	//schedule(CC_SCHEDULE_SELECTOR(GameLayer::logic), 0.5f);
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::updatemoney), 1.0f);

	// ����¼�����
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// ��ʼschedule
	scheduleUpdate();

	// �����һ�¿ɷ��õ㣬�ĳ�Vector
	int arraySize = sizeof(GanYuanBase*) * MAP_WIDTH * MAP_HEIGHT;

	// ��ʼ������
	//initWave();

	return true;
}

void GameLayer::initToolLayer()
{
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	addChild(toolLayer, 10);
	

	//�������
	money = 8;
	instance->setMoney(money);
	auto moneyText = patch::to_string(money);//ת��Ϊstring
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


	//3��
	star3 = Sprite::create("Pictures/star3.png");
	star3->setScale(0.5);
	star3->setAnchorPoint(Point(0.5f, 1));
	star3->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
	star3->setTag(333);//�ı�ʱɾȥsprite
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
	//��������ͼ������ӽڵ�
	Button* back = Button::create("Pictures/pause.png", "Pictures/pause.png", "");//��ʾһ������״̬��һ��ѡ��״̬��һ�����ɵ��״̬
	back->setScale(2);
	back->setAnchorPoint(Vec2(0, 1));
	back->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
	back->setPressedActionEnabled(true);
	toolLayer->addChild(back);
	//���Ӵ����¼� �����ó���
	back->addTouchEventListener(CC_CALLBACK_1(GameLayer::menuBackCallback, this));
}

void GameLayer::updatemoney(float dt)
{

	if (money - instance->getMoney() == 1) {
		money += 1;
		instance->setMoney(money);
	}
	else {
		money= instance->getMoney() + 1;
	}
	auto moneyText = patch::to_string(money);

	moneyLabel->setString(moneyText);
}

//�˵���ť
void GameLayer::menuBackCallback(Ref* pSender)
{
	// ������Ч
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("Music/button.mp3").c_str(), false);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	// ������ʵ���ļ���ȡ������ؿ�

	//instance->clear();
	//�õ����ڵĴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture* renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	//������ǰ��������ӽڵ���Ϣ������renderTexture�С�
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����
	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}

// return a float value of current time in a formal way
float GameLayer::getNowTime()
{
	return GetCurrentTime() / 1000.f;
}

// calculate the interval between two parameters
float GameLayer::getInterval(float a, float b)
{
	return a - b;
}

// wasted
//Wave* GameLayer::currentWave()
//{
//	Wave* w;
//	if (!instance->waveVector.empty())
//	{
//		w = (Wave*)instance->waveVector.at(instance->waveVector.size() - 1);
//	}
//	else 
//	{
//		w = NULL;
//	}
//	return w;
//}

// give you the earliest showed wave
Wave* GameLayer::findEarliestWave()
{
	Wave* w = NULL;
	if (!instance->waveVector.empty() && this->allWavesSuccessful())
	{
		/*w = (Wave*)instance->waveVector.at(instance->waveVector.size() - 1);*/
		float minShowTime = MAX_GAME_DURATION;
		for (auto tmp : instance->waveVector)
		{
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
	instance = GameManager::getInstance();

	Wave* curWave = Wave::create();

	if (curWave->init())
	{
		curWave->setShowTime(showtime);

		for (auto ene : il)
		{
			curWave->addEnemy(ene.type, ene.road);
		}

		curWave->finishAdd();
	}
}

// initiate it in each Scene!
void GameLayer::initWave()
{
	GameLayer::addWaveEnemy(10.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} });

	GameLayer::addWaveEnemy(20.f, { {rand() % 2 + 5,AROAD},{rand() % 2 + 5,AROAD}, {rand() % 2 + 5,AROAD} });

	GameLayer::addWaveEnemy(30.f, { {1,AROAD},{2,AROAD}, {3,AROAD} });

}

// handle enemies in waves waiting to be added in Scene
void GameLayer::addSceneEnemy(float dt)
{
	instance = GameManager::getInstance();

	it = waveQ.begin();

	while (it != waveQ.end())
	{
		auto groupEnemy = *it;

		EnemyType et;

		if (groupEnemy == NULL)
		{
			return;
		}
		else if (!groupEnemy->enemies.empty())
		{
			et = groupEnemy->enemies.front();

			if (et.type == ENEMY1_TYPE) {
				// �볡��Ч
				//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
				// ������һ�ֵ��ˣ�Ѫ��500
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
			}
			else if (et.type == ENEMY3_TYPE) {
				//enemy = Enemy3::createEnemy3(pointsVector, 900);
				//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
				//groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
				//this->addChild(enemy, 10);
				//instance->enemyVector.pushBack(enemy);
			}

			groupEnemy->enemies.erase(groupEnemy->enemies.begin());

		}
		else
		{
			waveQ.erase(groupEnemy);
		}

		it++;
	}
}

bool GameLayer::allWavesSuccessful()
{
	if (!instance->waveVector.empty())
	{
		for (auto tmp : instance->waveVector)
		{
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
	Wave* groupEnemy = this->findEarliestWave();

	if (groupEnemy == NULL)
	{
		return;
	}
	else
	{
		if (groupEnemy->enemies.empty())
		{

		}
		else
		{
			if (this->getInterval(this->getNowTime(), groupEnemy->getShowTime()) > 0.f)
			{
				if (waveQ.count(groupEnemy) == 0)
				{
					waveQ.insert(groupEnemy);
				}
			}
		}
	}
}

//����ʬ�Ե����������
void GameLayer::enemyIntoHouse()
{
	auto enemyVector = instance->enemyVector;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		//auto enemy = enemyVector.at(i);
		//if (enemy->getEnemySuccessful())
		//{
		//	instance->enemyVector.eraseObject(enemy);
		//	enemy->removeFromParent();
		//	auto playHp = getPlayHpPercentage() - 10;
		//	if (playHp > 0) {
		//		setPlayHpPercentage(playHp);
		//		playHpBar->setPercentage(playHp);
		//	}
		//	else {
		//		instance->clear();
		//      Director::getInstance()->replaceScene(TransitionFade::create(0.1f,FailedScene::scene(renderTexture));
		//		
		//	}
		//}
	}
}

// ��ʼ�������š���Ӯ����
void GameLayer::YingZhengTouchesTheElectricSwitch()
{
	/*if (this->blue > 0 && this->currentWave() == NULL)
	{
		this->isSuccessful = true;
	}*/

	if (isSuccessful)
	{
		// ��֪������
		isSuccessful = false;

		// ��ѡ�Ǽ�
		//auto star = this->getBlue();
		// 
		//auto star = 0;
		//auto remainBlue = this->getBlue();

		//if (remainBlue > 0 && remainBlue <= 1) { star = 1; }
		//else if (remainBlue > 1 && remainBlue <= 2) { star = 2; }
		//else if (remainBlue > 60 && remainBlue <= 100) { star = 3; }

		// ��һ��
		// �����������˻�������
		//if (star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
		//{
		//	UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
		//	auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
		//	UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
		//}

		//auto nextlevel = instance->getNextLevelFile();
		//UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);

		/*instance->clear();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f,WinScene::scene(renderTexture));
		*/
	}

	return;
}

//bool GameLayer::onTouchBegan(Touch* touch, Event* event)
//{
//	this->removeChild(chooseTowerpanel);
//	chooseTowerpanel = NULL;
//	auto location = touch->getLocation();
//
//	checkAndAddTowerPanle(location);
//	return true;
//}

void GameLayer::bulletFlying()
{
	if (!instance->bulletVector.empty())
	{
		for (auto bullet : instance->bulletVector)
		{
			bullet->calculatePosition();

			if (bullet->calculateDistance() < 10.f)
			{
				auto receiver = bullet->getTarget();

				if (receiver != NULL)
				{
					receiver->takeDamage(bullet->getDamage());
				}

				bullet->removeBullet(bullet);
				//CC_SAFE_DELETE(bullet);
			}
		}
	}
}

// update runs every frame
void GameLayer::update(float dt)
{
	//addTower();
	//CollisionDetection();
	//logic();
	//GanYuanShield::ShieldInstance->checkNearestEnemy();
	//GanYuanShield::ShieldInstance->attack(GanYuanShield::ShieldInstance->nearestEnemy);
	for (int i = 0; i < instance->ganyuanVector.size(); i++) {
		GanYuanBase* temp= instance->ganyuanVector.at(i);
		//temp->checkNearestEnemy();
		//temp->attack(temp->nearestEnemy);
	}
	bulletFlying();
	enemyIntoHouse();
	YingZhengTouchesTheElectricSwitch();
}

