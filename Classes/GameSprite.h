#ifndef _GAME_SPRITE_H_
#define _GAME_SPRITE_H_

#include <iostream>
#include "cocos2d.h"
#include "GanYuanBase.h"

USING_NS_CC;

typedef enum
{
    ARROW_TOWER = 0,
    ATTACK_TOWER = 1,
    MULTIDIR_TOWER,
    ANOTHER
} TowerType;

class GameSprite : public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(GameSprite);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

    CC_SYNTHESIZE(TowerType, chooseTowerType, ChooseTowerType);

private:

    Sprite* sprite1;
    Sprite* sprite2;
    Sprite* sprite3;
};


#endif /* defined(_GAME_SPRITE_H_) */