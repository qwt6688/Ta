#include "GameScene.h"
#include "WelcomeScene.h"
#include "SpriteShape.h"
#include "SimpleAudioEngine.h"

//#define Back "sound/playscene.mp3"
using namespace CocosDenshion;

GameScene::GameScene()
	:spriteSheet(nullptr),
	isAction(true),
	isFillSprite(false),
	isTouchEna(true),
	staSprite(nullptr),
	endSprite(nullptr)
	,m_time(60)
    ,m_score(0)
{

}

GameScene::~GameScene()
{


}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init())
	{
	    return false;
	}

	
	// 加载plist和png
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("yi.plist");
    spriteSheet = SpriteBatchNode::create("yi.png");
    addChild(spriteSheet);

	gameOve = GameOve::create();
	this->addChild(gameOve,2,3);
	// 初始化坐标值
    	mapBX = (Game_SCREE_WIDTH - SPRITE_WIDTH * COLS - (COLS - 1) * BOADER_WIDTH) / 2;
	    mapBY = (Game_SCREE_HEIGHT - SPRITE_WIDTH * ROWS - (ROWS - 1) * BOADER_WIDTH) / 2;


	//添加背景图片
	auto sprite = Sprite::create("back2.png");
	sprite->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2));
	sprite->setScaleY(1.5f);
	//sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite,-1);

	//添加暂停按钮
	auto stopItem = MenuItemImage::create(
		                                 "Title_Pause.png",
										 "Title_Pause.png",
										 CC_CALLBACK_1(GameScene::menuBackCallback,this)
		                                );
	stopItem->setPosition(Vec2(Game_SCREE_WIDTH-stopItem->getContentSize().width,stopItem->getContentSize().height+15));
	stopItem->setScale(0.8f);
	auto menu = Menu::create(stopItem,nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	
	auto node = Node::create();
	node->setPosition(Vec2(0,-Game_SCREE_HEIGHT));
	addChild(node,2,4);
	node->setVisible(false);

	auto resBtn =MenuItemImage ::create("continue_game.png","continue_game.png",CC_CALLBACK_1(GameScene::menuCstarCallback,this));
	resBtn->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2));
	resBtn->setScale(1.0f);
	

	auto exitBtn = MenuItemImage::create("exit_game_select.png","exit_game_select.png",CC_CALLBACK_1(GameScene::menuCstarCallback,this));
	exitBtn->setPosition(Vec2(Game_SCREE_WIDTH/2,Game_SCREE_HEIGHT/2-100));
	exitBtn->setScale(1.0f);
	resBtn->setTag(12);
	exitBtn->setTag(13);

	auto men = Menu::create(resBtn, exitBtn, nullptr);
	men->setPosition(CCPointZero);
	node->addChild(men);

	// 加载ttf字体
	TTFConfig config("fonts/arial.ttf",30);
	// 游戏时间的显示
	auto labelTime = Label::createWithTTF(config,StringUtils::format("Time: %d ",m_time));
	labelTime->setColor(Color3B(0,230,250));
	labelTime -> setPosition(Vec2( Game_SCREE_WIDTH/2 , Game_SCREE_HEIGHT - labelTime->getContentSize().height*2.6 ));
	labelTime -> setTag(11);
	this ->addChild(labelTime);

	// 分数显示
	auto labelScore = Label::createWithTTF(config,StringUtils::format("Score: %d ",m_score) );
	labelScore -> setPosition(Vec2(labelTime->getContentSize().width/2+5 , Game_SCREE_HEIGHT - labelScore->getContentSize().height-10 ));
	labelScore -> setTag(10);
	labelScore->setColor(Color3B(25,0,250));
	this->addChild(labelScore);

	auto touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	touchEvent->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchEvent,this);
	initMap();
	scheduleUpdate();
	schedule(schedule_selector(GameScene::myClock),1.0f );

	
//	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(Back);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic(Back,true);
	return true;
}

