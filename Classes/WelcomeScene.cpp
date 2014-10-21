#include "WelcomeScene.h"
#include "Background.h"
#include "GameScene.h"
#include "R.h"
#include "AdmobHelper.h"
#include "UmengConfig.h"
#include "StringsRes.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	_leftwall = nullptr;
	_rightwall = nullptr;
}

WelcomeLayer::~WelcomeLayer()
{
	CC_SAFE_RELEASE_NULL(_leftwall);
	CC_SAFE_RELEASE_NULL(_rightwall);
}

Scene* WelcomeLayer::scene()
{
	WelcomeLayer* layer = WelcomeLayer::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	auto bg = LayerColor::create(Color4B(130, 217, 212, 255));
	scene->addChild(bg,-1);
	return scene;
}

bool WelcomeLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		//init land
		_leftwall = Land::create();
		_leftwall->retain();
		Ref* obj=NULL;
		CCARRAY_FOREACH(_leftwall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			this->addChild(sprite);
		};
		_rightwall = Land::create();
		_rightwall->retain();
		_rightwall->turnRightWall();
		CCARRAY_FOREACH(_rightwall->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			this->addChild(sprite);
		}
		//init hero
		//_bird = Bird::creat();
		//_bird->setPosition(origin.x + visibleSize.width / 2, origin.y + _land->getOneLandSize().height + (visibleSize.height - _land->getOneLandSize().height) / 2);
		//_batchNode->addChild(_bird);
		//_bird->idle();
		//init logo
		/*Sprite* logo = Sprite::createWithSpriteFrameName(R::text_game_name);
		logo->setPosition(_bird->getPositionX(), _bird->getPositionY() + _bird->getContentSize().height/2+40);
		_batchNode->addChild(logo);*/
		//init menu
		Sprite* btnRate = Sprite::createWithSpriteFrameName(R::btn_rate);
		Sprite* btnPlay = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnPlaySelected = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnRank = Sprite::createWithSpriteFrameName(R::btn_rank);
		Sprite* btnShare = Sprite::createWithSpriteFrameName(R::btn_share);
		Sprite* btnShareSelected = Sprite::createWithSpriteFrameName(R::btn_share);
		auto itemRate = MenuItemSprite::create(btnRate, btnRate);
		auto itemRank = MenuItemSprite::create(btnRank, btnRank);
		auto itemPlay = MenuItemSprite::create(btnPlay, btnPlaySelected, NULL, [](Ref* obj){
			log("onStartButton click....");
			TransitionScene* scene = TransitionFade::create(0.5f, GameScene::create());
			Director::getInstance()->replaceScene(scene);
		});
		auto itemShare = MenuItemSprite::create(btnShare, btnShareSelected, NULL, [](Ref* obj){
#ifdef UMENG
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
			sdk->setTargetUrl("http://www.umeng.com/social");
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
			sdk->openShare(StringRes::getInstance()->getString(R::string::share_intro).c_str(), NULL, share_selector(umengShareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			sdk->openShare(StringRes::getInstance()->getString(R::string::share_intro).c_str(), NULL, share_selector(umengShareCallback));
#endif
#endif
		});
		itemRate->setAnchorPoint(Point(0.5, 0));
		itemRank->setAnchorPoint(Point(0.5, 0));
		itemPlay->setAnchorPoint(Point(0.5, 0));
		itemShare->setAnchorPoint(Point(0.5, 0));
		itemRate->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2);
		itemPlay->setPosition(itemRate->getPositionX() - itemPlay->getContentSize().width / 2 - 20, itemRate->getPositionY() - itemRate->getContentSize().height - 40);
		itemRank->setPosition(itemRate->getPositionX() + itemRank->getContentSize().width / 2 + 20, itemPlay->getPositionY() );
		itemShare->setPosition(itemRate->getPositionX(), itemPlay->getPositionY()-100);
		Menu* menu = Menu::create(itemPlay,itemRank,itemRate,itemShare,NULL);
		menu->setPosition(origin);
		this->addChild(menu,1);

		this->scheduleUpdate();

		AdmobHelper::showAd();


		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeLayer::update(float dt)
{
	_leftwall->scroll(2);
	_rightwall->scroll(2);
}