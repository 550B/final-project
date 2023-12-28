#include "GanYuanBase.h"
#include "GameManager.h"
GanYuanBase::GanYuanBase() :
	// 赵明泽注释的，理由：请在Actor里赋初始值
	//scope(0)
	//, lethality(0)   // 杀伤力
	//, hp(0)  // 最大血量
	//, health(0) // 当前血量
	//, defence(0)  // 防御力
	//, alive(true)//是否仍然活着
	//, intervalTime(0)//攻击间隔时间
	selected(false)
	, coolTime(0)//死亡冷却时间;
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
//初始化一个干员基类
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
	// 将selectmenu和menu_select保存为成员变量
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

		// 创建一个延迟动作，在5秒后移除提示语
		DelayTime* delay = DelayTime::create(1.0f);
		CallFunc* removeLabel = CallFunc::create([label]() {
			label->removeFromParent();
			});
		// 应用延迟动作到提示语标签
		label->runAction(Sequence::create(delay, removeLabel, nullptr));
	}
	
	//selected = true;
}


// 不选择回调函数
void GanYuanBase::unselectCallback(Ref* sender)
{
	Menu* unselectOption = static_cast<Menu*>(sender);
	unselectOption->setColor(Color3B::RED);

	// 设置布尔值为false
	selected = false;
}
void GanYuanBase::ifmove() {
	//初始化位置
	/*
	while (1) {
		moveToPosition();
		
		
		//state = true;
	}
	this->setPose(getPosition());//记录干员的位置*/
}
void GanYuanBase::moveToPosition() {
	//拖拽部分（借鉴csdn代码）
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	//通过 lambda 表达式 直接实现触摸事件的回掉方法
	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);//点击的时候精灵颜色变暗，255为最大值，9最小return true;
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
		target->setOpacity(255);//手势松开时使精灵恢复原来的颜色
		bool state = false;
		Vec2 p;
		positionLegal(state, p);
		if (!state) {
			// 创建一个标签用于显示提示语
			Label* label = Label::createWithTTF("Position ILLEGAL!", "fonts/arial.ttf", 200);
			label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));;
			label->setColor(Color3B::RED);
			this->addChild(label);

			// 创建一个延迟动作，在5秒后移除提示语
			DelayTime* delay = DelayTime::create(1.0f);
			CallFunc* removeLabel = CallFunc::create([label]() {
				label->removeFromParent();
				});
			// 应用延迟动作到提示语标签
			label->runAction(Sequence::create(delay, removeLabel, nullptr));
			this->setPosition(firstPose);//放置回原来位置

		}
		else {
			//this->setPose(getPosition());
			//this->setPose(p);
			GameManager* instance = GameManager::getInstance();
			this->setPosition(p);
			instance->occupied.push_back(p);
		}
		};
	//将触摸事件绑定到精灵身上
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
}
void GanYuanBase::positionLegal(bool &state, Vec2& p) {  }//当前位置是否合法

