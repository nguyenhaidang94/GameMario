#include "KoopaTroopa.h"


KoopaTroopa::KoopaTroopa()
{
}


KoopaTroopa::~KoopaTroopa()
{
}

KoopaTroopa::KoopaTroopa(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopa);	//set sprite
	_Size = D3DXVECTOR2(KOOPATROOPA_WIDTH, KOOPATROOPA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-KOOPATROOPA_VELOCITY_X, -KOOPATROOPA_VELOCITY_Y);			//set position

	// KoopaTroopa
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;								//set time the turn
	SetFrame(objectTypeID);													//set frame
	_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
	_KoopaTroopaRevived = true;
	_KoopaTroopaStop = false;
}

void KoopaTroopa::Update()
{
	DWORD timeNow = GetTickCount();

	if (_KoopaTroopaRevived)
	{
		if (!_KoopaTroopaStop)
		{
			if (_MonsterVelocityX > 0.0f)
			{
				_FrameStart = _FrameStartType + 2;
				_FrameCurrent = _FrameStart;
				_FrameEnd = _FrameStart + 1;
			}
			else
			{
				_FrameStart = _FrameStartType;
				_FrameCurrent = _FrameStart;
				_FrameEnd = _FrameStart + 1;
			}
		}
		else
		{
			_Velocity.x = 0.0f;
			// REVIVED
			if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
			{
				_KoopaTroopaStop = false;
			}
		}
	}
	else
	{
		if (_KoopaTroopaStop)
		{
			_FrameStart = _FrameStartType + 4;
			_FrameEnd = _FrameCurrent = _FrameStart;
			_Velocity.x = 0.0f;

			// REVIVED
			if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
			{
				_TimeStartVelocity = timeNow;
				_KoopaTroopaRevived = true;
				_FrameStart = _FrameStartType + 4;
				_FrameEnd = _FrameStart + 1;
			}
		}
		else//chạy với mai rùa
		{
			_FrameStart = _FrameStartType + 4;
			_FrameEnd = _FrameStart;
			/*Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
			if (_Position.x < cameraBox.fX - KOOPATROOPA_WIDTH || _Position.x > cameraBox.fX + cameraBox.fWidth + KOOPATROOPA_WIDTH ||
				_Position.y > cameraBox.fY + KOOPATROOPA_WIDTH || _Position.y < cameraBox.fY - cameraBox.fHeight - KOOPATROOPA_WIDTH)
			{
				_Tag = eGameTag::eDestroyed;
			}*/
		}
	}

	if (timeNow - _TimeStartFrame >= _TimePerFrame)
	{
		_TimeStartFrame = timeNow;
		_FrameCurrent = SpriteManager::GetInstance()->NextFrame(_FrameCurrent, _FrameStart, _FrameEnd);
	}

	//location
	_Position.x += _Velocity.x;
	_Position.y += _Velocity.y;
	
	//set velocity
	_Velocity.x = 0.0f;
	_Velocity.y = -KOOPATROOPA_VELOCITY_Y;
}

void KoopaTroopa::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void KoopaTroopa::Release()
{
	if (_Sprite != NULL)
		delete _Sprite;
}

void KoopaTroopa::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	Box objectBox = object->GetBoundaryBox();
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
#pragma region va chạm ngược
	case eGround:
		DirectionsCollision(object, collisionDirection);
	//	DirectionsFrame();
		break;
	case ePipe:
		DirectionsCollision(object, collisionDirection);
	//	DirectionsFrame();
		break;
	case ePipeHorizontal:
		DirectionsCollision(object, collisionDirection);
	//	DirectionsFrame();
		break;
	case eBrick:
		DirectionsCollision(object, collisionDirection);
	//	DirectionsFrame();
		break;
	case eHardBrick:
		DirectionsCollision(object, collisionDirection);
	//	DirectionsFrame();
		break;
#pragma endregion
	case eMonster:
		DirectionsCollision(object, collisionDirection);
		//DirectionsFrame();
		break;
	case eMario:
		switch (collisionDirection)
		{
			case eTop:
				if (_KoopaTroopaStop == false)//chưa đứng yên
				{
					_Velocity.x = 0.0f;
					_KoopaTroopaStop = true;
					_KoopaTroopaRevived = false;
					_TimeStartVelocity = GetTickCount();		//set time now: will revive
					_Position.y = objectBox.fY - _Size.y / 2;
					if (_KoopaTroopaRevived == false)
					{
						_MonsterVelocityX = _MonsterVelocityX / _MonsterVelocityX * KOOPATROOPA_VELOCITY_X;	//set velocity trở về vận tốc mặt định nhưng hướng vẫn giữ nguyên
					}
				}
				break;
			case eRight:
				if (_KoopaTroopaRevived == false && _KoopaTroopaStop == true)//chết và đứng yên
				{
					_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X - 6.5;
					_Velocity.x = _MonsterVelocityX;
					_KoopaTroopaStop = false;
					_Position.x = objectBox.fX - _Size.y / 2 - 1;
				}
				break;
			case eLeft:
				if (_KoopaTroopaRevived == false && _KoopaTroopaStop == true)
				{
					_MonsterVelocityX = KOOPATROOPA_VELOCITY_X + 6.5;
					_Velocity.x = _MonsterVelocityX;
					_KoopaTroopaStop = false;
					_Position.x = objectBox.fX + objectBox.fWidth + _Size.y / 2 + 1;
				}
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

//set frame loại
void KoopaTroopa::SetFrame(int KoopaTroopaType)
{
	switch (KoopaTroopaType)
	{
	case 28:
		_FrameStartType = 0;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 5;
		break;
	case 29:
		_FrameStartType = 6;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 11;
		break;
	case 30:
		_FrameStartType = 12;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 17;
		break;
	case 4:
		_FrameStartType = 18;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 23;
		break;
	default:
		_FrameStartType = 0;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 5;
		break;
	};
}
