#include "Background.h"
#include "R.h"

USING_NS_CC;

Background::Background()
{

}

Background::~Background()
{

}

bool Background::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		/*time_t t = time(NULL);
		tm* lt = localtime(&t);
		int hour = lt->tm_hour;
		const char* bgStr = (hour > 6 && hour < 17) ? R::bg_day : R::bg_night;
		Sprite* measureB = Sprite::createWithSpriteFrameName(bgStr);
		SpriteBatchNode* batchNode = SpriteBatchNode::createWithTexture(CCTextureCache::getInstance()->getTextureForKey(R::main_png));
		this->addChild(batchNode);
		batchNode->setPosition(origin);
		int bgCount = (visibleSize.width * 2 - 1) / measureB->getContentSize().width;
		for (int i = 0; i < bgCount;i++)
		{
		Sprite* b = Sprite::createWithSpriteFrameName(bgStr);
		b->setAnchorPoint(Point::ZERO);
		b->setPosition(origin.x + b->getContentSize().width*i, origin.y);
		b->getTexture()->setAliasTexParameters();
		batchNode->addChild(b);
		}*/
		bRet = true;
	} while (0);
	return bRet;
}

