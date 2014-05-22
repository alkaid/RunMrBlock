#include "WelcomeScene.h"
#include "Background.h"
#include "GameScene.h"
#include "R.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	_leftwall = nullptr;
	_rightwall = nullptr;
}

WelcomeLayer::~WelcomeLayer()
{
	CC_SAFE_RELEASE_NULL(_leftwall);
	CC_SAFE_RELEASE_NULL(_rightwall);
}

Scene* WelcomeLayer::scene()
{
	WelcomeLayer* layer = WelcomeLayer::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	auto bg = LayerColor::create(Color4B(0, 0, 0, 255));
	scene->addChild(bg,-1);
	return scene;
}

bool WelcomeLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		//init land
		_leftwall = Land::create();
		_leftwall->retain();
		Ref* obj=NULL;
		CCARRAY_FOREACH(_leftwall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			this->addChild(sprite);
		};
		_rightwall = Land::create();
		_rightwall->retain();
		_rightwall->turnRightWall();
		CCARRAY_FOREACH(_rightwall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			this->addChild(sprite);
		}
		//init hero
		//_bird = Bird::creat();
		//_bird->setPosition(origin.x + visibleSize.width / 2, origin.y + _land->getOneLandSize().height + (visibleSize.height - _land->getOneLandSize().height) / 2);
		//_batchNode->addChild(_bird);
		//_bird->idle();
		//init logo
		/*Sprite* logo = Sprite::createWithSpriteFrameName(R::text_game_name);
		logo->setPosition(_bird->getPositionX(), _bird->getPositionY() + _bird->getContentSize().height/2+40);
		_batchNode->addChild(logo);*/
		//init menu
		Sprite* btnRate = Sprite::createWithSpriteFrameName(R::btn_rate);
		Sprite* btnPlay = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnPlaySelected = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnRank = Sprite::createWithSpriteFrameName(R::btn_rank);
		auto itemRate = MenuItemSprite::create(btnRate, btnRate);
		auto itemRank = MenuItemSprite::create(btnRank, btnRank);
		auto itemPlay = MenuItemSprite::create(btnPlay, btnPlaySelected, NULL, [](Ref* obj){
			log("onStartButton click....");
			TransitionScene* scene = TransitionFade::create(0.5f, GameScene::create());
			Director::getInstance()->replaceScene(scene);
		});
		itemRate->setAnchorPoint(Point(0.5, 0));
		itemRank->setAnchorPoint(Point(0.5, 0));
		itemPlay->setAnchorPoint(Point(0.5, 0));
		itemRate->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2);
		itemPlay->setPosition(itemRate->getPositionX() - itemPlay->getContentSize().width / 2 - 20, itemRate->getPositionY() - itemRate->getContentSize().height - 40);
		itemRank->setPosition(itemRate->getPositionX() + itemRank->getContentSize().width / 2 + 20, itemPlay->getPositionY() );
		Menu* menu = Menu::create(itemPlay,itemRank,itemRate,NULL);
		menu->setPosition(origin);
		this->addChild(menu,1);

		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeLayer::update(float dt)
{
	_leftwall->scroll(2);
	_rightwall->scroll(2);
}

