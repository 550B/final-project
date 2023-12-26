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


    return true;
}


