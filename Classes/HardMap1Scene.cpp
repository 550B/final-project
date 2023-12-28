#include "HardMap1Scene.h"

USING_NS_CC;

Scene* HardMap1::createScene()
{
    auto scene = Scene::create();
    auto layer = HardMap1::create();
    scene->addChild(layer);
    auto spr = GanYuanShield::create();
    scene->addChild(spr);
    return scene;
}
TMXTiledMap* HardMap1::createMap()
{
    //�����ͼ����
    TMXTiledMap* map = TMXTiledMap::create("hardmap1.tmx");
    return map;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapScene1.cpp\n");
}

// on "init" you need to initialize your instance
bool HardMap1::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    //�����ͼ����
    map = createMap();
    //ͼ���
    bgLayer = map->getLayer("hardmap1");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //�����
    aroad = map->getObjectGroup("aroad");
    broad = map->getObjectGroup("broad");
    croad = map->getObjectGroup("croad");
    droad = map->getObjectGroup("droad");//���˻� �����
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");

    this->addChild(map, 0);

    // ���Ӱ�ť
    GameLayer::init();

   ValueVector ravalues = aroad->getObjects();
    for (Value value : ravalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        aroad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }
    ValueVector rbvalues = broad->getObjects();
    for (Value value : rbvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        broad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }
    ValueVector rcvalues = croad->getObjects();
    for (Value value : rcvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        croad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }
    ValueVector rdvalues = droad->getObjects();
    for (Value value : rdvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        droad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }
    instance->roadsPosition.push_back(aroad_path);
    instance->roadsPosition.push_back(broad_path);
    instance->roadsPosition.push_back(croad_path);
    instance->roadsPosition.push_back(droad_path);

    ValueVector tvalues = towers->getObjects();
    for (Value value : tvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        towers_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }

    ValueVector gvalues = grounds->getObjects();
    for (Value value : gvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        grounds_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2));
    }

    instance->towersPosition = towers_path;
    instance->groundsPosition = grounds_path;
    //instance->setMoney(money);//xjy加，使得manager money更新
    //������һ������
    Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    enemy_ground->setScale(0.125);
    enemy_ground->setPosition(aroad_path[0]);
    this->addChild(enemy_ground);

    //�洢����
    Vector<FiniteTimeAction*> actions;

    for (int i = 1; i < (int)aroad_path.size(); i++)//��������·����
    {


        float lenth = (aroad_path[i - 1] - aroad_path[i]).getLength();
        MoveTo* moveTo = MoveTo::create(lenth / 100, aroad_path[i]);
        actions.pushBack(moveTo);//�������뵽˳�����

    }

    Sequence* seqAct = Sequence::create(actions);//������ж���
    enemy_ground->runAction(seqAct);//ִ�ж���


    return true;
}


