#include "MainLayer.h"
#include "WHPublic.h"
#include "WHFunc.h"
using namespace wayhome;
NS_MF;

#include "network\HttpRequest.h"
#include "network\HttpClient.h"
using namespace network;

bool MainLayer::init()
{
	//super init first
    if ( !Layer::init() ){return false; }
	//auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();	

	m_time = 0;
	timeEsp = 60;

	m_displayLayer = DisplayLayer::create();
	this->addChild(m_displayLayer, 10);

	m_controlLayer = ControlLayer::create();
	this->addChild(m_controlLayer, CTL_LYR_Z);
	log("create CTL_LYR successfully");

	m_gameLayer = GameLayer::create();
	this->addChild(m_gameLayer, GM_LYR_Z);
	log("create GAME_LYR successfully");

	this->schedule(schedule_selector(MainLayer::onUpdate));
	
	if (first)
	{
		first = false;
		m_displayLayer->setTitle("Connecting to server..."); 
		checkVer();
	}

	return true;
	//instance=MainLayer::create();
}

void MainLayer::onUpdate( float dt )
{
	//log("MainLayer::onUpdate");
	m_gameLayer->handleInput(m_controlLayer->getCMD());
	m_gameLayer->adjustCamera();

	if ((m_time % timeEsp) == 0 && m_gameLayer->isExtraFlag())
	{
		timeEsp -= 2;
		if (timeEsp <= 0)timeEsp = 10;
		m_gameLayer->extraStage();
	}

	m_time++;
	//m_gameLayer->getPlayer()->drop();
	//m_gameLayer->fixCollision();
}

void MainLayer::CloudTimerCallBack( float dt ) {
    INIT_RANDOM_ENGINE;
    auto CloudSprite = Sprite::create(CLOUD_BOT);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size CloudSize = CloudSprite->getContentSize();
	CloudSprite->setPosition(
		Vec2(visibleSize.width + CloudSize.width / 2,
		visibleSize.height * (mf::rn(6, 8) / 10)));
	auto CloudSpriteTop = Sprite::create(CLOUD_TOP);
	CloudSpriteTop->setPosition(CloudSprite->getPosition());
	CloudSprite->addChild(CloudSpriteTop,-2);


    this->addChild(CloudSprite, -2);
    auto CloudRotate = RotateBy::create(80,
                                          mf::rn(0, 1) ? 360 : -360);
    auto CloudRotateForever = RepeatForever::create(CloudRotate);
    auto CloudMove = MoveBy::create(30, Vec2(-(visibleSize.width + CloudSize.width), 0));
    auto CloudActionSeque = Sequence::create(CloudMove,
		CallFuncN::create(CC_CALLBACK_1(MainLayer::CloudMoveDoneCallBack,this)), NULL);
    CloudSprite->runAction(CloudRotateForever);
    CloudSprite->runAction(CloudActionSeque);
}

void MainLayer::CloudMoveDoneCallBack( cocos2d::Node *sprite ) {
    this->removeChild(sprite);
}

void MainLayer::checkVer()
{
	HttpRequest* request = new HttpRequest();//请求对象
	string str = SERVER_ROOT_URL CHECK_VER_URL;
	//char buffer[80];
	//sprintf(buffer, "%s", str);
	request->setUrl((char *)str.data());
	request->setRequestType(HttpRequest::Type::POST);
	//request->setResponseCallback(CC_CALLBACK_2(GameLayer::checkVerDone,this));
	request->setResponseCallback(this, httpresponse_selector(MainLayer::checkVerDone));

	const char* postData ="version="CUR_VERSION ;
	request->setRequestData(postData, strlen(postData));//设置请求数据
	request->setTag("POST test");
	//log(buffer);
	HttpClient::getInstance()->send(request);//发送请求

	request->release();//释放请求
}

void MainLayer::checkVerDone(cocos2d::Node *sender, void *data)
{
	//char buf[80];
	//MainLayer *mainLayer = dynamic_cast<MainLayer *>(this->getParent());
	DisplayLayer * dl = m_displayLayer;
	HttpResponse *response = static_cast<HttpResponse*>(data);

	if (!response)
	{
		dl->setTitle("Fail to connect to server");
		return;
	}
	std::vector<char> *buffer = response->getResponseData();
	string recieveData;
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		log((*buffer)[i]);
		recieveData += (*buffer)[i];
	}

	int op = recieveData.find("<info>") + 6;
	int ed = recieveData.find("</info>");
	if (ed <=op)
		dl->setTitle("An error occured on server");
	else
	{
		string ret(recieveData, op, ed - op);
		//sprintf(buf, "%s", ret);
		dl->setTitle(ret);
	}
}

//MainLayer *MainLayer::instance=MainLayer::create();

//MainLayer *MainLayer::getInstance()
//{
//	return instance;
//}