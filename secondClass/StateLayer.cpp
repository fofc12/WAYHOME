#include "StateLayer.h"


StateLayer::StateLayer()
{
	global->stateLayer = this;
}

StateLayer::~StateLayer()
{
}

bool StateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init() );
				auto Hp = HpShow::create();
		this->addChild(Hp);

		ret = true;
	} while(0);

	return ret;
}
