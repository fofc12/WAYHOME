#include "PlayerLayer.h"

PlayerLayer *PlayerLayer::create(string texture,Vec2 p)
{
	PlayerLayer *t=PlayerLayer::create();
	auto ch=Character::create();
	t->m_ch=ch;
	ch->setTag(TAG_CH);
	ch->setPosition(p);
	ch->setAnchorPoint(Vec2(0.5f, 0.5f));
	ch->setTexture(texture);
	//ch->setPhyBody();
	t->addChild(ch);

	return t;
}

bool PlayerLayer::init()
{
	if(!Layer::init()){return false;}

	return true;
}

void PlayerLayer::chJump()
{
	log("WH:chJump()");
	//m_ch->jump();
	auto actionJump = JumpBy::create(JUMP_DURATION, Vec2(0, JUMP_HEIGHT), JUMP_HEIGHT, 1);
	m_ch->runAction(actionJump);
}

void PlayerLayer::chMove(Vec2 dir)
{
	m_ch->move(dir);
	/*auto actionMove=MoveBy::create((float)240 / (float)80 / (float)10, dir);
	m_ch->runAction(actionMove);*/
	//log("m_ch move ");
}