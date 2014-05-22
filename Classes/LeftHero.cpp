#include "LeftHero.h"
#include "R.h"

USING_NS_CC;


LeftHero::LeftHero()
{
	_dieAction = nullptr;
	_afraidAction = nullptr;
	_idleAction = nullptr;
	_proudAction = nullptr;
}

LeftHero::~LeftHero()
{

}

LeftHero* LeftHero::creat()
{
	LeftHero* sprite = new LeftHero();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool LeftHero::init()
{
	bool bRet = false;
	do
	{
		//random color for a new bird
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName(R::hero_left));
		//create idle action
		
		bRet = true;
	} while (0);
	return bRet;
}

void LeftHero::idle()
{

}

void LeftHero::proud()
{

}

void LeftHero::afraid()
{

}

void LeftHero::die()
{

}
