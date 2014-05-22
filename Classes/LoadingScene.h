#pragma once
#include "BaseLayer.h"

USING_NS_CC;

class LoadingLayer:public BaseLayer
{
public:
	static Scene*  scene();
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
protected:
private:
};

