#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LeftHero : public Sprite{
public:
	LeftHero();
	virtual ~LeftHero();
	static LeftHero* creat();
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