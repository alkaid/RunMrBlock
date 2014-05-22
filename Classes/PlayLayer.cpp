#include "PlayLayer.h"


PlayLayer::PlayLayer()
{
	_delegate = nullptr;
	_touchMode = Point(0, 0);
	_leftDt = 0;
	_rightDt = 0;
}

PlayLayer::~PlayLayer()
{

}

bool PlayLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = [this](const std::vector<Touch*>& touches, Event *unused_event)->void
		{
			for (Touch* t : touches)
			{
				Point start = t->getStartLocation();
				Point old = Point(_touchMode);
				if (start.x > this->origin.x + this->visibleSize.width / 2){
					_touchMode.y=1;
					_rightDt = 0;
				}
				else{
					_touchMode.x = 1;
					_leftDt = 0;
				}
				this->_delegate->onTouchModeChanged(old, _touchMode);
				//this->_delegate->onTouchBegin(start.x > this->origin.x + this->visibleSize.width / 2);
			}
		};

		listener->onTouchesEnded = [this](const std::vector<Touch*>& touches, Event *unused_event)->void
		{
			for (Touch* t : touches)
			{
				Point start = t->getStartLocation();
				Point old = Point(_touchMode);
				if (start.x > this->origin.x + this->visibleSize.width / 2){
					_touchMode.y = 0;
					_rightDt = 0;
				}
				else{
					_touchMode.x = 0;
					_leftDt = 0;
				}
				this->_delegate->onTouchModeChanged(old, _touchMode);
			}
		};
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void PlayLayer::update(float dt)
{
	_leftDt += dt;
	_rightDt += dt;
	_delegate->onHolding(dt);
}

