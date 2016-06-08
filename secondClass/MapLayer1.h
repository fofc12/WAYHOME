#ifndef _MAP_LAYER_H_
#define _MAP_LAYER_H_
#include <cocos2d.h>
USING_NS_CC; 
#include "Global.h"

namespace second
{

	class MapLayer : public Layer
	{
	public:
		MapLayer();
		~MapLayer();
		virtual bool init();
		void update(float dt);
		void setViewpointCenter(Point pos);
		CREATE_FUNC(MapLayer);
	private:
		void initMapWithFile(const char * path);
	};
}
#endif