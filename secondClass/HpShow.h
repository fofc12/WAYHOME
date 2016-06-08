#ifndef _HP_SHOW_H_
#define _HP_SHOW_H_
#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;

class HpShow : public Node
{
public:
	HpShow();
	~HpShow();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(HpShow);
private:
	ProgressTimer* m_preal;
};

#endif