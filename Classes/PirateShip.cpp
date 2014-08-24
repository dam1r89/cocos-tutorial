#include "PirateShip.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* PirateShip::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an aut orelease object
	auto layer = PirateShip::create();

	auto world = scene->getPhysicsWorld();
	//world->setDebugDrawMask(world->DEBUGDRAW_ALL);


	world->setGravity(Vec2(0,-300));

	layer->setPhysicsWorld(world);


	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PirateShip::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !LayerColor::initWithColor(Color4B(165,196,243,255)))
	{
		return false;
	}
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();
	isShooting = false;
	timeSinceLastShot = 1;
	this->schedule(schedule_selector(PirateShip::update));

	sea = Sprite::create("sea.png");
	sea2 = Sprite::create("sea.png");
	sea->setAnchorPoint(Vec2(0,0));
	sea2->setAnchorPoint(Vec2(0,0));
	sea->setPosition(0,0);
	sea2->setPosition(sea2->getContentSize().width,0);
	this->addChild(sea);
	this->addChild(sea2);

	sea->runAction(RepeatForever::create(Sequence::create(EaseInOut::create(MoveBy::create(5,Vec2(0,-30)),2),EaseInOut::create(MoveBy::create(5,Vec2(0,30)),2),NULL)));
	sea2->runAction(RepeatForever::create(Sequence::create(EaseInOut::create(MoveBy::create(5,Vec2(0,-30)),2),EaseInOut::create(MoveBy::create(5,Vec2(0,30)),2),NULL)));

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PirateShip::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	sprite = Sprite::create("pirateShip.png");
	sprite->setPosition(100, 100);
	sprite->setAnchorPoint(Vec2(0.2,0));
	sprite->setRotation(20);
	sprite->runAction(RepeatForever::create(Sequence::create(EaseInOut::create(MoveBy::create(2.0,Vec2(0,-40)),2),EaseInOut::create(MoveBy::create(2.0,Vec2(0,40.0)),2),NULL)));
	sprite->runAction(RepeatForever::create(Sequence::create(EaseInOut::create(RotateBy::create(2.0,-40.0),2),EaseInOut::create(RotateBy::create(2.0,40.0),2),NULL)));


	this->addChild(sprite, 0);



	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(PirateShip::touchBegin, this);
	listener->onTouchEnded = CC_CALLBACK_2(PirateShip::touchEnd, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	audioEngine = SimpleAudioEngine::getInstance();

	audioEngine->preloadEffect("Call.wav");


	return true;
}

void PirateShip::update(float delta){

	//OVO TREBA DA SE URADI SA PARALLAX BACKGROUND, NE SA DVA SPRAJTA JADNO.
	//Nazalost, nakon podosta guglanja, nisam nasao kako, al sam nasao tutorijal od onog naseg vec poznatog drugara koji je uradio sa dva sprajta
	//pa reko jebes ga, kasno je, uradicu i ja sa dva sprajta. Oprostite mi moje grijehe
	sea->setPositionX(sea->getPositionX() - 100*delta);
	sea2->setPositionX(sea2->getPositionX() - 100*delta);
	if (sea->getPositionX() < - sea->getContentSize().width)
		sea->setPositionX(sea->getContentSize().width);
	if (sea2->getPositionX() < - sea2->getContentSize().width)
		sea2->setPositionX(sea2->getContentSize().width);


	//Ni ovaj deo nije mnogo bolji. Basically, na osnovu ugla broda moramo da proracunamo i x y poziciju iz koje izlazi kugla
	//kako se brod rotira oko tacke koja je levo i dole, top se znacajno pomera.
	//Takodje proracunavamo vector koji dodeljujemo kugli na osnovu rotacije broda
	//sve je zbudzeno, naravno.
	timeSinceLastShot += delta;
	if (isShooting && timeSinceLastShot > 0.4){
		timeSinceLastShot = 0;

		auto ball = Sprite::create("Ball.png");
		ball->setScale(0.4);
		ball->setOpacity(0);
		ball->runAction(FadeIn::create(0.06));

		auto body = PhysicsBody::createCircle(12.5,PHYSICSBODY_MATERIAL_DEFAULT,Vec2::ZERO);

		auto angleRadian = (sprite->getRotation() * 2) * (3.1415 / 180); // * 2 da bi akcentovali promenu ugla, sam brod se ne rotira dovoljno da pokrije narocito veliki spektar uglova za pucanje

		auto ballPosAngleRadian = ((sprite->getRotation() * -1) * (3.1415 / 180))  + 0.338; // 0.338 je u radianima ugao izmedju anchora broda i pozicije gde je top

		auto ballPosX = sprite->getPosition().x + cos(ballPosAngleRadian) * 276; // a 276 je udaljenost od anchora do topa
		auto ballPosY = sprite->getPosition().y + sin(ballPosAngleRadian) * 276;

		auto vecx = cos(angleRadian);
		auto vecy = -sin(angleRadian);


		ball->setPosition(Vec2(ballPosX,ballPosY));		
		body->setVelocity(Vec2(vecx,vecy)*550);

		ball->setPhysicsBody(body);

		this->addChild(ball);

	}


}

bool PirateShip::touchBegin(cocos2d::Touch *touch, cocos2d::Event *event){
	isShooting = true;

	return true;
}

void PirateShip::touchEnd(cocos2d::Touch *touch, cocos2d::Event *event){
	isShooting = false;
}

void PirateShip::menuCloseCallback(Ref* pSender)
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
