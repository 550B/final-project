#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
#include <initializer_list>
#include <unordered_set>
#include <cmath>
#include "cocos2d.h"
#include "Enemy.h"
#include "GanYuanMedical.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GanYuanBase.h"
#include "GameManager.h"
#include "Menu.h"
#include "Bullet.h"
#include "Wave.h"
#include "Const.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;
using namespace cocos2d::utils;
#include "Gamepause.h"
USING_NS_CC;

class GameLayer : public Layer
{
public:
    GanYuanShield* shield;
    GanYuanShooter* shooter;
    GanYuanMedical* medical;
    GameLayer();

    static cocos2d::Scene* createScene();

    // type of this map
    int mapType;

    virtual bool init() override;
    CREATE_FUNC(GameLayer);

    float startTime;
    float getNowTime() const;
    float getInterval(float a, float b) const;
   
    virtual void update(float dt) override;
    //virtual bool onTouchBegan(Touch* touch, Event* event) override;

    int totalEnemies;

    Vector<Wave*> waveQ;
    void addSceneEnemy(float dt);
    bool allWavesSuccessful();
    void addWaveEnemy(float showtime, std::initializer_list<EnemyType> il);
    void initWave();
    Wave* findEarliestWave();
    void logic();
    void runEnemies();
    void runmedical();
    void updatemoney(float dt);

    void bulletFlying(float dt);
    void removeBullet(Bullet* pSender);
    //void initLabelText();

protected:

    float interval;

    SpriteBatchNode* spriteSheet;
    TMXTiledMap* map;
    TMXLayer* bgLayer;
    TMXObjectGroup* towers;
    TMXObjectGroup* grounds;
    std::vector<Vec2> towers_path;
    std::vector<Vec2> grounds_path;


    float offX;

    int waveCounter;


    int moneyL;
    int star;
    Label* moneyLabel;
    Label* groupLabel;
    Label* groupTotalLabel;
    Layer* toolLayer;

    Sprite* sprite_money;
    Sprite* star3;
    Sprite* star2;
    Sprite* star1;
    Sprite* star0;
    void initToolLayer();

    bool isTouchEnable;
    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
    Point convertToMatrixCoord(Point position);
    void checkAndAddTowerPanle(Point position);
    void CollisionDetection();

    void menuBackCallback(Ref* pSender);

    Point towerPos;

    // to judge whether win or lose
    // win
    void win();

    // lose
    void lose();
};

#endif /* defined(_GAME_LAYER_H_) */