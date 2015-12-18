#include "KingBowser.h"


KingBowser::KingBowser()
{
}


KingBowser::~KingBowser()
{
}

KingBowser::KingBowser(int objectTypeID, int positionX, int positionY)
{
	//Object																//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKingBowser);	//set sprite
	_Size = D3DXVECTOR2(KINGBOWSER_WIDTH, KINGBOWSER_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eKingBowser;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;											//set type id of object

	// KingBowser
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;									//set time the turn
	SetFrame(1);
	_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
	_MonsterVelocityY = -KINGBOWSER_VELOCITY_Y;
	_KingBowserALive = 6;

	//Box
	_PositionX = positionX;
	int iPosition = _PositionX / SCREEN_WIDTH;
	iPosition *= SCREEN_WIDTH;								//lấy vị trí khung bắt đầu
	_WorldWidth = Camera::GetInstance()->GetWorldSize().x;	//chiều dài thế giới game
	_BoxWidthMin = iPosition + SCREEN_WIDTH / 2;
	_BoxWidthMax = iPosition + SCREEN_HEIGHT;
	if (positionX<_BoxWidthMin || positionX>_BoxWidthMax)
	{
		_Position.x = _BoxWidthMin;
		_PositionX = _Position.x;
	}
	
	
	//_KingBowserBoxWidthMin = 2624 * 2;						//2624= 5*512 + 512/8; Khoảng cách trong game mà quái duy chuyển
	//_KingBowserBoxWidthMax = 2624*2 + SCREEN_WIDTH / 4*3;
}

void KingBowser::KingBowserMove()
{ 
	//int r = rand() % 255;

	Mario::GetInstance()->GetPosition().x;

	float iViewPortX = Camera::GetInstance()->GetViewPort().x;
	_KingBowserBoxWidthMin = _BoxWidthMin;
	_KingBowserBoxWidthMax = iViewPortX + SCREEN_WIDTH;

	if (_BoxWidthMax < _KingBowserBoxWidthMax)
	{
		_KingBowserBoxWidthMax = _BoxWidthMax;
	}
	
	if (_Velocity.y == 0.0f)
	{
		int min = 0;
		int max = 4;
		int random = rand() % (max - min + 1) + min;
		if (random == 0)
		{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
		}
	}
	//nháy
	_Velocity.y -= KOOPAPARATROOPA_ACCELERATION;


	if (_Position.x >= _KingBowserBoxWidthMax || _Position.x <= _KingBowserBoxWidthMin)
	{
		_MonsterVelocityX = -_MonsterVelocityX;
		_TimeStartFrame = GetTickCount() - _TimePerFrame;
		_Velocity.x = _MonsterVelocityX;
	}
}

void KingBowser::Update()
{
	if (_TypeSpriteID == eSpriteID::eKingBowser)
	{
		DWORD timeNow = GetTickCount();

		//--Random vị trí của KingBowser--------------------------------------------------------------------
		KingBowserMove();
		//-----------------------------------------------------------------------------------------------

		if (_MonsterAlive)
		{
			if (_MonsterVelocityX < 0)
			{
				_FrameStart = 0;
				_FrameEnd = 3;
			}
			else
			{
				if (_MonsterVelocityX > 0)
				{
					_FrameStart = 4;
					_FrameEnd = 7;
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

			//_Velocity.y = -KINGBOWSER_VELOCITY_Y;
			//_Velocity.x = 0.0f;							///Cái này chặn tốc độ không cho di chuyển khi chưa cho phép nếu nhảy lên k chạm dất k di chuyển dc

			//delete object if it move out of active site
			if (!AABBCheck(Camera::GetInstance()->GetActiveSite(), this->GetBoundaryBox()))
			{
				this->_Tag = eGameTag::eDestroyed;
			}
		}
	}
	else//chết bị tác động
	{
	}
}

void KingBowser::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void KingBowser::Release()
{
}

void KingBowser::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	if (_MonsterAlive){
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
	//		DirectionsCollision(object, collisionDirection);
			break;
		case eHardBrick:
	//		DirectionsCollision(object, collisionDirection);
			break;
		#pragma endregion
		#pragma region Monster
		case eMonster:
			switch (object->GetSpriteID())
			{
			case ePiranhaPlant://k xét va chạm với con Piranha
				break;
			case eKoopaTroopaDanger:
				switch (collisionDirection)
				{
				case eRight:
					MonsterDead(2);
					_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
					break;
				case eLeft:
					MonsterDead(2);
					_MonsterVelocityX = KINGBOWSER_VELOCITY_X;
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
			//if (object->GetTag() == eMarioIsSmall || object->GetTag() == eMarioIsBig)//bình thường
			//{
			//	
			//}
			//else
			//{
			//	if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)//ngôi sao
			//	{
			//		switch (collisionDirection)
			//		{
			//		case eRight:
			//			_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
			//			MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
			//			break;
			//		case eLeft:
			//			_MonsterVelocityX = KINGBOWSER_VELOCITY_X;
			//			MonsterDead(2);
			//			break;
			//		}
			//	}
			//}
			break;
		#pragma endregion
		#pragma region bullet
		case eBullet:
			switch (collisionDirection)
			{
			case eRight:
				_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				break;
			case eLeft:
				_MonsterVelocityX = KINGBOWSER_VELOCITY_X;
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

void KingBowser::SetFrame(int MonsterType)
{
	switch (MonsterType)
	{
	case 1:
		_FrameStart = 0;
		_FrameCurrent = _FrameStart;
		_FrameEnd = 3;
		break;
	case 2:
		_FrameStart = 4;
		_FrameCurrent = _FrameStart;
		_FrameEnd = 7;
		break;
	}
}

void KingBowser::MonsterDead(int MonsterTypeDead)
{
	
}