void GameScene::initMap()
{
	 for (int i=0; i<ROWS;++i)
	  {
		  for (int j =0; j <COLS; ++j)
		{   
			createShprite(i,j);
		  
		 }
	 }	

}

void GameScene::createShprite(int row, int col)
{
	SpriteShape* spr = SpriteShape::create(row, col);

	//下落
	Point endPosition = PositionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y + Game_SCREE_HEIGHT / 2);  
    spr->setPosition(startPosition);  
    float speed = startPosition.y / (1.5 * Game_SCREE_HEIGHT);  
    spr->runAction(MoveTo::create(speed, endPosition));  
	spriteSheet->addChild(spr);

	map[row][col] = spr;
}

Point GameScene::PositionOfItem(int row,int col)
{
	float x = mapBX +(SPRITE_WIDTH + BOADER_WIDTH)*col + SPRITE_WIDTH /2;
	float y = mapBY +(SPRITE_WIDTH + BOADER_WIDTH)*row + SPRITE_WIDTH /2;
	 
    return Point(x,y);
}

void GameScene::menuBackCallback(Ref* pSender)
{
	
	auto resultNode = (Node*)this->getChildByTag(4);
	resultNode->setVisible(true);

	auto move = EaseBackOut::create(MoveTo::create(1.0f,CCPointZero));
	resultNode->runAction(Sequence::create(DelayTime::create(0.8f),move,nullptr));
	this->stopAllActions();
	this->pauseSchedulerAndActions();
	//this->unschedule(schedule_selector( GameScene::myClock));
}

void GameScene::update(float dt)
{
	if (isAction)
	{
		isAction = false;
		for (int i=0; i<ROWS; ++i)
		{
		   for (int j=0; j<COLS; ++j)
		   {
			   SpriteShape* sprite = map[i][j];
			   
			   if (sprite && sprite->getNumberOfRunningActions() >0)
			   {
				   isAction = true;
				   break;
			   }
		   
		   }
		}
	
	}
	// 如果精灵正在移动中，忽视触摸事件
	isTouchEna = !isAction;

	// 如果没有动作执行    
    if (!isAction) {
		// 是否有精灵需要填补
		if ( isFillSprite ) {
            //爆炸效果结束后才掉落新精灵，增强打击感
            fillSprite();
            isFillSprite = false;
		}
		else
		{
			checkAndRemoveSprite();
		}
    }

	// 分数变化
	Label *labelScore = (Label *)this -> getChildByTag(10);
	labelScore -> setString( StringUtils::format("Score: %d ",m_score));
}
//检测是否有可消除的精灵
void GameScene::checkAndRemoveSprite()
{
	SpriteShape *sprite;
	for (int i=0; i<ROWS; ++i)
	{
	   for (int j=0; j<COLS; ++j)
	   {
	       sprite = map[i][j];

		   if ( !sprite)
		   {
			   continue;
		   }

		   if (sprite->getIsNeedRemove())
		   {
		       continue;
		   }
		   std::list<SpriteShape*> colChainList;
		   getColChain(sprite,colChainList);

		   std::list<SpriteShape*> rowChainList;
		   getRowChain(sprite,rowChainList);

		   std::list<SpriteShape*> &longerList = colChainList.size() > rowChainList.size() ?colChainList : rowChainList;
			  
		   if ( longerList.size() <3)
			{
				     continue;
		    }
		   std::list<SpriteShape*>::iterator it;
		   for (it = longerList.begin(); it !=longerList.end(); ++it)
		   {
			   sprite = (SpriteShape*)* it;
			   if ( !sprite)
			   {
				   continue;
			   }
			   markRemove(sprite);
		   }
	   }
	
	}

	removeSprtie();
}

//标记可以移除的精灵
void GameScene::markRemove(SpriteShape* spr)
{
	//如果已经标记了要移除，就不需要在标记
	if ( spr->getIsNeedRemove())
	{
	    return ;
	}
	//标记该精灵可以被移除
	spr->setIsNeedRemove(true);

}
//移除精灵
void GameScene::removeSprtie()
{
	isAction = true;

	for (int i = 0; i < ROWS; ++i)
	{
	    for (int j=0; j < COLS; ++j)
		{
			SpriteShape *sprite = map[i][j];
			if ( !sprite)
			{
				continue;
			}

			if (sprite->getIsNeedRemove())
			{
				isFillSprite = true;
				exploSprite(sprite);
			}
		
		}
	
	}

}
	//精灵的爆炸移除
