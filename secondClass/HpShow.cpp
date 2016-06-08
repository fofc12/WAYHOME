#include "HpShow.h"

HpShow::HpShow()
{
}
HpShow::~HpShow()
{
}
bool HpShow::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Node::init());
		auto visibleSize =  Director::getInstance()->getVisibleSize();
		Sprite* HeroHp = Sprite::create("bloodBg.png");
		HeroHp->setPosition(HeroHp->getContentSize().width/2,
			visibleSize.height-HeroHp->getContentSize().height/2);
		this->addChild(HeroHp);

		m_preal = ProgressTimer::create(Sprite::create("blood.png"));
		m_preal->setType(ProgressTimer::Type::BAR);
		m_preal->setMidpoint(Point(0,0.5));		
		m_preal->setBarChangeRate(Point(1.0, 0));	
		m_preal->setPosition(HeroHp->getContentSize()/2);
		m_preal->setPercentage(100);
		HeroHp->addChild(m_preal);

		this->scheduleUpdate();
		ret = true;
	} while(0);
	return ret;
}


void HpShow::update(float dt)
{
	m_preal->setPercentage((float)global->hero->getCurtLifeValue()/global->hero->getSumLifeValue()*100);
}
