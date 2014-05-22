#include "LoadingScene.h"
#include "R.h"
#include "WelcomeScene.h"

USING_NS_CC;

Scene* LoadingLayer::scene()
{
	srand((unsigned)time(nullptr));
	LoadingLayer* layer = LoadingLayer::create();
	Scene* scene = Scene::create();
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
		background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		this->addChild(background);
		//Texture2D::PVRImagesHavePremultipliedAlpha(true);
		TextureCache::getInstance()->addImageAsync(R::main_png, [](Texture2D* texture){
			CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(R::main_plist);
			//TransitionScene* scene = TransitionScene::create(1.0, WelcomeLayer::scene());
			//TODO 注意 此处不能用TransitionScene::create(),会导致第二个scene的Menu点击无效
			TransitionScene* scene = TransitionFade::create(1.0, WelcomeLayer::scene());
			Director::getInstance()->replaceScene(scene);
		});
		bRet = true;
	} while (0);
	return bRet;
}
