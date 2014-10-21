#pragma once
#include "AppMacro.h"
#include "Land.h"
#include "LeftHero.h"
#include "RightHero.h"
#include "BaseLayer.h"
#include "PlayLayer.h"
#include "StatusLayer.h"

USING_NS_CC;

class GameLayer :public BaseLayer,public PlayDelegate
{
public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init(StatusDelegate* delegate);
	//CREATE_FUNC(GameLayer);
	static GameLayer* create(StatusDelegate* delegate) \
	{ \
	GameLayer *pRet = new GameLayer(); \
	if (pRet && pRet->init(delegate)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
	}
	virtual void update(float dt) override;
	//CC_SYNTHESIZE(StatusDelegate*, _delegate, Delegate);
	CC_SYNTHESIZE(PhysicsWorld*, _world, PhyWorld);
	void onTouchModeChanged(Point oldMode, Point newMode) override;
	void onHolding(float dt) override;
private:
	StatusDelegate* _delegate;
	Land* _leftWall;
	Land* _rightWall;
	float _heroWidth;
	LeftHero* _leftHero;
	RightHero* _rightHero;
	float _leftHeroSpeed;
	float _rightHeroSpeed;
	float _leftDt;
	float _rightDt;
	Point _touchMode;
	float _thornSpeed;
	/*����ʹ�õ��ϰ�*/
	__Array* _thornsUsed;
	/*�ϰ��أ����ڻ��ճ�����Ļ���ϰ�*/
	__Array* _thornPool;
	/*�ϰ��߶�...��ԴͼƬ���*/
	std::vector<float> _thornsHeights;
	int _score;
	bool _isNewRecord;
	std::vector<bool> _isNews;
	//��������ָ��
	bool _isLeftCollisionWall;
	bool _isRightCollisionWall;
	int _guideStep;

	void createThorns();
	void checkHit();
	void gameOver();
	bool collision(Node* hero,Node* thorn);
	void leftHeroDead();
	void rightHeroDead();
};