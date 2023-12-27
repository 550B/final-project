#include "Gamepause.h"

//����һ��renderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
Scene* Gamepause::scene(RenderTexture* sqr)
{
	Scene* scene = Scene::create();
	Gamepause* layer = Gamepause::create();
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


	//�����Ϸ��ͣ����Сͼ�������Ű�ť
	Sprite* back_small_spr = Sprite::create("Pictures/options.png");
	back_small_spr->setAnchorPoint(Vec2(0.5f, 0.5f));
	back_small_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�
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

	//������Ϸ��ť
	MenuItemImage* pContinueItem = MenuItemImage::create(
		"Pictures/Continue.png",
		"Pictures/Continue.png",
		CC_CALLBACK_1(Gamepause::menuContinueCallback, this));
	pContinueItem->setAnchorPoint(Vec2(0.5f, 0.5f));
	pContinueItem->setPosition(Vec2(0, 0+ 30));

	//��������
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