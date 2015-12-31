#include "SpriteShape.h"

SpriteShape::SpriteShape()
	:m_row(0),
	m_col(0),
	m_imeIndex(0),
	m_isNeedRemove(false)
{

	//srand(unsigned(time(NULL)));
}
	
SpriteShape::~SpriteShape()
{


}
SpriteShape*  SpriteShape::create(int row, int col)
{
	SpriteShape *spriteShape = new SpriteShape();
	spriteShape->m_row = row;
	spriteShape->m_col = col;
	spriteShape->m_imeIndex = rand()% TOTAL_SPRITE;
	spriteShape->initWithSpriteFrameName(spriteName[spriteShape->m_imeIndex]);
	spriteShape->setScale(1.2f);
	spriteShape->autorelease();

	return spriteShape;
}