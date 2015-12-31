#include "WelcomeScene.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelpLayer.h"

//#define BackMusic "sound/BackMusic.mp3"
using namespace CocosDenshion;

WelcomeScene::WelcomeScene()
{

}

WelcomeScene::~WelcomeScene()
{


}

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);

	return scene;

}

bool WelcomeScene::init()
{
	if ( !Layer::init())
	{
	    return false;
	}


	//Ìí¼Ó±³¾°Í¼Æ¬
	auto sprite = Sprite::create("menu_bg2.png");
	sprite->setPosition(Vec2(Game_SCREE_WIDTH*0.74,Game_SCREE_HEIGHT*0.64));
	//sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite);


	auto t1 = Sprite::create("q1.png");
	t1->setPosition(Vec2(-Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2));
	t1->setScale(2.0f);
	this->addChild(t1,1);

	auto moveto = MoveTo::create(2.0f,Vec2(Game_SCREE_WIDTH/2-100,Game_SCREE_HEIGHT/2+100));
	t1->runAction(moveto);
	 

	auto t2 = Sprite::create("q4.png");
	t2->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT*1.5));
	t2->setScale(2.0f);
	this->addChild(t2,1);

    auto move = MoveTo::create(2.0f,Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2+150));
	t2->runAction(move);

	auto t3 = Sprite::create("q3.png");
	t3->setPosition(Vec2(0,Game_SCREE_HEIGHT/2));
	t3->setScale(2.0f);
	this->addChild(t3,1);

	auto jumpTo = JumpTo::create(2.0,Vec2(Game_SCREE_WIDTH/2+65,Game_SCREE_HEIGHT/2+80),50,3);
	t3->runAction(jumpTo);

	//Ìí¼Ó¿ªÊ¼°´Å¥
	auto starItem = MenuItemImage::create(
		                              "start_game.png",
		                              "start_game_select.png",
									  CC_CALLBACK_1(WelcomeScene::menuStarCallback,this)
		                                );
	
	starItem->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_WIDTH*0.75));
	starItem->setTag(1);

	auto soundSet = MenuItemImage::create(
		                              "soundset.png",
		                              "soundset_select.png",
									  CC_CALLBACK_1(WelcomeScene::menuStarCallback,this)
		                                );
	
	soundSet->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_WIDTH*0.6));
	soundSet->setTag(2);

    auto helpSet = MenuItemImage::create(
		                              "help.png",
		                              "help_select.png",
									  CC_CALLBACK_1(WelcomeScene::menuStarCallback,this)
		                                );
	
	helpSet->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_WIDTH*0.45));
	helpSet->setTag(3);

	auto exitGame = MenuItemImage::create(
		                              "exit_game.png",
		                              "exit_game_select.png",
									  CC_CALLBACK_1(WelcomeScene::menuStarCallback,this)
		                                );
	
	exitGame->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_WIDTH*0.3));
	exitGame->setTag(4);

	auto menu = Menu::create(starItem, soundSet,helpSet,exitGame,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(BackMusic);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(BackMusic,true);

	  return true;
}

void WelcomeScene::menuStarCallback(Ref *pSender)
{
	//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("sound/button.wav");
	auto num =(MenuItemSprite*)pSender;
	int tag = num->getTag();
	if (tag == 1)
	{
       auto gamescene = GameScene::createScene();
       Director::sharedDirector()->replaceScene(gamescene);
	}
	else if ( tag == 2)
	{
	     ;
	}
	else if (tag ==3)
	{
		auto helpLayer = Help::createScene();
		Director::getInstance()->replaceScene(helpLayer);
	}
	else
		Director::getInstance()->end();
}
