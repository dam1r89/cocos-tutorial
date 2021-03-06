#ifndef __PIRATESHIP_SCENE_H__
#define __PIRATESHIP_SCENE_H__
#include "cocos2d.h"

class PirateShip : public cocos2d::LayerColor
{
private:
    bool isShooting;
    cocos2d::PhysicsWorld* world;
    float timeSinceLastShot;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref *pSender);
    
    void setPhysicsWorld(cocos2d::PhysicsWorld *world){
        this->world = world;
    };
    
    bool touchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
    void touchEnd(cocos2d::Touch *touch, cocos2d::Event *event);
    
    CocosDenshion::SimpleAudioEngine *audioEngine;
    cocos2d::Sprite *sprite;
	cocos2d::Sprite *sea;
	cocos2d::Sprite *sea2;
	
    // implement the "static create()" method manually
    CREATE_FUNC(PirateShip);
    
    void update(float);
};

#endif // __PIRATESHIP_SCENE_H__
