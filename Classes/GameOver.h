#ifndef _GameOver_h_
#define _GameOver_h_

#include "cocos2d.h"

USING_NS_CC;

class GameOve: public Layer
{
public:
	GameOve();
	~GameOve();

	virtual bool init();

	CREATE_FUNC(GameOve);

	void showResult();    //显现结束
 	void addScore();      //增加分数

private:
	Size size;
	void menuCstarCallback(Ref* pSender);

 	LabelBMFont *m_scoreLabel;      //游戏中的分数文本
	LabelBMFont *m_resultScoreLabel;  //游戏结果中的游戏分数文本

    int m_score;     //分数


};
#endif