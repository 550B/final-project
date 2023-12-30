#ifndef _GAN_YUAN_SHIELD_H_
#define _GAN_YUAN_SHIELD_H_
/*
   CC_SYNTHESIZE(int, scope, Scope);  // �������߷�Χ
   CC_SYNTHESIZE(int, lethality, Lethality);   // ɱ����
   CC_SYNTHESIZE(float, hp, Hp);  // ���Ѫ��
   CC_SYNTHESIZE(float, health, Health);  // ��ǰѪ��*/
#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
class GanYuanBase;

class GanYuanShield : public GanYuanBase
{
public:

    CC_SYNTHESIZE(int, block, Block);  //�赲��
    CC_SYNTHESIZE(int, curBlock, CurBlock);  //�Ѿ��赲��
    //base������
    
    //��ɳ�ʼ��
    //��ʼ����
    CC_SYNTHESIZE(Animation*, attackAnimation, AttackAnimation);//����ʱ�Ķ���
    CC_SYNTHESIZE(Animation*, bigMoveAnimation, BigMoveAnimation);//����ʱ�Ķ���

   
    
    bool init();
    static GanYuanShield* create();//������̬create����
    virtual void setDefaultData();//����Ĭ����ֵ
    virtual void positionLegal(bool& state, Vec2& p);;//��ǰλ���Ƿ�Ϸ�
    virtual void initial();//��ʼ��
    virtual void weaponCallback(Ref* sender);

    
    //��ɳ�ʼ��������������ֵ��ʼ���Լ�������ʼ��
    void shoot();//����
    void bigMove();//�Ƿ�ﵽ����
    void castBigMove();//���Ŵ���
    //��ȴ״̬
    bool beingCool();//��ȴ״̬������ʾ���Լ��˳���ȴ״̬
    //reset
    bool reset();//��ȴ������

private:
    void updateHealth(float delta);//����Ѫ��
    void updateLethality(float delta);//����ɱ�����������ͷţ�
    void updatDefence(float delta);//���·����������ܼӳɣ�

    Sprite* ganyuanShield;

};

#endif /* defined(_GAN_YUAN_SHIELD_H_) */