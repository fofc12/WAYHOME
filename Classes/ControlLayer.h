#pragma once

#include "WHPublic.h"

#define CMD_UP			1
#define CMD_DOWN		(1<<1)
#define CMD_LEFT		(1<<2)
#define CMD_RIGHT		(1<<3)
#define CMD_JUMP		(1<<4)
#define CMD_ON(cmd)		(m_cmd |= cmd)
#define CMD_OFF(cmd)	(m_cmd &= ~cmd)
#define BTN_SWITCH(__CMD__) \
	switch(touchType) \
	{ \
		case Widget::TouchEventType::BEGAN: CMD_ON(__CMD__);		break;\
		case Widget::TouchEventType::MOVED:							break;\
		case Widget::TouchEventType::ENDED: CMD_OFF(__CMD__);		break;\
		case Widget::TouchEventType::CANCELED: CMD_OFF(__CMD__);	break;\
	}
/*#define BTN_SWITCH(__BTN__) \
	switch(touchType) \
	{ \
		case Widget::TouchEventType::BEGAN: \
			__BTN__=true; \
			break; \
		case Widget::TouchEventType::MOVED: \
			break; \
		case Widget::TouchEventType::ENDED: \
			__BTN__=false; \
			break; \
		case Widget::TouchEventType::CANCELED: \
			__BTN__=false; \
			break; \
	}*/

//win32平台按键控制部分
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)

//enum EKEY_CODE
//{
//	KEY_KEY_UP = 0x26,  // Up key   
//	KEY_KEY_DOWN = 0x28,  // Down key  
//	KEY_KEY_LEFT = 0x25,  // Left key  
//	KEY_KEY_RIGHT = 0x27,  // Right key  
//
//	VK_BS = 0x08,  // BackSpace key  
//	KEY_KEY_F = 0x46,  // F key  
//
//	KEY_KEY_CODES_COUNT = 0xFF // this is not a key, but the amount of keycodes there are.
//};

#endif


class ControlLayer:public cocos2d::Layer
{
	//ButtonsState bs;
	//bool m_btnLeft,m_btnRight;
	bool m_can_ctrl=true;
	int m_cmd;

protected:
	//void doItButtonCheck(cocos2d::Ref* pSender, cocos2d::ui::TouchEventType type);
	void BtnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType touchType);
	//void uiOutActionDoneCallBack(float dt); 

public:
	CREATE_FUNC(ControlLayer);
	virtual bool init();

	void setCanCtrl(bool b){ m_can_ctrl = b; }

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void keyboardMapping(float);
#endif
	int getCMD(){ return m_cmd; }
	//Input getInput(){Input bs;bs.left=m_btnLeft;bs.right=m_btnRight;return bs;}
};