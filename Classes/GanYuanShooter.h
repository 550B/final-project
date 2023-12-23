#ifndef _GAN_YUAN_SHOOTER_H_
#define _GAN_YUAN_SHOOTER_H_

#include "cocos2d.h"
USING_NS_CC;

class GanYuanShooter :public cocos2d::Sprite
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
    void setDefaultData();//����Ĭ����ֵ
    void firstInteract();//��ʼ����������ѡ����קȥ����λ�ò���
    void moveToPosition();//��ʼ��ק
    
    //��ɳ�ʼ��������������ֵ��ʼ���Լ�������ʼ��
    bool attack();//����
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