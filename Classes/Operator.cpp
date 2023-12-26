#include"Operator.h"

USING_NS_CC;


Scene* OperatorFormation::createScene()
{
    auto scene = Scene::create();
    auto layer = OperatorFormation::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Operator.cpp\n");
}

// on "init" you need to initialize your instance
bool OperatorFormation::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
    //载入菜单背景图（最底层）
    auto sprite = Sprite::create("Pictures/Operator_scene.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

    //系统bgm
    auto audio_menu = SimpleAudioEngine::getInstance();
    if (!audio_menu->isBackgroundMusicPlaying()) {
        audio_menu->playBackgroundMusic("Music/Operator.mp3", true);
    }
   //返回按钮、音乐开关
    reMenu();

    Role();

    return true;
}
void OperatorFormation::Role() {
    auto Shield_pic = MenuItemImage::create("Pictures/Shield.png", "Pictures/Shield.png");
    MenuItemToggle* Shield_item = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OperatorFormation::Shield, this), Shield_pic, Shield_pic, NULL);
    auto Shield = Menu::create(Shield_item, NULL);
    Shield->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    Shield->setScale(0.5);
    Shield->setPosition(Vec2(visibleSize.width / 6.00 + origin.x, 300 + origin.y));
    Shield->setTag(1);
    this->addChild(Shield, 1);

    auto Shooter_pic = MenuItemImage::create("Pictures/Shooter.png", "Pictures/Shooter.png");
    MenuItemToggle* Shooter_item = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OperatorFormation::Shooter, this), Shooter_pic, Shooter_pic, NULL);
    auto Shooter = Menu::create(Shooter_item, NULL);
    Shooter->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    Shooter->setScale(0.25);
    Shooter->setPosition(Vec2(visibleSize.width / 6.00 + origin.x + 450, 300 + origin.y));
    Shooter->setTag(2);
    this->addChild(Shooter, 1);

    auto Medical_pic = MenuItemImage::create("Pictures/Medical.png", "Pictures/Medical.png");
    MenuItemToggle* Medical_item = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OperatorFormation::Medical, this), Medical_pic, Medical_pic, NULL);
    auto Medical = Menu::create(Medical_item, NULL);
    Medical->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    Medical->setScale(0.25);
    Medical->setPosition(Vec2(visibleSize.width / 6.00 + origin.x + 800, 300 + origin.y));
    Medical->setTag(3);
    this->addChild(Medical, 1);
}
void OperatorFormation::reMenu() {
    //返回主菜单
    auto layer = Layer::create();
    this->addChild(layer);

    //创建背景图精灵的子节点
    string back_y = "Pictures/back_n.png";
    string back_n = "Pictures/back_y.png";
    Button* back = Button::create(back_n, back_y, "");//表示一个正常状态，一个选择状态，一个不可点击状态
    back->setScale(0.125);//缩小8倍
    back->setAnchorPoint(Vec2(0, 1));
    back->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
    back->setPressedActionEnabled(true);
    layer->addChild(back);
    //增加触摸事件 弹出该场景
    back->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
            Scene* scene = Menusys::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
        }
        });

    auto offMusic = MenuItemImage::create("Pictures/stopMusic.png", "Pictures/stopMusic.png");
    auto onMusic = MenuItemImage::create("Pictures/continueMusic.png", "Pictures/continueMusic.png");

    //展示不同按钮状态（开关音乐）
    MenuItemToggle* MusicMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(OperatorFormation::MenuMusicCallBack, this), onMusic, offMusic, NULL);
    auto Menu_Music = Menu::create(MusicMenu, NULL);
    Menu_Music->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    Menu_Music->setPosition(Vec2(1221, 661));
    this->addChild(Menu_Music, 1);
}
void OperatorFormation::MenuMusicCallBack(Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (audio->isBackgroundMusicPlaying()) {
        audio->pauseBackgroundMusic();
    }
    else {
        audio->resumeBackgroundMusic();
    }
}
void OperatorFormation::Shield(Ref* pSender) {
    onButtonEffect();
    this->removeChildByTag(1);
    this->removeChildByTag(2);
    this->removeChildByTag(3);
    Sprite* Shield = Sprite::create("Pictures/Shield_.png");
    Shield->setScale(0.5);
    Shield->setPosition(Vec2(visibleSize.width / 2.00 + origin.x, visibleSize.height / 2.00+origin.y));
    this->addChild(Shield, 1);
}
void OperatorFormation::Shooter(Ref* pSender) {
    onButtonEffect();
    this->removeChildByTag(1);
    this->removeChildByTag(2);
    this->removeChildByTag(3);
    Sprite* Shooter = Sprite::create("Pictures/Shooter_.png");
    Shooter->setScale(0.5);
    Shooter->setPosition(Vec2(visibleSize.width / 2.00 + origin.x, visibleSize.height / 2.00 + origin.y));
    this->addChild(Shooter, 1);
}
void OperatorFormation::Medical(Ref* pSender) {
    onButtonEffect();
    this->removeChildByTag(1);
    this->removeChildByTag(2);
    this->removeChildByTag(3);
    Sprite* Medical = Sprite::create("Pictures/Medical_.png");
    Medical ->setScale(0.5);
    Medical ->setPosition(Vec2(visibleSize.width / 2.00 + origin.x, visibleSize.height / 2.00 + origin.y));
    this->addChild(Medical, 1);
}
void OperatorFormation::onButtonEffect()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/button.mp3", false); //false表示不循环
}