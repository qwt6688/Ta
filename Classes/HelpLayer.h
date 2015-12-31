#ifndef _HELPLAYER_H_
#define _HELPLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Help: public Layer
{
public:
	Help();
	~Help();
	static Scene* createScene();
	virtual bool init();

	void bCallBack(Ref* pSender);

	CREATE_FUNC(Help);

};
#endif