#include "NormalMap3Scene.h"

USING_NS_CC;

Scene* NormalMap3::createScene()
{
    auto scene = Scene::create();
    auto layer = NormalMap3::create();
    scene->addChild(layer);
    auto spr = GanYuanShield::create();
    scene->addChild(spr);
    return scene;
}
TMXTiledMap* NormalMap3::createMap()
{
    //�����ͼ����
    TMXTiledMap* map = TMXTiledMap::create("normalmap3.tmx");
    return map;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in NormalMapScene3.cpp\n");
}

// on "init" you need to initialize your instance
bool NormalMap3::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //�����ͼ����
    map = createMap();
    //ͼ���
    bgLayer = map->getLayer("normalmap3");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //�����
    aroad = map->getObjectGroup("aroad");
    broad = map->getObjectGroup("broad");
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");
    this->addChild(map, 0);

    // ��Ӱ�ť
    GameLayer::init();


    //��tower,ground��road��Vec2�����ʼ��


    ValueVector rvalues = aroad->getObjects();
    for (Value value : rvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        aroad_path.push_back(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//��·���㱣�浽·����
    }
    ValueVector tvalues = towers->getObjects();
    for (Value value : tvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        towers_path.push_back(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//��·���㱣�浽·����
    }
    ValueVector gvalues = grounds->getObjects();
    for (Value value : gvalues)
    {
        ValueMap valueMap = value.asValueMap();//�������ֵ��Valueת����ValueMap       
        grounds_path.push_back(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//��·���㱣�浽·����
    }


    //������һ������
    Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    enemy_ground->setScale(0.125);
    enemy_ground->setPosition(aroad_path[0]);
    this->addChild(enemy_ground);

    //�洢����
    Vector<FiniteTimeAction*> actions;

    for (int i = 1; i < (int)aroad_path.size(); i++)//��������·����
    {


        float lenth = (aroad_path[i - 1] - aroad_path[i]).getLength();//��һ����ȥǰһ����ַ����ȡ�ó���
        MoveTo* moveTo = MoveTo::create(lenth / 100, aroad_path[i]);//����
        actions.pushBack(moveTo);//�������뵽˳�����

    }

    Sequence* seqAct = Sequence::create(actions);//������ж���
    enemy_ground->runAction(seqAct);//ִ�ж���




    return true;
}