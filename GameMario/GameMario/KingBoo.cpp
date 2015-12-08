#include "KingBoo.h"


KingBoo::KingBoo()
{
}


KingBoo::~KingBoo()
{
}

KingBoo::KingBoo(int objectTypeID, int positionX, int positionY)
{
	//Object																//set id
	_Position = D3DXVECTOR2(positionX-200, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKingBoo);	//set sprite
	_Size = D3DXVECTOR2(KINGBOO_WIDTH, KINGBOO_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eKingBoo;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;											//set type id of object

	// KingBoo
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;									//set time the turn
	SetFrame(1);
	_MonsterVelocityX = KINGBOO_VELOCITY_X;
	_MonsterVelocityY = -KINGBOO_VELOCITY_Y;
}

void KingBoo::Update()
{
	if (_TypeSpriteID == eSpriteID::eKingBoo)
	{
		DWORD timeNow = GetTickCount();
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

			_Velocity.y = -KINGBOO_VELOCITY_Y;
			_Velocity.x = 0.0f;

			
		}
	}
	else//chết bị tác động
	{
	}
}

void KingBoo::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void KingBoo::Release()
{
}

void KingBoo::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
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
			DirectionsCollision(object, collisionDirection);
			break;
		case eHardBrick:
			DirectionsCollision(object, collisionDirection);
			break;
#pragma endregion
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
					_MonsterVelocityX = -KINGBOO_VELOCITY_X;
					break;
				case eLeft:
					MonsterDead(2);
					_MonsterVelocityX = KINGBOO_VELOCITY_X;
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

		case eMario:
			switch (collisionDirection)
			{
			case eTop:
				MonsterDead(1);
				break;
				//-------------Cái này sẽ dược cập nhật thay thế cho Mario ăn ngôi sao------------------------
			case eRight:
				if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)
				{
					_MonsterVelocityX = -KINGBOO_VELOCITY_X;
					MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				}
				break;
			case eLeft:
				if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)
				{
					_MonsterVelocityX = KINGBOO_VELOCITY_X;
					MonsterDead(2);
				}
				break;
			}
			break;

			//------------- Monster dead -----------------------
		case eBullet:
			switch (collisionDirection)
			{
			case eRight:
				_MonsterVelocityX = -KINGBOO_VELOCITY_X;
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				break;
			case eLeft:
				_MonsterVelocityX = KINGBOO_VELOCITY_X;
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

void KingBoo::SetFrame(int MonsterType)
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

void KingBoo::MonsterDead(int MonsterTypeDead)
{
	
}