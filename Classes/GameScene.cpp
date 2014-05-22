#include "GameScene.h"
#include "GameLayer.h"
#include "StatusLayer.h"
#include "Background.h"
#include "PlayLayer.h"
#include "R.h"

USING_NS_CC;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::initWithPhysics());
		//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		this->getPhysicsWorld()->setGravity(Vect(0, 0));
		/*Background* backgroundLayer = Background::create();
		this->addChild(backgroundLayer);*/
		auto bg = LayerColor::create(Color4B(0, 0, 0, 255));
		this->addChild(bg);
		GameLayer* gameLayer = GameLayer::create();
		StatusLayer* statusLayer = StatusLayer::create();
		gameLayer->setDelegate(statusLayer);
		gameLayer->setPhyWorld(this->getPhysicsWorld());
		this->addChild(gameLayer);
		this->addChild(statusLayer);
		PlayLayer* playLayer = PlayLayer::create();
		playLayer->setDelegate(gameLayer);
		this->addChild(playLayer);
		bRet = true;
	} while (0);
	return bRet;
}
