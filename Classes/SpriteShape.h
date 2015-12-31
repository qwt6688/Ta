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

	CC_SYNTHESIZE(int, m_row, Row);  //定义了保护型变量m_row，在定义getRow函数和setRow函数
	CC_SYNTHESIZE(int, m_col, Col);
	CC_SYNTHESIZE(int, m_imeIndex, ImeIndex);  
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);
};
#endif