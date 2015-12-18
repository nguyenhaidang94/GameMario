#include "KoopaParatroopa.h"


KoopaParatroopa::KoopaParatroopa()
{
}


KoopaParatroopa::~KoopaParatroopa()
{
}

KoopaParatroopa::KoopaParatroopa(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY);										//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKoopaParatroopa);		//set sprite
	_Size = D3DXVECTOR2(KOOPAPARATROOPA_WIDTH, KOOPAPARATROOPA_HEIGHT);					//set size
	_Velocity = D3DXVECTOR2(0, 0);	//set position
	_TypeSpriteID = eSpriteID::eKoopaParatroopa;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;														//set type id of object

	// KoopaParatroopa
	_TimeStartFrame = GetTickCount();													//set time now
	_TimePerFrame = TIMES_TURN;															//set time the turn
	_TimeStartVelocity = GetTickCount();												//set time now
	_TimePerVelocity = TIMES_REVIVED_VELOCITY;											//set time the turn
	SetFrame(objectTypeID);																//set frame
	_MonsterVelocityX = -KOOPAPARATROOPA_VELOCITY_X;
	_MonsterVelocityY = -KOOPAPARATROOPA_VELOCITY_Y;
	_KoopaParatroopaRevived = true;
}

void KoopaParatroopa::Update()
{
	if (_KoopaParatroopaRevived)
	{
		DWORD timeNow = GetTickCount();
		if (_MonsterVelocityX > 0.0f)//set frame bên phải
		{
			_FrameStart = _FrameStartType + 2;
			_FrameEnd = _FrameStart + 1;
		}
		else
		{
			_FrameStart = _FrameStartType;
			_FrameEnd = _FrameStart + 1;
		}
		if (_Velocity.y == 0.0f)
		{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
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
		_Velocity.x = _MonsterVelocityX;
		_Velocity.y -= KOOPAPARATROOPA_ACCELERATION;
		//delete object if it move out of active site
		if (!AABBCheck(Camera::GetInstance()->GetActiveSite(), this->GetBoundaryBox()))
		{
			this->_Tag = eGameTag::eDestroyed;
		}
	}
	else
	{
		KoopaTroopa::Update();
	}
}

void KoopaParatroopa::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void KoopaParatroopa::Release()
{
}

void KoopaParatroopa::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	if (_KoopaParatroopaRevived)
	{
		Box objectBox = object->GetBoundaryBox();
		//Handling collision by object type here
		switch (object->GetObjectTypeID())
		{
		#pragma region va chạm ngược
			case eGround:				//đất
				DirectionsCollision(object, collisionDirection);
				//	DirectionsFrame();
				break;
			case ePipe:					//ống dẫn nước đứng
				DirectionsCollision(object, collisionDirection);
				//	DirectionsFrame();
				break;
			case ePipeHorizontal:		//ống nằm ngang
				DirectionsCollision(object, collisionDirection);
				//	DirectionsFrame();
				break;
			case eBrick:				//Gạch
				//DirectionsCollision(object, collisionDirection);
				//	DirectionsFrame();
				break;
			case eHardBrick:			//Đá
				//DirectionsCollision(object, collisionDirection);
				//	DirectionsFrame();
				break;
		#pragma endregion
		#pragma region Monster
			case eMonster:				//quái
				switch (object->GetSpriteID())
				{
				case ePiranhaPlant://k xét va chạm với con Piranha
					break;
				case eKoopaTroopaDanger:
					switch (collisionDirection)
					{
					case eRight:
						MonsterDead(2);
						break;
					case eLeft:
						MonsterDead(2);
						break;
					default:
						break;
					}
					break;
				default:
					DirectionsCollision(object, collisionDirection);
					break;
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
						_Position.y = objectBox.fY - _Size.y / 2;
						MonsterDead(1);
						break;
					}
				}
				else
				{
					if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)//ngôi sao
					{
						switch (collisionDirection)
						{
						case eTop:
							MonsterDead(2);
							break;
						case eRight:
							MonsterDead(2);
							break;
						case eLeft:
							MonsterDead(2);
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
				case eRight:
					MonsterDead(2);
					break;
				case eLeft:
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
	else
	{
		KoopaTroopa::OnCollision(object, collisionDirection);
	}
}

//set frame loại
void KoopaParatroopa::SetFrame(int MonsterType)
{
	switch (MonsterType)
	{
	case 1:
		_FrameStartType = 0;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 3;
		break;
	case 2:
		_FrameStartType = 4;
		_FrameCurrent = _FrameStartType;
		_FrameEndType = 7;
		break;
	case 31:
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

//hạ cấp nó xuống thành con KoopaTroopa
void KoopaParatroopa::MonsterDead(int MonsterTypeDead)
{
	_KoopaParatroopaRevived = false;

	//set to KoopaParatroopa
	_TypeSpriteID = eSpriteID::eKoopaTroopa;										//set type Id of sprite
	_MonsterTypeID = 30;														//set type id of object
	KoopaTroopa::SetKoopaTroopa(30, _Position.x, _Position.y);
}