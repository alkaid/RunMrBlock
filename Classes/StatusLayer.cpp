#include "StatusLayer.h"
#include "R.h"
#include "GameScene.h"

StatusLayer::StatusLayer()
{
	isNewRecord = false;
	_scoreLabel = nullptr;
	_scoreResult = nullptr;
	currentScore = 0;
	tmpScore = 0;
}

StatusLayer::~StatusLayer()
{

}

bool StatusLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		_scoreLabel = LabelAtlas::create("0", R::number_l, 24, 36, '0');
		_scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height* 4 / 5);
		this->addChild(_scoreLabel);
		whiteSprite = Sprite::createWithSpriteFrameName(R::rect_small_white);
		whiteSprite->setScale(100);
		whiteSprite->setOpacity(0);
		this->addChild(whiteSprite, 10000);
		bRet = true;
	} while (0);
	return bRet;
}

void StatusLayer::onGameStart()
{
	_scoreLabel->setString("0");
}

void StatusLayer::onGamePlaying(int score)
{
	_scoreLabel->setString(__String::createWithFormat("%d",score)->getCString());
}

void StatusLayer::onGameReady()
{

}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	this->showOverStatus(curScore, bestScore);
}

void StatusLayer::showOverStatus(int curScore, int bestScore) {
	this->currentScore = curScore;
	this->bestScore = bestScore;
	if (curScore > bestScore){
		this->bestScore = curScore;
		this->isNewRecord = true;
	}
	else{
		this->isNewRecord = false;
	}
	this->removeChild(_scoreLabel);
	this->blinkFullScreen();
}

void StatusLayer::blinkFullScreen(){
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn, fadeOut, NULL);
	CallFunc *actionDone = CallFuncN::create(CC_CALLBACK_0(StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver(){
	// create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrameName(R::text_over);
	gameoverSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 3));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFuncN::create(CC_CALLBACK_0(StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel(){
	// create the score panel
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrameName(R::bg_medal);
	scorepanelSprite->setPosition(Point(origin.x + this->visibleSize.width / 2, origin.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);

	//display the  best score on the score panel
	LabelAtlas*  bestScoreSprite = LabelAtlas::create(String::createWithFormat("%i", this->bestScore)->getCString(), R::number_m, 12, 14, '0');
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width - 28,40);
	scorepanelSprite->addChild(bestScoreSprite);
	_scoreResult = LabelAtlas::create(String::createWithFormat("%i",this->tmpScore)->getCString(), R::number_m, 12, 14, '0');
	_scoreResult->setAnchorPoint(Point(1, 0));
	_scoreResult->setPosition(scorepanelSprite->getContentSize().width - 28, 70);
	scorepanelSprite->addChild(_scoreResult);


	std::string medalsName = this->getMedalsName(currentScore);
	if (medalsName != "") {
		Sprite* medalsSprite = Sprite::createWithSpriteFrameName(medalsName);
		//medalsSprite->addChild(this->blink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}

	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if (this->isNewRecord){
		Sprite* newTagSprite = Sprite::createWithSpriteFrameName(R::tip_new);
		newTagSprite->setPosition(-20, 2);
		bestScoreSprite->addChild(newTagSprite);
	}

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f, Point(origin.x + this->visibleSize.width / 2, origin.y + this->visibleSize.height / 2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFuncN::create(CC_CALLBACK_0(StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorepanelSprite->stopAllActions();
	//SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn(){
	Node * tmpNode = Node::create();

	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrameName(R::btn_play);
	Sprite* restartBtnActive = Sprite::createWithSpriteFrameName(R::btn_play);
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn, restartBtnActive, NULL, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Point(this->origin.x + this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->origin.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrameName(R::btn_rate);
	rateBtn->setPosition(Point(this->origin.x + this->visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->origin.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
	//tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);

	CallFunc *actionDone = CallFuncN::create(CC_CALLBACK_0(StatusLayer::refreshScoreCallback, this));
	auto sequence = Sequence::createWithTwoActions(fadeIn, actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback(){
	this->tmpScore = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor), 0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt){
	this->tmpScore++;
	_scoreResult->setString(String::createWithFormat("%i", this->tmpScore)->getCString());
	if (this->tmpScore > this->currentScore){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

//void StatusLayer::setBlinkSprite() {
//	this->blink = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("blink_00"));
//	Animation *animation = Animation::create();
//	animation->setDelayPerUnit(0.1f);
//	for (int i = 0; i < 3; i++){
//		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
//		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
//		animation->addSpriteFrame(frame);
//	}
//	for (int i = 2; i >= 0; i--){
//		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
//		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
//		animation->addSpriteFrame(frame);
//	}
//	auto animate = Animate::create(animation);
//	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction, this));
//	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
//	blink->runAction(RepeatForever::create(sequence));
//}
//
//void StatusLayer::blinkAction() {
//	if (this->blink && this->blink->getParent()) {
//		Size activeSize = this->blink->getParent()->getContentSize();
//		this->blink->setPosition(rand() % ((int)(activeSize.width)), rand() % ((int)(activeSize.height)));
//	}
//}

std::string StatusLayer::getMedalsName(int score){
	//this->setBlinkSprite();

	//display the golden silver or bronze iron
	std::string medalsName = "";
	if (this->currentScore >= 0 && this->currentScore < 20){//iron medals
		medalsName = R::medal_0;
	}
	else if (this->currentScore >= 20 && currentScore < 30){//bronze medals
		medalsName = R::medal_1;
	}
	else if (currentScore >= 30 && currentScore < 50){//silver medals
		medalsName = R::medal_2;
	}
	else if (currentScore >= 50){//golden medals
		medalsName = R::medal_3;
	}
	return medalsName;
}

void StatusLayer::menuRestartCallback(Object* pSender){
	//SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

