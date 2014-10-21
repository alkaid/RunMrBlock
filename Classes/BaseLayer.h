#pragma once

#include "AppMacro.h"

USING_NS_CC;

class BaseLayer :public cocos2d::Layer
{
public:
	virtual bool init();
protected:
	Point origin;
	Size visibleSize;
private:

};
