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
	// ���ػ�ӭ���溯��
	void menuBackCallback(Ref* pSender);
    void	menuCstarCallback(Ref* pSender);
	void initMap();
	void createShprite(int row,int col);
	Point PositionOfItem(int row,int col);

	//����Ƿ��п������ľ���
	void checkAndRemoveSprite();
	//��ǿ����ƶ��ľ���
	void markRemove(SpriteShape* spr);
	//�Ƴ�����
	void removeSprtie();
	//����ı�ը�Ƴ�
	void exploSprite(SpriteShape* spr);
	//���Ƴ��ľ�����еĲ���
	void actionEndCallback(Node* node);
	//������
	void getColChain(SpriteShape* spr,std::list<SpriteShape*> &chainList);
	//������
	void getRowChain(SpriteShape* spr,std::list<SpriteShape*> &chainList);
	//����ȱλ��
	void fillSprite();
	//����
	void update(float dt);
	// ���ݴ����ĵ�λ�ã������ǵ�ͼ���ĸ�����
	SpriteShape* spriteOfPoint(Point *point);

	//�����¼� 
	bool onTouchBegan(Touch *touch, Event *unused);
    void onTouchMoved(Touch *touch, Event *unused);
	// ��������
	void swapSprite();

    void myClock( float dt );
	void gameOver(float dt);
	
	CREATE_FUNC(GameScene);
private:
	// ��ά����
	SpriteShape* map[ROWS][COLS];
	// ����һ��ͼƬ
	SpriteBatchNode* spriteSheet;
   // ��ͼ�����½�����λ��
	float mapBX,mapBY;

	GameOve * gameOve;

	// ʱ��
	int m_time;
	// ����
	int m_score;

	// Դ���飬Ŀ�꾫��
	SpriteShape* staSprite;
	SpriteShape* endSprite;

	// ��־ �Ƿ���ִ�ж���
	bool isAction;
	// ��־ �Ƿ��п�ȱ��Ҫ�
    bool isFillSprite;
	// ��־ �Ƿ���Դ���
	bool isTouchEna;

	
};
#endif