#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
//#include <initializer_list>
#include "cocos2d.h"
//#include "Enemy.h"
//#include "GanYuanMedical.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GameManager.h"

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

    //创建瓦片地图
    static cocos2d::TMXTiledMap* createMap();

    virtual bool init() override;
    CREATE_FUNC(GameLayer);

    //virtual void update(float dt) override;
    //virtual bool onTouchBegan(Touch* touch, Event* event) override;

    //Wave* currentWave();
    //Wave* nextWave();
    //void addWaveEnemy(std::initializer_list<EnemyType> il);
    //void initWave();
    void logic(float dt);
    //void initLabelText();

private:

    float interval;

    SpriteBatchNode* spriteSheet;
    TMXTiledMap* map;
    TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;

    GameManager* instance;
    float offX;

    int waveCounter;
    int money;

    Label* moneyLabel;
    Label* groupLabel;
    Label* groupTotalLabel;
    Layer* toolLayer;
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