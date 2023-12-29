#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
#include <initializer_list>
#include <unordered_set>
#include <cmath>
#include "cocos2d.h"
//#include "Enemy.h"
//#include "GanYuanMedical.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GameManager.h"
#include "Menu.h"
#include "Bullet.h"
#include "Wave.h"
#include "Const.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;
#include "Gamepause.h"
USING_NS_CC;

class GameLayer : public Layer
{
public:
    GameLayer();

    //��������
    static cocos2d::Scene* createScene();


    virtual bool init() override;
    CREATE_FUNC(GameLayer);

    float startTime;
    float getNowTime();
    float getInterval(float a, float b);
   
    virtual void update(float dt) override;
    //virtual bool onTouchBegan(Touch* touch, Event* event) override;

    int totalEnemies;

    std::unordered_set<Wave*> waveQ;
    std::unordered_set<Wave*>::iterator it;
    void addSceneEnemy(float dt);
    bool allWavesSuccessful();
    void addWaveEnemy(float showtime, std::initializer_list<EnemyType> il);
    void initWave();
    Wave* findEarliestWave();
    void logic();

    void updatemoney(float dt);

    void bulletFlying();
    //void initLabelText();
protected://��Ϊprojected

    float interval;

    GameManager* instance;
    GanYuanShield* shield;
    GanYuanShooter* shooter;
   // GanYuanMedical* medical;
    int money;
    SpriteBatchNode* spriteSheet;
    TMXTiledMap* map;//��ͼ
    TMXLayer* bgLayer;//������
    TMXObjectGroup* towers;//����
    TMXObjectGroup* grounds;//����
    std::vector<Vec2> towers_path;
    std::vector<Vec2> grounds_path;


    float offX;

    int waveCounter;


    int money;
    int star;
    Label* moneyLabel;
    Label* groupLabel;
    Label* groupTotalLabel;
    Layer* toolLayer;

    Sprite* sprite_money;//���ͼ��
    Sprite* star3;//3��ͼ��
    Sprite* star2;//2��ͼ��
    Sprite* star1;//1��ͼ��
    Sprite* star0;//0��ͼ��
    int star;
    void initToolLayer();

    CC_SYNTHESIZE(int, blue, Blue);

    // ����Ҫ�ؿ�Ѫ��
    //CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
    bool isSuccessful;

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
    void YingZhengTouchesTheElectricSwitch();

    // lose
    void enemyIntoHouse();
};

#endif /* defined(_GAME_LAYER_H_) */