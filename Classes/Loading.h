#ifndef _LOADING_H_
#define _LOADING_H_

#include "cocos2d.h"

USING_NS_CC;

class Loading: public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	void turnToScene();

	void loadingCallBack(float delta);

	CREATE_FUNC(Loading);

private:
	LabelTTF* m_pLabelLoading;
	LabelTTF* m_pLabelPercent;
	int m_nNumberSprites;
	float m_nNumberLoadedSprite;

	ProgressTimer* loadProgress;  //½ø¶ÈÌõ


};
#endif

