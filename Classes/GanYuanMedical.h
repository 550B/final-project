#ifndef _GAN_YUAN_MEDICAL_H_
#define _GAN_YUAN_MEDICAL_H_

#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
USING_NS_CC;
class GanYuanBase;

class GanYuanMedical :public GanYuanBase
{
public:

    virtual bool init();

    CREATE_FUNC(GanYuanMedical);


    //��ɳ�ʼ��
       //��ʼ����
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//����ʱ�Ķ���
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//����ʱ�Ķ���


    void initial();
    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void positionLegal(bool& state, Vec2& p);;//��ǰλ���Ƿ�Ϸ�

    //void firstInteract();//��ʼ����������ѡ����קȥ����λ�ò���
    //virtual void moveToPosition();//��ʼ��ק

    //��ɳ�ʼ��������������ֵ��ʼ���Լ�������ʼ��
    //void shoot();//����
    //bool bigMove();//�Ƿ�ﵽ����

    void castBigMove();//���Ŵ���
    //��ȴ״̬
    bool beingCool();//��ȴ״̬������ʾ���Լ��˳���ȴ״̬
    //reset
    bool reset();//��ȴ������

    void setTowerRect(std::vector<Rect> vec) {
        this->towerRectVec = vec;
    }

private:
    void updateHealth(float delta);//����Ѫ��
    void updateLethality(float delta);//����ɱ�����������ͷţ�
    void updatDefence(float delta);//���·����������ܼӳɣ�

    Rect getCurTowerRect(Point touchP);

    std::vector<Rect> towerRectVec;
    Rect curTowerRect;
    Point originPos;

};

#endif 