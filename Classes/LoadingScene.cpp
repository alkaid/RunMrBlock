#include "LoadingScene.h"
#include "R.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "StringsRes.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LoadingLayer::scene()
{
	srand((unsigned)time(nullptr));
	LoadingLayer* layer = LoadingLayer::create();
	Scene* scene = Scene::create();
	LayerColor* back = LayerColor::create(Color4B::WHITE);
	scene->addChild(back);
	scene->addChild(layer);
	return scene;
}

bool LoadingLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		Sprite* background = Sprite::create(R::splash);
		background->setScale(2.0);
		background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3*2);
		this->addChild(background);
		//Texture2D::PVRImagesHavePremultipliedAlpha(true);
		TextureCache::getInstance()->addImageAsync(R::main_png, [](Texture2D* texture){
			CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(R::main_plist);
			TextureCache::getInstance()->addImageAsync(R::lang_png, [](Texture2D* texture){
				CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(R::lang_plist);
				//load audio
				SimpleAudioEngine::getInstance()->preloadBackgroundMusic(R::a_bg_playing);
				SimpleAudioEngine::getInstance()->preloadEffect(R::a_thorn);
				SimpleAudioEngine::getInstance()->preloadEffect(R::a_wall);
				//load strings
				StringRes::getInstance();
				//TransitionScene* scene = TransitionScene::create(1.0, WelcomeLayer::scene());
				//TODO ע�� �˴�������TransitionScene::create(),�ᵼ�µڶ���scene��Menu�����Ч
				TransitionScene* scene = TransitionFade::create(1.0, WelcomeLayer::scene());
				Director::getInstance()->replaceScene(scene);
			});
			
		});
		bRet = true;
	} while (0);
	return bRet;
}
