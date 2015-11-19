#include "Goomba.h"


Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

Goomba::Goomba(int objectTypeID, int positionX, int positionY)
{
	//Object
	SetObjectType(eMonster);												//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eGoomba);	//set sprite
	_Size = D3DXVECTOR2(GOOMBA_WIDTH, GOOMBA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-GOOMBA_SPEED, -GOOMBA_SPEED);			//set position
	
	// Goomba
	 _TimeStartFrame= GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;									//set time the turn
	SetFrame(1);
	_GoobaVelocity = -GOOMBA_SPEED;
	_GoombaAlive = true;													//set alive
}

void Goomba::SetFrame(int GoombaType)
{
	switch (GoombaType)
	{
		case 1:
			_FrameCurrent = 0;
			_FrameStart = 0;
			_FrameEnd = 1;
			break;
		case 2:
			_FrameCurrent = 3;
			_FrameStart = 3;
			_FrameEnd = 4;
			break;
		case 3:
			_FrameCurrent = 6;
			_FrameStart = 6;
			_FrameEnd = 7;
			break;
		case 4:
			_FrameCurrent = 9;
			_FrameStart = 9;
			_FrameEnd = 10;
			break;
		default:
			_FrameCurrent = 0;
			_FrameStart = 0;
			_FrameEnd = 1;
			break;
	};
}

void Goomba::Update()
{
	DWORD timeNow = GetTickCount();
	if (timeNow - _TimeStartFrame >= _TimePerFrame && _FrameCurrent != _FrameEnd + 1)
	{
		_TimeStartFrame = timeNow;
		_FrameCurrent = SpriteManager::GetInstance()->NextFrame(_FrameCurrent, _FrameStart, _FrameEnd);
	}
	if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
	{
		_TimeStartVelocity = timeNow;
		//location
		_Position.x += _Velocity.x;
		_Position.y += _Velocity.y;
	}
	_Velocity.x = 0.0f;
	_Velocity.y = -GOOMBA_VELOCITY_Y;
}

void Goomba::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void Goomba::Release()
{

}

void Goomba::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
		case eGround:
			_Velocity.x = _GoobaVelocity;
			switch (collisionDirection)
			{
			case eBottom:
				_Velocity.y = 0.0f;
				break;
			case eRight:
				_GoobaVelocity = -_GoobaVelocity;
				_Velocity.x = _GoobaVelocity;
				break;
			case eLeft:
				_GoobaVelocity = -_GoobaVelocity;
				_Velocity.x = _GoobaVelocity;
				break;
			default:
				break;
			}
			break;
		case eBrick:
			_Velocity.x = _GoobaVelocity;
			switch (collisionDirection)
			{
			case eBottom:
				_Velocity.y = 0.0f;
				_Position.y = object->GetBoundaryBox().fY + _Size.y / 2;
				break;
			case eRight:
				_GoobaVelocity = -_GoobaVelocity;
				_Velocity.x = _GoobaVelocity;
				_Position.x = object->GetBoundaryBox().fX - _Size.x / 2;
				break;
			case eLeft:
				_GoobaVelocity = -_GoobaVelocity;
				_Velocity.x = _GoobaVelocity;
				_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x / 2;
				break;
			default:
				break;
			}
			break;
		case eMario:
			switch (collisionDirection)
			{
				case eTop:
				//	GoombaDead();
					break;
				default:
					break;
			}
			break;
		default:
			_Velocity.x = 0.0f;
			//_Velocity.y = -GOOMBA_SPEED;
			break;
			//object->SetObjectType(eUndefined);
	}

	//switch (tag)
	//{
	//case eToUnderground1_1:
	//	return D3DXVECTOR2(48, 448);
	//case eToMiddleOnGround1_1:
	//	return D3DXVECTOR2(5250, 128);
	//default:
	//	break;
	//}
	//return D3DXVECTOR2();
}

void Goomba::GoombaDead()
{
	_FrameCurrent = _FrameEnd + 1;
	_Velocity.x = 0;
}