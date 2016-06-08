#include "WHPublic.h"
#include "MapLayer.h"
//#include "DisplayLayer.h"
//#include "MainLayer.h"

//USING_NS_CC;
using namespace wayhome;

bool MapLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	return true;
}

void MapLayer::initWithFile(std::string map)
{
	log("WH:Creating TMX_LYR");
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_tileMap = TMXTiledMap::create(map);
	this->addChild(m_tileMap, TMX_LYR_Z, 100);

	//Size tSize = m_tileMap->getTileSize();
	//读取对象层及其属性
	TMXObjectGroup *group = m_tileMap->getObjectGroup("objects");
	Value v = group->getProperty("obj_cnt");
	int blockCount = v.asInt();

	//添加对应砖块
	for (int i = 1; i <= blockCount; i++)
	{
		char buffer[80];
		sprintf(buffer, "%s%d", "obj", i);
		this->addChild(createNode(getObjType(buffer), getObjPoint(buffer), getObjSize(buffer)));
		//, TMX_LYR_Z, TAG_TMX);
	}

	addPhyEdge();
	log("WH:Create TMX_LYR suc");
}

void MapLayer::addPhyEdge()
{
	auto size = m_tileMap->getContentSize();
	//定义物理边界
	auto body = PhysicsBody::createEdgeBox(size, PhysicsMaterial(0.99f, 0.0f, 1.0f), 3.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(size.width / 2, size.height / 2));
	edgeNode->setPhysicsBody(body);

	this->addChild(edgeNode);
}

std::string MapLayer::getObjType(std::string s)
{
	TMXObjectGroup *group = m_tileMap->getObjectGroup("objects");
	ValueMap vm = group->getObject(s);
	
	return vm["type"].asString();
}

Vec2 MapLayer::getObjPoint(std::string s)
{
	//tmx层取数据
	TMXObjectGroup *group = m_tileMap->getObjectGroup("objects");
	ValueMap vm = group->getObject(s);
	Size size = Size(vm["width"].asFloat(), vm["height"].asFloat());

	float x = vm["x"].asFloat() + size.width / 2;
	float y = vm["y"].asFloat() + size.height / 2;
	return Vec2(x, y);
}

Size MapLayer::getObjSize(std::string s)
{
	TMXObjectGroup *group = m_tileMap->getObjectGroup("objects");
	ValueMap vm = group->getObject(s);

	float w = vm["width"].asFloat();
	float h = vm["height"].asFloat();
	return Size(w,h);
}

Node* MapLayer::createNode(std::string type,Vec2 pos,Size size)
{
	float w = size.width;
	float h = size.height;

	auto edgeNode = Node::create();
	edgeNode->setPosition(pos.x, pos.y);
	edgeNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	auto body = PhysicsBody::createEdgeBox(Size(w, h), PHYSICSBODY_MATERIAL_DEFAULT);
	//	,PHYSICSBODY_MATERIAL_DEFAULT);
	body->setCategoryBitmask(1);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(1);

	edgeNode->setContentSize(Size(w, h));
	edgeNode->setPhysicsBody(body);

	if (type == "block")
	{

		edgeNode->setTag(OBJ_TAG_BLOCK);

		return edgeNode;
	}
	else if (type == "death_point")
	{
		edgeNode->setTag(OBJ_TAG_DP);

		return edgeNode;
	}
	else if (type == "home")
	{
		edgeNode->setTag(OBJ_TAG_HOME);

		return edgeNode;
	}
	else if (type == "spring")
	{
		edgeNode->setTag(OBJ_TAG_SPRING);

		return edgeNode;
	}
	else if (type == "drop_stones")
	{
		edgeNode->setTag(OBJ_TAG_DROP_STONES);

		return edgeNode;
	}
	else if (type == "stage1")
	{
		edgeNode->setTag(OBJ_TAG_STAGE1);

		return edgeNode;
	}
	else if (type == "stage2")
	{
		edgeNode->setTag(OBJ_TAG_STAGE2);

		return edgeNode;
	}
	else if (type == "stage3")
	{
		edgeNode->setTag(OBJ_TAG_STAGE3);

		return edgeNode;
	}

	return nullptr;
}
//
//bool MapLayer::isCollidable(Vec2 pos)
//{
//	if (pos.x<0 || pos.x>m_tileMap->getContentSize().width || pos.y<0 || pos.y>m_tileMap->getContentSize().height)
//		return true;
//
//	Vec2 tileCoord=this->tileCoordFromPosition(pos);
//	int tileGid=m_collidable->getTileGIDAt(tileCoord);
//	if(tileGid>0)
//	{
//		Value v=m_tileMap->getPropertiesForGID(tileGid);
//		ValueMap vm=v.asValueMap();
//
//		std::string collision=vm["Collidable"].asString();
//
//		if(collision=="true"){return true;}
//	}
//	return false;
//}
//
//
//
//Vec2 MapLayer::tileCoordFromPosition(Vec2 pos)
//{
//	int x = pos.x / m_tileMap->getTileSize().width + 1;
//	int y = ((m_tileMap->getMapSize().height*m_tileMap->getTileSize().height) - pos.y) / m_tileMap->getTileSize().height;
//
//	return Vec2(x, y);
//}