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
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eKoopaTroopa;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;													//set type id of object

	// KoopaTroopa
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;														//set time the turn
	_TimeStartVelocity = GetTickCount();											//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;										//set time the turn
	_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
	_KoopaTroopaRevived = true;
	_KoopaTroopaStop = false;
	SetFrame(objectTypeID);															//set frame
}

void KoopaTroopa::SetKoopaTroopa(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);									//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopa);		//set sprite
	_Size = D3DXVECTOR2(KOOPATROOPA_WIDTH, KOOPATROOPA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eKoopaTroopa;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;													//set type id of object

	// KoopaTroopa
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;														//set time the turn
	_TimeStartVelocity = GetTickCount();											//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;										//set time the turn
	_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
	_KoopaTroopaRevived = true;
	_KoopaTroopaStop = false;
	SetFrame(objectTypeID);															//set frame
}

void KoopaTroopa::Update()
{
	if (_MonsterAlive)
	{
		DWORD timeNow = GetTickCount();

		//rơi tự do cộng với quận tốc quán tính
		if (_Velocity.y != 0.0f)//rơi tự do
		{
			//Koopa red
			if (_MonsterTypeID == 30)
			{
				_MonsterVelocityX = -_MonsterVelocityX;			//cho chạy ngược lại
				_Velocity.x = _MonsterVelocityX;
				_Velocity.y = 0.0f;								//set lại vận tốc
				_Position.x += _Velocity.x * 12;				//chỉnh lại vị trí trước đó, tránh trường hợp đứng trên không sẽ đổi tiếp: bị xóa đối tượng nếu đứng trên 0 do trừ ra sẽ va chạm ra ngoài quatree
				_TimeStartFrame = timeNow - _TimePerVelocity;	//mục đích chỉnh thời gian để set lại hình do quay ngược lại.
			}
			else
			{
				if (_MonsterVelocityX > 0.0f)
					_Velocity.x = 0.4f;
				else
					_Velocity.x = -0.4f;
			}
		}

		if (_KoopaTroopaRevived)//còn sống chưa hồi sinh
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
					_TypeSpriteID = eSpriteID::eKoopaTroopa;	//trạng thái di chuyển
					_Size.y = KOOPATROOPA_HEIGHT;				//set lại kích thước
					_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopa);		//set sprite
					SetFrame(_MonsterTypeID);
				}
			}
		}
		else
		{
			if (_KoopaTroopaStop)
			{
				_FrameStart = _FrameStartType;//set về frame đứng yên
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
				_FrameStart = _FrameStartType;
				_FrameEnd = _FrameStart;
				_TypeSpriteID = eSpriteID::eKoopaTroopaDanger;
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

		if (!AABBCheck(Camera::GetInstance()->GetActiveSite(), this->GetBoundaryBox()))
		{
			this->_Tag = eGameTag::eDestroyed;
		}
	}
	else//chết
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
			if (object->GetTag() == eGameTag::eBrickBounceUp)
			{
				switch (collisionDirection)
				{
					//-------------Cái này sẽ dược cập nhật thay thế cho Mario ăn ngôi sao------------------------
				case eBottom:
					MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
					break;
				}
			}
			else
			{
				//DirectionsCollision(object, collisionDirection);
			}
			break;
			break;
		case eHardBrick:
			DirectionsCollision(object, collisionDirection);
			break;
		#pragma endregion
		#pragma region Monster
		case eMonster:
			if (_KoopaTroopaRevived)//nếu nó di chuyển: Khi đứng yên thì tốc độ và hướng sẽ k thay đổi
			{
				switch (object->GetSpriteID())
				{
					case ePiranhaPlant:
						break;
					case eKoopaTroopaDanger:
						if (_TypeSpriteID == eSpriteID::eKoopaTroopaDanger)//2 con nguy hiểm sẽ vội ra
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
					case eKoopaTroopa:
						DirectionsCollisionNoBox(object, collisionDirection);
					default:
						DirectionsCollision(object, collisionDirection);
						break;
				}
			}
			break;
		#pragma endregion
		#pragma region Mario
		case eMario:
			if (object->GetTag() == eMarioIsSmall || object->GetTag() == eMarioIsBig)//bình thường
			{
				switch (collisionDirection)
				{
				case eTop:
					if (_KoopaTroopaStop == false)//chưa đứng yên
					{
						if (_KoopaTroopaRevived == false)//nếu đã chết và bị đá nhưng lại bị dậm lần nữa sẽ set lai tốc độ
						{
							_MonsterVelocityX = _MonsterVelocityX / (KOOPATROOPA_VELOCITY_X + 7.0) * KOOPATROOPA_VELOCITY_X;	//set velocity trở về vận tốc mặt định nhưng hướng vẫn giữ nguyên
						}
						_Velocity.x = 0.0f;
						_KoopaTroopaStop = true;
						_KoopaTroopaRevived = false;
						_TypeSpriteID = eSpriteID::eKoopaTroopaStop;	//trạng thái đứng yên
						_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopaStop);		//set sprite
						SetFrame(_MonsterTypeID);
						_Size.y = KOOPATROOPASTOP_HEIGHT;
						_TimeStartVelocity = GetTickCount();			//set time now: will revive
					}
					break;
				case eRight:
						if (_KoopaTroopaStop == true)					//đứng yên: chết hoặc hồi sinh lại do đang cựa cậy
						{
							_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X - 7.0;//tăng tốc khi bị đá
							_Velocity.x = _MonsterVelocityX;
							_KoopaTroopaStop = false;
							_KoopaTroopaRevived = false;				// nếu đá có sống lại cũng chết
							_TypeSpriteID = eSpriteID::eKoopaTroopaDanger;	//trạng thái di chuyển
							_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaTroopaStop);		//set sprite
							//	_Position.x = objectBox.fX - _Size.y / 2 - 1;
							_Position.x += _Velocity.x * 3;
						}
					break;
				case eLeft:
						if (_KoopaTroopaStop == true)
						{
							_MonsterVelocityX = KOOPATROOPA_VELOCITY_X + 7.0;
							_Velocity.x = _MonsterVelocityX;
							_KoopaTroopaStop = false;
							_KoopaTroopaRevived = false;				// nếu đá có sống lại cũng chết
							_TypeSpriteID = eSpriteID::eKoopaTroopaDanger;	//trạng thái di chuyển
							//_Position.x = objectBox.fX + objectBox.fWidth + _Size.y / 2 + 1;
							_Position.x += _Velocity.x * 3;
						}
					break;
				default:
					break;
				}
			}
			else
			{
				if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)//ngôi sao
				{
					switch (collisionDirection)
					{
					case eRight:
						_MonsterVelocityX = -KOOPATROOPA_VELOCITY_X;
						MonsterDead(2);									//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
						break;
					case eLeft:
						_MonsterVelocityX = KOOPATROOPA_VELOCITY_X;
						MonsterDead(2);
						break;
					default:
						break;
					}
				}
			}
			break;
		#pragma endregion
		#pragma region bullet
		case eBullet:
			switch (collisionDirection)
			{
			case eTop:
				_MonsterVelocityX = -_MonsterVelocityX;
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				break;
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
		#pragma endregion
		#pragma region Not Collision
		case eMagicMushroom://nấm
			break;
		case eFireFlower:	//đạn
			break;
		case e1upMushroom:	//nấm mạng
			break;
		case eStarMan:		//sao
		default:
			break;
		#pragma endregion
		}
	}
}

//set frame loại
void KoopaTroopa::SetFrame(int MonsterType)
{
	if (_MonsterAlive)
	{
		if (_KoopaTroopaRevived)//đi bình thường
		{
			switch (MonsterType)
			{
			case 28:
				_FrameStartType = 0;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 3;
				break;
			case 29:
				_FrameStartType = 4;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 7;
				break;
			case 30:
				_FrameStartType = 8;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 11;
				break;
			case 4:
				_FrameStartType = 12;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 15;
				break;
			default:
				_FrameStartType = 0;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 3;
				break;
			};
		}
		else
		{
			switch (MonsterType)//mai rùa stop
			{
			case 28:
				_FrameStartType = 0;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 1;
				break;
			case 29:
				_FrameStartType = 2;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 3;
				break;
			case 30:
				_FrameStartType = 4;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 5;
				break;
			case 4:
				_FrameStartType = 6;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 7;
				break;
			default:
				_FrameStartType = 0;
				_FrameCurrent = _FrameStartType;
				_FrameEndType = 1;
				break;
			};
		}
	}
	else
	{
		switch (MonsterType)//chết
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