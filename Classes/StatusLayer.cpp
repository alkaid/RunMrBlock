#include "StatusLayer.h"
#include "R.h"
#include "GameScene.h"
#include "AdmobHelper.h"
#include "UmengConfig.h"
#include "StringsRes.h"

USING_NS_CC;

const int StatusLayer::GUIDE_STEPS = 4;

StatusLayer::StatusLayer()
{
	isNewRecord = false;
	_scoreLabel = nullptr;
	_scoreResult = nullptr;
	_clip = nullptr;
	_guideLeftHand = nullptr;
	//_guideLeftHigh = nullptr;
	_stencil = nullptr;
	_currentGuideStep = 0;
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
		_scoreLabel->setVisible(false);
		whiteSprite = Sprite::createWithSpriteFrameName(R::rect_small_white);
		whiteSprite->setScale(100);
		whiteSprite->setOpacity(0);
		this->addChild(whiteSprite, 10000);
		bRet = true;
	} while (0);
	return bRet;
}

void StatusLayer::onNextGuide()
{
	++_currentGuideStep;
	//添加该层触摸 
	if (_currentGuideStep <= 1){
		_status = guide;
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, Event *unused_event)->bool
		{
			Point start = touch->getStartLocation();
			switch (this->_currentGuideStep)
			{
			case 1:
				//第一步引导 仅响应左边区域 屏蔽右边区域
				return (start.x > this->origin.x + this->visibleSize.width / 2);
				break;
			case 2:
				//第2步引导 仅响应右边区域 屏蔽左边区域
				return (start.x < this->origin.x + this->visibleSize.width / 2);
				break;
			case 3:
				return false;
				break;
			case 4:
				return false;
				break;
			default:
				return false;
				break;
			}
		};
		dispatcher->addEventListenerWithFixedPriority(listener, -100);
	}else if (_currentGuideStep > GUIDE_STEPS){
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		dispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		onGameStart();
		return;
	}
	if (_currentGuideStep==1){
		_clip = ClippingNode::create();
		_clip->setInverted(true);
		LayerColor* back = LayerColor::create(Color4B(0, 0, 0, 100));
		_clip->addChild(back);
		this->addChild(_clip);
		//clip->setStencil(_guideLeftHigh);
		_stencil = DrawNode::create();
		Point rect[] = { Point(0, 0), Point(visibleSize.width/2,0),Point(visibleSize.width/2,visibleSize.height),Point(0,visibleSize.height) };
		_stencil->drawPolygon(rect, 4, Color4F(1, 1, 1, 1), 0, Color4F(1, 1, 1, 1));
		_clip->setStencil(_stencil);
		_guideLeftHand = Sprite::createWithSpriteFrameName(R::guide_left_hand);
		_guideLeftHand->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 4);
		//_guideLeftHigh = Sprite::createWithSpriteFrameName(R::guide_left_high);
		//_guideLeftHigh->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2);
		//this->addChild(_guideLeftHigh);
		_guideTxt1 = Sprite::createWithSpriteFrameName(R::guide_txt_1);
		_guideTxt1->setAnchorPoint(Point(0.5, 1));
		_guideTxt1->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
		this->addChild(_guideLeftHand);
		this->addChild(_guideTxt1,100);
		ActionInterval* scaleBig = ScaleBy::create(0.25f, 0.95f);
		ActionInterval* scaleBack = scaleBig->reverse();
		_guideLeftHand->runAction(RepeatForever::create(Sequence::create(scaleBig,scaleBack, nullptr)));
	}
	else if (_currentGuideStep == 2){
		_stencil->setPosition(origin.x + visibleSize.width / 2, origin.y);
		_guideLeftHand->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), CallFunc::create([this](){
			_guideRightHand = Sprite::createWithSpriteFrameName(R::guide_left_hand);
			_guideRightHand->setPosition(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.height / 4);
			_guideRightHand->setFlippedX(true);
			this->addChild(_guideRightHand);
			ActionInterval* scaleBig = ScaleBy::create(0.25f, 0.95f);
			ActionInterval* scaleBack = scaleBig->reverse();
			_guideRightHand->runAction(FadeIn::create(0.5f));
			_guideRightHand->runAction(RepeatForever::create(Sequence::create(scaleBig, scaleBack, nullptr)));
		})));
		//_guideLeftHigh->setPosition(origin.x + visibleSize.width / 4 * 3, origin.y + visibleSize.height / 2);
		//_guideLeftHand->stopAllActions();
		_guideTxt1->runAction(Sequence::create(FadeOut::create(0.3f), CallFunc::create([this](){
			this->removeChild(_guideTxt1);
			_guideTxt2 = Sprite::createWithSpriteFrameName(R::guide_txt_2);
			_guideTxt2->setAnchorPoint(Point(0.5, 1));
			_guideTxt2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
			this->addChild(_guideTxt2);
			_guideTxt2->runAction(FadeIn::create(0.5f));
		}), nullptr));
	}
	else if (_currentGuideStep == 3){
		_guideTxt2->runAction(Sequence::create(FadeOut::create(0.3f), CallFunc::create([this](){
			this->removeChild(_clip);
			this->removeChild(_guideTxt2);
			_guideTxt3 = Sprite::createWithSpriteFrameName(R::guide_txt_3);
			_guideTxt3->setAnchorPoint(Point(0.5, 1));
			_guideTxt3->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
			this->addChild(_guideTxt3);
			_guideTxt3->runAction(FadeIn::create(0.5f));
		}), nullptr));
		_guideRightHand->runAction(Sequence::createWithTwoActions(FadeOut::create(0.3f), CallFunc::create([this](){
			_guideLeftHand->runAction(FadeIn::create(0.5f));
			_guideRightHand->runAction(FadeIn::create(0.5f));
		})));
	}
	else if (_currentGuideStep == 4){
		_guideTxt3->runAction(Sequence::create(FadeOut::create(0.3f), CallFunc::create([this](){
			this->removeChild(_guideTxt3);
			_guideTxt5 = Sprite::createWithSpriteFrameName(R::guide_txt_5);
			_guideTxt5->setAnchorPoint(Point(0.5, 1));
			_guideTxt5->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50);
			this->addChild(_guideTxt5);
			_guideTxt5->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create([this](){
				_guideTxt5->runAction(Sequence::create(FadeOut::create(5.0f), CallFunc::create([this](){
					this->removeChild(_guideTxt5);
					onNextGuide();
				}), nullptr));
			}), nullptr));
		}), nullptr));
		_guideLeftHand->runAction(FadeOut::create(0.3f));
		_guideRightHand->runAction(FadeOut::create(0.3f));
	}
}

