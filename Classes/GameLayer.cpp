#include "GameLayer.h"
#include "ControlLayer.h"
#include "Character.h"
#include "MainLayer.h"
#include "DisplayLayer.h"
using namespace wayhome;
USING_NS_CC;

namespace cui = cocos2d::ui;

bool GameLayer::init()
{

	//super init first
    if ( !Layer::init() ){return false; }
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();	
	
	initMap(STG0_MAP);
	initPlayer();

	schedule(schedule_selector(MainLayer::CloudTimerCallBack), 9.0f, kRepeatForever, 0.1f);

	//注册
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(GameLayer::onContactSeperate, this);
	/*contactListener->onContactPostSolve = [=](PhysicsContact& contact, const PhysicsContactPostSolve &solve)
	{
		//m_player->resetJump();
		auto contactData = contact.getContactData();
		if (contactData->normal.y < -(1e-10))m_player->setCanJump(false);
	};*/
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	//this->schedule(schedule_selector(GameLayer::onUpdate));

	return true;
}

//void GameLayer::onUpdate(float dt){}

void GameLayer::initMap(std::string s)
{
	m_mapLayer = MapLayer::create();
	m_mapLayer->initWithFile(s);

	this->addChild(m_mapLayer, MAP_LYR_Z, TAG_MAP);
}

void GameLayer::initPlayer()
{
	m_player = Character::create();

	//m_player->setTag(TAG_CH);
	m_player->setTexture(CH_IMG);
	//float w = m_player->getSprite()->getContentSize().width;
	//float h = m_player->getSprite()->getContentSize().height;
	m_player->setPosition(m_mapLayer->getObjPoint("spawnPoint"));
	m_player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto playerBody = PhysicsBody::createBox(m_player->getSprite()->getContentSize(), PhysicsMaterial(0.99f, 0.0f, 1.0f));
	playerBody->setCategoryBitmask(0x1);    // 
	playerBody->setContactTestBitmask(0x1); // 
	playerBody->setCollisionBitmask(0x1);   //
	//playerBody->setGravityEnable(false);
	playerBody->setGravityEnable(true);
	m_player->setPhysicsBody(playerBody);

	this->addChild(m_player, PLAYER_LYR_Z, TAG_PLAYER);
}


