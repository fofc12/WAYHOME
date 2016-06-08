#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//#include "ui/CocosGUI.h"//UI相关的头文件 
#include"cocostudio/CocoStudio.h"//在CocosStudio.h 头文件中已经包含了Studio所需要的各个头文件(除CocosGUI)因此我们使用Studio仅需要包含他就可以 
using namespace cocos2d;//CSLoader位于cocos2d命名空间。 
using namespace cocostudio::timeline;//动画相关的类位于cocostuio::timeline当中 
 
#include "MainLayer.h"

class HelloWorld : public cocos2d::Layer
{	
	MainLayer *m_mainLayer;
	static Node *m_rootNode;

	void initWelcome();
	void initMainLayer();

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuItemStartCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__
