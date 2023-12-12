/*ÎäÜÆ¶ä2151422
2023.12.12
À§ÄÑ¹Ø¿¨ÌùÍ¼¡¢µĞÈËÂ·¾¶µã£¨»¹Î´´¦Àí£©*/
#include "HardMap1Scene.h"

USING_NS_CC;

Scene* HardMap1::createScene()
{
    auto scene = Scene::create();
    auto layer = HardMap1::create();
    scene->addChild(layer);
    return scene;
}
TMXTiledMap* HardMap1::createMap()
{
    //ÔØÈëµØÍ¼±³¾°
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

    //ÔØÈëµØÍ¼±³¾°
    TMXTiledMap* map = createMap();
    //Í¼¿é²ã
    auto  layer_normalmap = map->getLayer("hardmap1");
    layer_normalmap->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    layer_normalmap->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //¶ÔÏó²ã
    TMXObjectGroup* objects = map->getObjectGroup("road");
    this->addChild(map, 0);


    return true;
}


