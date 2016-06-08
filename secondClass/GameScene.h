#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include <cocos2d.h>
USING_NS_CC;
#include "GameLayer.h"
#include "StateLayer.h"
#include "OperateLayer.h"
class GameScene :public Scene
{
public:
	static cocos2d::Scene* createScene();
};

#endif