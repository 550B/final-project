#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "GameLayer.h"
#include "GameManager.h"
//#include "WinScene.h"
//#include "FailedScene.h"
//#include "LevelScene.h"
#include "Menu.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
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
	, objects(NULL)
	, pointsVector(NULL)
	//, chooseTowerpanel(NULL)
	, towerMatrix(NULL)
	, waveCounter(0)
	, money(0)
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
	pointsVector.clear();
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

	// 随机数种子
	srand((unsigned int)(time(0)));

	// 初始每两秒添加一波
	interval = 2.0f;

	// 获取导演
	Size winSize = Director::getInstance()->getWinSize();
	instance = GameManager::getInstance();

	// 背景
	//auto gameBg = Sprite::create(instance->getCurBgName());
	//gameBg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	//addChild(gameBg, -20);

	// 添加当前地图背景
	//map = TMXTiledMap::create(instance->getCurMapName());
	//bgLayer = map->getLayer("bg");
	//bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
	//bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));

	// 添加object节点
	//objects = map->getObjectGroup("obj");
	//this->addChild(map, -10);

	// 添加按钮
	//initToolLayer();

	// 计算一下画面偏移，对正点位
	//offX = (map->getContentSize().width - winSize.width) / 2;
	//initPointsVector(offX);

	// 每两秒检查一下游戏逻辑
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::logic), interval);

	// 点击事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// 开始schedule
	scheduleUpdate();

	// 后面改一下可放置点，改成Vector
	//int arraySize = sizeof(GanYuanBase*) * MAP_WIDTH * MAP_HEIGHT;
	//towerMatrix = (GanYuanBase**)malloc(arraySize);
	//memset((void*)towerMatrix, 0, arraySize);

	//for (int row = 0; row < MAP_HEIGHT; row++) {
	//	for (int col = 0; col < MAP_WIDTH; col++) {
	//		towerMatrix[row * MAP_WIDTH + col] = NULL;
	//	}
	//}

	// 初始化波次
	//initWave();

	return true;
}

// 初始化点集向量
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
//		// 在这里初始化点集！！！！
//		/////////////////////////////////////////
//		this->pointsVector.pushBack(runOfPoint);
//		count++;
//		point = objects->getObject(patch::to_string(count));
//	}
//	runOfPoint = NULL;
//}

// 在这里面添加按钮
//void GameLayer::initToolLayer()
//{
//	auto size = Director::getInstance()->getWinSize();
//	toolLayer = Layer::create();
//	addChild(toolLayer);
//
//	auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
//	spritetool->setAnchorPoint(Point(0.5f, 1));
//	spritetool->setPosition(Point(size.width / 2, size.height));
//	toolLayer->addChild(spritetool);
//
//	//
//	money = instance->getMoney();
//	moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
//	moneyLabel->setPosition(Point(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2));
//	moneyLabel->setAnchorPoint(Point(0, 0.5f));
//	auto moneyText = patch::to_string(money);
//	moneyLabel->setString(moneyText);
//	spritetool->addChild(moneyLabel);
//
//	//
//	/*playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
//	playHpBar->setType(ProgressTimer::Type::BAR);
//	playHpBar->setMidpoint(Point(0, 0.4f));
//	playHpBar->setBarChangeRate(Point(1, 0));
//	playHpBar->setPercentage(playHpPercentage);
//	playHpBar->setPosition(Point(spritetool->getContentSize().width / 5 * 4, spritetool->getContentSize().height / 2));
//	spritetool->addChild(playHpBar);*/
//
//	auto star = Sprite::createWithSpriteFrameName("playstar.png");
//	star->setPosition(Point(spritetool->getContentSize().width / 5 * 4, spritetool->getContentSize().height / 2));
//	spritetool->addChild(star);
//
//	//
//	/*int groupTotal = instance->getGroupNum();
//	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
//	groupLabel->setPosition(Point(spritetool->getContentSize().width / 8 * 3, spritetool->getContentSize().height / 2));
//	groupLabel->setAnchorPoint(Point(0.5f, 0.5f));
//	auto groupInfoText = patch::to_string(waveCounter + 1);
//	groupLabel->setString(groupInfoText);
//	spritetool->addChild(groupLabel);*/
//
//	/*groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
//	groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2, spritetool->getContentSize().height / 2));
//	groupTotalLabel->setAnchorPoint(Point(0.5f, 0.5f));
//	auto groupTotalText = patch::to_string(groupTotal);
//	groupTotalLabel->setString(groupTotalText);
//	spritetool->addChild(groupTotalLabel);*/
//
//	// back
//	Sprite* backItem1 = Sprite::createWithSpriteFrameName("playbutton1.png");
//	Sprite* backItem2 = Sprite::createWithSpriteFrameName("playbutton2.png");
//	MenuItemSprite* pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(GameLayer::menuBackCallback, this));
//	pPauseItem->setPosition(Point(spritetool->getContentSize().width - backItem1->getContentSize().width / 2, spritetool->getContentSize().height / 2));
//	pPauseItem->setAnchorPoint(Point(0, 0.4f));
//	Menu* pMenu = Menu::create(pPauseItem, NULL);
//	pMenu->setPosition(Point::ZERO);
//	spritetool->addChild(pMenu);
//}