void GameScene::exploSprite(SpriteShape* spr)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/click.mp3");
	spr->runAction(Sequence::create(ScaleTo::create(0.2f,0.0),
		CallFuncN::create(CC_CALLBACK_1(GameScene::actionEndCallback,this)),nullptr));
}
	
//对移除的精灵进行的操作
void GameScene::actionEndCallback(Node* node)
{
	SpriteShape *sprite =(SpriteShape*)node;
	map[sprite->getRow()][sprite->getCol()] = NULL;
	sprite->removeFromParent();

}

//纵向检查
void GameScene::getColChain(SpriteShape* spr,std::list<SpriteShape*> &chainList)
{
	//添加第一个精灵
	chainList.push_back(spr);

	//向左查找
	int neighborCol = spr->getCol() - 1;
	while( neighborCol >=0)
	{
		SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
		if ( neighborSprite && 
			(neighborSprite->getImeIndex() == spr->getImeIndex())
			&& !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborCol--;
		
		}
		else
		{
		    break;
		}
	
	}

	neighborCol = spr->getCol() + 1;
	while ( neighborCol < COLS)
	{
		SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
		if ( neighborSprite && 
			(neighborSprite->getImeIndex() == spr->getImeIndex())
			&& !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborCol++;
		
		}
		else
		{
		    break;
		}
	
	}

}

//横向检查
void GameScene::getRowChain(SpriteShape* spr,std::list<SpriteShape*> &chainList)
{
	//添加第一个精灵
	chainList.push_back(spr);

	//向上查找
	int neighborRow = spr->getRow() +1;
	while( neighborRow <ROWS)
	{
		SpriteShape *neighborSprite = map[neighborRow ][spr->getCol()];
		if ( neighborSprite && 
			(neighborSprite->getImeIndex() == spr->getImeIndex())
			&& !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborRow++;
		
		}
		else
		{
		    break;
		}
	
	}

	//向下查找
	neighborRow = spr->getRow() -1;
	while ( neighborRow >=0)
	{
		SpriteShape *neighborSprite = map[neighborRow][spr->getCol()];
		if ( neighborSprite && 
			(neighborSprite->getImeIndex() == spr->getImeIndex())
			&& !neighborSprite->getIsNeedRemove())
		{
			chainList.push_back(neighborSprite);
			neighborRow--;
		
		}
		else
		{
		    break;
		}
	
	}


}
//补空缺位置
void GameScene::fillSprite()
{
	//移动方向标记
	isAction = true;
	int sum = 0;

	int *colEmptyInfo = (int *)malloc(sizeof(int)*COLS);
	memset((void*)colEmptyInfo,0,sizeof(int)* COLS);

	//存在的精灵下落下来
	SpriteShape *sprite = nullptr;
	for (int i =0; i < COLS; ++i)
	{
	    int removedSpriteOfCol =0;
        for (int j=0; j <ROWS; ++j)
		{
			sprite = map[j][i];  //列不变，行变
			if (sprite == NULL)
			{
				++removedSpriteOfCol;
			}
			else
			{
				if ( removedSpriteOfCol >0)
				{
					int newRow = j - removedSpriteOfCol;
					map[newRow][i] = sprite;
					map[j][i] = NULL;

					Point starPosition = sprite->getPosition();
					Point endPosition =PositionOfItem(newRow,i);
					 float speed = (starPosition.y - endPosition.y) / Game_SCREE_HEIGHT*3;  
					 sprite->stopAllActions();  
                   sprite->runAction(CCMoveTo::create(speed, endPosition));  
                       
                    sprite->setRow(newRow);  

				
				}
			}
		}
		//列移除的数量
		colEmptyInfo[i] = removedSpriteOfCol;
		sum += removedSpriteOfCol;
	}

	//新建的精灵，并降落
	for (int i =0; i<COLS; ++i)
	{
		for (int j= ROWS- colEmptyInfo[i]; j < ROWS; ++j)
		{
			createShprite(j,i);
		}
	
	}

	m_score += sum*10;
	free(colEmptyInfo);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused)
{
	staSprite = nullptr;
	endSprite = nullptr;

	if ( isTouchEna ) {
        auto location = touch->getLocation();
		staSprite = spriteOfPoint(&location);
    }
	return isTouchEna;

}

