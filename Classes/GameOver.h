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

	void showResult();    //���ֽ���
 	void addScore();      //���ӷ���

private:
	Size size;
	void menuCstarCallback(Ref* pSender);

 	LabelBMFont *m_scoreLabel;      //��Ϸ�еķ����ı�
	LabelBMFont *m_resultScoreLabel;  //��Ϸ����е���Ϸ�����ı�

    int m_score;     //����


};
#endif