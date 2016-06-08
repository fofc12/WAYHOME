#pragma once 

#include "WHPublic.h"
#include "Character.h"

class PlayerLayer:public cocos2d::Layer
{
	Character *m_mainCh;
	//float chX,chY;
	//string chTexture;Vec2 chSpawnPoint;

public:
	CREATE_FUNC(PlayerLayer);
	static PlayerLayer* create(std::string,Vec2);
	virtual bool init();

	Character *getCh(){return m_mainCh;}
	//float getChX(){return m_ch->getPositionX();}
	////void setChX(float x){chX=x;}
	//float getChY(){return m_ch->getPositionY();}
	////void setChY(float y){chY=y;}
	//Size getChSize(){return m_ch->getContentSize();}
	////void setChW(int x){chX=x;}
	//int getChH(){return m_ch->getContentSize().height;}
	////void setChY(int y){chY=y;}
	//int getChW(){return m_ch->getContentSize().width;}
	//int getChFlag(){ return  m_ch->getFlag(); }
	//void setChFlag(int flag){ return  m_ch->setFlagTrue(flag); }
	//void removeChFlag(int flag){ return  m_ch->setFlagFalse(flag); }

	
	void chMove(cocos2d::Vec2 dir);
	void chJump();
};