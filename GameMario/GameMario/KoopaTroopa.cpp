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
	_Position = D3DXVECTOR2(positionX, positionY);									//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopa);		//set sprite
	_Size = D3DXVECTOR2(KOOPATROOPA_WIDTH, KOOPATROOPA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-KOOPATROOPA_VELOCITY_X, -KOOPATROOPA_VELOCITY_Y);		//set position
	_TypeSpriteID = eSpriteID::eKoopaTroopa;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;													//set type id of object

	// KoopaTroopa
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;														//set time the turn
	_TimeStartVelocity = GetTickCount();											//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;										//set time the turn
	SetFrame(objectTypeID);															//set frame
	_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
	_KoopaTroopaRevived = true;
	_KoopaTroopaStop = false;
}

void KoopaTroopa::SetKoopaTroopa(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);									//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopa);		//set sprite
	_Size = D3DXVECTOR2(KOOPATROOPA_WIDTH, KOOPATROOPA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-KOOPATROOPA_VELOCITY_X, -KOOPATROOPA_VELOCITY_Y);		//set position
	_TypeSpriteID = eSpriteID::eKoopaTroopa;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;													//set type id of object

	// KoopaTroopa
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;														//set time the turn
	_TimeStartVelocity = GetTickCount();											//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;										//set time the turn
	SetFrame(objectTypeID);															//set frame
	_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
	_KoopaTroopaRevived = true;
	_KoopaTroopaStop = false;
}

