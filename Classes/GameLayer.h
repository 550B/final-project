#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include <iostream>
#include <initializer_list>
#include "cocos2d.h"
//#include "Enemy.h"
//#include "GanYuanMedical.h"
#include "GanYuanShield.h"
#include "GanYuanShooter.h"
#include "GameManager.h"
#include "Menu.h"
#include "Bullet.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d::ui;
#include "Gamepause.h"
USING_NS_CC;

// �������࣬���ֵ��˵�����
struct EnemyType
{
    int type;
    int count;
};

class GameLayer : public Layer
{
public:

    GameLayer();

    //��������
    static cocos2d::Scene* createScene();


    virtual bool init() override;
    CREATE_FUNC(GameLayer);

   
    virtual void update(float dt) override;
    //virtual bool onTouchBegan(Touch* touch, Event* event) override;

    //Wave* currentWave();
    //Wave* nextWave();
    //void addWaveEnemy(std::initializer_list<EnemyType> il);
    //void initWave();
     void updatemoney(float dt);
     void logic(float dt);
     void bulletFlying();
    //void initLabelText();

protected://��Ϊprojected

    float interval;

    SpriteBatchNode* spriteSheet;
    TMXTiledMap* map;//��ͼ
    TMXLayer* bgLayer;//������
    TMXObjectGroup* towers;//����
    TMXObjectGroup* grounds;//����
    std::vector<Vec2> towers_path;
    std::vector<Vec2> grounds_path;


    GameManager* instance;
    float offX;

    int waveCounter;
    int money;
    Label* moneyLabel;
    Label* groupLabel;
    Label* groupTotalLabel;
    Layer* toolLayer;

    Sprite* sprite_money;//���ͼ��
    Sprite* star3;//3��ͼ��
    Sprite* star2;//2��ͼ��
    Sprite* star1;//1��ͼ��
    Sprite* star0;//0��ͼ��
    void initToolLayer();

    CC_SYNTHESIZE(int, blue, Blue);

    // ����Ҫ�ؿ�Ѫ��
    //CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
    bool isSuccessful;

    bool isTouchEnable;
    //GameSprite* chooseTowerpanel;
    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
    Point convertToMatrixCoord(Point position);
    void checkAndAddTowerPanle(Point position);
    void CollisionDetection();

    void menuBackCallback(Ref* pSender);

    Point towerPos;
    void initPointsVector(float offX);
    void addSceneEnemy();
    //void addTower();
    //GanYuanBase** towerMatrix;

    // to judge whether win or lose
    // win
    void YingZhengTouchesTheElectricSwitch();

    // lose
    void enemyIntoHouse();
};

#endif /* defined(_GAME_LAYER_H_) */