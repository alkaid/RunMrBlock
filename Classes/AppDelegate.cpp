#include "AppDelegate.h"
#include "LoadingScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	initShareSDK();

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		glview->setFrameSize(640, 1136);
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// set dir
	std::vector<std::string> resDirOrders;
	LanguageType lan = Application::getInstance()->getCurrentLanguage();
	switch (lan)
	{
	case kLanguageChinese:
		resDirOrders.push_back("zh");
		break;
	case kLanguageEnglish:
	default:
		break;
	}
	resDirOrders.push_back("en");
	FileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);

    // create a scene. it's an autorelease object
    auto scene = LoadingLayer::scene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initShareSDK()
{   
	//C2DXShareSDK::open(CCString::create("1f043626e0a0"), false);
	////sina
	//CCDictionary *sinaConfigDict = CCDictionary::create();
	//sinaConfigDict->setObject(CCString::create("3658075933"), "app_key");
	//sinaConfigDict->setObject(CCString::create("c1cd752323e5da7f0837f62c78cd4d49"), "app_secret");
	//sinaConfigDict->setObject(CCString::create("http://coodroid.com/download/down.php?f=runmrblock&p=app"), "redirect_uri");
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);

	//// wechat
	//CCDictionary *wcConfigDict = CCDictionary::create();
	//wcConfigDict->setObject(CCString::create("wxe53a15e94b6977e0"), "app_id");
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wcConfigDict);
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiTimeline, wcConfigDict);
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiFav, wcConfigDict);

	////facebook 
	//CCDictionary *facebookDict = CCDictionary::create();
	//facebookDict->setObject(CCString::create("1451052891808897"), "api_key");
	//facebookDict->setObject(CCString::create("347ca95436a085340c58c66f064c5313"), "app_secret");
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFacebook, facebookDict);

	////twitter
	//CCDictionary *twitterConfigDict = CCDictionary::create();
	//twitterConfigDict->setObject(CCString::create("EpJ1BYWLuoPUF0GsU9NtKp2NN"), "consumer_key");
	//twitterConfigDict->setObject(CCString::create("u2Hvd8NzInYIysb0LwnVTssdPgxPFssuQEafu17DR9XP2XejLh"), "consumer_secret");
	//twitterConfigDict->setObject(CCString::create("http://coodroid.com/download/down.php?f=runmrblock&p=app"), "redirect_uri");
	//C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTwitter, twitterConfigDict);

}
