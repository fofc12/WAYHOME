#ifndef _OPERATE_LAYER_H_
#define _OPERATE_LAYER_H_
#include <cocos2d.h>
USING_NS_CC; 
#include "Joystick.h"
#include "SkillButton.h"
class OperateLayer : public Layer
{
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();

	void attackButton(Ref* pSender);

	CREATE_FUNC(OperateLayer);
};

#endif