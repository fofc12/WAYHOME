#include "ControlLayer.h"

#include "GameLayer.h"
#include "MainLayer.h"
#include "VKCodes.h"
//USING_NS_CC;

using namespace wayhome;

using namespace cocos2d::ui;
namespace cui = cocos2d::ui;
using namespace cocostudio;

//extern GameLayer *g_gameLayer;
//extern PlayerLayer *g_playerLayer;
bool ControlLayer::init()
{
	//m_btnLeft=m_btnRight=false;
	m_cmd = 0;
	//setTouchEnabled(true);
	//setTouchMode(kCCTouchesOneByOne); 
	//ControlUI
	auto ControlUI = CSLoader::createNode(CTL_SC_PATH);
	this->addChild(ControlUI,-1);

	auto btnJ = static_cast<Button *>(ControlUI->getChildByName("btnJump"));
	//btnJ->addTouchEventListener( this, toucheventselector(ControlLayer::BtnJClick));
	btnJ->addTouchEventListener(CC_CALLBACK_2(ControlLayer::BtnClick,this));
	auto btnL = static_cast<Button *>(ControlUI->getChildByName("btnLeft"));
	btnL->addTouchEventListener(CC_CALLBACK_2(ControlLayer::BtnClick,this));
	auto btnR = static_cast<Button *>(ControlUI->getChildByName("btnRight"));
	btnR->addTouchEventListener(CC_CALLBACK_2(ControlLayer::BtnClick,this));
	auto btnS = static_cast<Button *>(ControlUI->getChildByName("btnSkill"));
	btnS->addTouchEventListener(CC_CALLBACK_2(ControlLayer::BtnClick,this));

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	this->schedule(schedule_selector(ControlLayer::keyboardMapping));
#endif
	return true;
}


void ControlLayer::BtnClick(cocos2d::Ref* pSender, Widget::TouchEventType touchType)
{
	GameLayer * gameLayer = (dynamic_cast<MainLayer *>(this->getParent()))->getGameLayer();
	if (static_cast<Button *>(pSender)->getName() == "btnSkill")
	{
		gameLayer->restart();
	}
	if (!m_can_ctrl)return;
	
	//GameLayer *gameLayer=MainLayer::getInstance()->getGameLayer();
	if(static_cast<Button *>(pSender)->getName()=="btnJump")
	{
		//log("btnJump");
		//gameLayer->getPlayerLayer()->characterJump();
		BTN_SWITCH(CMD_JUMP);
	}
	else if(static_cast<Button *>(pSender)->getName()=="btnLeft")
	{
		//log("btnLeft");
		//gameLayer->getPlayerLayer()->characterMove(Vec2(-1,0));
		//BTN_SWITCH(m_btnLeft);
		BTN_SWITCH(CMD_LEFT);
	}
	else if(static_cast<Button *>(pSender)->getName()=="btnRight")
	{
		//log("btnRight");
		//gameLayer->getPlayerLayer()->characterMove(Vec2(1,0));
		//BTN_SWITCH(m_btnRight);
		BTN_SWITCH(CMD_RIGHT);
	}
	//else 
}

//¼üÅÌÓ³Éäº¯Êý
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void ControlLayer::keyboardMapping(float dt)
{
	if (KEY_DOWN(VK_UP)){}
	if (KEY_UP(VK_UP)){}

	if (KEY_DOWN(VK_DOWN)){}
	if (KEY_UP(VK_DOWN)){}

	if (KEY_DOWN(VK_LEFT)){CMD_ON(CMD_LEFT);}
	if (KEY_UP(VK_LEFT)){CMD_OFF(CMD_LEFT);}

	if (KEY_DOWN(VK_RIGHT)){CMD_ON(CMD_RIGHT);}
	if (KEY_UP(VK_RIGHT)){CMD_OFF(CMD_RIGHT);}

	if (KEY_DOWN(VK_SPACE))		{CMD_ON(CMD_JUMP);}
	if (KEY_UP(VK_SPACE))		{CMD_OFF(CMD_JUMP);}
}
#endif