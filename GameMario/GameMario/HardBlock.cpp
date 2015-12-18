#include "HardBlock.h"


HardBlock::HardBlock(void)
{
}

HardBlock::HardBlock(int objectID, int x, int y)
{
	Initialize(x, y);
	_ObjectTypeID = eObjectTypeID::eHardBrick;
	//setup current sprite for brick
	switch (objectID)
	{
	case 4:	
		_Color = eColorID::eBrown;
		_CurrentFrame = 1;
		break;
	case 5:	
		_Color = eColorID::eBlue;
		_CurrentFrame = 12;
		break;
	case 32:	
		_Color = eColorID::eBrown;
		_CurrentFrame = 5;
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