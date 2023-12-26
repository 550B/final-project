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
    //背景滚动界面
    ScrollView* scrollView = ScrollView::create();

    ChooseMap(scrollView);
    //返回按钮
    reMenu();
    //插入关卡按钮
    ChooseNmap(scrollView);
    
    return true;
}
void MapChoose::ChooseMap(ScrollView* scrollView) {
    //水平滚动
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    //开启触摸事件
    scrollView->setTouchEnabled(true);
    //设置内容大小
    scrollView->setContentSize(Director::getInstance()->getVisibleSize());
    //隐藏滚动条
    scrollView->setScrollBarEnabled(false);
    this->addChild(scrollView);
    //创建背景地图(按住左键进行拖动)
    Sprite* imageView = nullptr;
    string filePath;
    float nextPosX = 0.f;
    //延长图片：first1280*720 second580*720
    for (int i = 1; i < 3; i++)
    {
        filePath = "Pictures/Normapchoose" + to_string(i) + ".png";
        imageView = Sprite::create(filePath);
        //长宽放大2倍
        imageView->setScale(2);
        //更改锚点位置是因为地图跟前面的地图宽度不一致
        imageView->setAnchorPoint(Vec2(0, 0.5));
        imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
        nextPosX += imageView->getContentSize().width * 2;//地图总长度
        scrollView->addChild(imageView, 0);
    }
    //设置ScrollView的布局容器大小
    scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));
}

void MapChoose::reMenu() {
    //返回主菜单
    auto layer = Layer::create();
    this->addChild(layer);
    //该背景图始终在屏幕的左上角(单独layer）
    Sprite* back_pic = Sprite::create("Pictures/back64.png");
    back_pic->setAnchorPoint(Vec2(0, 1));
    back_pic->setPosition(0, Director::getInstance()->getVisibleSize().height);
    layer->addChild(back_pic);

    //系统bgm
    auto audio_menu = SimpleAudioEngine::getInstance();
    if (!audio_menu->isBackgroundMusicPlaying()) {
        audio_menu->playBackgroundMusic("Music/m_choose.mp3", true);
    }
    auto offMusic = MenuItemImage::create("Pictures/stopMusic.png", "Pictures/stopMusic.png");
    auto onMusic = MenuItemImage::create("Pictures/continueMusic.png", "Pictures/continueMusic.png");

    //展示不同按钮状态（开关音乐）
    MenuItemToggle* MusicMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapChoose::MenuMusicCallBack, this), onMusic, offMusic, NULL);
    auto Menu_Music = Menu::create(MusicMenu, NULL);
    Menu_Music->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    Menu_Music->setPosition(Vec2(1221, 661));
    this->addChild(Menu_Music, 1);

    //创建背景图精灵的子节点
    string back_y = "Pictures/back_n.png";
    string back_n = "Pictures/back_y.png";
    Button* back = Button::create(back_n, back_y, "");//表示一个正常状态，一个选择状态，一个不可点击状态
    back->setScale(0.125);//缩小8倍
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(Vec2(8, 10));
    back->setPressedActionEnabled(true);
    back_pic->addChild(back);
    //增加触摸事件 弹出该场景
    back->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Scene* scene = Menusys::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
        }
     });

}

void MapChoose::ChooseNmap(ScrollView* scrollView)
{
    TMXTiledMap* map = TMXTiledMap::create("ChooseNmap.tmx");
    //获取瓦片地图中的对象层
    TMXObjectGroup* objectGroup = map->getObjectGroup("Nmaps");
    //将对象层中的所有对象获取出来
    ValueVector objs = objectGroup->getObjects();
    
    //按钮
    Button* button;
    //文件名
    string Normap_n, Normap_y;
    for (int i = 1; i <= (int)objs.size()-1; i++)
    {
        Normap_n = "Pictures/Normap" + to_string(i) + "_n.png";
        Normap_y = "Pictures/Normap" + to_string(i) + "_y.png";
        //根据瓦片地图中位置坐标信息配置关卡按钮
        button = Button::create(Normap_n, Normap_y,"");
        scrollView->addChild(button,10, i);//i表示tag
       
        ValueMap valueMap = objs[i].asValueMap(); //获得属性值：Value转换成ValueMap
        //按钮的位置坐标
        button->setPosition(Vec2(valueMap["x"].asFloat(),valueMap["y"].asFloat()));//获取对象的属性:(as一类的方法 （转换类型）
        //设置按钮Tag，实际上就是当前关卡数，索引从1开始
        button->setTag(i);
        button->setScale(0.70f);
        //触摸事件监听器
        if (i == 1) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED)
            {
                SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
                Scene* scene = NormalMap1::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
            }
            });
        }
        else if (i == 2) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED)
                {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
                    Scene* scene = NormalMap2::createScene();
                    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
                }
                });
        }
        else if (i == 3) {
            button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
                if (type == ui::Widget::TouchEventType::ENDED)
                {
                    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止系统bgm
                    Scene* scene = NormalMap3::createScene();
                    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
                }
                });
        }
    }

}

//开关音乐
void  MapChoose::MenuMusicCallBack(Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (audio->isBackgroundMusicPlaying()) {
        audio->pauseBackgroundMusic();
    }
    else {
        audio->resumeBackgroundMusic();
    }
}