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

    //������Ƭ��ͼ
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