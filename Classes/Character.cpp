#include "Character.h"

//USING_NS_CC;

bool Character::init()
{
	if(!Node::init())return false;

	_state=0;
	_jumpCnt = 0;

	this->initSprite();
	
	/*auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile("smoke.plist");
	auto animation2 = cache->getAnimation("dance_1");
	auto action2 = Animate::create(animation2);
	mDieAnimate = Animate::create(animation2);*/

	return true;
}

void Character::initSprite()
{
	//´´½¨¾«Áé(äÖÈ¾)
	m_sprite=Sprite::create();
	this->addChild(m_sprite);
}

void Character::setTexture(std::string s)
{
	//this->setContentSize(m_sprite->getContentSize());
	m_sprite->setTexture(s);
	
	//this->updateTransform();
}

void Character::move(Vec2 dir)
{
	if ((_state & BAN_MOVE))return;
	if (_state & IS_MOVING)return;
	//if (LOCK)return;
	//dir.y-=0.1f;
	if (dir.x < 0)dir = Vec2(-MOVE_SPEED_PER_F,0);
	else dir=Vec2(MOVE_SPEED_PER_F, 0);
	
	//if(dir.x>0?CH_RIGHT:CH_LEFT;
	
	auto call = [&]()  { BIT_OFF(_state,IS_MOVING); };
	//	auto callEnd = [&]()  {  //this->stateFlag&=~flag;};   
	auto action = MoveBy::create(MOVE_DURATION, dir);
	auto actionSeq = Sequence::create(
												action,
												CallFunc::create(call),
												NULL
											);
	BIT_ON(_state, IS_MOVING);
	actionSeq->setTag(MOVE_TAG);
	this->runAction(actionSeq);
	//this->runActionWithFlag(actionMove,flag);
	log("WH:ch moved to (%f,%f)" , this->getPositionX() , this->getPositionY());
}

void Character::jump()
{
	if ((_state&BAN_JUMP))return;
	//if (_state & IS_DROPPING)return;
	/*if (_jumpCnt == 0 && _playerState != PS_WALK) {
		return false;
	}

	if (_jumpCnt >= 2) {
		return false;
	}

	if (!touchBegin) {
		if (_playerState == PS_JUMP) {
			_jumpAction->change();
		}
		return false;
	}*/
	if (_jumpCnt >=1)return;

	//if (_state == PS_JUMP || _playerState == PS_JUMPBACK) 
	if(_state & IS_JUMPING)
	{
		//this->stopActionByTag(11);//rotate
		this->stopActionByTag(JUMPSEQ_TAG);//jumpseq
		//this->stopActionByTag(DROP_TAG);//jumpdone
	}
	
	BIT_ON(_state , IS_JUMPING);
	

	//runRotateAction();
	// _jumpAction = MyJump::create((float)240 / (float)80 / (float)10, ccp(0, 240), 60, 1);
	auto _jumpAction = JumpBy::create(JUMP_DURATION, Vec2(0, JUMP_HEIGHT), JUMP_HEIGHT, 1);
	//auto _jumpAction = MoveBy::create(JUMP_DURATION, Vec2(0, JUMP_HEIGHT*2));
	_jumpAction->setTag(JUMP_TAG);
	auto jumpSeq = Sequence::create(
		_jumpAction,
		CallFunc::create(CC_CALLBACK_0(Character::drop,this)),
		NULL);
	jumpSeq->setTag(JUMPSEQ_TAG);

	_jumpCnt++;
	//BIT_OFF(_state, IS_DROPPING);
	BIT_ON(_state, IS_JUMPING);
	this->runAction(jumpSeq);

	/*GameLayer * gl = (GameLayer *)this->getParent();
	if (gl->soundIsOn()){
		if (_jumpCnt == 1) {
			cd::SimpleAudioEngine::sharedEngine()->playEffect("sounds/jumpA.wav");
		}
		else if (_jumpCnt == 2) {
			cd::SimpleAudioEngine::sharedEngine()->playEffect("sounds/jumpB.wav");
		}
	}*/
	//return true;
}

void Character::drop()
{
	//if (_state & IS_DROPPING)return;
	//this->stopActionByTag(JUMP_TAG);
	//_jumpAction->retain();
	//auto pos = this->getParent()->convertToWorldSpace(this->getPosition());

	/*auto pos = this->getPosition();
	auto height = pos.y + DROP_HEIGHT_EX;
	auto downAction = MoveBy::create(height / DROP_SPEED_PER_H, Vec2(0, -height));
	//downAction->setTag(DROP_TAG);
	auto esiDown = EaseSineIn::create(downAction);
	esiDown->setTag(DROP_TAG);*/

	BIT_OFF(_state, IS_JUMPING);

	//BIT_ON(_state, IS_DROPPING);
	//this->runAction(esiDown);
	//this->runAction(downAction);

	//BIT_OFF(_state,IN_AIR);
	//_playerState = PS_JUMPBACK;
}

void Character::resetTo(Vec2 pos)
{
	//this->stopActionByTag(DROP_TAG);
	//this->stopActionByTag(JUMPSEQ_TAG);
	//BIT_ON(_state, IS_MOVING);
	
	//this->setRotation(0);
	//auto size = this->getContentSize();
	//auto prePos = this->getPosition();
	this->setPosition(Vec2(pos.x,pos.y));
	this->stopAllActions();

	_jumpCnt = 0;
	BIT_OFF(_state,IS_JUMPING) ;
	BIT_OFF(_state, IS_DROPPING);
	BIT_OFF(_state, IS_MOVING);
	//_state = 0;
}

void Character::die()
{
	this->stopAllActions();

	Vector<SpriteFrame*>allframe;
	for (int i = 0; i < 7; i++)
	{
		SpriteFrame *sf = SpriteFrame::create("smoke.png", Rect((i%3) * 84, i/3*64, 84, 64));
		allframe.pushBack(sf);
	}
	Animation *ani = Animation::createWithSpriteFrames(allframe, 0.3f);
	/*auto act = Sequence::create(
		Animate::create(ani)
		, CallFuncN::create(m_sprite,SEL_CallFuncN( Character::remove))
		, nullptr);

	this->m_sprite->runAction(act);*/
	m_sprite->runAction(Animate::create(ani));
		
		//this->runAction(Sequence::create(
	//	mDieAnimate, Hide::create(), NULL));

	//mState = E_DIE;
	/*auto actionSeq= Sequence::create(	CallFunc::create(CC_CALLBACK_0(Character::setFlagTrue,this,flag)), 
										action,
										CallFunc::create(CC_CALLBACK_0(Character::setFlagFalse,this,flag)),
										NULL
									);
	auto callStart = [&]()  {  this->stateFlag|=flag;};  
	auto callEnd = [&]()  {  //this->stateFlag&=~flag;};   
	auto actionSeq= Sequence::create(CallFunc::create(callStart),action,CallFunc::create(callEnd), NULL);
	this->runAction(actionSeq);*/
}

void Character::remove()
{
	this->removeAllChildren();
}