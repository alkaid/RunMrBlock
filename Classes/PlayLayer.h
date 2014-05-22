#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"

USING_NS_CC;

class PlayDelegate
{
public:
	//virtual void onTouchEnded(bool isRight) = 0;
	//virtual void onTouchBegin(bool isRight) = 0;
	//virtual void onTouchMoved(bool isRight) = 0;
	virtual void onTouchModeChanged(Point oldMode, Point newMode) = 0;
	virtual void onHolding(float dt) = 0;
private:
	
};

class PlayLayer:public BaseLayer
{
public:
	PlayLayer();
	virtual ~PlayLayer();
	CC_SYNTHESIZE(PlayDelegate*, _delegate, Delegate);
	virtual bool init();
	CREATE_FUNC(PlayLayer);
	virtual void update(float dt) override;
private:
	/*用Point来表示触摸,(0,0)表示没有触碰屏幕,(1,0)表示仅触摸左边屏幕，(0,1)表示仅触摸右边屏幕，(1,1)表示左右屏幕均触摸*/
	Point _touchMode;
	float _leftDt;
	float _rightDt;
};
