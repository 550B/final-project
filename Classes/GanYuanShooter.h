#ifndef _GAN_YUAN_SHOOTER_H_
#define _GAN_YUAN_SHOOTER_H_

#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"

USING_NS_CC;

class GanYuanShooter : public GanYuanBase
{
public:
    CREATE_FUNC(GanYuanShooter); 
    CC_SYNTHESIZE(int, block, Block);  //�赲��
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //�Ѿ��赲��
    //base������
    
    //��ɳ�ʼ��
    //��ʼ����
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//����ʱ�Ķ���
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//����ʱ�Ķ���

    
    void initial();
    bool init();
    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void positionLegal(bool& state, Vec2& p);;//��ǰλ���Ƿ�Ϸ�

    //void firstInteract();//��ʼ����������ѡ����קȥ����λ�ò���
    //virtual void moveToPosition();//��ʼ��ק
    
    //��ɳ�ʼ��������������ֵ��ʼ���Լ�������ʼ��
    void shoot();//����
    bool bigMove();//�Ƿ�ﵽ����

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