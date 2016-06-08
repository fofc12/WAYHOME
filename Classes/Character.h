#pragma once

#include "WHPublic.h"

#define IS_MOVING		1
#define IS_JUMPING		(1<<1)
#define IS_DROPPING		(1<<2)
#define BAN_JUMP		(1<<4)
#define BAN_MOVE		(1<<5)

#define MOVE_TAG			10
#define JUMP_TAG			12
#define JUMPSEQ_TAG			11
#define	DROP_TAG			13

class Character:public cocos2d::Node
{
	cocos2d::Sprite* m_sprite;
	int _jumpCnt;
	//bool m_canJump;
	Animate* mDieAnimate;

	void initSprite();

public :
	int _state;

	CREATE_FUNC(Character);

	virtual bool init() override;

	Sprite* getSprite()
	{
		return m_sprite;
	}

	int getState()
	{
		return _state;
	}

	void setState(int state)
	{
		_state = state;
	}

	void setTexture(std::string s);

	Size getSpriteSize()
	{
		return m_sprite->getContentSize();
	}

	//void setFlagTrue(int flag){stateFlag=0;stateFlag|=flag;}
	//void setFlagFalse(int flag){stateFlag=0;stateFlag&=~flag;}
	//void runActionWithFlag(Action *action,int flag);
	void setCanJump(bool t)
	{
		if (t)BIT_OFF(_state, BAN_JUMP); else
		{
			BIT_ON(_state, BAN_JUMP);
		}
	}

	void setCanMove(bool t)
	{
		if (t)BIT_OFF(_state, BAN_MOVE); else
		{
			BIT_ON(_state, BAN_MOVE);
		}
	}

	void resetJump()
	{
		_jumpCnt = 0;
	}

	void resetTo(Vec2 pos);

	void move(Vec2 dir);
	void jump();
	void drop();
	void die();
	void remove();
};
