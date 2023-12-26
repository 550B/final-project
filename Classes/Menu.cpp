/*武芷朵2151422
2023.12.12
实现主界面、跳转地图、音乐*/
#include "Menu.h"
#include"NormalMapChoose.h"
#include "HardMap1Scene.h"
#include "GanYuanShield.h"
USING_NS_CC;

Scene* Menusys::createScene()
{
    auto scene = Scene::create();
    auto layer = Menusys::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Menu.cpp\n");
}

// on "init" you need to initialize your instance
bool Menusys::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //预加载
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/m_sys.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/button.mp3");

    //载入菜单背景图（最底层）
    auto sprite = Sprite::create("Pictures/Menu.jpg");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

    //系统bgm
    auto audio_menu = SimpleAudioEngine::getInstance();
    if (!audio_menu->isBackgroundMusicPlaying()) {
        audio_menu->playBackgroundMusic("Music/m_sys.mp3", true);
    }
    auto offMusic = MenuItemImage::create("Pictures/stopMusic.png", "Pictures/stopMusic.png");
    auto onMusic = MenuItemImage::create("Pictures/continueMusic.png", "Pictures/continueMusic.png");

    //展示不同按钮状态（开关音乐）
    MenuItemToggle* MusicMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Menusys::MenuMusicCallBack, this), onMusic, offMusic,NULL );
    auto Menu_Music= Menu::create(MusicMenu, NULL);
    Menu_Music->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    Menu_Music->setPosition(Vec2(1221, 661));
    this->addChild(Menu_Music, 1);

    //1 普通关卡--Normal
    //插入文字 
    auto label_normal = Label::createWithSystemFont("NormalMap", "fonts/arial.ttf", 30);
    auto menuitem_normal = MenuItemLabel::create(label_normal, CC_CALLBACK_1(Menusys::NormalMap, this));

    //创建好了菜单条目，就需要加入菜单中，所以下面就是创建菜单
    auto menu_normal = Menu::create(menuitem_normal, NULL);
    if (menu_normal == nullptr || menu_normal->getContentSize().width <= 0 || menu_normal->getContentSize().height <= 0) {
        problemLoading("'NormalMap'");
    }
    else {
        menu_normal->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y + 175));
        menu_normal->setColor(Color3B(41, 36, 33));

        this->addChild(menu_normal);
    }


    //2 剿灭作战--Hard
    //插入文字
    auto label_Hard = Label::createWithSystemFont("HardMap", "fonts/arial.ttf", 30);
    auto menuitem_Hard = MenuItemLabel::create(label_Hard, CC_CALLBACK_1(Menusys::HardMap, this));

    auto menu_Hard = Menu::create(menuitem_Hard, NULL);
    if (menu_Hard == nullptr || menu_Hard->getContentSize().width <= 0 || menu_Hard->getContentSize().height <= 0) {
        problemLoading("'HardMap'");
    }
    else {
        menu_Hard->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y + 75));
        menu_Hard->setColor(Color3B(41, 36, 33));

        this->addChild(menu_Hard);
    }
    

    //3干员编队—Operator
    auto label_Operator = Label::createWithSystemFont("OperatorFormation", "fonts/arial.ttf", 30);
    auto menuitem_Operator = MenuItemLabel::create(label_Operator, CC_CALLBACK_1(Menusys::OperatorFormation, this));

    auto menu_Operator = Menu::create(menuitem_Operator, NULL);
    if (menu_Operator == nullptr || menu_Operator->getContentSize().width <= 0 || menu_Operator->getContentSize().height <= 0) {
        problemLoading("'OperatorFormation'");
    }
    else {
        menu_Operator->setPosition(Vec2(visibleSize.width / 2 + origin.x + 370, visibleSize.height / 2 + origin.y - 25));
        menu_Operator->setColor(Color3B(41, 36, 33));

        this->addChild(menu_Operator);
    }

    return true;
}
//开关音乐
void Menusys::MenuMusicCallBack(Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (audio->isBackgroundMusicPlaying()) {
        audio->pauseBackgroundMusic();
    }
    else {
        audio->resumeBackgroundMusic();
    }
}
//普通关卡
void Menusys::NormalMap(Ref* pSender)
{
    onButtonEffect();
    Emode mode=normal;//设置全局变量mode
    Scene* scene = MapChoose::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
//剿灭作战
void Menusys::HardMap(Ref* pSender)
{
    onButtonEffect();
    Emode mode = hard;//设置全局变量mode;
    Scene* scene = HardMap1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
//干员编队
void Menusys::OperatorFormation(Ref* pSender)
{
    onButtonEffect();
    Emode mode = biandui;//设置全局变量mode;
    //Scene* scene = OperatorFormation::createScene();
    //Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
//按钮特效
void Menusys::onButtonEffect()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/button.mp3", false); //false表示不循环
}

