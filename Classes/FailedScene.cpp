#include "FailedScene.h"

//传入一个renderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
Scene* Failed::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	Failed* layer = Failed::create();
	scene->addChild(layer, 1);//游戏层

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	//得到窗口的大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_spr->setOpacity(180);
	back_spr->setFlippedY(1);            //翻转
	scene->addChild(back_spr);


	return scene;
}

bool Failed::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Failed.mp3");
	auto audio_battle = SimpleAudioEngine::getInstance();
	if (!audio_battle->isBackgroundMusicPlaying()) {
		audio_battle->playBackgroundMusic("Music/Failed.mp3", false);
	}


	MenuItemImage* Failed = MenuItemImage::create("Pictures/Failed.png", "Pictures/Failed.png", CC_CALLBACK_1(Failed::menuLogin, this));
	Failed->setScale(2.5f);

	Menu* pMenu = Menu::create(Failed, NULL, NULL);
	pMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	pMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pMenu, 2);
	return true;
}


void Failed::menuLogin(Ref* pSender)
{
	Scene* scene = Menusys::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}