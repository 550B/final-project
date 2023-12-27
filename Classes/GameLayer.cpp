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
	//, objects(NULL)
	//, pointsVector(NULL)
	//, chooseTowerpanel(NULL)
	, towerMatrix(NULL)
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

GameLayer::~GameLayer()
{
	if (towerMatrix) {
		free(towerMatrix);
	}
	//pointsVector.clear();
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

	// ����һ�»���ƫ�ƣ�������λ
	//offX = (map->getContentSize().width - winSize.width) / 2;
	//initPointsVector(offX);

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
	//towerMatrix = (GanYuanBase**)malloc(arraySize);
	//memset((void*)towerMatrix, 0, arraySize);

	//for (int row = 0; row < MAP_HEIGHT; row++) {
	//	for (int col = 0; col < MAP_WIDTH; col++) {
	//		towerMatrix[row * MAP_WIDTH + col] = NULL;
	//	}
	//}

	// ��ʼ������
	//initWave();

	return true;
}

// ��ʼ���㼯����
//void GameLayer::initPointsVector(float offX)
//{
//	Node* runOfPoint = NULL;
//	int count = 0;
//	ValueMap point;
//	point = objects->getObject(patch::to_string(count));
//	while (point.begin() != point.end())
//	{
//		float x = point.at("x").asFloat();
//		float y = point.at("y").asFloat() - 20;
//		runOfPoint = Node::create();
//		runOfPoint->setPosition(Point(x - offX, y));
//
//		/////////////////////////////////////////
//		// �������ʼ���㼯��������
//		/////////////////////////////////////////
//		this->pointsVector.pushBack(runOfPoint);
//		count++;
//		point = objects->getObject(patch::to_string(count));
//	}
//	runOfPoint = NULL;
//}

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

// ��Ϸ�߼�
// ÿ���벻ͣ�����
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

// ��ָ�ŵ���Ļ��
//bool GameLayer::onTouchBegan(Touch* touch, Event* event)
//{
//	this->removeChild(chooseTowerpanel);
//	chooseTowerpanel = NULL;
//	auto location = touch->getLocation();
//
//	checkAndAddTowerPanle(location);
//	return true;
//}

// ����ѡ����
//void GameLayer::addTowerChoosePanel(Point point)
//{
//	chooseTowerpanel = GameSprite::create();
//	chooseTowerpanel->setPosition(point);
//	this->addChild(chooseTowerpanel);
//}

// ת������Ƭ����
//Point GameLayer::convertTotileCoord(Point position)
//{
//	int x = (position.x + offX) / map->getContentSize().width * map->getMapSize().width;
//	int y = map->getMapSize().height - position.y / map->getContentSize().height * map->getMapSize().height;
//	return Point(x, y);
//}

// ת���ɾ�������
// ����֮��Ӧ�ò���Ҫ��
//Point GameLayer::convertToMatrixCoord(Point position)
//{
//	int x = (position.x + offX) / map->getContentSize().width * map->getMapSize().width;
//	int y = position.y / map->getContentSize().height * map->getMapSize().height;
//	return Point(x, y);
//}

// ���λ�ã����ø�Ա
//void GameLayer::checkAndAddTowerPanle(Point position)
//{
//	// ��Ա��Ƭ����
//	Point towerCoord = convertTotileCoord(position);
//	// ��������
//	Point matrixCoord = convertToMatrixCoord(position);
//
//	// ��ȡ��Ƭ��GID
//	int gid = bgLayer->getTileGIDAt(towerCoord);
//
//	// ��map�������GID������Ʒ
//	auto tmp_value = map->getPropertiesForGID(gid);
//	//�����Ǻ��ʵķ���λ��
//	if (tmp_value.getType() != Value::Type::MAP)
//	{
//		return;
//	}
//	//����ȡ����λ�õ��Ǹ���Ƭ
//	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
//	//���������꣬
//	//�����ˣ�����
//	int MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
//
//	int TouchVaule;
//	if (tileTemp.empty())
//	{
//		TouchVaule = 0;
//	}
//	else
//	{
//		TouchVaule = tileTemp.at("canTouch").asInt();
//	}
//	auto tileWidth = map->getContentSize().width / map->getMapSize().width;
//	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
//	towerPos = Point((towerCoord.x * tileWidth) + tileWidth / 2 - offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight / 2);
//
//	if (1 == TouchVaule && towerMatrix[MatrixIndex] == NULL)
//	{
//		addTowerChoosePanel(towerPos);
//	}
//	else
//	{
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
//		auto tips = Sprite::createWithSpriteFrameName("no.png");
//		tips->setPosition(towerPos);
//		this->addChild(tips);
//		tips->runAction(Sequence::create(DelayTime::create(0.8f),
//			CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
//			NULL));
//	}
//}

