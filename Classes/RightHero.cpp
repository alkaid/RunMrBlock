#include "RightHero.h"
#include "R.h"

USING_NS_CC;


RightHero::RightHero()
{
	_dieAction = nullptr;
	_afraidAction = nullptr;
	_idleAction = nullptr;
	_proudAction = nullptr;
}

RightHero::~RightHero()
{

}

RightHero* RightHero::creat()
{
	RightHero* sprite = new RightHero();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool RightHero::init()
{
	bool bRet = false;
	do
	{
		//random color for a new bird
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName(R::hero_right));
		//create idle action

		bRet = true;
	} while (0);
	return bRet;
}

void RightHero::idle()
{

}

void RightHero::proud()
{

}

void RightHero::afraid()
{

}

void RightHero::die()
{

}
