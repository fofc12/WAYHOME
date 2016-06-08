#pragma once
#include "cocos2d.h"
#include "PlayerLayer.h"

#define TMX_LYR_Z			-1
#define PLAYER_LYR_Z		10

#define OBJ_TAG_MENU		199
#define OBJ_TAG_BLOCK		100
#define OBJ_TAG_DP			101
#define OBJ_TAG_HOME		102
#define OBJ_TAG_SPRING		103
#define OBJ_TAG_DROP_STONES	104
#define OBJ_TAG_STAGE1		200
#define OBJ_TAG_STAGE2		201
#define OBJ_TAG_STAGE3		202

namespace wayhome
{
	class MapLayer :public cocos2d::Layer
	{
		PlayerLayer* m_playerLayer;

		cocos2d::TMXTiledMap* m_tileMap;
		TMXLayer* m_collidable;
		//protected:
		//Vec2 tileCoordFromPosition(Vec2 pos);
	public:
		CREATE_FUNC(MapLayer);

		virtual bool init() override;

		void initWithFile(std::string map);
		void addPhyEdge();

		TMXTiledMap* getTileMap()
		{
			return m_tileMap;
		}

		Size getTileMapSize()
		{
			return m_tileMap->getContentSize();
		}

		std::string getObjType(std::string s);
		Vec2 getObjPoint(std::string s);
		Size getObjSize(std::string s);

		Node* createNode(std::string, Vec2, Size);
	};
}