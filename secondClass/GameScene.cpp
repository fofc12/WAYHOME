#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto gamelayer=GameLayer::create();
	scene->addChild(gamelayer, 0);
	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer, 1);
	auto statelayer =StateLayer::create();
	scene->addChild(statelayer);
	return scene;
}
