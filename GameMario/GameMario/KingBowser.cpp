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
	
	// KingBowser
	_TimeStartFrame = GetTickCount();										//set time now
	_TimePerFrame = TIMES_TURN;												//set time the turn
	_TimeStartShoot = GetTickCount();										//set time now
	_TimePerShoot = TIMES_TURN_SHOOT;										//set time the turn
	SetFrame(1);
	_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
	_MonsterVelocityY = -KINGBOWSER_VELOCITY_Y;
	_KingBowserALive = 6;
	_Left = true;

	//Box
	_PositionX = positionX;
	_PositionY = positionY;
	int iPosition = _PositionX / SCREEN_WIDTH;
	iPosition *= SCREEN_WIDTH;								//lấy vị trí khung bắt đầu
	_WorldWidth = Camera::GetInstance()->GetWorldSize().x;	//chiều dài thế giới game
	_BoxWidthMin = iPosition + SCREEN_WIDTH / 4;
	_BoxWidthMax = iPosition + SCREEN_HEIGHT;
	//set lại vị trí cho vào khung đúng
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

	float iViewPortX = Camera::GetInstance()->GetViewPort().x;
	_KingBowserBoxWidthMin = iViewPortX + SCREEN_WIDTH / 2;
	_KingBowserBoxWidthMax = iViewPortX + SCREEN_WIDTH + BUFFER_FOR_SCREEN;

	if (_KingBowserBoxWidthMin < _BoxWidthMin)
	{
		_KingBowserBoxWidthMin = _BoxWidthMin;
	}
	if (_KingBowserBoxWidthMax > _BoxWidthMax)
	{
		_KingBowserBoxWidthMax = _BoxWidthMax;
	}
	//giữa màn hình lớn hơn: giửa mh
	//nhảy

	int iMarioPositionX = Mario::GetInstance()->GetPosition().x;
	
	if (_Velocity.y == 0.0f)
	{
		if (iMarioPositionX >= _Position.x - KINGBOWSER_WIDTH && iMarioPositionX <= _Position.x + KINGBOWSER_WIDTH)
		{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
		}
		else
		{
			int min = 0;
			int max = 10;
			int random = rand() % (max - min + 1) + min;
			if (random == 0)
			{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
			}
		}
	}
	else
	{
		//nhảy
		_Velocity.y -= KOOPAPARATROOPA_ACCELERATION;
	}

	//không được đổi ngược vận tốc phải gán tránh trường hợp thay đổi liên tục khi nằm ngoài vùng
	if (_Position.x >= _KingBowserBoxWidthMax)
	{
		_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
		_TimeStartFrame = GetTickCount() - _TimePerFrame;
		_Velocity.x = _MonsterVelocityX;
	}
	else
	{
		if (_Position.x <= _KingBowserBoxWidthMin)
		{
			_MonsterVelocityX = KINGBOWSER_VELOCITY_X;
			_TimeStartFrame = GetTickCount() - _TimePerFrame;
			_Velocity.x = _MonsterVelocityX;
		}
	}
}

void KingBowser::KingBowserGun()
{
	DWORD timeNow = GetTickCount();
	if (timeNow - _TimeStartShoot >= _TimePerShoot)
	{
		_TimeStartShoot = timeNow;

		int iMarioPositionX = Mario::GetInstance()->GetPosition().x;
		if (iMarioPositionX < _Position.x)
		{
			_KingBowserGun.GunShoot(D3DXVECTOR2(_Position.x - KINGBOWSER_WIDTH / 2, _Position.y), true, D3DXVECTOR2(_PositionX, _PositionY), 1);
		}
		else
		{
			if (iMarioPositionX > _Position.x)
			{
				_KingBowserGun.GunShoot(D3DXVECTOR2(_Position.x + KINGBOWSER_WIDTH, _Position.y + KINGBOWSER_HEIGHT / 3), false, D3DXVECTOR2(_PositionX, _PositionY), 1);
			}
		}
	}
}

void KingBowser::Update()
{
	if (_TypeSpriteID == eSpriteID::eKingBowser)
	{
		DWORD timeNow = GetTickCount();

		//--Random vị trí của KingBowser--------------------------------------------------------------------
		KingBowserMove();
		KingBowserGun();
		_KingBowserGun.Update();
		//---------------------------------------------------------------------------------------------------

		if (_MonsterAlive)
		{
			int iMarioPositionX = Mario::GetInstance()->GetPosition().x;

			if (iMarioPositionX < _Position.x)
			{
				_FrameStart = 0;
				_FrameEnd = 3;
			}
			else
			{
				if (iMarioPositionX >  _Position.x)
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
			/*if (_Position.x >= Camera::GetInstance()->GetViewPort().x + SCREEN_WIDTH + BUFFER_FOR_SCREEN)
			{
				_Position.x = Camera::GetInstance()->GetViewPort().x + SCREEN_WIDTH + BUFFER_FOR_SCREEN - 10;
			}*/
			
			//delete object if it move out of active site
			/*if (!AABBCheck(Camera::GetInstance()->GetActiveSite(), this->GetBoundaryBox()))
			{
				this->_Tag = eGameTag::eDestroyed;
			}*/
		}
	}
}

void KingBowser::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
	_KingBowserGun.Render();
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
			break;
		#pragma endregion
		#pragma region Mario
		case eMario:
			if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)//ngôi sao
			{
				switch (collisionDirection)
				{
				case eRight:
			//		MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
					break;
				case eLeft:
			//		MonsterDead(2);
					break;
				}
			}
			break;
		#pragma endregion
		#pragma region bullet
		case eBullet:
			switch (collisionDirection)
			{
			case eTop:
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
			case eRight:
				MonsterDead(2);//để sau _MonsterVelocityX để hàm cập nhật lại _Velocity.x
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
	switch (MonsterTypeDead)
	{
	case 1:

		break;
	case 2:
		_KingBowserALive--;
		if (_KingBowserALive < 1)
		{
			//dead
			int a = 0;
		}
		break;
	}
	
}