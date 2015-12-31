#include "HelpLayer.h"
#include "WelcomeScene.h"
#include "GameDefine.h"

Help::Help()
{

}

Help::~Help()
{


}

Scene* Help:: createScene()
{
	auto scene = Scene::create();
	auto layer = Help::create();
	scene->addChild(layer);


	return scene;
}

bool Help:: init()
{
	if ( !Layer::init())
	{
	    return false;
	}

	auto Backsprite = Sprite::create("helpbg.png");
	Backsprite->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2));
	this->addChild(Backsprite);

	auto callBack = MenuItemImage::create("btn_back02.png",
		                                   "btn_back02.png",
		                                   CC_CALLBACK_1(Help::bCallBack,this));
	callBack->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2 - 300));
	
	auto menu = Menu::create(callBack,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
    
	return true;
}

void Help:: bCallBack(Ref*  pSender)
{
	auto scene = WelcomeScene::createScene();
	Director::getInstance()->replaceScene(scene);

}