void StatusLayer::onGameStart()
{
	_status = start;
	_scoreLabel->setString("0");
	_scoreLabel->setVisible(true);
}

void StatusLayer::onGamePlaying(int score)
{
	_scoreLabel->setString(__String::createWithFormat("%d",score)->getCString());
}

void StatusLayer::onGameReady()
{

}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	_status = GameStatus::end;
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
	auto  itemRestart = MenuItemSprite::create(restartBtn, restartBtnActive, NULL, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
	auto menu = Menu::create(itemRestart, NULL);
	menu->setPosition(this->origin);
	itemRestart->setPosition(Point(this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2 - 10, this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);
	this->addChild(tmpNode);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrameName(R::btn_rate);
	Sprite* rateBtnActive = Sprite::createWithSpriteFrameName(R::btn_rate);
	rateBtnActive->setPositionY(-4);
	auto  itemRate = MenuItemSprite::create(rateBtn, rateBtnActive, NULL, [](Ref* obj){
		
	});
	itemRate->setPosition(Point(this->visibleSize.width / 2+restartBtn->getContentSize().width / 2 + 10 , itemRestart->getPositionY()));
	menu->addChild(itemRate);

	//share
	Sprite* btnShare = Sprite::createWithSpriteFrameName(R::btn_share);
	Sprite* btnShareSelected = Sprite::createWithSpriteFrameName(R::btn_share);
	btnShareSelected->setPositionY(-4);
	String shareText;
	shareText.initWithFormat(StringRes::getInstance()->getString(R::string::share_score).c_str(), currentScore);
	log(shareText.getCString());
	auto itemShare = MenuItemSprite::create(btnShare, btnShareSelected, NULL, [shareText](Ref* obj){
		if (AdmobHelper::isAdShowing)
		{
			AdmobHelper::hideAd();
		}
		std::string path = "screenshot.png";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		path="/sdcard/temp/screenshort_runmrblock.png";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		
#endif
		utils::captureScreen([shareText](bool b, const std::string& name){
			log("catpture: %s", name.c_str());
#ifdef UMENG
			if(b){
				// 获取一个CCUMSocialSDK实例
				CCUMSocialSDK *sdk = CCUMSocialSDK::create("53a4054e56240bbe7600968c");
				// 设置友盟appkey,如果create中设置了不用调用该函数
				// sdk->setAppKey("4eaee02c527015373b000003");
				// **********************   设置平台信息  ***************************
				// sdk->setQQAppIdAndAppKey("设置QQ的app id", "appkey");
				sdk->setWeiXinAppId("wxe53a15e94b6977e0");
				// sdk->setYiXinAppKey("设置易信和易信朋友圈的app id");
				// sdk->setLaiwangAppInfo("设置来往和来往动态的app id", 
				//                  "设置来往和来往动态的app key", "我的应用名");
				sdk->setFacebookAppId("fb1451052891808897");
				//     // 打开或者关闭log
				sdk->setLogEnable(true);
				// **********************   END ***************************

				// 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
				sdk->setTargetUrl(nullptr);
				// 设置友盟分享面板上显示的平台
				vector<int>* platforms = new vector<int>();

				platforms->push_back(FACEBOOK);
				platforms->push_back(TWITTER);
				platforms->push_back(SINA);
				platforms->push_back(WEIXIN);
				platforms->push_back(WEIXIN_CIRCLE);

				// 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
				sdk->setPlatforms(platforms);

				// 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
				// 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
				sdk->openShare(shareText.getCString(), name.c_str(), share_selector(umengShareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				sdk->openShare(shareText.getCString(), name.c_str(), share_selector(umengShareCallback));
#endif
			}
#endif	//UMENG
		}, path.c_str());
		if (!AdmobHelper::isAdShowing)
		{
			AdmobHelper::showAd();
		}

	});
	itemShare->setPosition(this->visibleSize.width / 2, btnShare->getContentSize().height + 10);
	menu->addChild(itemShare);

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
