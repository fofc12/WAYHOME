#pragma once 

#include "cocos2d.h"

//#include "WHPublic.h"
#include "ControlLayer.h"
#include "GameLayer.h"
#include "DisplayLayer.h"

#define GM_LYR_Z	0
#define CTL_LYR_Z	1


//OBJ_TAG_BLOCK

class MainLayer:public cocos2d::Layer
{	
	//int m_time;
	ControlLayer	*m_controlLayer;
 	wayhome::GameLayer		*m_gameLayer;
	DisplayLayer	*m_displayLayer;
	bool first = true;

	
	int timeEsp ;
	void onUpdate( float dt );
	/*static MainLayer *instance;*/
public:
	CREATE_FUNC(MainLayer);
	virtual bool init();

	CC_SYNTHESIZE(int, m_time, Time);
	ControlLayer	*getControlLayer(){return m_controlLayer;}
	wayhome::GameLayer		*getGameLayer(){return m_gameLayer;}
	DisplayLayer		*getDisplayLayer(){ return m_displayLayer; }

	void CloudTimerCallBack(float dt);
	void CloudMoveDoneCallBack(cocos2d::Node *sprite);
	
	void checkVer();
	void checkVerDone(cocos2d::Node *sender, void *data);
	/*static MainLayer *getInstance();*/
};