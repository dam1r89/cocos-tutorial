#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an aut orelease object
    auto layer = HelloWorld::create();
    
    auto world = scene->getPhysicsWorld();
    
    world->setDebugDrawMask(1);
    
    layer->setPhysicsWorld(world);
    
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto director = Director::getInstance();
    Size visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();

    
    this->schedule(schedule_selector(HelloWorld::update));
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    
    auto edgeBoxBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(visibleSize/2);
    edgeNode->setPhysicsBody(edgeBoxBody);
    
    addChild(edgeNode);
    
    sprite = Sprite::create("Dino.png");
    sprite->setPosition(50, 50);

    this->addChild(sprite, 0);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegin, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnd, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);
    
    audioEngine = SimpleAudioEngine::getInstance();
    
    audioEngine->preloadEffect("Call.wav");
    
    
    return true;
}

void HelloWorld::update(float delta){
    timeSinceLastShot += delta;
    if (isShooting && timeSinceLastShot > 1){
        timeSinceLastShot = 0;
        
        auto ball = Sprite::create("Ball.png");
        
        ball->setPosition(sprite->getPosition());
    
        
    
        auto body  = PhysicsBody::createCircle(ball->getContentSize().width / 2);
        body->addMass(500);
        body->setVelocity(Vec2(500,500));
        ball->setPhysicsBody(body);
        
        
        
//        ball->runAction(JumpBy::create(1, Vec2(500,0), 200, 1));
        
        this->addChild(ball);

    }
    
    
}

bool HelloWorld::touchBegin(cocos2d::Touch *touch, cocos2d::Event *event){
    isShooting = true;
    
    return true;
}

void HelloWorld::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event){
    isShooting = false;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
