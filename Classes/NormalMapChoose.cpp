#include"NormalMapChoose.h"

USING_NS_CC;


Scene* MapChoose::createScene()
{
    auto scene = Scene::create();
    auto layer = MapChoose::create();
    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in NormalMapChoose.cpp\n");
}

// on "init" you need to initialize your instance
bool MapChoose::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
 
    ScrollView* scrollView = ScrollView::create();

    ChooseMap(scrollView);
  
    reMenu();
 
    ChooseNmap(scrollView);
    
    return true;
}
void MapChoose::ChooseMap(ScrollView* scrollView) {
  
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
  
    scrollView->setTouchEnabled(true);
  
    scrollView->setContentSize(Director::getInstance()->getVisibleSize());
   
    scrollView->setScrollBarEnabled(false);
    this->addChild(scrollView);
  
    Sprite* imageView = nullptr;
    string filePath;
    float nextPosX = 0.f;
   
    for (int i = 1; i < 3; i++)
    {
        filePath = "Pictures/Normapchoose" + to_string(i) + ".png";
        imageView = Sprite::create(filePath);
     
        imageView->setScale(2);
    
        imageView->setAnchorPoint(Vec2(0, 0.5));
        imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
        nextPosX += imageView->getContentSize().width * 2;
        scrollView->addChild(imageView, 0);
    }
   
    scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));
}

void MapChoose::reMenu() {
 
    auto layer = Layer::create();
    this->addChild(layer);
  
    Sprite* back_pic = Sprite::create("Pictures/back64.png");
    back_pic->setAnchorPoint(Vec2(0, 1));
    back_pic->setPosition(0, Director::getInstance()->getVisibleSize().height);
    layer->addChild(back_pic);

    auto audio_menu = SimpleAudioEngine::getInstance();
    if (!audio_menu->isBackgroundMusicPlaying()) {
        audio_menu->playBackgroundMusic("Music/m_choose.mp3", true);
    }
    auto offMusic = MenuItemImage::create("Pictures/stopMusic.png", "Pictures/stopMusic.png");
    auto onMusic = MenuItemImage::create("Pictures/continueMusic.png", "Pictures/continueMusic.png");


    MenuItemToggle* MusicMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapChoose::MenuMusicCallBack, this), onMusic, offMusic, NULL);
    auto Menu_Music = Menu::create(MusicMenu, NULL);
    Menu_Music->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    Menu_Music->setPosition(Vec2(1221, 661));
    this->addChild(Menu_Music, 1);

    string back_y = "Pictures/back_n.png";
    string back_n = "Pictures/back_y.png";
    Button* back = Button::create(back_n, back_y, "");
    back->setScale(0.125);
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(Vec2(8, 10));
    back->setPressedActionEnabled(true);
    back_pic->addChild(back);
  
    back->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Scene* scene = Menusys::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
        }
     });

}

void MapChoose::ChooseNmap(ScrollView* scrollView)
{
    TMXTiledMap* map = TMXTiledMap::create("ChooseNmap.tmx");

    TMXObjectGroup* objectGroup = map->getObjectGroup("Nmaps");
 
    ValueVector objs = objectGroup->getObjects();
    
   
    Button* button;
    
    string Normap_n, Normap_y;
    for (int i = 1; i <= (int)objs.size()-1; i++)
    {
        Normap_n = "Pictures/Normap" + to_string(i) + "_n.png";
        Normap_y = "Pictures/Normap" + to_string(i) + "_y.png";
     
        button = Button::create(Normap_n, Normap_y,"");
        scrollView->addChild(button,10, i);
       
        ValueMap valueMap = objs[i].asValueMap(); 
     
        button->setPosition(Vec2(valueMap["x"].asFloat(),valueMap["y"].asFloat()));
     
        button->setTag(i);
        button->setScale(0.70f);
       
        if (i == 1) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ֹͣϵͳbgm
                Scene* scene = NormalMap1::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
            }
            });
        }
        else if (i == 2) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED)
                {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ֹͣϵͳbgm
                    Scene* scene = NormalMap2::createScene();
                    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
                }
                });
        }
        else if (i == 3) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED)
                {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ֹͣϵͳbgm
                    Scene* scene = NormalMap3::createScene();
                    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
                }
                });
        }
    }

}


void  MapChoose::MenuMusicCallBack(Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (audio->isBackgroundMusicPlaying()) {
        audio->pauseBackgroundMusic();
    }
    else {
        audio->resumeBackgroundMusic();
    }
}