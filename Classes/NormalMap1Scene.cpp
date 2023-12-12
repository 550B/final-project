/*���ƶ�2151422
2023.12.12
��ͨ�ؿ���ͼ������·���㣨��δ����*/
#include "NormalMap1Scene.h"

USING_NS_CC;

Scene* NormalMap1::createScene()
{
    auto scene = Scene::create();
    auto layer = NormalMap1::create();
    scene->addChild(layer);
    return scene;
}
TMXTiledMap* NormalMap1::createMap()
{
    //�����ͼ����
    TMXTiledMap* map = TMXTiledMap::create("normalmap1.tmx");
    return map;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapScene1.cpp\n");
}

// on "init" you need to initialize your instance
bool NormalMap1::init()
{
   
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    //�����ͼ����
    TMXTiledMap* map = createMap();
    //ͼ���
    auto  layer_normalmap = map->getLayer("normalmap1");
    layer_normalmap->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    layer_normalmap->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //�����
    TMXObjectGroup* objects = map->getObjectGroup("road");
    this->addChild(map, 0);


    return true;
}



