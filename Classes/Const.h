#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include "cocos2d.h"
USING_NS_CC;

#define FRAMES_PER_SECOND 60

#define ShieldScope 50
#define ShieldLethality 193
#define ShieldHp 1221
#define ShieldBlock 3
#define ShieldDefence 249
#define ShieldIntervalTime 1.2
#define ShieldCoolTime 60

#define ShooterScope 50
#define ShooterLethality 337
#define ShooterHp 709
#define ShooterBlock 0
#define ShooterDefence 79
#define ShooterIntervalTime 1.6
#define ShooterCoolTime 70

//class GanYuanBase;

enum Emode
{
	normal,
	hard,
	biandui,
};

//һЩȫ�ֱ�����������ȫ�ֿɲٿص�
//Emode mode;//ģʽ
//Scene* gameScene;//��ǰ������hard/normal��ͼ��
//bool gameStart = false;//�Ƿ���Ϸ�Ѿ���ʼ����,����Ѿ��������Աѡ���ǲ��ܼ����ģ���ʼ�뷨����ư�ť�ɾ�����ʼ

#endif // !Constant_H