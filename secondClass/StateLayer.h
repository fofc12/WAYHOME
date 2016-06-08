#ifndef _STATE_LAYER_H_
#define _STATE_LAYER_H_
#include <cocos2d.h>
USING_NS_CC; 
#include "Global.h"
#include "HpShow.h"
class StateLayer : public Layer
{
public:
	StateLayer();
	~StateLayer();
	virtual bool init();

	CREATE_FUNC(StateLayer);
};

#endif