#pragma once
#include "AppMacro.h"

USING_NS_CC;

class RightHero : public Sprite{
public:
	RightHero();
	virtual ~RightHero();
	static RightHero* creat();
	void idle();
	void proud();
	void afraid();
	void die();
protected:
	Action* _idleAction;
	Action* _proudAction;
	Action* _afraidAction;
	Action* _dieAction;
	virtual bool init();
};