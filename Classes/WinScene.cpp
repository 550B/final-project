#include "WinScene.h"

//����һ��renderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
Scene* Win::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	Win* layer = Win::create();
	scene->addChild(layer, 1);//��Ϸ��

	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	//����Sprite��ӵ�GamePause��������
	//�õ����ڵĴ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
	back_spr->setOpacity(180);
	back_spr->setFlippedY(1);            //��ת
	scene->addChild(back_spr);


	return scene;
}

bool Win::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/Win.mp3");
	auto audio_battle = SimpleAudioEngine::getInstance();
	if (!audio_battle->isBackgroundMusicPlaying()) {
		audio_battle->playBackgroundMusic("Music/Win.mp3", false);
	}
	
	
	MenuItemImage* win = MenuItemImage::create("Pictures/Win.png", "Pictures/Win.png", CC_CALLBACK_1(Win::menuLogin, this));
	win->setScale(2.5f);

	Menu* pMenu = Menu::create(win,NULL,NULL);
	pMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	pMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(pMenu, 2);
	return true;
}


void Win::menuLogin(Ref* pSender)
{
	Scene* scene = Menusys::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}