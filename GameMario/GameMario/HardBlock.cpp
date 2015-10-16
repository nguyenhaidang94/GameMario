#include "HardBlock.h"


HardBlock::HardBlock(void)
{
}

HardBlock::HardBlock(int objectID, int x, int y)
{
	Initialize(x, y);
	//setup current sprite for brick
	switch (objectID)
	{
	case 4:	
		_Type = eBlockTypeID::eBrownBlock;
		_CurrentFrame = 1;
		break;
	default:
		break;
	}
}


HardBlock::~HardBlock(void)
{
}

void HardBlock::Update()
{
}

void HardBlock::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void HardBlock::Release()
{
}

void HardBlock::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
}