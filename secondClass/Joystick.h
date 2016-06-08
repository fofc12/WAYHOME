#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include "cocos2d.h"
USING_NS_CC; 
#include "Global.h"

class Hero;
class Joystick : public Sprite
{
public:
	Joystick();
	~Joystick();
	virtual bool init();
	virtual	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);	
	void setJoystick(Vec2 point);
	CREATE_FUNC(Joystick);
private:
	void showJoystick();
	void hideJoystick();
	void updateJoystick(Touch* touch);
	int m_pJoystickr;
	int m_pJoystickR;
	Sprite *m_pJoystick;
	Sprite *m_pJoystickBg;
	Vec2 start;
};

#endif