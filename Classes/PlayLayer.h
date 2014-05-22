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
	/*��Point����ʾ����,(0,0)��ʾû�д�����Ļ,(1,0)��ʾ�����������Ļ��(0,1)��ʾ�������ұ���Ļ��(1,1)��ʾ������Ļ������*/
	Point _touchMode;
	float _leftDt;
	float _rightDt;
};
