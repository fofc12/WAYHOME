#pragma once

#include"cocos2d.h"
//#include "editor-support/cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//#include "WHFunc.h"

USING_NS_CC;
using namespace std;

#define CUR_VERSION				"1.1"

#define DESIGN_W			480
#define DESIGN_H			320
#define DEBUG_DRAW			false

#define ZEROF				(1e-10)
#define MOVE_DURATION		0.01f
#define JUMP_DURATION		0.6f
#define JUMP_HEIGHT			70	
#define DROP_HEIGHT_EX		30
#define DROP_SPEED_PER_H	(1300.0f/2)
#define MOVE_SPEED_PER_F	3

#define TAG_TMX				1
#define TAG_CH				2
//#define CS_PATH				"../res
#define STG0_MAP			"TiledMaps/whmap0.tmx"
#define STG1_MAP			"TiledMaps/whmap1.tmx"
#define STG2_MAP			"TiledMaps/whmap2.tmx"
#define STG3_MAP			"TiledMaps/whmap3.tmx"

#define CS_PATH				
#define LOGO_SC_PATH		"LogoScene.csb"
#define CTL_SC_PATH			"ControlUI.csb"

#define CH_IMG				"Img/player.png"
//cloud
#define CLOUD_BOT			"Img/cloudBottom.png"
#define CLOUD_TOP			"Img/cloudTop.png"

//#define MAP_PATH			"TiledMaps/testmap.tmx"

#define BIT_ON(panel,switcher)		(panel |= switcher)
#define BIT_OFF(panel,switcher)		(panel &= ~switcher)
#define IS_ON(panel,switcher)		(panel & switcher)

#define GET_WIDTH			getContentSize().width
#define GET_HEIGHT			getContentSize().height

//#define SERVER_ROOT_URL		"auony.usa1.1stidc1.com/WhCommunity"	
#define SERVER_ROOT_URL		"https://wayhomec-auony.c9.io"	
#define CHECK_VER_URL		"/check_ver.php"