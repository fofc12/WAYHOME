#include "GameLayer.h"

	GameLayer::GameLayer()
	{
		global->gameLayer = this;
	}
	GameLayer::~GameLayer()
	{
	}
	bool GameLayer::init()
	{
		bool ret = false;
		do {
			CC_BREAK_IF(!Layer::init());
			_visibleSize = Director::getInstance()->getVisibleSize();
			_visibleOrigin = Director::getInstance()->getVisibleOrigin();
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boy.plist", "Boy.pvr.ccz");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy.plist", "Enemy.pvr.ccz");

			this->addHero();
			this->addEnemies(5);
			auto map = MapLayer::create();
			this->addChild(map, -100);
			this->scheduleUpdate();

			ret = true;
		} while (0);
		return ret;
	}
	void GameLayer::update(float dt)
	{
		this->updateHero(dt);
		this->updateEnemies(dt);
	}
	void GameLayer::updateHero(float dt)
	{
		m_pHero->updateSelf();//自更新状态
	}
	void GameLayer::addHero()
	{
		m_pHero = Hero::create();
		m_pHero->setPosition(_visibleOrigin + Vec2(100, 50));
		m_pHero->runIdleAction();
		//属性设置
		m_pHero->setDamageStrenth(15);
		m_pHero->setSumLifeValue(200);
		m_pHero->setCurtLifeValue(m_pHero->getSumLifeValue());

		m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
		this->addChild(m_pHero);
	}
	void GameLayer::addEnemies(int number)
	{
		m_pEnemies = __Array::createWithCapacity(number);
		m_pEnemies->retain();
		for (int i = 0; i < number; i++)
		{
			Enemy *pEnemy = Enemy::create();
			pEnemy->setPosition(Vec2(random(_visibleSize.width / 2, _visibleSize.width), 70));
			pEnemy->runIdleAction();
			pEnemy->setLocalZOrder(_visibleSize.height - pEnemy->getPositionY());

			//属性设置
			pEnemy->setVelocity(Vec2(0.5f, 0.5f));
			pEnemy->setEyeArea(300);
			pEnemy->setAttackArea(80);
			pEnemy->setDamageStrenth(5);
			pEnemy->setSumLifeValue(100);
			pEnemy->setCurtLifeValue(m_pHero->getSumLifeValue());

			m_pEnemies->addObject(pEnemy);
			this->addChild(pEnemy, 0);
		}
		global->enemies = m_pEnemies;
	}
	void GameLayer::updateEnemies(float dt)
	{
		Ref *Obj = NULL;
		Vec2 distance = Vec2::ZERO;
		CCARRAY_FOREACH(m_pEnemies, Obj)//遍历所有的怪物
		{
			Enemy *pEnemy = (Enemy*)Obj;
			pEnemy->updateSelf();//自更新状态

			//如果死了就移除他们
			if (pEnemy->getDeadAction()->isDone())
				m_pEnemies->removeObject(pEnemy);
		}
	}
