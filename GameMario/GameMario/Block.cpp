#include "Block.h"



Block::Block(void)
{
}


Block::~Block(void)
{
}

void Block::Initialize(int x, int y)
{
	_Position.x = x;
	_Position.y = y;
	_DefaultY = y;
	_Size.x = BRICK_WIDTH;
	_Size.y = BRICK_HEIGHT;
	_Color = eColorID::eBrown;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eObjectTitle);
	_ObjectTypeID = eObjectTypeID::eBrick;
	_IsBounce = false;
}