void KoopaTroopa::Update()
{
	if (_MonsterAlive)
	{
		DWORD timeNow = GetTickCount();

		if (_KoopaTroopaRevived)//còn sống
		{
			if (!_KoopaTroopaStop)//và đi
			{
				if (_MonsterVelocityX > 0.0f)//bên phải
				{
					_FrameStart = _FrameStartType + 2;
					_FrameEnd = _FrameStart + 1;
				}
				else//bên trái
				{
					_FrameStart = _FrameStartType;
					_FrameEnd = _FrameStart + 1;
				}
			}
			else
			{
				_Velocity.x = 0.0f;
				// REVIVED: cựa cậy sau 1 khoản tg sẽ hồi sinh: trước đó nó sẽ cựa cậy
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
				_FrameStart = _FrameStartType + 4;//set về frame đứng yên
				_FrameEnd = _FrameCurrent = _FrameStart;
				_Velocity.x = 0.0f;

				// REVIVED
				if (timeNow - _TimeStartVelocity >= _TimePerVelocity)
				{
					_TimeStartVelocity = timeNow;
					_KoopaTroopaRevived = true;
					_FrameEnd = _FrameStart + 1;// sau 1 khoảng tg nó có hiện tượng sống lại bằng cách cựa cậy
				}
			}
			else//chạy với mai rùa
			{
				_FrameStart = _FrameStartType + 4;
				_FrameEnd = _FrameStart;
				_TypeSpriteID = eSpriteID::eKoopaTroopaDanger;
			}
		}

		//rơi tự do cộng với quận tốc quán tính
		if (_Velocity.y != 0.0f)//rơi tự do
		{
			if (_MonsterVelocityX > 0.0f)
				_Velocity.x = 0.4f;
			else
				_Velocity.x = -0.4f;
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
	else
	{
		if (_Velocity.y == 0.0f)
		{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
		}

		//location
		_Position.x += _Velocity.x;
		_Position.y += _Velocity.y;

		//set velocity
		_Velocity.x = _MonsterVelocityX;
		_Velocity.y -= KOOPATROOPA_ACCELERATION;
	}
}

void KoopaTroopa::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void KoopaTroopa::Release()
{
}

void KoopaTroopa::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if (_MonsterAlive)
	{
		//Box objectBox = object->GetBoundaryBox();
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
			if (_KoopaTroopaRevived)//nếu nó di chuyển: Khi đứng yên thì tốc độ và hướng sẽ k thay đổi
			{
				switch (object->GetSpriteID())
				{
					case ePiranhaPlant:
						break;
					case eKoopaTroopaDanger:
						if (_TypeSpriteID == eSpriteID::eKoopaTroopaDanger)//2 con nguy hiểm sẽ dậu ra
						{
							DirectionsCollision(object, collisionDirection);
							break;
						}
						else
						{
							switch (collisionDirection)
							{
							case eRight:
								MonsterDead(2);
								_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
								break;
							case eLeft:
								MonsterDead(2);
								_MonsterVelocityX = KOOPATROOPA_VELOCITY_X;
								break;
							default:
								break;
							}
						}
						break;
					default:
						DirectionsCollision(object, collisionDirection);
						break;
				}
			}
			break;
#pragma region Mario
		case eMario:
			switch (collisionDirection)
			{
			case eTop:
				if (_KoopaTroopaStop == false)//chưa đứng yên
				{
					if (_KoopaTroopaRevived == false)//nếu đã chết và bị đá nhưng lại bị dậm lần nữa sẽ set lai tốc độ
					{
						_MonsterVelocityX = _MonsterVelocityX / (KOOPATROOPA_VELOCITY_X + 7.0) * KOOPATROOPA_VELOCITY_X;	//set velocity trở về vận tốc mặt định nhưng hướng vẫn giữ nguyên
						_TypeSpriteID = eSpriteID::eKoopaTroopa;//set type stripeID don't dead
					}
					_Velocity.x = 0.0f;
					_KoopaTroopaStop = true;
					_KoopaTroopaRevived = false;
					_TimeStartVelocity = GetTickCount();		//set time now: will revive

				}
				break;
			case eRight:
				if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)
				{
					_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
					MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				}
				else
				{
					if (_KoopaTroopaStop == true)//đứng yên: chết hoặc hồi sinh lại do đang cựa cậy
					{
						_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X - 7.0;//tăng tốc khi bị đá
						_Velocity.x = _MonsterVelocityX;
						_KoopaTroopaStop = false;
						_KoopaTroopaRevived = false;// nếu đá có sống lại cũng chết
						//	_Position.x = objectBox.fX - _Size.y / 2 - 1;
					}
				}
				break;
			case eLeft:
				if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)
				{
					_MonsterVelocityX = KOOPATROOPA_VELOCITY_X;
					MonsterDead(2);
				}
				else
				{
					if (_KoopaTroopaStop == true)
					{
						_MonsterVelocityX = KOOPATROOPA_VELOCITY_X + 7.0;
						_Velocity.x = _MonsterVelocityX;
						_KoopaTroopaStop = false;
						_KoopaTroopaRevived = false;// nếu đá có sống lại cũng chết
						//_Position.x = objectBox.fX + objectBox.fWidth + _Size.y / 2 + 1;
					}
				}				
				break;
			default:
				break;
			}
			break;
#pragma endregion
		case eBullet:
			switch (collisionDirection)
			{
			case eRight:
				_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				break;
			case eLeft:
				_MonsterVelocityX = KOOPATROOPA_VELOCITY_X;
				MonsterDead(2);
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
}

//set frame loại
void KoopaTroopa::SetFrame(int MonsterType)
{
	if (_MonsterAlive)
	{
		switch (MonsterType)
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
	else
	{
		switch (MonsterType)
		{
		case 28:
			_FrameCurrent = 0;
			_FrameStart = 0;
			_FrameEnd = 0;
			break;
		case 29:
			_FrameCurrent = 1;
			_FrameStart = 1;
			_FrameEnd = 1;
			break;
		case 30:
			_FrameCurrent = 2;
			_FrameStart = 2;
			_FrameEnd = 2;
			break;
		case 4:
			_FrameCurrent = 3;
			_FrameStart = 3;
			_FrameEnd = 3;
			break;
		default:
			_FrameCurrent = 0;
			_FrameStart = 0;
			_FrameEnd = 0;
			break;
		};
	}
}

//Dead
void KoopaTroopa::MonsterDead(int MonsterTypeDead)
{
	_MonsterAlive = false;
	SetObjectType(eMonsterDead);
	switch (MonsterTypeDead)
	{
	case 2://bị tấn công
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopaDead);	//set sprite
		_TypeSpriteID = eSpriteID::eKoopaTroopaDead;
		SetFrame(_MonsterTypeID);
		_MonsterVelocityY = KOOPATROOPA_VELOCITY_Y;
		_Velocity.x = _MonsterVelocityX;
		_Velocity.y = _MonsterVelocityY;
		_Size = D3DXVECTOR2(32, 32);
		break;
	}
}