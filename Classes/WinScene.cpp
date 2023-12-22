#include "WinScene.h"
#include "Menu.h"

USING_NS_CC;


Scene* WinScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WinScene::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapScene1.cpp\n");
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ////Ԥ����
    //SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/m_sys.mp3");
    //SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/button.mp3");

    ////����˵�����ͼ����ײ㣩
    //auto sprite = Sprite::create("Menu.jpg");
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //this->addChild(sprite, 0);

    ////ϵͳbgm
    //auto audio_menu = SimpleAudioEngine::getInstance();
    //audio_menu->playBackgroundMusic("Music/m_sys.mp3", true);

    ////1 ��ͨ�ؿ�--Normal
    ////�������� 
    //auto label_normal = Label::createWithSystemFont("NormalMap", "fonts/arial.ttf", 30);
    //auto menuitem_normal = MenuItemLabel::create(label_normal, CC_CALLBACK_1(WinScene::NormalMap, this));

    ////�������˲˵���Ŀ������Ҫ����˵��У�����������Ǵ����˵�
    //auto menu_normal = Menu::create(menuitem_normal, NULL);
    //menu_normal->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y + 175));
    //menu_normal->setColor(Color3B(41, 36, 33));

    //this->addChild(menu_normal);


    ////2 ������ս--Hard
    ////��������
    //auto label_Hard = Label::createWithSystemFont("HardMap", "fonts/arial.ttf", 30);
    //auto menuitem_Hard = MenuItemLabel::create(label_Hard, CC_CALLBACK_1(WinScene::HardMap, this));

    //auto menu_Hard = Menu::create(menuitem_Hard, NULL);
    //menu_Hard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y + 75));
    //menu_Hard->setColor(Color3B(41, 36, 33));

    //this->addChild(menu_Hard);

    //3��Ա��ӡ�Operator
    auto label_Operator = Label::createWithSystemFont("OperatorFormation", "fonts/arial.ttf", 30);
    auto menuitem_Operator = MenuItemLabel::create(label_Operator, CC_CALLBACK_1(WinScene::OperatorFormation, this));

    auto menu_Operator = Menu::create(menuitem_Operator, NULL);
    menu_Operator->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y - 25));
    menu_Operator->setColor(Color3B(41, 36, 33));

    this->addChild(menu_Operator);

    return true;
}
//��ͨ�ؿ�
void WinScene::NormalMap(Ref* pSender)
{
    onButtonEffect();
    //Scene* scene = NormalMap1::createScene();
    ////֮��replace��Ϊpush
    //Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
//������ս
void WinScene::HardMap(Ref* pSender)
{
    onButtonEffect();
    /*Scene* scene = HardMap1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));*/
}
//��Ա���
void WinScene::OperatorFormation(Ref* pSender)
{
    onButtonEffect();
    //Scene* scene = OperatorFormation::createScene();
    //Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
//������Ч
void WinScene::onButtonEffect()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ֹͣϵͳbgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/button.mp3", false); //false��ʾ��ѭ��
}

