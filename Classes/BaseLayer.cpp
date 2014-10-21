#include "BaseLayer.h"

USING_NS_CC;

bool BaseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		origin = CCDirector::getInstance()->getVisibleOrigin();
		visibleSize = CCDirector::getInstance()->getVisibleSize();
		//ÍË³öÓÎÏ·
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)->void
		{
			String d;
			d.initWithFormat("keyCode=%i", keyCode);
			log(d.getCString());
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_BACKSPACE:
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance()->end();
			default:
				break;
			}
			
		};
		dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
		bRet = true;
	} while (0);
	return bRet;
}

