#ifndef __BAR_H__
#define __BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

enum EStateType
{
	Lethality,//杀伤力
	Health,//血量
	Defence//防御力
};

class Bar :public ui::LoadingBar
{
	CC_SYNTHESIZE(EStateType, stateType, StateType);//类型
	CC_SYNTHESIZE(int, maxState, MaxState);//最大值
	CC_SYNTHESIZE(int, currentState, CurrentState);//当前状态

public:
	Sprite* background;
	virtual bool init(EStateType stateType, int defaultState);
	static Bar* create(EStateType stateType, int defaultState);
	virtual void ifRecover(float delta);//判断当前是否需要重新绘制
	virtual void changeMaxBy(float delta);//修改最大值by,默认修改后还同时修改currentstate
	virtual void changeMaxTo(int newMax);//修改最大值To
	virtual void changeStateBy(float delta);//修改现在的值by稳定速率
	virtual void updatePercent();//修改百分比
};

#endif