void GameLayer::restart(){
	this->handleEvent(OBJ_TAG_MENU);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

bool GameLayer::onContactBegin(cocos2d::PhysicsContact& contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (!nodeA || !nodeB)return false;
	auto block = m_player == nodeA ? nodeB : nodeA;
	auto contactData = contact.getContactData();

	
	log("WH:CD %f,%f", contactData->normal.x, contactData->normal.y);
	if (abs(contactData->normal.y - 0)>ZEROF)
	{
		
	}

	if (contactData->normal.y > ZEROF)
	{
		if (extraFlag && (block->getTag() == 233))handleEvent(OBJ_TAG_DP);
		m_player->resetTo(m_player->getPosition());

	}
	if (contactData->normal.y < -ZEROF)
	{
		

		m_player->resetTo(Vec2(m_player->getPositionX(), m_player->getPositionY()-1));
		m_player->setCanJump(false);
	}
	
	handleEvent(block->getTag());//处理作发生的事件
	return true;
}

void GameLayer::onContactSeperate(cocos2d::PhysicsContact& contact) {
	log("WH:Sep");
	auto contactData = contact.getContactData();
	if (!contactData){return;}

	if (abs(contactData->normal.x-0)< ZEROF)
	{
		m_player->resetJump();
	}
	if (contactData->normal.y<ZEROF)
	{
		m_player->setCanJump(true);
	}
}

void GameLayer::handleInput(int cmd)
{
	if (cmd & CMD_LEFT)
	{
		m_player->move(Vec2(-1, 0));
	}
	else if (cmd & CMD_RIGHT)
	{
		m_player->move(Vec2(1, 0));
	}
	if (cmd & CMD_JUMP)
	{
		m_player->jump();
	}
}

void GameLayer::handleEvent(int tag)
{
	MainLayer *mainLayer = dynamic_cast<MainLayer *>(this->getParent());
	DisplayLayer * dl = mainLayer->getDisplayLayer();
	ControlLayer * cl = mainLayer->getControlLayer();
	char temp[10]; string s;

	switch (tag)
	{
	case OBJ_TAG_MENU:
		this->removeChildByTag(TAG_PLAYER);
		this->removeChildByTag(TAG_MAP);
		this->initMap(STG0_MAP);
		this->initPlayer();
		cl->setCanCtrl(true);
		//DisplayLayer * dl = (dynamic_cast<MainLayer *>(this->getParent()))->getDisplayLayer();
		dl->setTitle("Please select a stage");
		break;
	case OBJ_TAG_BLOCK:break;

	case OBJ_TAG_DP:
		//dl->setTitle("Game Over !");
		extraFlag = false;
		sprintf(temp, "%d", mainLayer->getTime()); s = temp;
		dl->setTitle("Game Over! Survive time: " + s);
		m_player->die();
		cl->setCanCtrl(false);
		break;

	case OBJ_TAG_HOME:
		sprintf(temp, "%d", mainLayer->getTime()); s = temp;
		dl->setTitle("Congratulations! Time used: "+s);
		cl->setCanCtrl(false);

		//auto sprite=Sprite::createWithSpriteFrame
		cl->setCanCtrl(false);
		m_player->setTexture("HelloWorld.png");
		m_player->setAnchorPoint(Vec2::ZERO);
		m_player->setPosition(0, 0);

		for (int i = m_player->getPositionX(); i < m_player->getPositionX() + 50; i+=5)
		{
			addNewSpriteAtPosition(Vec2(i, DESIGN_H));
		}
		break;

	case OBJ_TAG_DROP_STONES:
		if (!flag)return; flag = false;
		for (int i = m_player->getPositionX(); i < m_player->getPositionX()+4; i++)
		{
			addNewSpriteAtPosition(Vec2(i,DESIGN_H));
		}
		break;

	case OBJ_TAG_STAGE1:
		extraFlag = false;
		this->removeChildByTag(TAG_PLAYER);
		this->removeChildByTag(TAG_MAP);
		this->initMap(STG1_MAP);
		this->initPlayer();
		//DisplayLayer * dl = (dynamic_cast<MainLayer *>(this->getParent()))->getDisplayLayer();
		dl->setTitle("Stage 1-1");
		break;
	case OBJ_TAG_STAGE2:
		extraFlag = false;
		this->removeChildByTag(TAG_PLAYER);
		this->removeChildByTag(TAG_MAP);
		this->initMap(STG2_MAP);
		this->initPlayer();
		//DisplayLayer * dl = (dynamic_cast<MainLayer *>(this->getParent()))->getDisplayLayer();
		dl->setTitle("Stage 2-1");
		break;
	case OBJ_TAG_STAGE3:
		extraFlag = true;
		this->removeChildByTag(TAG_PLAYER);
		this->removeChildByTag(TAG_MAP);
		this->initMap(STG3_MAP);
		this->initPlayer();
		dl->setTitle("Stage 3-1");
		break;
	}
}


void GameLayer::adjustCamera()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto tm = m_mapLayer->getTileMap();
	int chX = m_player->getPositionX();
	int chY = m_player->getPositionY();
	int chW = m_player->GET_WIDTH;
	int chH = m_player->GET_HEIGHT;

	float x = chX + 0.5*chW - 0.5*Director::getInstance()->getVisibleSize().width;
	if (x<0)x = 0; if (x + visibleSize.width>tm->getContentSize().width) x = tm->getContentSize().width - visibleSize.width;
	float y = chY + 0.5*chH - 0.5*Director::getInstance()->getVisibleSize().height;
	if (y<0)y = 0; if (y + visibleSize.height>tm->getContentSize().height) y = tm->getContentSize().height - visibleSize.height;

	this->setPosition(Vec2(-x, -y));
}

void GameLayer::addNewSpriteAtPosition(Point p)
{
	auto sp = Sprite::create("1.png");
	sp->setTag(233);
	PhysicsBody *body = PhysicsBody::createCircle(sp->getContentSize().width / 2);
	body->setCategoryBitmask(1);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(1);
	sp->setPhysicsBody(body);
	//auto body = PhysicsBody::createBox(Size(33, 33));	
	//sp->setPhysicsBody(body);
	sp->setPosition(p);

	this->addChild(sp);
}

void GameLayer::extraStage()
{
	addNewSpriteAtPosition(Vec2(m_player->getPositionX(), DESIGN_H));
	
}


//void GameLayer::fixCollision()
//{
	//auto p =this->getMapLayer()->getPlayerLayer();
	//if(!isCollidable())return;

	//log("collision!");

//	do
//	{
//		if(ch->getFlag()&CH_LEFT)
//			ch->setPosition(ch->getPositionX()+1,ch->getPositionY());
//		else if(ch->getFlag()&CH_RIGHT)
//			{ch->setPosition(ch->getPositionX()-1,ch->getPositionY());}
//	}while(isCollidable());
//}





bool GameLayer::isCollidable()
{
	return false;
	//Character *ch =this->getMapLayer()->getPlayerLayer()->getCh();
	//auto tm=this->getMapLayer()->getTileMap();
	//return (																	
	//	ch->getPositionX()<=0 || ch->getPositionY()<=0		||							
	//	ch->getPositionX()+ch->getContentSize().width>=tm->getContentSize().width	||	
	//	ch->getPositionY()+ch->getContentSize().height>=tm->getContentSize().height	||		
	//	this->getMapLayer()->isCollidable(ch->getPosition())  ||						
	//	this->getMapLayer()->isCollidable(Vec2(ch->getPosition().x+ch->getContentSize().width,		 
	//		ch->getPosition().y+ch->getContentSize().height))							
	//	) ;
}



