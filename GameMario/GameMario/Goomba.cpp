#include "Goomba.h"


Goomba::Goomba()
{
}


Goomba::~Goomba()
{
}

Goomba::Goomba(int objectTypeID, int positionX, int positionY)
{
	//Object																//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eGoomba);	//set sprite
	_Size = D3DXVECTOR2(GOOMBA_WIDTH, GOOMBA_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(-GOOMBA_VELOCITY_X, -GOOMBA_VELOCITY_Y);		//set position
	_TypeSpriteID = eSpriteID::eGoomba;										//set type Id of sprite
	_MonsterTypeID = objectTypeID;											//set type id of object
	
	// Goomba
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartVelocity = GetTickCount();									//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;									//set time the turn
	SetFrame(objectTypeID);
	_MonsterVelocityX = -GOOMBA_VELOCITY_X;
	_MonsterVelocityY = -GOOMBA_VELOCITY_Y;
	_TimePerDead = TIMES_PER_DEAD;
	positionx = positionX;
}

void Goomba::Update()
{
	if (_TypeSpriteID == eSpriteID::eGoomba)
	{
		DWORD timeNow = GetTickCount();
		if (_MonsterAlive)
		{
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

				//vận tốc x khi rơi tự do
				if (_MonsterVelocityX > 0)
					_Velocity.x = 0.5f;
				else
					_Velocity.x = -0.5f;
			}

			_Velocity.y = -GOOMBA_VELOCITY_Y;
		}
		else//chết dậm
		{
			if (timeNow - _TimeStartDead > _TimePerDead)
			{
				_Tag = eGameTag::eDestroyed;
			}
		}
	}
	else//chết bị tác động
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
		_Velocity.y -= GOOMBA_ACCELERATION;
	}
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
					_MonsterVelocityX = -GOOMBA_VELOCITY_X;
					break;
				case eLeft:
					MonsterDead(2);
					_MonsterVelocityX = GOOMBA_VELOCITY_X;
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
						_MonsterVelocityX = -GOOMBA_VELOCITY_X;
						MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
					}
					break;
				case eLeft:
					if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)
					{
						_MonsterVelocityX = GOOMBA_VELOCITY_X;
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
				_MonsterVelocityX = -GOOMBA_VELOCITY_X;
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
				break;
			case eLeft:
				_MonsterVelocityX = GOOMBA_VELOCITY_X;
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

void Goomba::SetFrame(int MonsterType)
{
	if (_TypeSpriteID == eSpriteID::eGoomba)
	{
		switch (MonsterType)
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
	else
	{
		switch (MonsterType)
		{
		case 24:
			_FrameCurrent = 0;
			_FrameStart = 0;
			_FrameEnd = 0;
			break;
		case 25:
			_FrameCurrent = 1;
			_FrameStart = 1;
			_FrameEnd = 1;
			break;
		case 3:
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

void Goomba::MonsterDead(int MonsterTypeDead)
{
	_MonsterAlive = false;
	SetObjectType(eMonsterDead);
	switch (MonsterTypeDead)
	{
		case 1://dậm trên đầu
			_FrameCurrent = _FrameEnd + 1;
			_Velocity.x = 0;
			_MonsterVelocityX = 0;
			_TimeStartDead = GetTickCount();
			break;
		case 2://bị tấn công
			_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eGoombaDead);	//set sprite
			_TypeSpriteID = eSpriteID::eGoombaDead;
			SetFrame(_MonsterTypeID);
			_MonsterVelocityY = GOOMBA_VELOCITY_Y;
			_Velocity.x = _MonsterVelocityX;
			_Velocity.y = _MonsterVelocityY;
			break;
	}
}