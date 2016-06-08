#include "MapLayer.h"

MapLayer::MapLayer()
{
}
MapLayer::~MapLayer()
{
}

bool MapLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init() );
		this->initMapWithFile("mymap.tmx");//地图初始化

		this->scheduleUpdate();
		ret = true;
	} while(0);

	return ret;
}
void MapLayer::initMapWithFile(const char * path)
{
	TMXTiledMap *TileMap = TMXTiledMap::create(path);
	TileMap->setPosition(Vec2(0,0));
	global->tileMap=TileMap;
	this->addChild(TileMap); 
}

void MapLayer::update(float dt)
{
	this->setViewpointCenter(global->hero->getPosition());
}

void MapLayer::setViewpointCenter(Point pos)  //这个是移动地图,同时跟踪X,Y轴标准算法
{  
	Size winSize = Director::getInstance()->getWinSize();  
	auto _map = global->tileMap;

	//如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取对象的坐标  
	int x = MAX(pos.x, winSize.width/2);  
	int y = MAX(pos.y, winSize.height/2);  

	//如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标 )
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - winSize.width/2);  
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - winSize.height/2);  

	//对象当前所在坐标
	Point actualPosition = Vec2(x, y); 

	//计算屏幕中点和所要移动的目的点之间的距离
	Point centerOfView = Vec2(winSize.width/2, winSize.height/2);  
	Point viewPoint = centerOfView - actualPosition;  

	//设定一下地图的位置 ,这里一定要注意,单纯移动自己或者是_MAP移动都是无效的,在这里足足卡了好长时间
	//_map->setPosition(viewPoint);  
	//this->setPosition(viewPoint);
	//global->gameLayer->setPosition(viewPoint);
	this->getParent()->setPosition(viewPoint);
}  
