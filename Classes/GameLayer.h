#pragma once

#include "WHPublic.h"
#include "MapLayer.h"

#define MAP_LYR_Z	1

#define TAG_MAP			10
#define TAG_PLAYER		11

namespace wayhome{
	class GameLayer :public cocos2d::Layer
	{
		MapLayer* m_mapLayer;//地图层
		Character *m_player;//角色

		bool flag = true;
		bool extraFlag = false;
	protected:
		virtual bool onContactBegin(cocos2d::PhysicsContact& contact);//接触回调
		virtual void onContactSeperate(cocos2d::PhysicsContact& contact);//分离回调

		void initMap(std::string s);//初始化地图层
		void initPlayer();//初始化角色
		//void setPhyEdge();//设置物理边界

		//void onUpdate(float dt);

	public:
		CREATE_FUNC(GameLayer);
		virtual bool init();

		Character *getPlayer(){ return m_player; }
		bool isExtraFlag(){ return extraFlag; }
		void restart();
		
		void handleInput(int cmd);//处理输入
		void handleEvent(int tag);//处理事件

		void adjustCamera();//调整镜头
		void addNewSpriteAtPosition(Point p);
		void extraStage();

		bool isCollidable();
		
	};
}