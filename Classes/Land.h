#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Land:public Ref
{
public:
	Land();
	virtual ~Land();
	virtual bool init();
	CREATE_FUNC(Land);
	void scroll(float speed);
	Size getOneLandSize();
	/*…Ë÷√Œª”“«Ω*/
	void turnRightWall();
	static Size getOneSize();
protected:
	Point origin;
	Size visibleSize;
	void setOrigin(Point origin, Point anchor);
	CC_SYNTHESIZE_READONLY(int, count, Count);
	CC_SYNTHESIZE_READONLY(__Array*, lands, Lands);
private:
	Size _landSize;
};
