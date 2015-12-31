#ifndef _GameScene_H_
#define _GameScene_H_
#include "GameDefine.h"
#include "SpriteShape.h"
#include "cocos2d.h"
#include "GameOver.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* createScene();
	virtual bool init();
	// 返回欢迎界面函数
	void menuBackCallback(Ref* pSender);
    void	menuCstarCallback(Ref* pSender);
	void initMap();
	void createShprite(int row,int col);
	Point PositionOfItem(int row,int col);

	//检测是否有可消除的精灵
	void checkAndRemoveSprite();
	//标记可以移动的精灵
	void markRemove(SpriteShape* spr);
	//移除精灵
	void removeSprtie();
	//精灵的爆炸移除
	void exploSprite(SpriteShape* spr);
	//对移除的精灵进行的操作
	void actionEndCallback(Node* node);
	//纵向检查
	void getColChain(SpriteShape* spr,std::list<SpriteShape*> &chainList);
	//横向检查
	void getRowChain(SpriteShape* spr,std::list<SpriteShape*> &chainList);
	//补空缺位置
	void fillSprite();
	//更新
	void update(float dt);
	// 根据触摸的点位置，返回是地图中哪个精灵
	SpriteShape* spriteOfPoint(Point *point);

	//触摸事件 
	bool onTouchBegan(Touch *touch, Event *unused);
    void onTouchMoved(Touch *touch, Event *unused);
	// 交换精灵
	void swapSprite();

    void myClock( float dt );
	void gameOver(float dt);
	
	CREATE_FUNC(GameScene);
private:
	// 二维数组
	SpriteShape* map[ROWS][COLS];
	// 绘制一批图片
	SpriteBatchNode* spriteSheet;
   // 绘图的最下角坐标位置
	float mapBX,mapBY;

	GameOve * gameOve;

	// 时间
	int m_time;
	// 分数
	int m_score;

	// 源精灵，目标精灵
	SpriteShape* staSprite;
	SpriteShape* endSprite;

	// 标志 是否在执行动作
	bool isAction;
	// 标志 是否有空缺需要填补
    bool isFillSprite;
	// 标志 是否可以触摸
	bool isTouchEna;

	
};
#endif