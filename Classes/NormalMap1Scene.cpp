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
    //�����ͼ����
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
    //�����ͼ����
    map = createMap();
    //ͼ���
    bgLayer = map->getLayer("normalmap1");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //�����
    road = map->getObjectGroup("road");
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");
    this->addChild(map, 0);

    // ��Ӱ�ť
    GameLayer::init();

    //��tower,ground��road��Vec2�����ʼ��
    ValueVector rvalues = road->getObjects();
    for (Value value : rvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        road_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//��·���㱣�浽·����
    }

    instance->roadsPosition.push_back(road_path);

    ValueVector tvalues = towers->getObjects();
    for (Value value : tvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        towers_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//��·���㱣�浽·����
    }
    ValueVector gvalues = grounds->getObjects();
    for (Value value : gvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        grounds_path.push_back(Vec4(valueMap["x"].asFloat(), valueMap["y"].asFloat(), valueMap["width"].asFloat(), valueMap["height"].asFloat()));//��·���㱣�浽·����
    }

    
    //������һ������
    Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    enemy_ground->setScale(0.125);
    enemy_ground->setPosition(Vec2(road_path[0].x + road_path[0].z/2, road_path[0].y + road_path[0].w / 2));
    this->addChild(enemy_ground);
    
    //�洢����
    Vector<FiniteTimeAction*> actions;

    for (int i = 1; i < (int)road_path.size(); i++)//��������·����
    {

    
        float lenth = sqrtf((road_path[i - 1].x - road_path[i].x)* (road_path[i - 1].x - road_path[i].x)+(road_path[i - 1].y - road_path[i].y)* (road_path[i - 1].y - road_path[i].y));//��һ����ȥǰһ����ַ����ȡ�ó���
        MoveTo* moveTo = MoveTo::create(lenth / 100, Vec2(road_path[i].x + road_path[i].z / 2, road_path[i].y + road_path[i].w / 2));//����
        actions.pushBack(moveTo);//�������뵽˳�����

    }

    Sequence* seqAct = Sequence::create(actions);//������ж���
    enemy_ground->runAction(seqAct);//ִ�ж���

    
    

    return true;
}



