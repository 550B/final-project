#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
#include <initializer_list>
#include "cocos2d.h"
//#include "Enemy.h"
//#include "GanYuanMedical.h"
#include "GanYuanShield.h"
//#include "GanYuanShooter.h"
//#include "GameSprite.h"
#include "GameManager.h"
#include "cocos2d.h"
#include "Menu.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;
#include "Gamepause.h"
USING_NS_CC;

// 敌人种类，这种敌人的数量
struct EnemyType
{
    int type;
    int count;
};

class GameLayer : public Layer
{
public:

    GameLayer();
    ~GameLayer();

    //创建场景
    static cocos2d::Scene* createScene();


    virtual bool init() override;
    CREATE_FUNC(GameLayer);

   
    //virtual void update(float dt) override;
    //virtual bool onTouchBegan(Touch* touch, Event* event) override;

    //Wave* currentWave();
    //Wave* nextWave();
    //void addWaveEnemy(std::initializer_list<EnemyType> il);
    //void initWave();
     void updatemoney(float dt);
     void logic(float dt);
    //void initLabelText();

protected://改为projected

    float interval;

    SpriteBatchNode* spriteSheet;
    TMXTiledMap* map;//地图
    TMXLayer* bgLayer;//背景层
    TMXObjectGroup* towers;//箱子
    TMXObjectGroup* grounds;//地面
    std::vector<Vec4> towers_path;
    std::vector<Vec4> grounds_path;


    GameManager* instance;
    float offX;

    int waveCounter;
    int money;
    Label* moneyLabel;
    Label* groupLabel;
    Label* groupTotalLabel;
    Layer* toolLayer;

    Sprite* sprite_money;//金币图标
    Sprite* star3;//3星图标
    Sprite* star2;//2星图标
    Sprite* star1;//1星图标
    Sprite* star0;//0星图标
    void initToolLayer();

    CC_SYNTHESIZE(int, blue, Blue);

    // 不需要关卡血条
    //CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
    bool isSuccessful;

    bool isTouchEnable;
    //GameSprite* chooseTowerpanel;
    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
    Point convertToMatrixCoord(Point position);
    void checkAndAddTowerPanle(Point position);
    void CollisionDetection();
    void enemyIntoHouse();
    void menuBackCallback(Ref* pSender);

    Point towerPos;
    void initPointsVector(float offX);
    void addSceneEnemy();
    void addTower();
    GanYuanBase** towerMatrix;

    // 判断输赢
    void YingZhengTouchesTheElectricSwitch();

};

#endif /* defined(_GAME_LAYER_H_) */