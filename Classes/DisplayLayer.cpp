#include "DisplayLayer.h"

bool DisplayLayer::init()
{
	//super init first
	if (!Layer::init()){ return false; }
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	lbl = Label::createWithTTF("Select Level","fonts/Marker Felt.ttf",32);
	lbl->setColor(Color3B::GRAY);
	lbl->setPosition(DESIGN_W/2, DESIGN_H-32);
	this->addChild(lbl);
	
	//this->schedule(schedule_selector(GameLayer::onUpdate));

	return true;
}

void DisplayLayer::setTitle(string t)
{
	m_title = t;
	lbl->setString(t);
}