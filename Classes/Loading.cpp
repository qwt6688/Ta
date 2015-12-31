#include "Loading.h"
#include "WelcomeScene.h"

Scene* Loading::createScene()
{
	auto scene =Scene::create();
	auto layer = Loading::create();
	scene->addChild(layer);

	return scene;
}

bool Loading:: init()
{
	if (!Layer::init())
	{
	   return false;
	
	}

	Size visition = Director::getInstance()->getVisibleSize();

	

	auto loading = Sprite::create("back1.png");
	loading->setPosition(Vec2(visition.width/2,visition.height/2));
	this->addChild(loading);
	loading->setScaleY(1.5f);
	
	m_nNumberSprites =5;
    
	auto loadBg = Sprite::create("sliderTrack.png");
	loadBg->setPosition(Vec2(visition.width/2,visition.height*0.25));
	this->addChild(loadBg);
	loadBg->setScale(1.0f);

	loadProgress = ProgressTimer::create(Sprite::create("sliderProgress.png"));
	loadProgress->setBarChangeRate(Vec2(1,0));
	loadProgress->setType(ProgressTimer::Type::BAR);
	loadProgress->setMidpoint(Vec2(0,0));
	loadProgress->setPosition(Vec2(visition.width/2,visition.height*0.25));
	loadProgress->setPercentage(0.0f);
	loadProgress->setScale(1.0f);
	this->addChild(loadProgress,1);
	
	//进度条更新的次数=100/需要加载的资源数量
	 m_nNumberLoadedSprite = 100.0 / (float)m_nNumberSprites;
	 this->schedule(schedule_selector(Loading::loadingCallBack),1.0f);
	

	return true;
}

void Loading::turnToScene()
{
	Director::getInstance()->replaceScene(WelcomeScene::createScene());
}

void Loading::loadingCallBack(float delta)
{
	//渐进的方式显示图片
	auto ac = ProgressTo::create(1,100-m_nNumberLoadedSprite*m_nNumberSprites );
	loadProgress->runAction(ac);
	
	if (m_nNumberSprites <0)
	{
		turnToScene();
		loadProgress->stopAllActions();
	
	}
	m_nNumberSprites--;
}