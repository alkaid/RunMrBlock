#pragma once
#include "cocos2d.h"
#include "Land.h"
#include "LeftHero.h"
#include "RightHero.h"
#include "BaseLayer.h"
#include "PlayLayer.h"

USING_NS_CC;

enum GameStatus
{
	ready,start,end
};

class StatusDelegate
{
public:
	virtual void onGameStart() = 0;
	virtual void onGameReady() = 0;
	virtual void onGameEnd(int curScore, int bestScore) = 0;
	virtual void onGamePlaying(int score) = 0;
};

class GameLayer :public BaseLayer,public PlayDelegate
{
public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void update(float dt) override;
	CC_SYNTHESIZE(StatusDelegate*, _delegate, Delegate);
	CC_SYNTHESIZE(PhysicsWorld*, _world, PhyWorld);
	void onTouchModeChanged(Point oldMode, Point newMode) override;
	void onHolding(float dt) override;
private:
	Land* _leftWall;
	Land* _rightWall;
	float _heroWidth;
	LeftHero* _leftHero;
	RightHero* _rightHero;
	float _leftHeroSpeed;
	float _rightHeroSpeed;
	float _leftDt;
	float _rightDt;
	GameStatus _status;
	Point _touchMode;
	float _thornSpeed;
	/*正在使用的障碍*/
	__Array* _thornsUsed;
	/*障碍池，用于回收超出屏幕的障碍*/
	__Array* _thornPool;
	/*障碍高度...资源图片相关*/
	std::vector<float> _thornsHeights;
	int _score;
	bool _isNewRecord;
	std::vector<bool> _isNews;
	void createThorns();
	void checkHit();
	void gameOver();
	bool collision(Node* hero,Node* thorn);
};