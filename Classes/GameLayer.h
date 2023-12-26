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
    ~GameLayer();

    //��������
    static cocos2d::Scene* createScene();


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
    ProgressTimer* playHpBar;//������
    Sprite* star3;//3��ͼ��
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
    void enemyIntoHouse();
    void menuCallback(Ref* pSender);
    void menuBackCallback(Ref* pSender);

    Point towerPos;
    void initPointsVector(float offX);
    void addSceneEnemy();
    void addTower();
    GanYuanBase** towerMatrix;

    // �ж���Ӯ
    void YingZhengTouchesTheElectricSwitch();

};

#endif /* defined(_GAME_LAYER_H_) */