#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
USING_NS_CC; 

#include "Singleton.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "StateLayer.h"

//需引入以下类，否则在这些类中访问单例对象会报错
class GameLayer;
class OperateLayer;
class StateLayer;
class Hero;
class Enemy;

//全局单例
class Global :public Singleton<Global>
{
public:
	Global(void);
	~Global(void);

	//GameScene *gameScene;

	GameLayer *gameLayer;			//游戏层
	OperateLayer *operateLayer;		//操作层
	StateLayer * stateLayer;		//状态层
	Hero *hero;						//英雄
	__Array *enemies;				//敌人
	TMXTiledMap *tileMap;			//地图

	Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = NULL);//将point转换成地图GID的point
	bool  tileAllowMove(Vec2 MovePoint);
};

#define global Global::instance()

#endif