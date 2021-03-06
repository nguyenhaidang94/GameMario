#include "Brick.h"

Brick::Brick(void)
{
}

Brick::Brick(int objectID, int x, int y)
{
	Initialize(x, y);
	_IsAboutToDestroy = -1;
	//setup current sprite for brick
	switch (objectID)
	{
	case 2:	
		_Color = eColorID::eBrown;
		_CurrentFrame = 0;
		break;
	case 3:
		_Color = eColorID::eBlue;
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

void Brick::Update()
{
	if(_IsBounce)
	{
		_Position.y += _Velocity.y;
		_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
		
		//set tag to empty when brick no longer bounce up
		if(_Velocity.y < 0 && _Tag != eGameTag::eEmpty)
		{
			_Tag = eGameTag::eEmpty;
		}

		//brick return to default position
		if(_Position.y <= _DefaultY)
		{
			_Velocity.y = 0;
			_Position.y = _DefaultY;
			_IsBounce = false;
		}
	}
	if(_IsAboutToDestroy >= 0)
	{
		if(_IsAboutToDestroy == 0)
		{
			_IsAboutToDestroy = 1;
		}
		else
		{
			if(_IsAboutToDestroy == 1)
			{
				_Tag = eGameTag::eDestroyed;
				EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eBreakBrick, _Color);
			}
		}
	}
}

void Brick::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Brick::Release()
{
}

void Brick::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//ignore collision when object is boucning
	if(!_IsBounce)
	{
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
					_Tag = eGameTag::eBrickBounceUp;
					_IsAboutToDestroy = 0;	//hold 1 tick for check collision before destroy
					break;

				//small mario make brick bounce
				case eMarioIsSmall:
				case eMarioIsSmallInvincible:
					_Tag = eGameTag::eBrickBounceUp;	//kill enemy if bounce up(?)
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
}
