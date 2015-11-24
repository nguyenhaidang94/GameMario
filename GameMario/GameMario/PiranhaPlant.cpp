#include "PiranhaPlant.h"


PiranhaPlant::PiranhaPlant()
{
}


PiranhaPlant::~PiranhaPlant()
{
}

PiranhaPlant::PiranhaPlant(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::ePiranhaPlant);	//set sprite
	_Size = D3DXVECTOR2(PIRANHAPLANT_WIDTH, PIRANHAPLANT_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-PIRANHAPLANT_VELOCITY_X, -PIRANHAPLANT_VELOCITY_Y);			//set position

	// PiranhaPlant
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;								//set time the turn position+velocity
	SetFrame(objectTypeID);
	_MonsterVelocityX = -PIRANHAPLANT_VELOCITY_X;
	_MonsterVelocityY = -PIRANHAPLANT_VELOCITY_Y;
	_PositionY = positionY;
	_TimeStartStop = GetTickCount();
	_TimePerStop = TIMES_TURN_STOP;
	_PiranhaPlantStop = false;
}

void PiranhaPlant::Update()
{
	DWORD timeNow = GetTickCount();
	if (timeNow - _TimeStartFrame >= _TimePerFrame)
	{
		_TimeStartFrame = timeNow;
		_FrameCurrent = SpriteManager::GetInstance()->NextFrame(_FrameCurrent, _FrameStart, _FrameEnd);
	}

	if (_Position.y >= _PositionY)
	{
		_Position.y = _PositionY;
		_MonsterVelocityY = -PIRANHAPLANT_VELOCITY_Y;
		_PiranhaPlantStop = true;
	}
	if (_Position.y <= _PositionY - 1.4 * 30)//_MonsterVelocityY<0
	{
		_Position.y = _PositionY - 1.4 * 30;
		_MonsterVelocityY = PIRANHAPLANT_VELOCITY_Y;
		_PiranhaPlantStop = true;
	}

	if (_PiranhaPlantStop)
	{
		if (timeNow - _TimeStartStop >= _TimePerStop)
		{
			_TimeStartStop = timeNow;
			_Velocity.y = _MonsterVelocityY;
			_Position.y += _Velocity.y;
			_PiranhaPlantStop = false;
		}
	}
	else
	{
		//if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
		{
			//_TimeStartVelocity = timeNow;
			_Position.y += _Velocity.y;
		}
	}

	//cach 2------------------------------------------------
	//if (_Velocity.y <= -6.0f && _MonsterVelocityY < 0)//trường hợp xuống đáy
	//{
	//	_PiranhaPlantStop = true;
	//	if (timeNow - _TimeStartStop >= _TimePerStop)
	//	{
	//		_TimeStartStop = timeNow;
	//		_MonsterVelocityY = -_MonsterVelocityY;
	//		_Velocity.y = 6.0f;
	//		_PiranhaPlantStop = false;
	//	}
	//}

	//if (_Velocity.y <= 0.0f && _MonsterVelocityY > 0)
	//{
	//	_PiranhaPlantStop = true;
	//	if (timeNow - _TimeStartStop >= _TimePerStop)
	//	{
	//		_TimeStartStop = timeNow;
	//		_MonsterVelocityY = -_MonsterVelocityY;
	//		_Velocity.y = 0.0f;
	//		_PiranhaPlantStop = false;
	//	}
	//}

	////location
	//if (!_PiranhaPlantStop)
	//{
	//	if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
	//	{
	//		_TimeStartVelocity = timeNow;
	//		_Position.y += _Velocity.y;
	//		_Velocity.y -= PIRANHAPLANT_ACCELERATION;//Trừ gia tốc
	//	}
	//}
}

void PiranhaPlant::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void PiranhaPlant::Release()
{
}

void PiranhaPlant::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
#pragma region va chạm ngược
	case eGround:
		//DirectionsCollision(object, collisionDirection);
		break;
	case ePipe:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case ePipeHorizontal:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case eBrick:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case eHardBrick:
	//	DirectionsCollision(object, collisionDirection);
		break;
#pragma endregion
	case eMonster:
		//DirectionsCollision(object, collisionDirection);
		break;

	case eMario:
		switch (collisionDirection)
		{
		case eTop:
		//	PiranhaPlantDead();
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

void PiranhaPlant::SetFrame(int PiranhaPlantType)
{
	switch (PiranhaPlantType)
	{
	case 26:
		_FrameCurrent = 0;
		_FrameStart = 0;
		_FrameEnd= 1;
		break;
	case 27:
		_FrameCurrent = 2;
		_FrameStart = 2;
		_FrameEnd = 3;
		break;
	case 3:
		_FrameCurrent = 4;
		_FrameStart = 4;
		_FrameEnd = 5;
		break;
	case 4:
		_FrameCurrent = 6;
		_FrameStart = 6;
		_FrameEnd = 7;
		break;
	default:
		_FrameCurrent = 0;
		_FrameStart = 0;
		_FrameEnd = 1;
		break;
	};
}

void PiranhaPlant::PiranhaPlantDead()
{
	_FrameCurrent = _FrameEnd;
	_Velocity.x = 0;
	_MonsterVelocityX = 0;
	//_Tag = eGameTag::eDestroyed;
}