// 退出按钮
void GameLayer::menuBackCallback(Ref* pSender)
{
	// 播放音效
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("Music/button.mp3").c_str(), false);

	// 在这里实现文件读取，缓存关卡


	instance->clear();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, Menusys::createScene()));
}

// 获取当前波次
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

// 获取下一波
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

// 加入敌人到波次
// 参数：{{1,2),{2,3},...}
// 解释：第1种敌人添加2个，第2种敌人添加3个，无限长参数
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
//		// 设置索引
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

// 初始化波次
// 在这里编辑出场的敌人
//void GameLayer::initWave()
//{
//	// 第一波
//	// 随机出现3种敌人
//	GameLayer::addWaveEnemy({ {rand() % 3 + 1,1},{rand() % 3 + 1,1}, {rand() % 3 + 1,1} });
//
//	// 第二波
//    // 随机出现3种敌人，每种敌人2个
//	GameLayer::addWaveEnemy({ {rand() % 3 + 1,2},{rand() % 3 + 1,2}, {rand() % 3 + 1,2} });
//
//	// 第三波
//    // 出现敌人1,2,3，每种敌人1个
//	GameLayer::addWaveEnemy({ {1,1},{2,1}, {3,1} });
//
//	// 第四波，第五波...
//}

// 加入敌人到场景
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
//		// 波次之间停的稍微长一点
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
//	//* 在这里面创建敌人 *//
//	//********************//
//	////////////////////////
//	if (et.count > 0 && et.type == 1) {
//		// 入场音效
//		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
//		// 创建第一种敌人，血量500
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

// 游戏逻辑
// 每两秒不停跑这个
void GameLayer::logic(float dt)
{
	//Wave* groupEnemy = this->currentWave();

	//if (groupEnemy == NULL)
	//{
	//	// 2023年12月22日23点52分 赵明泽
	//	// 写到这里了
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

//　僵尸吃掉了你的脑子
void GameLayer::enemyIntoHouse()
{
	auto enemyVector = instance->enemyVector;
	for (int i = 0; i < enemyVector.size(); i++)
	{

		// 逻辑：敌人走到最后一个点并且有血
		// 设置敌人胜利
		// 蓝点-1
		// 等大家把敌人坐标判断搞出来，把下面这段释放


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

// 秦始皇摸电门——赢麻了
void GameLayer::YingZhengTouchesTheElectricSwitch()
{
	/*if (this->blue > 0 && this->currentWave() == NULL)
	{
		this->isSuccessful = true;
	}*/

	if (isSuccessful)
	{
		// 不知道用意
		isSuccessful = false;

		// 评选星级
		//auto star = this->getBlue();
		// 
		//auto star = 0;
		//auto remainBlue = this->getBlue();

		//if (remainBlue > 0 && remainBlue <= 1) { star = 1; }
		//else if (remainBlue > 1 && remainBlue <= 2) { star = 2; }
		//else if (remainBlue > 60 && remainBlue <= 100) { star = 3; }

		// 下一关
		// 不这样做，退回主界面
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

// 手指放到屏幕上
//bool GameLayer::onTouchBegan(Touch* touch, Event* event)
//{
//	this->removeChild(chooseTowerpanel);
//	chooseTowerpanel = NULL;
//	auto location = touch->getLocation();
//
//	checkAndAddTowerPanle(location);
//	return true;
//}

// 跳出选塔栏
//void GameLayer::addTowerChoosePanel(Point point)
//{
//	chooseTowerpanel = GameSprite::create();
//	chooseTowerpanel->setPosition(point);
//	this->addChild(chooseTowerpanel);
//}

// 转换成瓦片坐标
//Point GameLayer::convertTotileCoord(Point position)
//{
//	int x = (position.x + offX) / map->getContentSize().width * map->getMapSize().width;
//	int y = map->getMapSize().height - position.y / map->getContentSize().height * map->getMapSize().height;
//	return Point(x, y);
//}

// 转换成矩阵坐标
// 改完之后应该不需要了
//Point GameLayer::convertToMatrixCoord(Point position)
//{
//	int x = (position.x + offX) / map->getContentSize().width * map->getMapSize().width;
//	int y = position.y / map->getContentSize().height * map->getMapSize().height;
//	return Point(x, y);
//}

// 检查位置，放置干员
//void GameLayer::checkAndAddTowerPanle(Point position)
//{
//	// 干员瓦片坐标
//	Point towerCoord = convertTotileCoord(position);
//	// 矩阵坐标
//	Point matrixCoord = convertToMatrixCoord(position);
//
//	// 获取瓦片的GID
//	int gid = bgLayer->getTileGIDAt(towerCoord);
//
//	// 在map里面根据GID搜索物品
//	auto tmp_value = map->getPropertiesForGID(gid);
//	//　不是合适的放置位置
//	if (tmp_value.getType() != Value::Type::MAP)
//	{
//		return;
//	}
//	//　获取放置位置的那个瓦片
//	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
//	//　矩阵坐标，
//	//　废了，不用
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

//　买干员
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

//　旧版子弹碰撞检测
//　这里要大改，适配明日方舟的攻击逻辑
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

//　每帧都执行这个
//void GameLayer::update(float dt)
//{
//	//addTower();
//	//CollisionDetection();
//	enemyIntoHouse();
//	YingZhengTouchesTheElectricSwitch();
//
//	// 金钱
//}

