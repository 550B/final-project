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
		loadTexture("Pictures/orangeBar.png", TextureResType::LOCAL);
		setOpacity(200);
	}
	else if (stateType == EStateType::Health)
	{
		loadTexture("Pictures/redBar.png", TextureResType::LOCAL);
		setOpacity(200);
		setPercent(100);
	}
	else {
		loadTexture("Pictures/blueBar.png", TextureResType::LOCAL);
		setOpacity(200);
	}
	
	setStateType(stateType);
	setMaxState(defaultState);
	setCurrentState(defaultState);
	background = Sprite::create("Pictures/grayBar.png");
	auto size = getContentSize();
	background->setPosition(size / 2);
	background->setOpacity(200);
	addChild(background,-1);
	_barRenderer->setLocalZOrder(1);
	schedule([=](float dt) {
		ifRecover(dt);
		}, 1.0f, "recover_schedule");

	return true;
}
void Bar::ifRecover(float delta)
{
	if (currentState <= maxState && currentState>=0)
	{
		changeStateBy(delta);
	}
}
void Bar::changeStateBy(float delta)
{
	if (currentState <= 0)
		return;
	currentState += delta;
	
	currentState = std::min(maxState, currentState);
	currentState = std::max(0, currentState);
	updatePercent();
}

void Bar::updatePercent()
{
	auto tmp = currentState * 100.0 / maxState;
	setPercent(currentState * 100.0 / maxState);
}
void Bar::changeMaxBy(float delta) {
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