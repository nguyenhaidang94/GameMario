#include "Brick.h"

Brick::Brick(void)
{
}

Brick::Brick(int objectID, int x, int y)
{
	Initialize(x, y);
	//setup current sprite for brick
	switch (objectID)
	{
	case 2:	
		_Type = eBlockTypeID::eBrownBlock;
		_CurrentFrame = 0;
		break;
	case 3:
		_Type = eBlockTypeID::eBlueBlock;
		_CurrentFrame = 6;
	default:
		break;
	}
}

Brick::~Brick(void)
{
	int temp = 0;
	temp += 1;
}

Box Brick::GetMovementRangeBox()
{
	return GetBoundaryBox();
}

void Brick::Update()
{
	if(_IsBounce)
	{
		_Position.y += _Velocity.y;
		_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
		if(_Position.y <= _DefaultY)
		{
			_Velocity.y = 0;
			_Position.y = _DefaultY;
			_IsBounce = false;
		}
	}
}

void Brick::Render()
{
	if(_Tag != eGameTag::eDestroyed)
	{
		_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
	}
}

void Brick::Release()
{
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
			//handle how brick behave base on mario state
			switch (object->GetTag())
			{
			//big mario destroy brick
			case eMarioIsBig:
			case eMarioIsBigInvincible:
				_Tag = eGameTag::eDestroyed;
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eBreakBrick, _Type);
				break;

			//small mario make brick bounce
			case eMarioIsSmall:
			case eMarioIsSmallInvincible:
				_Velocity.y = BOUNCE_VELOCITY;
				_IsBounce = true;
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
