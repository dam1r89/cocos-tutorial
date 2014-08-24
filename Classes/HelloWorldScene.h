#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
private:
    bool isShooting;
    cocos2d::PhysicsWorld* world;
    float timeSinceLastShot = 1.0;
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
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float);
};

#endif // __HELLOWORLD_SCENE_H__
