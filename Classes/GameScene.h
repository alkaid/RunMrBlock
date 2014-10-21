#pragma once
#include "AppMacro.h"

USING_NS_CC;

class GameScene:public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
private:

};
