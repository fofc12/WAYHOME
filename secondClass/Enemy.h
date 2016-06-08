#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <cocos2d.h>
USING_NS_CC;
#include "Global.h"
#include "Role.h"

typedef enum {
	AI_IDLE = 0,
	AI_PATROL,
	AI_ATTACK,
	AI_PURSUIT
}AiState;

class Enemy : public Role
{
public:
	Enemy();
	~Enemy();
	bool init();
	void updateSelf();
	CREATE_FUNC(Enemy);
	CC_SYNTHESIZE(cocos2d::Vec2, m_moveDirection, MoveDirection);
	CC_SYNTHESIZE(float, m_eyeArea, EyeArea);
	CC_SYNTHESIZE(float, m_attackArea, AttackArea)
	CC_SYNTHESIZE(AiState, m_aiState, AiState);
	
	
	void attackCallBackAction(Node* pSender);//ÆÕÍ¨¹¥»÷»Øµ÷
private:
	void decide(const cocos2d::Vec2& target, float targetBodyWidth);
	void execute(const cocos2d::Vec2& target, float targetBodyWidth);
	unsigned int m_nextDecisionTime;
};


#endif