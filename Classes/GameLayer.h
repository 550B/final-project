#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"
#include "GanYuanMedical.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GameSprite.h"
#include "GameManager.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:

    GameLayer();
    ~GameLayer();

    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(GameLayer);

    virtual void update(float dt) override;
    virtual bool onTouchBegan(Touch* touch, Event* event) override;

    Wave* currentWave();
    Wave* nextWave();
    void addWaveEnemy();
    void logic(float dt);
    void initLabelText();

private:

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
    CC_SYNTHESIZE(float, playHpPercentage, PlayHpPercentage);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
    bool isSuccessful;

    bool isTouchEnable;
    GameSprite* chooseTowerpanel;
    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
    Point convertToMatrixCoord(Point position);
    void checkAndAddTowerPanle(Point position);
    void CollisionDetection();
    void enemyIntoHouse();
    void menuBackCallback(Ref* pSender);

    Point towerPos;
    void initPointsVector(float offX);
    void addEnemy();
    void addTower();
    GanYuanBase** towerMatrix;

};

#endif /* defined(_GAME_LAYER_H_) */