#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>
#include "EnemyBase.h"
#include "Const.h"
#include "Bar.h"
#include "cocos2d.h"

USING_NS_CC;

//class EnemyBase;

// �����������������
// ������
class Enemy1 : public EnemyBase
{
public:

    bool init();

    static Enemy1* create();//������̬create����

    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void initial();//��ʼ��

};

// �ڶ��ֵ���
// ������
class Enemy2 : public EnemyBase
{
public:

    bool init();

    static Enemy2* create();//������̬create����

    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void initial();//��ʼ��

};

// �����ֵ���
// ������
class Enemy3 : public EnemyBase
{
public:

    bool init();

    static Enemy3* create();//������̬create����

    virtual void setDefaultData();//����Ĭ����ֵ

    virtual void initial();//��ʼ��

};


#endif /* defined(_ENEMY_H_) */