#include "GanYuanShield.h"

USING_NS_CC;
//����һ����װ
bool GanYuanShield::init()
{
    if (!GanYuanBase::init("Pictures/snake.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // ��ʼ��GanYuanShield���������Ժ���Ϊ
    this->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));//����Shield��Ƴ���x���ķ�֮һ����y��
    this->setScale(0.4);
    setDefaultData();//����Ĭ��ֵ
    initial();
    return true;
}


GanYuanShield* GanYuanShield::create()
{
    GanYuanShield* shield = new GanYuanShield();
    if (shield && shield->init())
    {
        shield->autorelease();
        return shield;
    }
    CC_SAFE_DELETE(shield);
    return nullptr;
}

void GanYuanShield::setDefaultData() {
    // �趨��װĬ����ֵ
    scope = ShieldScope;
    setLethality(ShieldLethality);   // ɱ����
    setHp(ShieldHp);  // ���Ѫ��
    setHealth(ShieldHp);  // ��ǰѪ��
    setBlock(ShieldBlock);  //�赲��
    setCurBlock(0);  //�Ѿ��赲��*/
    setDefence(ShieldDefence);  // ������
    setAlive(true);//�Ƿ���Ȼ����
    setIntervalTime(ShieldIntervalTime);//�������ʱ��
    setCoolTime(ShieldCoolTime);//������ȴʱ��;
    setFirstPose(Vec2(getPosition()));
}
void GanYuanShield::initial()
{
    //�����Ļ�ĳ�ʼ��
    if (!gameStart) {//ֻҪ��Ϸ��û��ʼ���Ϳ�����ק�ø�Ա�ϳ�
        //firstInteract();
        moveToPosition();
    }
}
//���λ�úϷ�
void GanYuanShield:: positionLegal(bool& state) {
    for (int i = 0; i < towers_path.size(); i++) {
        if (this->getPosition() == towers_path[i])//ȷ������װ�ɵ���λ��
        {
            state = true;
            break;
        }
    }
    state=false;
}