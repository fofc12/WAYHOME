#include "Joystick.h"
using namespace std;

Joystick::Joystick()
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Sprite::init() );
		m_pJoystickBg = Sprite::create("JoystickBg.png");//背景
		m_pJoystick = Sprite::create("Joystick.png");//摇杆
		this->addChild(m_pJoystickBg, 0);
		this->addChild(m_pJoystick, 1);
		this->hideJoystick();
		//this->showJoystick();
		m_pJoystickR= m_pJoystickBg->getContentSize().width/2;
		m_pJoystickr= m_pJoystick->getContentSize().width/2;

		//新的API注册这么写
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this); 
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		ret = true;
	} while(0);

	return ret;
}

void Joystick::showJoystick()
{
	//显示摇杆
	m_pJoystick->setVisible(true); 
	m_pJoystickBg->setVisible(true);
}

void Joystick::hideJoystick()
{
	//隐藏摇杆
	//m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	//m_pJoystickBg->setVisible(false);
	m_pJoystickBg->setVisible(true);
}

void Joystick::updateJoystick(Touch* touch)
{
	//更新摇杆状态
	//我用向量来判断
	Vec2 hit = touch->getLocation();
	float distance = start.getDistance(hit);
	Vec2 direction = (hit - start).getNormalized();
	//为了防止摇杆移出摇杆背景
	if(distance < m_pJoystickr/2)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}else if(distance >m_pJoystickr) {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr));
	}else {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr/2));
	}

	global->hero->onMove(direction,distance);
}


void Joystick::onTouchesBegan(const vector<Touch*>& touches, Event *unused_event)
{
	//按下事件处理
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if(m_pJoystick->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->showJoystick();
		updateJoystick(touch);
		CCLOG("***************");
		CCLOG("update touch:%f %f",touch->getLocation().x,touch->getLocation().y);

		return;
	}
}

void Joystick::onTouchesMoved(const vector<Touch*>& touches, Event *unused_event)
{
	//移动时处理
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if(m_pJoystick->isVisible())
	{
		updateJoystick(touch);
		return;
	}
}

void Joystick::onTouchesEnded(const vector<Touch*>& touches, Event *unused_event)
{
	//离开是处理
	//m_pJoystick->runAction(MoveTo::create(0.08f,start));
	//m_pJoystick->setPosition(start);
	global->hero->onStop();
	this->hideJoystick();

}
void Joystick::setJoystick(Vec2 point)
{
	//将这个摇杆的放在某个坐标上
	start =point;
	m_pJoystickBg->setPosition(start);
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
}