SpriteShape *GameScene::spriteOfPoint(Point *point)  
{  
	SpriteShape *spr = nullptr;  
    Rect rect = Rect(0, 0, 0, 0);  
    Size sz;  
    sz.height=SPRITE_WIDTH;  
    sz.width=SPRITE_WIDTH;  
   
    for( int i = 0 ; i< ROWS ; ++i )    {  
        for( int j = 0 ; j < COLS ; ++j )    {  
            spr = map[i][j];  
            if( spr )   {  
                rect.origin.x = spr->getPositionX() - ( SPRITE_WIDTH / 2);  
                rect.origin.y = spr->getPositionY() - ( SPRITE_WIDTH / 2);  
   
                rect.size = sz;  
                if (rect.containsPoint(*point)) {  
                    return spr;  
                }  
            }  
        }  
    }  
       
    return NULL;  
}

// 触摸后移动的方向
void GameScene::onTouchMoved(Touch *touch, Event *unused)	{
	// 如果没有初始精灵 或者 触摸事件不可行，直接返回
	if (!staSprite || !isTouchEna) {
        return;
    }
    
	// 获取 初始精灵 的行列
    int row = staSprite->getRow();
    int col = staSprite->getCol();
    
	// 获取移动到的 点 的位置
    auto location = touch->getLocation();
    auto halfSpriteWidth = SPRITE_WIDTH / 2;
    auto halfSpriteHeight = SPRITE_WIDTH / 2;
    
    auto  upRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
                        staSprite->getPositionY() + halfSpriteHeight,
                        SPRITE_WIDTH,
                        SPRITE_WIDTH);
    
	// 判断是在向哪个方向移动，
    if (upRect.containsPoint(location)) {
        ++row;
        if ( row < ROWS ) {
            endSprite = map[row][col];
        }
        swapSprite();
        return;
    }
    
    auto  downRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
                        staSprite->getPositionY() - (halfSpriteHeight * 3),
                        SPRITE_WIDTH,
                        SPRITE_WIDTH);
    
    if (downRect.containsPoint(location)) {
        --row;
        if ( row >= 0 ) {
            endSprite = map[row][col];
        }
        swapSprite();
        return;
    }
    
    auto  leftRect = Rect(staSprite->getPositionX() - (halfSpriteWidth * 3),
                          staSprite->getPositionY() - halfSpriteHeight,
                          SPRITE_WIDTH,
						  SPRITE_WIDTH);
    
    if (leftRect.containsPoint(location)) {
        --col;
        if ( col >= 0 ) {
            endSprite = map[row][col];
        }
        swapSprite();
        return;
    }
    
    auto  rightRect = Rect(staSprite->getPositionX() + halfSpriteWidth,
                          staSprite->getPositionY() - halfSpriteHeight,
                          SPRITE_WIDTH,
                          SPRITE_WIDTH);
    
    if (rightRect.containsPoint(location)) {
        ++col;
        if ( col < COLS ) {
			endSprite = map[row][col];
        }
        swapSprite();
        return;
    }
    
    // 否则，并非一个有效的移动
}

//关于交换精灵，有两种情况

//交换后，满足消除条件，消除

//交换后，不满足消除条件，返回原样

