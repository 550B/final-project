#include "FailedScene.h"

//����һ��renderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
Scene* Failed::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	Failed* layer = Failed::create();
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