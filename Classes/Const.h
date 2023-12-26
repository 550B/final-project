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
class GanYuanBase;
enum Emode
{
	normal,
	hard,
	biandui,
};
extern TMXObjectGroup* road;
extern TMXObjectGroup* towers;
extern TMXObjectGroup* grounds;
extern std::vector<Vec2> road_path;
extern std::vector<Vec2> towers_path;
extern std::vector<Vec2> grounds_path;
extern Emode mode;//ģʽ
extern Scene* gameScene;//��ǰ������hard/normal��ͼ��
extern bool gameStart;

#endif // !Constant_H