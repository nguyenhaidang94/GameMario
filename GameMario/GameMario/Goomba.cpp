#include "Goomba.h"


Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

Goomba::Goomba(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eGoomba);	//set sprite
	_Size = D3DXVECTOR2(GOOMBA_WIDTH, GOOMBA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-GOOMBA_VELOCITY_X, -GOOMBA_VELOCITY_Y);			//set position
	
	// Goomba
	 _TimeStartFrame= GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;									//set time the turn
	SetFrame(objectTypeID);
	_MonsterVelocityX = -GOOMBA_VELOCITY_X;
	positionx = positionX;
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
		#pragma region va chạm ngược
		case eGround:
			DirectionsCollision(object, collisionDirection);
			break;
		case ePipe:
			DirectionsCollision(object, collisionDirection);
			break;
		case ePipeHorizontal:
			DirectionsCollision(object, collisionDirection);
			break;
		case eBrick:
			DirectionsCollision(object, collisionDirection);
			break;
		case eHardBrick:
			DirectionsCollision(object, collisionDirection);
			break;
		#pragma endregion
		case eMonster:
			DirectionsCollision(object, collisionDirection);
			break;
		
		case eMario:
			switch (collisionDirection)
			{
				case eTop:
					GoombaDead();
					break;
				default:
					break;
			}
			break;
		case eMagicMushroom://nấm
			break;
		case eFireFlower:	//đạn
			break;
		case e1upMushroom:	//nấm mạng
			break;
		case eStarMan:		//sao
		default:
			break;
	}
}

void Goomba::SetFrame(int GoombaType)
{
	switch (GoombaType)
	{
	case 24:
		_FrameCurrent = 0;
		_FrameStart = 0;
		_FrameEnd = 1;
		break;
	case 25:
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

void Goomba::GoombaDead()
{
	_FrameCurrent = _FrameEnd + 1;
	_Velocity.x = 0;
	_MonsterVelocityX = 0;
	//_Tag = eGameTag::eDestroyed;
}