//�����Ա
//void GameLayer::addTower()
//{
//	if (chooseTowerpanel)
//	{
//		auto type = chooseTowerpanel->getChooseTowerType();
//		if (type == TowerType::ANOTHER)
//		{
//			return;
//		}
//		Point matrixCoord = convertToMatrixCoord(towerPos);
//		int MatrixIndex = static_cast<int>(matrixCoord.y * MAP_WIDTH + matrixCoord.x);
//		bool noMoneyTips = false;
//		GanYuanBase* tower = NULL;
//		if (type == TowerType::ARROW_TOWER)
//		{
//			if (money >= 200)
//			{
//				tower = GanYuanMedical::create();
//				money -= 200;
//			}
//			else
//				noMoneyTips = true;
//		}
//		else if (type == TowerType::ATTACK_TOWER)
//		{
//			if (money >= 150)
//			{
//				tower = GanYuanShield::create();
//				money -= 150;
//			}
//			else
//				noMoneyTips = true;
//		}
//		else if (type == TowerType::MULTIDIR_TOWER)
//		{
//			if (money >= 500)
//			{
//				tower = GanYuanShooter::create();
//				money -= 500;
//			}
//			else
//				noMoneyTips = true;
//		}
//		if (tower != NULL)
//		{
//			tower->setPosition(towerPos);
//			tower->runAction(Sequence::create(FadeIn::create(1.0f), NULL));
//			this->addChild(tower);
//			towerMatrix[MatrixIndex] = tower;
//		}
//		type = TowerType::ANOTHER;
//		chooseTowerpanel->setChooseTowerType(type);
//		this->removeChild(chooseTowerpanel);
//		chooseTowerpanel = NULL;
//
//		auto moneyText = patch::to_string(money);
//		moneyLabel->setString(moneyText);
//
//		if (noMoneyTips == true)
//		{
//			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
//			auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
//			tips->setPosition(towerPos);
//			this->addChild(tips);
//			tips->runAction(Sequence::create(DelayTime::create(0.5f),
//				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
//				NULL));
//		}
//	}
//}

//���ɰ��ӵ���ײ���
//������Ҫ��ģ��������շ��۵Ĺ����߼�
//void GameLayer::CollisionDetection()
//{
//	auto bulletVector = instance->bulletVector;
//	auto enemyVector = instance->enemyVector;
//
//	if (bulletVector.empty() || enemyVector.empty()) {
//		return;
//	}
//	Vector<EnemyBase*> enemyNeedToDelete;
//	Vector<Sprite*> bulletNeedToDelete;
//	for (int i = 0; i < bulletVector.size(); i++)
//	{
//		auto bullet = bulletVector.at(i);
//		if (bullet->getParent() == NULL)
//		{
//			return;
//		}
//		auto  bulletRect = Rect(bullet->getPositionX() + bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
//			bullet->getPositionY() + bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
//			bullet->getContentSize().width,
//			bullet->getContentSize().height);
//
//		for (int j = 0; j < enemyVector.size(); j++)
//		{
//			auto enemy = enemyVector.at(j);
//			//auto enemyRect = enemy->sprite->getBoundingBox();
//			auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
//				enemy->sprite->getPositionY() - enemy->sprite->getContentSize().height / 4,
//				enemy->sprite->getContentSize().width / 2,
//				enemy->sprite->getContentSize().height / 2);
//			if (bulletRect.intersectsRect(enemyRect))
//			{
//				auto currHp = enemy->getCurrHp();
//				currHp--;
//				enemy->setCurrHp(currHp);
//
//				auto currHpPercentage = enemy->getHpPercentage();
//				auto offHp = 100 / enemy->getMaxHp();
//				currHpPercentage -= offHp;
//				if (currHpPercentage < 0) {
//					currHpPercentage = 0;
//				}
//				enemy->setHpPercentage(currHpPercentage);
//				enemy->getHpBar()->setPercentage(currHpPercentage);
//
//				if (currHp <= 0)
//				{
//					enemyNeedToDelete.pushBack(enemy);
//					auto valueMoney = enemy->getVaule();
//					money += valueMoney;
//					auto moneyText = patch::to_string(money);
//					moneyLabel->setString(moneyText);
//				}
//				bulletNeedToDelete.pushBack(bullet);
//				break;
//			}
//		}
//		for (EnemyBase* enemyTemp : enemyNeedToDelete)
//		{
//			enemyTemp->enemyExpload();
//			instance->enemyVector.eraseObject(enemyTemp);
//		}
//		enemyNeedToDelete.clear();
//	}
//
//	for (Sprite* bulletTemp : bulletNeedToDelete)
//	{
//		instance->bulletVector.eraseObject(bulletTemp);
//		bulletTemp->removeFromParent();
//	}
//	bulletNeedToDelete.clear();
//}

//��ÿ֡��ִ�����
//void GameLayer::update(float dt)
//{
//	//addTower();
//	//CollisionDetection();
//	enemyIntoHouse();
//	YingZhengTouchesTheElectricSwitch();
//
//	// ��Ǯ
//}

