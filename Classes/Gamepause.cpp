#include "Gamepause.h"

//传入一个renderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
Scene* Gamepause::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	Gamepause* layer = Gamepause::create();
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


	//添加游戏暂停背景小图，用来放按钮
	Sprite* back_small_spr = Sprite::create("Pictures/options.png");
	back_small_spr->setAnchorPoint(Vec2(0.5f, 0.5f));
	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_small_spr->setScale(0.4);
	scene->addChild(back_small_spr);


	return scene;
}

bool Gamepause::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//继续游戏按钮
	MenuItemImage* pContinueItem = MenuItemImage::create(
		"Pictures/Continue.png",
		"Pictures/Continue.png",
		CC_CALLBACK_1(Gamepause::menuContinueCallback, this));
	pContinueItem->setAnchorPoint(Vec2(0.5f, 0.5f));
	pContinueItem->setPosition(Vec2(0, 0+ 30));

	//回主界面
	MenuItemImage* pLoginItem = MenuItemImage::create(
		"Pictures/Giveup.png",
		"Pictures/Giveup.png",
		CC_CALLBACK_1(Gamepause::menuLogin, this));
	pLoginItem->setAnchorPoint(Vec2(0.5f, 0.5f));
	pLoginItem->setScale(1.2);
	pLoginItem->setPosition(Vec2(0, 0- 70));

	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pContinueItem, pLoginItem, NULL);
	pMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pMenu, 2);


	return true;
}
void Gamepause::menuContinueCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->popScene();
}

void  Gamepause::menuLogin(Ref* pSender)
{
	Scene* scene = Menusys::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}