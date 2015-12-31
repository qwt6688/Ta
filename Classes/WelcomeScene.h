#ifndef _WelcomeScene_H_
#define _WelcomeScene_H_

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	WelcomeScene();
	~WelcomeScene();
	virtual bool init();
	static Scene* createScene();
	void menuStarCallback(Ref * pSender);
	CREATE_FUNC(WelcomeScene);

};
#endif
