#pragma once
#include "AppMacro.h"
#include "BaseLayer.h"

USING_NS_CC;

class Background:public BaseLayer
{
public:
	Background();
	virtual ~Background();
	virtual bool init();
	CREATE_FUNC(Background);
private:

};
