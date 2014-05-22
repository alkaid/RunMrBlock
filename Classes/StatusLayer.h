#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "GameLayer.h"

USING_NS_CC;

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
private:
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
