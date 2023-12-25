#include "Bar.h"
#include "cmath"

Bar* Bar::create(EStateType stateType, int defaultState) {
	Bar* bar = new (std::nothrow) Bar;
	if (bar && bar->init(stateType, defaultState))
	{
		bar->autorelease();
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return nullptr;
}
bool Bar::init(EStateType stateType, int defaultState)
{
	if (!LoadingBar::init())
	{
		return false;
	}

	if (stateType == EStateType::Lethality)
	{
		loadTexture("Pictures/orangeBar.png", TextureResType::LOCAL);//杀伤力橘
		setOpacity(200);
	}
	else if (stateType == EStateType::Health)
	{
		loadTexture("Pictures/redBar.png", TextureResType::LOCAL);//血条红
		setOpacity(200);
	}
	else {
		loadTexture("Pictures/blueBar.png", TextureResType::LOCAL);//防御力蓝
		setOpacity(200);
	}
	//设定一些默认值
	setStateType(stateType);
	setMaxState(defaultState);
	setCurrentState(defaultState);
	setPercent(100);
	auto background = Sprite::create("Pictures/blueBar.png");
	auto size = getContentSize();
	background->setPosition(size / 2);
	background->setOpacity(0);
	addChild(background, -1);//初始展示
	_barRenderer->setLocalZOrder(1);
	schedule([=](float dt) {//1秒执行一次recover函数
		ifRecover(dt);
		}, 1.0f, "recover_schedule");

	return true;
}
void Bar::ifRecover(float delta)
{
	if (currentState < maxState && currentState>0)
	{
		changeStateBy(delta);
	}
}
void Bar::changeStateBy(int delta)
{
	if (currentState < 0)//当前state已经没了就直接返回
		return;
	currentState += delta;
	//特判如果超过了max或者小于0
	currentState = std::min(maxState, currentState);
	currentState = std::max(0, currentState);
	updatePercent();
}

void Bar::updatePercent()
{
	setPercent(currentState * 100.0 / maxState);
}
void Bar::changeMaxBy(int delta) {
	setMaxState(maxState + delta);
	if (delta > 0)
	{
		setCurrentState(currentState + delta);
	}
	maxState = std::min(maxState, currentState);
	maxState = std::max(maxState, 0);
	updatePercent();
}
void Bar::changeMaxTo(int newMax)
{
	auto oldMax = maxState;
	setMaxState(newMax);
	setCurrentState(currentState + newMax - oldMax);
	updatePercent();
}