// 交换精灵
void GameScene::swapSprite()	{
	// 移动中，不允许再次触摸，执行动作设置为true
    isAction = true;
    isTouchEna = false;

	// 初始精灵 和 终止精灵 均不能为空
	if (!staSprite || !endSprite) {
        return;
    }
    
	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

    float time = 0.2;
    
    // 在数组中交换位置
	map[ staSprite -> getRow() ][staSprite -> getCol() ] = endSprite;
	map[ endSprite -> getRow() ][endSprite -> getCol() ] = staSprite;

    int tmpRow = staSprite->getRow();
    int tmpCol = staSprite->getCol();
    staSprite->setRow(endSprite->getRow());
    staSprite->setCol(endSprite->getCol());
    endSprite->setRow(tmpRow);
    endSprite->setCol(tmpCol);
    
    // 检查是否能消除
	std::list<SpriteShape *> colChainListOfFirst;
    getColChain(staSprite, colChainListOfFirst);
    
    std::list<SpriteShape *> rowChainListOfFirst;
    getRowChain(staSprite, rowChainListOfFirst);
    
    std::list<SpriteShape *> colChainListOfSecond;
    getColChain(endSprite, colChainListOfSecond);
    
    std::list<SpriteShape *> rowChainListOfSecond;
    getRowChain(endSprite, rowChainListOfSecond);
    
    if (colChainListOfFirst.size() >= 3
        || rowChainListOfFirst.size() >= 3
        || colChainListOfSecond.size() >= 3
        || rowChainListOfSecond.size() >= 3) {
        // 如果能够消除，仅仅进行移动（不会移动回来）
        staSprite->runAction(MoveTo::create(time, posOfDest));
        endSprite->runAction(MoveTo::create(time, posOfSrc));
        return;
    }
    
    // 不能消除，则移动过去还要返回
	map[ staSprite -> getRow()][staSprite -> getCol() ] = endSprite;
	map[ endSprite -> getRow()][endSprite -> getCol() ] = staSprite;

    tmpRow = staSprite->getRow();
    tmpCol = staSprite->getCol();
    staSprite->setRow(endSprite->getRow());
    staSprite->setCol(endSprite->getCol());
    endSprite->setRow(tmpRow);
    endSprite->setCol(tmpCol);
    
    staSprite->runAction(Sequence::create(
                                      MoveTo::create(time, posOfDest),
                                      MoveTo::create(time, posOfSrc),
                                      nullptr));
    endSprite->runAction(Sequence::create(
                                      MoveTo::create(time, posOfSrc),
                                      MoveTo::create(time, posOfDest),
                                      nullptr));
	SimpleAudioEngine::getInstance()->playEffect("sound/appear.wav");
}

void GameScene::myClock( float dt )
{
	// 时间变化
	--m_time;
	// 如果时间归0，那么执行游戏结束动画，并跳到游戏结束界面
	if( m_time == 0 )
	{
		Label *labelTime = (Label *)this -> getChildByTag(11);
		labelTime->setScale(0);

		// 跳转到游戏结束界面
		scheduleOnce(schedule_selector(GameScene::gameOver),0.5f);

		return;
	}
	// 如果还有时间，那么时间减少
	if( m_time > 0 )	{
		Label *labelTime = (Label *)this -> getChildByTag(11);
		labelTime -> setString( StringUtils::format("Time: %d ",m_time));
		if (m_time <= 10)
		{	
		labelTime->setColor(Color3B(250,0,0));
		auto bink = ToggleVisibility::create();
		labelTime->runAction(bink);
		}
	}
}

// 游戏结束函数
void GameScene::gameOver(float dt)
{
	isTouchEna = false;
	this->unscheduleAllSelectors();
	gameOve->showResult();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	
	
}

void GameScene:: menuCstarCallback(Ref* pSender)
{
	auto item = (MenuItemSprite*)pSender;

	if ( item ->getTag() == 12)
	{
		auto resultNode = (Node*)this->getChildByTag(4);
	    resultNode->setVisible(false);
	   Director::getInstance()->startAnimation();
	   this->resumeSchedulerAndActions();
	 
		
	}
	else if (item->getTag() == 13)
	{
	    Director::getInstance()->end();
	
	}

}
