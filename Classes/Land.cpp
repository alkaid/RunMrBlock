#include "Land.h"
#include "R.h"

USING_NS_CC;

Land::Land()
{
	count = 0;
	lands = NULL;
}

Land::~Land()
{
	CC_SAFE_RELEASE_NULL(lands);
}

bool Land::init()
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* measureLand = Sprite::createWithSpriteFrameName(R::land);
	_landSize = measureLand->getContentSize();
	count = (visibleSize.height * 2 - 1) / _landSize.height + 1;	//保证滚动连续
	lands = __Array::createWithCapacity(count);
	lands->retain();
	for (int i = 0; i < count; i++){
		Sprite* land = Sprite::createWithSpriteFrameName(R::land);
		land->setAnchorPoint(Point::ZERO);
		land->setPosition(origin.x, origin.y + land->getContentSize().height*i);
		land->getTexture()->setAliasTexParameters();
		lands->addObject(land);
	}
	return true;
}

void Land::scroll(float speed)
{
	Ref* obj = NULL;
	CCARRAY_FOREACH(lands, obj){
		Sprite* land = (Sprite*)obj;
		land->setPositionY(land->getPositionY() - speed);
	}
	for (int i = 0; i < count; i++){
		Sprite* land = (Sprite*)(lands->getObjectAtIndex(i));
		if (land->getPositionY() < origin.y - land->getContentSize().height){
			int last = i - 1 < 0 ? count - 1 : i - 1;
			Sprite* lastLand = (Sprite*)(lands->getObjectAtIndex(last));
			land->setPositionY(lastLand->getPositionY() + lastLand->getContentSize().height);
		}
	}
}

Size Land::getOneLandSize()
{
	return _landSize;
}

void Land::setOrigin(Point origin,Point anchor)
{
	for (int i = 0; i < count; i++){
		Sprite* land = (Sprite*)(lands->getObjectAtIndex(i));
		land->setAnchorPoint(anchor);
		land->setPosition(origin.x , origin.y + land->getContentSize().height*i);
	}
}

void Land::turnRightWall()
{
	this->setOrigin(Point(origin.x + visibleSize.width - _landSize.width, origin.y), Point::ZERO);
}

Size Land::getOneSize()
{
	Sprite* measureLand = Sprite::createWithSpriteFrameName(R::land);
	return measureLand->getContentSize();
}

