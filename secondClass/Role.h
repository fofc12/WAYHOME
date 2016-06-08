#ifndef _ROLE_H_
#define _ROLE_H_
#include "cocos2d.h"
USING_NS_CC;
typedef struct _BoundingBox
{
	Rect actual;
	Rect original;
}BoundingBox;
typedef enum {
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_RUN,
	ACTION_STATE_JUMP,
	ACTION_STATE_NOMAL_ATTACK_A,
	ACTION_STATE_NOMAL_ATTACK_B,
	ACTION_STATE_NOMAL_ATTACK_C,
	ACTION_STATE_NOMAL_ATTACK_D,
	ACTION_STATE_CHANGE,
	ACTION_STATE_CHANGE_ATTACK,
	ACTION_STATE_RUSH_ATTACK,
	ACTION_STATE_JUMP_ATTACK_A,
	ACTION_STATE_JUMP_ATTACK_B,
	ACTION_STATE_SKILL_ATTACK_A,
	ACTION_STATE_SKILL_ATTACK_B,
	ACTION_STATE_SKILL_ATTACK_C,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD
}ActionState;
//基础角色类，主角和NPC都需要继承它
//单纯的控制播放动画,何时播放它在具体的类里面设置
class Role :public Sprite
{
public:
	Role(void);
	~Role(void);
	/* 角色状态设定,初始化角色状态等 */
	CC_SYNTHESIZE(std::string,Name,Name);							//角色名称
	CC_SYNTHESIZE(float,curtLifevalue,CurtLifeValue);				//角色当前生命值
	CC_SYNTHESIZE(float,sumLifevalue,SumLifeValue);					//角色总体生命值
	CC_SYNTHESIZE(float,damagestrenth,DamageStrenth);				//角色当前攻击力
	CC_SYNTHESIZE(Vec2, velocity, Velocity);						//角色移动速度
	//CC_SYNTHESIZE(Direction, roleDirection, RoleDirection);		//角色朝向(分向左还是向右)
	//CC_SYNTHESIZE(CCPoint, _vector, Vector);						//偏移量，AI自动移动时下一帧的偏移向量
	CC_SYNTHESIZE(bool, allowmove, AllowMove);						//角色是否允许移动，例如：攻击，受伤等动画执行期间不可移动
	CC_SYNTHESIZE(ActionState,currActionState,CurrActionState);		//当前Action状态(据此状态处理各个动画之间的衔接问题)

	/* 需要用creatNomalAnimation创建,只有普通动画，有受伤判定，无攻击判定 */
	CC_SYNTHESIZE_RETAIN(Action*, m_pidleaction, IdleAction);		//角色空闲时序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pwalkaction, WalkAction);		//角色移动时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_prunaction,  RunAction );		//角色跑动时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpaction, JumpAction);		//角色跳跃时动画帧序列

	/* 以下是攻击序列动画，需要用creatAttackAnimation创建，会在动作执行中间添加攻击判定和受伤飘字等*/
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattacka, NomalAttackA);	//角色普通攻击A时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackb, NomalAttackB);	//角色普通攻击B时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackc, NomalAttackC);	//角色普通攻击C时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackd, NomalAttackD);	//角色普通攻击D时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pchange,  Change);				//角色蓄力时的动画序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pchangeattack,  ChangeAttack);	//角色蓄力攻击时的动画序列

	CC_SYNTHESIZE_RETAIN(Action*, m_prushattack,   RushAttack  );	//角色跑动攻击时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattacka,  JumpAttackA );	//角色跳跃攻击A时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattackb,  JumpAttackb );	//角色跳跃攻击B时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattacka, SkillAttackA);	//角色技能攻击A时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackb, SkillAttackB);	//角色技能攻击B时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackc, SkillAttackC);	//角色技能攻击C时动画帧序列

	/*主角用createImmortalAnimation创建,只有动画效果,无受伤判定,也就是受伤时候播放动画是无敌的,而且会打断所有动画,敌人就去死吧*/
	CC_SYNTHESIZE_RETAIN(Action*, m_phurtaction, HurtAction);		//角色受伤时动画帧序列
	CC_SYNTHESIZE_RETAIN(Action*, m_pdeadaction, DeadAction);		//角色死亡时动画帧序列

	void Role::callBackAction(Node* pSender);						//动画执行完毕的通用回调处理

	/*	下面是所有的动画回调函数，用来执行此动画,	*/
	virtual void runIdleAction();								//执行闲置动画
	virtual void runWalkAction();								//执行移动行走动画
	virtual void runRunAction();								//执行跑动行走动画
	virtual void runJumpAction();								//执行跳跃动作动画
	virtual void runNomalAttackA();								//执行普通攻击A动画
	virtual void runNomalAttackB();								//执行普通攻击B动画
	virtual void runNomalAttackC();								//执行普通攻击C动画
	virtual void runNomalAttackD();								//执行普通攻击D动画
	virtual void runChange();									//执行蓄力动画
	virtual void runChangeAttack();								//执行蓄力攻击动画
	virtual void runRushAttack();								//执行跑动攻击动画
	virtual void runJumpAttackA();								//执行跳跃攻击A动画
	virtual void runJumpAttackB();								//执行跳跃攻击B动画
	virtual void runSkillAttackA(); 							//执行技能攻击A动画
	virtual void runSkillAttackB(); 							//执行技能攻击B动画
	virtual void runSkillAttackC(); 							//执行技能攻击C动画
	virtual void runHurtAction();								//执行被攻击后受伤动画
	virtual void runDeadAction();								//执行死亡动画等
	CallFunc* createIdleCallbackFunc();							//回调闲置动画

	BoundingBox createBoundingBox(Vec2 origin,Size size);
	CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);				//身体碰撞盒子
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);				//攻击碰撞盒子
	virtual void setPosition(const Vec2 &position);

	void updateBoxes();
protected:
	static Animation* createNomalAnimation(const char* formatStr, int frameCount, int fps);
	static Animation* createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd,int fps);
private:
	bool changeState(ActionState actionState);
	ActionState proActionState;
};
#endif