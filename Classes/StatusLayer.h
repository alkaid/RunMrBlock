#pragma once
#include "AppMacro.h"
#include "BaseLayer.h"

USING_NS_CC;

enum GameStatus
{
	guide, ready, start, end
};

class StatusDelegate
{
public:
	virtual void onGameStart() = 0;
	virtual void onGameReady() = 0;
	virtual void onGameEnd(int curScore, int bestScore) = 0;
	virtual void onGamePlaying(int score) = 0;
	virtual void onNextGuide() = 0;
	CC_SYNTHESIZE(GameStatus, _status, Status);
};

class StatusLayer:public BaseLayer,public StatusDelegate
{
public:
	StatusLayer();
	virtual ~StatusLayer();
	virtual bool init();
	CREATE_FUNC(StatusLayer);
	//void showReady();
	virtual void onGameStart();
	virtual void onGamePlaying(int score);
	virtual void onGameReady();
	virtual void onGameEnd(int curScore, int bestScore);
	virtual void onNextGuide();
private:
	static const int GUIDE_STEPS;
	int _currentGuideStep;
	bool isNewRecord;
	int currentScore;
	LabelAtlas* _scoreLabel;
	/*计分榜上该局分数*/
	LabelAtlas* _scoreResult;
	//Sprite* blink;
	Sprite* getreadySprite;
	Sprite* tutorialSprite;
	Sprite* whiteSprite;
	int bestScore;
	int tmpScore;
	//guide
	ClippingNode* _clip;
	DrawNode* _stencil;
	Sprite* _guideLeftHand;
	//Sprite* _guideLeftHigh;
	Sprite* _guideRightHand;
	Sprite* _guideTxt1;
	Sprite* _guideTxt2;
	Sprite* _guideTxt3;
	Sprite* _guideTxt4;
	Sprite* _guideTxt5;

	/*void setBlinkSprite();

	void blinkAction();*/

	void menuRestartCallback(Object *sender);

	void showReadyStatus();

	void showStartStatus();

	void showOverStatus(int curScore, int bestScore);

	void blinkFullScreen();

	void fadeInGameOver();

	void jumpToScorePanel();

	void fadeInRestartBtn();

	void refreshScoreCallback();

	void refreshScoreExecutor(float dt);

	std::string getMedalsName(int score);

	
};