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
    //������������
    ScrollView* scrollView = ScrollView::create();

    ChooseMap(scrollView);
    //���ذ�ť
    reMenu();
    //����ؿ���ť
    ChooseNmap(scrollView);
    
    return true;
}
void MapChoose::ChooseMap(ScrollView* scrollView) {
    //ˮƽ����
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    //���������¼�
    scrollView->setTouchEnabled(true);
    //�������ݴ�С
    scrollView->setContentSize(Director::getInstance()->getVisibleSize());
    //���ع�����
    scrollView->setScrollBarEnabled(false);
    this->addChild(scrollView);
    //����������ͼ(��ס��������϶�)
    Sprite* imageView = nullptr;
    string filePath;
    float nextPosX = 0.f;
    //�ӳ�ͼƬ��first1280*720 second580*720
    for (int i = 1; i < 3; i++)
    {
        filePath = "Pictures/Normapchoose" + to_string(i) + ".png";
        imageView = Sprite::create(filePath);
        //�����Ŵ�2��
        imageView->setScale(2);
        //����ê��λ������Ϊ��ͼ��ǰ��ĵ�ͼ���Ȳ�һ��
        imageView->setAnchorPoint(Vec2(0, 0.5));
        imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
        nextPosX += imageView->getContentSize().width * 2;//��ͼ�ܳ���
        scrollView->addChild(imageView, 0);
    }
    //����ScrollView�Ĳ���������С
    scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));
}

void MapChoose::reMenu() {
    //�������˵�
    auto layer = Layer::create();
    this->addChild(layer);
    //�ñ���ͼʼ������Ļ�����Ͻ�(����layer��
    Sprite* back_pic = Sprite::create("Pictures/back64.png");
    back_pic->setAnchorPoint(Vec2(0, 1));
    back_pic->setPosition(0, Director::getInstance()->getVisibleSize().height);
    layer->addChild(back_pic);

    //ϵͳbgm
    auto audio_menu = SimpleAudioEngine::getInstance();
    if (!audio_menu->isBackgroundMusicPlaying()) {
        audio_menu->playBackgroundMusic("Music/m_choose.mp3", true);
    }
    auto offMusic = MenuItemImage::create("Pictures/stopMusic.png", "Pictures/stopMusic.png");
    auto onMusic = MenuItemImage::create("Pictures/continueMusic.png", "Pictures/continueMusic.png");

    //չʾ��ͬ��ť״̬���������֣�
    MenuItemToggle* MusicMenu = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapChoose::MenuMusicCallBack, this), onMusic, offMusic, NULL);
    auto Menu_Music = Menu::create(MusicMenu, NULL);
    Menu_Music->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    Menu_Music->setPosition(Vec2(1221, 661));
    this->addChild(Menu_Music, 1);

    //��������ͼ������ӽڵ�
    string back_y = "Pictures/back_n.png";
    string back_n = "Pictures/back_y.png";
    Button* back = Button::create(back_n, back_y, "");//��ʾһ������״̬��һ��ѡ��״̬��һ�����ɵ��״̬
    back->setScale(0.125);//��С8��
    back->setAnchorPoint(Vec2(0, 0));
    back->setPosition(Vec2(8, 10));
    back->setPressedActionEnabled(true);
    back_pic->addChild(back);
    //���Ӵ����¼� �����ó���
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
    //��ȡ��Ƭ��ͼ�еĶ����
    TMXObjectGroup* objectGroup = map->getObjectGroup("Nmaps");
    //��������е����ж����ȡ����
    ValueVector objs = objectGroup->getObjects();
    
    //��ť
    Button* button;
    //�ļ���
    string Normap_n, Normap_y;
    for (int i = 1; i <= (int)objs.size()-1; i++)
    {
        Normap_n = "Pictures/Normap" + to_string(i) + "_n.png";
        Normap_y = "Pictures/Normap" + to_string(i) + "_y.png";
        //������Ƭ��ͼ��λ��������Ϣ���ùؿ���ť
        button = Button::create(Normap_n, Normap_y,"");
        scrollView->addChild(button,10, i);//i��ʾtag
       
        ValueMap valueMap = objs[i].asValueMap(); //�������ֵ��Valueת����ValueMap
        //��ť��λ������
        button->setPosition(Vec2(valueMap["x"].asFloat(),valueMap["y"].asFloat()));//��ȡ���������:(asһ��ķ��� ��ת�����ͣ�
        //���ð�ťTag��ʵ���Ͼ��ǵ�ǰ�ؿ�����������1��ʼ
        button->setTag(i);
        button->setScale(0.70f);
        //�����¼�������
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

//��������
void  MapChoose::MenuMusicCallBack(Ref* pSender) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    if (audio->isBackgroundMusicPlaying()) {
        audio->pauseBackgroundMusic();
    }
    else {
        audio->resumeBackgroundMusic();
    }
}