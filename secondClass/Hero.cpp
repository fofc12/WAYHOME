#include "Hero.h"

Hero::Hero(void)
{
	global->hero = this;
}
Hero::~Hero(void)
{
}

bool Hero::init(){
	bool ret = false;
	do 
	{
		this->initWithSpriteFrameName("boy_idle_00.png");
		//this->setAnchorPoint(Vec2(0.48f, 0.13f));

		//站立时播放动画
		Animation *idleAnim = this->createNomalAnimation("boy_idle_%02d.png", 3, 5);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		Animation *walkAnim = this->createNomalAnimation("boy_run_%02d.png", 8, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		//普通攻击A,分出招和收招,期间夹杂攻击判定.自己可以通过调节fps控制出招速度之类的
		Animation *attackAnima1 = this->createAttackAnimation("boy_attack_00_%02d.png", 0, 4, 10);
		Animation *attackAnima2 = this->createAttackAnimation("boy_attack_00_%02d.png", 4, 8, 15);
		this->setNomalAttackA(Sequence::create(
			Animate::create(attackAnima1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnima2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *attackAnimb1 = this->createAttackAnimation("boy_attack_01_%02d.png", 0, 3, 10);
		Animation *attackAnimb2 = this->createAttackAnimation("boy_attack_01_%02d.png", 3, 7, 15);
		this->setNomalAttackB(Sequence::create(
			Animate::create(attackAnimb1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *attackAnimc1 = this->createAttackAnimation("boy_attack_02_%02d.png", 0, 3, 10);
		Animation *attackAnimc2 = this->createAttackAnimation("boy_attack_02_%02d.png", 3, 6, 12);
		this->setNomalAttackC(Sequence::create(
			Animate::create(attackAnimc1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *chageAnim = this->createNomalAnimation("boy_change_attack_%02d.png", 4, 5);
		this->setChange(RepeatForever::create(Animate::create(chageAnim)));

		Animation *chageattAnim1= this->createAttackAnimation("boy_change_attack_%02d.png", 5, 7 , 2);
		Animation *chageattAnim2= this->createAttackAnimation("boy_change_attack_%02d.png", 7, 12 , 5);
		this->setChangeAttack(Sequence::create(
			Animate::create(chageattAnim1), 
			CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(chageattAnim2),
			Role::createIdleCallbackFunc(),
			NULL));

		Animation *gurtAnim = this->createNomalAnimation("boy_hurt_%02d.png", 2, 4);
		this->setHurtAction(Sequence::create(
			Animate::create(gurtAnim), 
			Role::createIdleCallbackFunc(), 
			NULL));

		Animation *deadAnim = this->createNomalAnimation("boy_dead_%02d.png", 3, 6);
		this->setDeadAction(Sequence::create(
			Animate::create(deadAnim), 
			Blink::create(3, 9), 
			NULL));

		//碰撞盒子设定
		this->m_bodyBox = this->createBoundingBox(Vec2(0,30), Size(30,60));
		this->m_hitBox = this->createBoundingBox(Vec2(35,50), Size(80, 90));


		ret = true;
	} while(0);

	return ret;
}

void Hero::onMove(Vec2 direction, float distance)//移动调用
{
	this->setFlippedX(direction.x < 0 ? true : false);
	this->runWalkAction();
	Vec2 velocity = direction * (distance < 33 ? 1 : 3);
	this->setVelocity(velocity);
}
void Hero::onStop()//站立
{
	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}
void Hero::onAttack(int number)//执行攻击
{
	this->runNomalAttackA();
}
void Hero::updateSelf()//刷新自己
{
	if(this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 currentP= this->getPosition();				//当前坐标
		Vec2 expectP = currentP + this->getVelocity();	//期望坐标
		Vec2 actualP = expectP;							//实际坐标
		float mapWidth = global->tileMap->getContentSize().width;	//整张地图宽度
		float herofat = this->getBodyBox().actual.size.width/2;		//角色横向宽度,以受攻击的bodybox为准
		////不能跑到墙上去
		//if(expectP.y<0 || !global->tileAllowMove(expectP))
		float maptileHeight = global->tileMap->getTileSize().height;
		if(expectP.y < 0 || expectP.y > maptileHeight * 3 )
		{
			actualP.y =currentP.y;
		}
		//不能跑出地图外面
		if(expectP.x < herofat || expectP.x >= mapWidth - herofat)
		{
			//if(!global->tileAllowMove(expectP))
			actualP.x = currentP.x;
		}
		this->setPosition(actualP);
		this->setLocalZOrder( Director::getInstance()->getVisibleSize().height - this->getPositionY());
	}
}
void Hero::attackCallBackAction(Node* pSender)
{//普通攻击回调
	__Array* pEnemies = global->enemies ;
	Ref *enemyObj = NULL;
	//遍历所有怪物 
	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemy = (Enemy*)enemyObj;
		if(fabsf(this->getPosition().y - pEnemy->getPosition().y) < 20)
		{
			Rect attackReck = m_hitBox.actual;//英雄攻击区域
			Rect hurtReck = pEnemy->getBodyBox().actual;;//怪物受伤区域
			if(attackReck.intersectsRect(hurtReck))
			{
				pEnemy->setAllowMove(false);
				//此处可处理怪物被攻击后的后续,产生伤害数字
				int damage = random(this->getDamageStrenth()*0.7,this->getDamageStrenth()*1.3);
				damageDisplay(damage , pEnemy->getBodyBox().actual.origin);
				pEnemy->runHurtAction();
				pEnemy->setCurtLifeValue(pEnemy->getCurtLifeValue() - damage);
				if(pEnemy->getCurtLifeValue() <= 0)
				{
					pEnemy->runDeadAction();
					pEnemy->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
				}
			}
		}
	}
	//this->runIdleAction();
}
void Hero::FontsCallBackAction(Node* pSender)
{
	//数字淡出回调
	global->gameLayer->removeChild(pSender);
}
void Hero::damageDisplay(int number,Vec2 point)
{
	//产生数字动画
	auto atLabel = Label::create();
	//char ch[100]={0};
	//sprintf(ch,"-%d",number);
	atLabel->setString(__String::createWithFormat("-%d",number)->getCString());
	atLabel->setSystemFontSize(18);
	atLabel->setColor(Color3B(0,0,128));
	atLabel->setPosition(point);
	global->gameLayer->addChild(atLabel,200);
	FiniteTimeAction * callFuncN = CallFuncN::create(atLabel, callfuncN_selector(Hero::FontsCallBackAction));
	FiniteTimeAction *sequence = Sequence::create(
		//FadeIn::create(1.5f),
		ScaleTo::create(0.2f,1.3f),
		MoveBy::create(0.2f,Vec2(0,20)),
		FadeOut::create(0.5f),
		callFuncN,
		NULL); 
	atLabel->runAction(sequence);
}