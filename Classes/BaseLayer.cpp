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
		bRet = true;
	} while (0);
	return bRet;
}

