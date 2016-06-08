#include "HelloWorldScene.h"

#include "WHPublic.h"
//#include "MapLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//super init first
    if ( !Layer::init() ){return false; }
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();					

	initWelcome();

    return true;
}

void HelloWorld::initWelcome()
{

	Node *rootNode = CSLoader::createNode(LOGO_SC_PATH);//传入Studio2.x的资源路径 
	this->addChild(rootNode);//
	log("read LOGO_SC successfully");

	//加载动画： 
	ActionTimeline *action = CSLoader::createTimeline(LOGO_SC_PATH);
	rootNode->runAction(action);

	//播放动画： 
	//action->gotoFrameAndPlay(0, 10, false);//DEBUG SKIP
	action->gotoFrameAndPlay(0,150,false);//从第0帧到200
	action->setLastFrameCallFunc(CC_CALLBACK_0(HelloWorld::initMainLayer, this));
}

void HelloWorld::initMainLayer() 
{  
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();	

	//创建物理世界场景
	auto scene = Scene::createWithPhysics();
	if(DEBUG_DRAW)scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//auto scene = Scene::create();

	//设置背景颜色
	auto layer = LayerColor::create(Color4B(159, 213, 204, 0xff), visibleSize.width, visibleSize.height);
    scene->addChild(layer, -10);	

	Vect gravity(0, -500.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	m_mainLayer = MainLayer::create();
	scene->addChild(m_mainLayer);
	
	//auto sc=TransitionTurnOffTiles::create(0.5f,scene);
	//auto sc=TransitionMoveInL::create(0.5f,scene);
	auto sc =scene;
	Director::getInstance()->replaceScene(sc);
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

void HelloWorld::menuItemStartCallback(Ref* pSender)
{
	
}

