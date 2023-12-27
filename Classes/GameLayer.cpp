#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "GameLayer.h"
//#include "WinScene.h"
//#include "FailedScene.h"
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
	// ���Ӱ�ť
	initToolLayer();

	// ÿ������һ����Ϸ�߼�
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::logic), interval);
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
	money+=1; //ÿ��+2
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

// ��ȡ��ǰ����
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

// ��ȡ��һ��
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

// ������˵�����
// ������{{1,2),{2,3},...}
// ���ͣ���1�ֵ�������2������2�ֵ�������3�������޳�����
//void GameLayer::addWaveEnemy(std::initializer_list<EnemyType> il)
//{
//	instance = GameManager::getInstance();
//
//	Wave* curWave = Wave::create();
//
//	int index = instance->waveVector.size();
//
//	if (curWave->init())
//	{
//		// ��������
//		curWave->setIndex(index);
//
//		for (auto ene : il)
//		{
//			curWave->addEnemy(ene.type, ene.count);
//		}
//
//		curWave->finishAdd();
//	}
//}

// ��ʼ������
// ������༭�����ĵ���
//void GameLayer::initWave()
//{
//	// ��һ��
//	// �������3�ֵ���
//	GameLayer::addWaveEnemy({ {rand() % 3 + 1,1},{rand() % 3 + 1,1}, {rand() % 3 + 1,1} });
//
//	// �ڶ���
//    // �������3�ֵ��ˣ�ÿ�ֵ���2��
//	GameLayer::addWaveEnemy({ {rand() % 3 + 1,2},{rand() % 3 + 1,2}, {rand() % 3 + 1,2} });
//
//	// ������
//    // ���ֵ���1,2,3��ÿ�ֵ���1��
//	GameLayer::addWaveEnemy({ {1,1},{2,1}, {3,1} });
//
//	// ���Ĳ������岨...
//}

// ������˵�����
//void GameLayer::addSceneEnemy()
//{
//	//GameManager* instance = GameManager::getInstance();
//	instance = GameManager::getInstance();
//
//	Wave* groupEnemy = this->currentWave();
//	if (groupEnemy == NULL)
//	{
//		return;
//	}
//	auto restStructNum = groupEnemy->enemies.size();
//	if (restStructNum <= 0) {
//		//groupEnemy->setIsFinishedAddGroup(true);
//		//groupEnemy->enemies.popBack();
//		instance->waveVector.popBack();
//
//		// ����֮��ͣ����΢��һ��
//		interval = 5.0f;
//		return;
//	}
//	else
//	{
//		interval = 2.0f;
//	}
//
//	//groupEnemy->setEnemyTotal(restStructNum);
//
//	EnemyBase* enemy = NULL;
//	EnemyType et = groupEnemy->enemies.at(restStructNum - 1);
//
//	////////////////////////
//	//********************//
//	//* �������洴������ *//
//	//********************//
//	////////////////////////
//	if (et.count > 0 && et.type == 1) {
//		// �볡��Ч
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		// ������һ�ֵ��ˣ�Ѫ��500
//		enemy = Enemy1::createEnemy1(pointsVector, 500);
//		//groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
//	}
//	else if (et.count > 0 && et.type == 2) {
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		enemy = Enemy2::createEnemy2(pointsVector, 700);
//		//groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
//	}
//	else if (et.count > 0 && et.type == 3) {
//		enemy = Enemy3::createEnemy3(pointsVector, 900);
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		//groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
//	}
//
//	//restStructNum--;
//	et.count--;
//	if (et.count <= 0)
//	{
//		groupEnemy->enemies.popBack();
//	}
//
//	this->addChild(enemy, 10);
//	this->addChild(enemy->getHpBarBg(), 1000);
//	instance->enemyVector.pushBack(enemy);
//}

void GameLayer::logic(float dt)
{
	//Wave* groupEnemy = this->currentWave();

	//if (groupEnemy == NULL)
	//{
	//	// 2023��12��22��23��52�� ������
	//	// д��������
	//	return;
	//}
	//if (groupEnemy->getIsFinished() == true && instance->enemyVector.size() == 0  && waveCounter < instance->getGroupNum())
	//{
	//	groupEnemy = this->nextWave();
	//	int groupTotal = instance->getGroupNum();
	//	auto groupInfoText = patch::to_string(waveCounter + 1);
	//	groupLabel->setString(groupInfoText);
	//	auto groupTotalText = patch::to_string(groupTotal);
	//	groupTotalLabel->setString(groupTotalText);
	//}
	//this->addSceneEnemy();
}

//����ʬ�Ե����������
void GameLayer::enemyIntoHouse()
{
	auto enemyVector = instance->enemyVector;
	for (int i = 0; i < enemyVector.size(); i++)
	{

		// �߼��������ߵ����һ���㲢����Ѫ
		// ���õ���ʤ��
		// ����-1
		// �ȴ�Ұѵ��������жϸ����������������ͷ�


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
		//		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailedScene::create()));
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
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, WinScene::createScene()));*/
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
	bulletFlying();
	enemyIntoHouse();
	YingZhengTouchesTheElectricSwitch();
}

