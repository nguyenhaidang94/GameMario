#include "Brick.h"

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32

Brick::Brick(void)
{
}

Brick::Brick(int objectID, int x, int y)
{
	_Position.x = x;
	_Position.y = y;
	_DefaultX = x;
	_Size.x = BRICK_WIDTH;
	_Size.y = BRICK_HEIGHT;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eObjectTitle);
	_ObjectTypeID = eObjectTypeID::eBrick;
	//setup current sprite for brick
	switch (objectID)
	{
	case 3:
		_CurrentFrame = 0;
		break;
	default:
		break;
	}
}

Brick::~Brick(void)
{
}

void Brick::Update()
{
}

void Brick::Render()
{
	if(_Tag != eGameTag::eIsDestroyed)
	{
		_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
	}
}

void Brick::Release()
{
	delete this;
}

void Brick::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	case eMario:
		switch (collisionDirection)
		{
		case eBottom:
			switch (object->GetTag())
			{
			//big mario destroy brick
			case eMarioIsBig:
				_Tag = eGameTag::eIsDestroyed;
				//missing brick destroy animation
				break;

			//small mario make brick bounce
			case eEmpty:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
}
