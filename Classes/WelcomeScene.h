#pragma once

#include "AppMacro.h"
#include "BaseLayer.h"
#include "Land.h"
#include <string>

USING_NS_CC;


class WelcomeLayer:public BaseLayer
{
public:
	WelcomeLayer();
	virtual ~WelcomeLayer();
	static Scene*  scene();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	virtual void update(float dt);
protected:
	Land* _leftwall;
	Land* _rightwall;
private:
};
