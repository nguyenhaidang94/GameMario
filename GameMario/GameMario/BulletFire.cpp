#include "BulletFire.h"


BulletFire::BulletFire()
{
	//Object						//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletFire);	//set sprite
	_Size = D3DXVECTOR2(BULLETFIRE_WIDTH, BULLETFIRE_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eBulletFire;										//set type Id of sprite

	// BulletFire
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;
	_MonsterVelocityX = 0;
	_MonsterVelocityY = 0;
	_BulletType = 0;
	_PositionEndY = _Position.y;
}


BulletFire::~BulletFire()
{
}


BulletFire::BulletFire(int objectTypeID, int positionX, int positionY)
{
	//Object																//set id
	_Position = D3DXVECTOR2(positionX, positionY);							//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBulletFire);	//set sprite
	_Size = D3DXVECTOR2(BULLETFIRE_WIDTH, BULLETFIRE_HEIGHT);						//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eBulletFire;										//set type Id of sprite

	// BulletFire
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn	
	if (objectTypeID == 36)
		_MonsterVelocityX = -BULLETFIRE_VELOCITY_X;
	else
		_MonsterVelocityX = BULLETFIRE_VELOCITY_X;
	SetFrame(objectTypeID);
	_MonsterVelocityY = 0.0f;
	_BulletType = 0;
	_PositionEndY = _Position.y;
}

void BulletFire::BulletFireMoveY( FLOAT PositionEndY)
{
	if (_Position.y != PositionEndY)
	{
		// _Position.y - PositionEndY : khoảng cách này có thể không thể bằng nhau do các khoảng gia tốc trừ ra có thể chệch
		if (abs(_Position.y - PositionEndY) < BULLETFIRE_VELOCITY_Y)
		{
			_Position.y = PositionEndY;
		}
		else
		{
			if (_Position.y < PositionEndY)
			{
				_Position.y += BULLETFIRE_VELOCITY_Y;
				_Velocity.x = _MonsterVelocityX / 2;
			}
			else
			{
				if (_Position.y > PositionEndY)
				{
					_Position.y -= BULLETFIRE_VELOCITY_Y;
					_Velocity.x = _MonsterVelocityX / 2;
				}
			}
		}
	}
}

void BulletFire::SetBullet(D3DXVECTOR2 BulletPosition, bool IsLeft, D3DXVECTOR2 PositionKing, int BulletType)
{
	_Size = D3DXVECTOR2(BULLETFIRE_WIDTH, BULLETFIRE_HEIGHT);						//set size
	_TypeSpriteID = eSpriteID::eBulletFire;											//set type Id of sprite

	// BulletFire
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;
	_Position = D3DXVECTOR2(BulletPosition.x, BulletPosition.y);
	if (IsLeft)
	{
		_MonsterVelocityX = -BULLETFIRE_VELOCITY_X;
	}
	else
	{
		_MonsterVelocityX = BULLETFIRE_VELOCITY_X;
	}
	_Velocity.x = _MonsterVelocityX;
	SetFrame(1);

	switch (BulletType)
	{
	case 0:									//position is position of KingBowser		: random
		_PositionEndY = _Position.y;
		break;
	case 1:									//position is position of ground + 32		: mario small
		_PositionEndY = PositionKing.y;
		break;
	case 2:									//position is position of ground + 32 + 32	: mario big
		_PositionEndY = PositionKing.y + 32;
		break;
	case 3:									//position is position of ground + 32 + 64	: mario jump
		_PositionEndY = PositionKing.y + 64;
		break;
	}

}

void BulletFire::Update()
{
	DWORD timeNow = GetTickCount();
	if (_MonsterAlive)
	{
		if (timeNow - _TimeStartFrame >= _TimePerFrame)
		{
			_TimeStartFrame = timeNow;
			_FrameCurrent = SpriteManager::GetInstance()->NextFrame(_FrameCurrent, _FrameStart, _FrameEnd);
		}

		BulletFireMoveY(_PositionEndY);
		//location
		_Position.x += _Velocity.x;
		_Position.y += _Velocity.y;

		_Velocity.x = _MonsterVelocityX;
		_Velocity.y = _MonsterVelocityY;
		//delete object if it move out of active site
	}
}

void BulletFire::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void BulletFire::Release()
{
}

void BulletFire::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	
}

void BulletFire::SetFrame(int MonsterType)
{
	if (_MonsterVelocityX <= 0)
	{
		_FrameStart = 0;
		_FrameEnd = 1;
	}
	else
	{
		_FrameStart = 2;
		_FrameEnd = 3;
	}
	_FrameCurrent = _FrameStart;
}

void BulletFire::MonsterDead(int MonsterTypeDead)
{
	SetTag(eEmpty);
}

void BulletFire::SetPosition(FLOAT PositionX, FLOAT PositionY)
{
	_Position.x = PositionX;
	_Position.y = PositionY;
}

void BulletFire::SetVelocity(FLOAT VelocityX, FLOAT VelocityY)
{
	_MonsterVelocityX = VelocityX;
	_MonsterVelocityX = VelocityY;
	_Velocity.x = _MonsterVelocityX;
	_Velocity.y = _MonsterVelocityY;
	SetFrame(1);
}