#include "Role.h"

Role::Role(void):
	m_pidleaction(NULL),
	m_pwalkaction(NULL),
	m_prunaction(NULL),
	m_pjumpaction(NULL),
	m_pnomalattacka(NULL),
	m_pnomalattackb(NULL),
	m_pnomalattackc(NULL),
	m_pnomalattackd(NULL),
	m_pchange(NULL),
	m_pchangeattack(NULL),
	m_prushattack(NULL),
	m_pjumpattacka(NULL),
	m_pjumpattackb(NULL),
	m_pskillattacka(NULL),
	m_pskillattackb(NULL),
	m_pskillattackc(NULL),
	m_phurtaction(NULL),
	m_pdeadaction(NULL),
	currActionState(ACTION_STATE_NONE)
{
	//this->setRoleDirection(RolelTurnRight);//设定初始朝向
}
Role::~Role(void)
{
	CC_SAFE_RELEASE_NULL(m_pidleaction);
	CC_SAFE_RELEASE_NULL(m_pwalkaction);
	CC_SAFE_RELEASE_NULL(m_prunaction);
	CC_SAFE_RELEASE_NULL(m_pjumpaction);
	CC_SAFE_RELEASE_NULL(m_pnomalattacka);
	CC_SAFE_RELEASE_NULL(m_pnomalattackb);
	CC_SAFE_RELEASE_NULL(m_pnomalattackc);
	CC_SAFE_RELEASE_NULL(m_pnomalattackd);
	CC_SAFE_RELEASE_NULL(m_pchange);
	CC_SAFE_RELEASE_NULL(m_pchangeattack);
	CC_SAFE_RELEASE_NULL(m_prushattack);
	CC_SAFE_RELEASE_NULL(m_pjumpattacka);
	CC_SAFE_RELEASE_NULL(m_pjumpattackb);
	CC_SAFE_RELEASE_NULL(m_pskillattacka);
	CC_SAFE_RELEASE_NULL(m_pskillattackb);
	CC_SAFE_RELEASE_NULL(m_pskillattackc);
	CC_SAFE_RELEASE_NULL(m_phurtaction);
	CC_SAFE_RELEASE_NULL(m_pdeadaction);
}

//各种动作
void Role::runIdleAction()
{	
	//通过changeState判断是否可以变更状态,之后执行动作
	if(changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_pidleaction);
	}
}


void Role::runWalkAction()
{
	if(changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_pwalkaction);
	}
}
void Role::runRunAction()
{	
	if(changeState(ACTION_STATE_RUN))
	{
		this->runAction(m_prunaction);
	}
}
void Role::runJumpAction()
{
	if(changeState(ACTION_STATE_JUMP))
	{
		this->runAction(m_pjumpaction);
	}

}

void Role::runNomalAttackA()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_A))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattacka);
	}
}
void Role::runNomalAttackB()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_B))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackb);
	}
}

void Role::runNomalAttackC()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_C))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackc);
	}
}
void Role::runNomalAttackD()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_D))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackd);
	}
}
void Role::runChange()
{
	if(changeState(ACTION_STATE_CHANGE))
	{
		this->setAllowMove(false);
		this->runAction(m_pchange);
	}
}
void Role::runChangeAttack()
{
	if(changeState(ACTION_STATE_CHANGE_ATTACK))
	{
		this->setAllowMove(false);
		this->runAction(m_pchangeattack);
	}
}
void  Role::runRushAttack()
{
	if(changeState(ACTION_STATE_RUSH_ATTACK))
	{
		this->runAction(m_prushattack);
	}
}
void  Role::runJumpAttackA()
{
	if(changeState(ACTION_STATE_JUMP_ATTACK_A))
	{
		this->runAction(m_pjumpattacka);
	}
}
void  Role::runJumpAttackB()
{
	if(changeState(ACTION_STATE_JUMP_ATTACK_B))
	{
		this->runAction(m_pjumpattackb);
	}
}
void  Role::runSkillAttackA()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_A))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattacka);
	}
}
void  Role::runSkillAttackB()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_B))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattackb);
	}
}
void  Role::runSkillAttackC()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_C))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattackc);
	}
}

void Role::runHurtAction()
{
	if(changeState(ACTION_STATE_HURT))
	{
		this->runAction(m_phurtaction);
	}
}
void Role::runDeadAction()
{
	if(changeState(ACTION_STATE_DEAD))
	{
		this->runAction(m_pdeadaction);
	}
}

Animation* Role::createNomalAnimation(const char* formatStr, int frameCount, int fps)
{
	Vector<SpriteFrame*> pFrames; 
	for(int i = 0; i < frameCount; i++ )
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}
Animation* Role::createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd,int fps)
{
	//通过frameCountBegan,frameCountEnd从SpriteFrameCache中创建一个动作
	Vector<SpriteFrame*> pFrames; 
	for(int i = frameCountBegan; i < frameCountEnd; i++ )
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i-frameCountBegan,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

bool Role::changeState(ActionState actionState)
{
	//允许改变状态,死了和状态不变不会在接受其他状态改变指令
	if(currActionState == ACTION_STATE_DEAD || currActionState == actionState)
	{
		return false;
	}
	this->stopAllActions();
	this->currActionState = actionState;
	return true;
}
CallFunc* Role::createIdleCallbackFunc()
{
	this->setAllowMove(true);
	return CallFunc::create(CC_CALLBACK_0(Role::runIdleAction, this));
}

BoundingBox Role::createBoundingBox(Vec2 origin, Size size)
{
	//创建一个BoundingBox,用于设置身体碰撞和攻击碰撞检测
	BoundingBox boundingBox;
	boundingBox.original.origin= origin;
	boundingBox.original.size= size;
	boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
	boundingBox.actual.size= size;
	return boundingBox;
}
void Role::updateBoxes()
{
	//通过方向刷行盒子位置
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if(isFlippedX) 
	{
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}else 
	{
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Vec2(x, this->getPosition().y + m_hitBox.original.origin.y);
	m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}

void Role::setPosition(const Vec2 &position)
{
	//每次重新设定坐标的时候刷新盒子
	Sprite::setPosition(position);
	this->updateBoxes();
}