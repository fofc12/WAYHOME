#include "Enemy.h"
Enemy::Enemy():
	m_nextDecisionTime(0)
{}
Enemy::~Enemy()
{}

bool Enemy::init()
{
	bool ret = false;
	do {
		this->initWithSpriteFrameName("bear_idle_00.png");
		//this->setAnchorPoint(Vec2(0.25f, 0.15f));

		Animation *idleAnim = this->createNomalAnimation("bear_idle_%02d.png", 3, 6);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		Animation *walkAnim = this->createNomalAnimation("bear_run_%02d.png", 4, 8);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		Animation *attackAnim = this->createAttackAnimation("bear_attack_00_%02d.png", 0, 8, 8);
		this->setNomalAttackA(Sequence::create(Animate::create(attackAnim),
			CallFuncN::create(CC_CALLBACK_1(Enemy::attackCallBackAction,this)),
			Role::createIdleCallbackFunc(), 
			NULL));

		Animation *hurtAnim = this->createNomalAnimation("bear_hurt_%02d.png", 2, 4);
		this->setHurtAction(Sequence::create(Animate::create(hurtAnim), Role::createIdleCallbackFunc(), NULL));

		Animation *deadAnim = this->createNomalAnimation("bear_dead_%02d.png", 2, 4);
		this->setDeadAction(Sequence::create(Animate::create(deadAnim), Blink::create(3, 9), NULL));

		Size enemyShowSize = this->getSpriteFrame()->getRect().size;
		this->m_bodyBox = this->createBoundingBox(Vec2(0,35), Size(60,70));
		this->m_hitBox = this->createBoundingBox(Vec2(40,35), Size(80, 70));


		ret = true;
	} while(0);

	return ret;
}
void Enemy::updateSelf()
{
	//this->execute(global->hero->getPosition() + global->hero->getBodyBox().actual.origin , global->hero->getBodyBox().actual.size.width);
	this->execute(global->hero->getPosition(), global->hero->getBodyBox().actual.size.width);//对象坐标及body宽度
	if(this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 location = this->getPosition();
		Vec2 direction = this->getMoveDirection();
		Vec2 expectP = location + direction;
		float maptileHeight = global->tileMap->getTileSize().height;
		//if(expectP.y<0 || !global->tileAllowMove(expectP))
		//这群笨蛋AI总跑出地图报错.后续再去改进吧
		if(expectP.y < 0 || expectP.y > maptileHeight * 3 )
		{
			direction.y  =0;
		}
		this->setFlippedX(direction.x < 0 ? true : false);
		this->setPosition(location + direction);
		this->updateBoxes();
		this->setLocalZOrder(this->getPositionY());
	}
	if(this->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_A) 
	{
		this->runNomalAttackA();
	}
}

void Enemy::execute(const Vec2& target, float targetBodyWidth)
{
	if(m_nextDecisionTime == 0)//lazy延时到0执行下一个动作判定
	{
		this->decide(target, targetBodyWidth);
	}else {
		-- m_nextDecisionTime;
	}
}
void Enemy::decide(const Vec2& target, float targetBodyWidth)
{
	//Vec2 location = this->getPosition()+ this->getBodyBox().actual.origin;//获得自己的身体中心的坐标
	Vec2 location = this->getPosition();//获得脚下坐标
	float distance = location.getDistance(target);//与对象Body的距离
	distance = distance - targetBodyWidth / 2;//距离范围应该减去body宽度

	bool isFlippedX = this->isFlippedX();
	bool isOnTargetLeft = (location.x < target.x ? true : false);//方向判定
	if((isFlippedX && isOnTargetLeft) || (!isFlippedX && !isOnTargetLeft)) {
		this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
	}else {
		if(distance < m_eyeArea)
		{
			this->m_aiState = (distance < m_attackArea)&&((fabsf(location.y - target.y) < 15)) ? AI_ATTACK : AI_PURSUIT;
		}else {
			this->m_aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
		}
	}
	switch(m_aiState)
	{
	case AI_ATTACK:
		{
			this->runNomalAttackA();
			//this->attack();
			this->m_nextDecisionTime = 50;
		}
		break;
	case AI_IDLE:
		{
			this->runIdleAction();
			this->m_nextDecisionTime = CCRANDOM_0_1() * 100;
		}
		break;
	case AI_PATROL:
		{
			this->runWalkAction();
			this->m_moveDirection.x = CCRANDOM_MINUS1_1();
			this->m_moveDirection.y = CCRANDOM_MINUS1_1();
			m_moveDirection.x  = m_moveDirection.x > 0 ? (m_moveDirection.x + velocity.x) : (m_moveDirection.x -velocity.x);
			m_moveDirection.y  = m_moveDirection.y > 0 ? (m_moveDirection.y +velocity.y) : (m_moveDirection.y -velocity.y);
			this->m_nextDecisionTime = CCRANDOM_0_1() * 100;
		}
		break;
	case AI_PURSUIT:
		{
			this->runWalkAction();
			this->m_moveDirection = (target - location).getNormalized();
			this->setFlippedX(m_moveDirection.x < 0 ? true : false);
			m_moveDirection.x  = m_moveDirection.x > 0 ? (m_moveDirection.x +velocity.x) : (m_moveDirection.x -velocity.x);
			m_moveDirection.y  = m_moveDirection.y > 0 ? (m_moveDirection.y +velocity.y) : (m_moveDirection.y -velocity.y);
			this->m_nextDecisionTime = 10;
		}
		break;
	}
}


void Enemy::attackCallBackAction(Node* pSender)
{
	Hero* t_hero = global->hero;
	Rect attackReck = m_hitBox.actual;//怪物攻击区域
	Rect hurtReck = t_hero->getBodyBox().actual;//英雄受伤区域
	if(attackReck.intersectsRect(hurtReck))
	{
		t_hero->setAllowMove(false);
		int damage = this->getDamageStrenth();
		t_hero->runHurtAction();
		t_hero->setCurtLifeValue(t_hero->getCurtLifeValue() - damage);
	}
	if(t_hero->getCurtLifeValue() <= 0)
	{
		t_hero->runDeadAction();
		t_hero->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
	}
}
