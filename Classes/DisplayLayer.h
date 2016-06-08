#pragma once

#include "WHPublic.h"

class DisplayLayer :public cocos2d::Layer
{
	string m_title;
	Label *lbl;
//protected:
	//void onUpdate(float dt);
public:
	CREATE_FUNC(DisplayLayer);
	virtual bool init() override;

	void setTitle(string);
};