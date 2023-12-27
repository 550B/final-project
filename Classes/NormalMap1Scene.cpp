#include "NormalMap1Scene.h"

USING_NS_CC;

Scene* NormalMap1::createScene()
{
    auto scene = Scene::create();
    auto layer = NormalMap1::create();
    scene->addChild(layer);
    auto spr = GanYuanShield::create();
    scene->addChild(spr);
    return scene;
}
TMXTiledMap* NormalMap1::createMap()
{
    //载入地图背景
    TMXTiledMap* map = TMXTiledMap::create("normalmap1.tmx");
    return map;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in  NormalMapScene1.cpp\n");
}

// on "init" you need to initialize your instance
bool NormalMap1::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //载入地图背景
    map = createMap();
    //图块层
    bgLayer = map->getLayer("normalmap1");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //对象层
    road = map->getObjectGroup("road");
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");
    this->addChild(map, 0);

    // 添加按钮
    GameLayer::init();

    //将tower,ground，road的Vec2数组初始化
    ValueVector rvalues = road->getObjects();
    for (Value value : rvalues)
    {
        ValueMap valueMap = value.asValueMap();//获得属性值：Value转换成ValueMap       
        road_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//将路径点保存到路径中
    }

    instance->roadsPosition.push_back(road_path);

    ValueVector tvalues = towers->getObjects();
    for (Value value : tvalues)
    {
        ValueMap valueMap = value.asValueMap();//获得属性值：Value转换成ValueMap       
        towers_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//将路径点保存到路径中
    }
    ValueVector gvalues = grounds->getObjects();
    for (Value value : gvalues)
    {
        ValueMap valueMap = value.asValueMap();//获得属性值：Value转换成ValueMap       
        grounds_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//将路径点保存到路径中
    }

    
    //创建第一个敌人
    Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    enemy_ground->setScale(0.125);
    enemy_ground->setPosition(Vec2(road_path[0].x + road_path[0].z/2, road_path[0].y + road_path[0].w / 2));
    this->addChild(enemy_ground);
    
    //存储动画
    Vector<FiniteTimeAction*> actions;

    for (int i = 1; i < (int)road_path.size(); i++)//遍历其他路径点
    {

    
        float lenth = sqrtf((road_path[i - 1].x - road_path[i].x)* (road_path[i - 1].x - road_path[i].x)+(road_path[i - 1].y - road_path[i].y)* (road_path[i - 1].y - road_path[i].y));//后一个减去前一个地址，再取得长度
        MoveTo* moveTo = MoveTo::create(lenth / 100, Vec2(road_path[i].x + road_path[i].z / 2, road_path[i].y + road_path[i].w / 2));//匀速
        actions.pushBack(moveTo);//动画加入到顺序表中

    }

    Sequence* seqAct = Sequence::create(actions);//组成序列动作
    enemy_ground->runAction(seqAct);//执行动画

    
    

    return true;
}



