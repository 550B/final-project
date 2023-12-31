#ifndef __BAR_H__
#define __BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

enum EStateType
{
	Lethality,//ɱ����
	Health,//Ѫ��
	Defence//������
};

class Bar :public ui::LoadingBar
{
	CC_SYNTHESIZE(EStateType, stateType, StateType);//����
	CC_SYNTHESIZE(int, maxState, MaxState);//���ֵ
	CC_SYNTHESIZE(int, currentState, CurrentState);//��ǰ״̬

public:
	Sprite* background;
	virtual bool init(EStateType stateType, int defaultState);
	static Bar* create(EStateType stateType, int defaultState);
	virtual void ifRecover(float delta);//�жϵ�ǰ�Ƿ���Ҫ���»���
	virtual void changeMaxBy(float delta);//�޸����ֵby,Ĭ���޸ĺ�ͬʱ�޸�currentstate
	virtual void changeMaxTo(int newMax);//�޸����ֵTo
	virtual void changeStateBy(float delta);//�޸����ڵ�ֵby�ȶ�����
	virtual void updatePercent();//�޸İٷֱ�
};

#endif