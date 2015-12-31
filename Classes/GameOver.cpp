#include "GameOver.h"
#include "GameScene.h"
#include "WelcomeScene.h"

GameOve::GameOve()
{
	m_score = 0;

}
GameOve::~GameOve()
{
	

}


bool GameOve::init()
{
    if ( !Layer::init())
	{
	    return false;
	
	}

	size = Director::getInstance()->getVisibleSize();

	auto node = Node::create();
	node->setPosition(Vec2(0,-size.height));
	addChild(node,2,3);
	node->setVisible(false);

	auto gameOver = Sprite::create("over@game.png");
	gameOver->setPosition(Vec2(size.width/2,size.height*0.7));
	gameOver->setScale(0.7f);
	node->addChild(gameOver);
    
	auto resultBg = Sprite::create("resultbg@game.png");
	resultBg->setPosition(Vec2(size.width/2,size.height*0.5));
	resultBg->setScale(0.7f);
	node->addChild(resultBg);

	m_resultScoreLabel = LabelBMFont::create("0","fonts/futura-48.fnt");
	m_resultScoreLabel->setAnchorPoint(Vec2(1,0.5f));
	m_resultScoreLabel->setPosition(Vec2(resultBg->getContentSize().width*0.9,resultBg->getContentSize().height*0.6));
	
	resultBg->addChild(m_resultScoreLabel);


	auto palyBtn =MenuItemImage ::create("btn_restart02.png","btn_restart02.png",CC_CALLBACK_1(GameOve::menuCstarCallback,this));
	palyBtn->setPosition(Vec2(size.width*0.3,size.height*0.35));
	palyBtn->setScale(0.7f);

	auto rankBtn = MenuItemImage::create("btn_back02.png","btn_back02.png",CC_CALLBACK_1(GameOve::menuCstarCallback,this));
	rankBtn->setPosition(Vec2(size.width*0.65,size.height*0.35));
	rankBtn->setScale(0.7f);
	palyBtn->setTag(10);
	rankBtn->setTag(11);

	auto menu = Menu::create(palyBtn, rankBtn, nullptr);
	menu->setPosition(CCPointZero);
	node->addChild(menu);

	auto label = LabelBMFont::create("score: ","fonts/futura-48.fnt");
	label->setPosition(Vec2(size.width/2-120,size.height-7));
	label->setScale(0.5);
	addChild(label,2);
	label->setVisible(false);

	m_scoreLabel = LabelBMFont::create("0","fonts/futura-48.fnt");
	m_scoreLabel->setPosition(Vec2(size.width/2-80,size.height-7));
	m_scoreLabel->setAnchorPoint(Vec2(0,0.5));
	m_scoreLabel->setScale(0.5);
	m_scoreLabel->setVisible(false);
	addChild(m_scoreLabel,2,4);
	

	return true;
}

//ÏÔÊ¾³öÀ´
void GameOve::showResult()
{
	auto resultNode = (Node*)this->getChildByTag(3);
	resultNode->setVisible(true);

	m_scoreLabel->setVisible(false);

	auto move = EaseBackOut::create(MoveTo::create(1.0f,CCPointZero));
	resultNode->runAction(Sequence::create(DelayTime::create(0.8f),move,nullptr));
}

void GameOve::menuCstarCallback(Ref* pSender)
{
	auto item = (MenuItemSprite*)pSender;

	if ( item ->getTag() == 10)
	{
		auto gamescene = GameScene::createScene();
		Director::getInstance()->replaceScene(gamescene);
	}
	else if (item->getTag() == 11)
	{
	   auto helloworldscene = WelcomeScene::createScene();
	   Director::getInstance()->replaceScene(helloworldscene);
	
	}

}

void GameOve::addScore()
{
	m_score +=10;
	m_scoreLabel->setString(String::createWithFormat("%d",m_score)->getCString());
	
}
