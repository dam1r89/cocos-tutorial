//
//  GameSprite.h
//  Tutorial
//
//  Created by Damir on 8/23/14.
//
//

#ifndef __Tutorial__GameSprite__
#define __Tutorial__GameSprite__

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : cocos2d::Sprite{
public:
    CC_SYNTHESIZE(Point, nextPosition, NextPosition);
    CC_SYNTHESIZE(Point, vector, Vector);
    CC_SYNTHESIZE(Touch *, _touch, Touch);
    GameSprite(void);
    ~GameSprite(void);
    
    static GameSprite * gameSpriteWithFile(const char* fileName);
    virtual void setPosition(const cocos2d::Vec2& pos);
    float radius();
};


#endif /* defined(__Tutorial__GameSprite__) */
