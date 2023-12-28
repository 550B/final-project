#include "GanYuanBase.h"
#include "GameManager.h"
GanYuanBase::GanYuanBase() :
	// ������ע�͵ģ����ɣ�����Actor�︳��ʼֵ
	//scope(0)
	//, lethality(0)   // ɱ����
	//, hp(0)  // ���Ѫ��
	//, health(0) // ��ǰѪ��
	//, defence(0)  // ������
	//, alive(true)//�Ƿ���Ȼ����
	//, intervalTime(0)//�������ʱ��
	selected(false)
	, coolTime(0)//������ȴʱ��;
{};
GanYuanBase* GanYuanBase::create(const std::string& filename)
{
	GanYuanBase* Base = new(std::nothrow)GanYuanBase;
	if (Base && Base->init(filename))
	{
		Base->autorelease();
		return Base;
	}
	CC_SAFE_DELETE(Base);
	return nullptr;
}

bool GanYuanBase::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	return true;
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Menu.cpp\n");
}
//��ʼ��һ����Ա����
void GanYuanBase::firstInteract() {
	auto selectmenu = MenuItemImage::create("Pictures/select.jpg", "Pictures/select.jpg", CC_CALLBACK_1(GanYuanBase::selectCallback, this));
	auto menu_select = Menu::create(selectmenu,NULL, NULL);
	if (menu_select == nullptr || menu_select->getContentSize().width <= 0 || menu_select->getContentSize().height <= 0) {
		problemLoading("'select'");
	}
	else {
		menu_select->setPosition(Vec2(-500, 0));
		menu_select->setScale(0.3);
		menu_select->setOpacity(200);
		this->addChild(menu_select);
	}
	// ��selectmenu��menu_select����Ϊ��Ա����
	m_selectMenu = selectmenu;
	m_menuSelect = menu_select;
}
void GanYuanBase::selectCallback(Ref* sender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	GameManager* managerInstance = GameManager::getInstance();
	if (managerInstance->getMoney() > price) {
		this->removeChild(m_selectMenu, true);
		this->removeChild(m_menuSelect, true);
		moveToPosition();
	}
	else {
		Label* label = Label::createWithTTF("MONEY NOT ENOUGH!", "fonts/arial.ttf", 200);
		label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		label->setColor(Color3B::RED);
		this->addChild(label);

		// ����һ���ӳٶ�������5����Ƴ���ʾ��
		DelayTime* delay = DelayTime::create(1.0f);
		CallFunc* removeLabel = CallFunc::create([label]() {
			label->removeFromParent();
			});
		// Ӧ���ӳٶ�������ʾ���ǩ
		label->runAction(Sequence::create(delay, removeLabel, nullptr));
	}
	
	//selected = true;
}


// ��ѡ��ص�����
void GanYuanBase::unselectCallback(Ref* sender)
{
	Menu* unselectOption = static_cast<Menu*>(sender);
	unselectOption->setColor(Color3B::RED);

	// ���ò���ֵΪfalse
	selected = false;
}
void GanYuanBase::ifmove() {
	//��ʼ��λ��
	/*
	while (1) {
		moveToPosition();
		
		
		//state = true;
	}
	this->setPose(getPosition());//��¼��Ա��λ��*/
}
void GanYuanBase::moveToPosition() {
	//��ק���֣����csdn���룩
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	//ͨ�� lambda ���ʽ ֱ��ʵ�ִ����¼��Ļص�����
	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);//�����ʱ������ɫ�䰵��255Ϊ���ֵ��9��Сreturn true;
			return true;
		}
		return false;
		};
	listener1->onTouchMoved = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
		};
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("sprite onTouchesEnded..");
		target->setOpacity(255);//�����ɿ�ʱʹ����ָ�ԭ������ɫ
		bool state = false;
		Vec2 p;
		positionLegal(state, p);
		if (!state) {
			// ����һ����ǩ������ʾ��ʾ��
			Label* label = Label::createWithTTF("Position ILLEGAL!", "fonts/arial.ttf", 200);
			label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));;
			label->setColor(Color3B::RED);
			this->addChild(label);

			// ����һ���ӳٶ�������5����Ƴ���ʾ��
			DelayTime* delay = DelayTime::create(1.0f);
			CallFunc* removeLabel = CallFunc::create([label]() {
				label->removeFromParent();
				});
			// Ӧ���ӳٶ�������ʾ���ǩ
			label->runAction(Sequence::create(delay, removeLabel, nullptr));
			this->setPosition(firstPose);//���û�ԭ��λ��

		}
		else {
			//this->setPose(getPosition());
			//this->setPose(p);
			GameManager* instance = GameManager::getInstance();
			this->setPosition(p);
			instance->occupied.push_back(p);
		}
		};
	//�������¼��󶨵���������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
}
void GanYuanBase::positionLegal(bool &state, Vec2& p) {  }//��ǰλ���Ƿ�Ϸ�

