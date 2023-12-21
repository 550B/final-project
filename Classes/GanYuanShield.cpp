#include "GanYuanShield.h"

USING_NS_CC;
//创建一个重装
bool GanYuanShield::init()
{
    if (!GanYuanBase::init("Pictures/snake.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 初始化GanYuanShield的其他属性和行为
    this->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 4));//对于Shield设计成在x的四分之一处，y的
    this->setScale(0.4);
    setDefaultData();//设置默认值
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
    // 设定重装默认数值
    scope = ShieldScope;
    setLethality(ShieldLethality);   // 杀伤力
    setHp(ShieldHp);  // 最大血量
    setHealth(ShieldHp);  // 当前血量
    setBlock(ShieldBlock);  //阻挡数
    setCurBlock(0);  //已经阻挡数*/
    setDefence(ShieldDefence);  // 防御力
    setAlive(true);//是否仍然活着
    setIntervalTime(ShieldIntervalTime);//攻击间隔时间
    setCoolTime(ShieldCoolTime);//死亡冷却时间;
    setFirstPose(Vec2(getPosition()));
}
void GanYuanShield::initial()
{
    //完成屏幕的初始化
    if (!gameStart) {//只要游戏还没开始，就可以拖拽该干员上场
        //firstInteract();
        moveToPosition();
    }
}
//检查位置合法
void GanYuanShield:: positionLegal(bool& state) {
    for (int i = 0; i < towers_path.size(); i++) {
        if (this->getPosition() == towers_path[i])//确定是重装可到达位置
        {
            state = true;
            break;
        }
    }
    state=false;
}