#ifndef _SpriteShape_H_
#define _SpriteShape_H_

#include "GameDefine.h"
#include "cocos2d.h"
USING_NS_CC;

class SpriteShape : public Sprite
{
public:
	SpriteShape();
	~SpriteShape();
	static SpriteShape* create(int row, int col);

	CC_SYNTHESIZE(int, m_row, Row);  //�����˱����ͱ���m_row���ڶ���getRow������setRow����
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imeIndex, ImeIndex);  
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);
};
#endif