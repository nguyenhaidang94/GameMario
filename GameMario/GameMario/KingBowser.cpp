#include "KingBowser.h"


KingBowser::KingBowser()
{
}


KingBowser::~KingBowser()
{
}

KingBowser::KingBowser(int objectTypeID, int positionX, int positionY)
{
	//Object																	//set id
	_Position = D3DXVECTOR2(positionX, positionY);								//set position
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eKingBowser);	//set sprite
	_Size = D3DXVECTOR2(KINGBOWSER_WIDTH, KINGBOWSER_HEIGHT);					//set size
	_Velocity = D3DXVECTOR2(0, 0);		//set position
	_TypeSpriteID = eSpriteID::eKingBowser;										//set type Id of sprite
	
	// KingBowser
	_TimeStartFrame = GetTickCount();											//set time now
	_TimePerFrame = TIMES_TURN;													//set time the turn sprite
	_TimeStartShoot = GetTickCount();											//set time now
	_TimePerShoot = TIMES_TURN_SHOOT;											//set time the turn shoot
	SetFrame(1);
	_MonsterVelocityX = -KINGBOWSER_VELOCITY_X;
	_MonsterVelocityY = -KINGBOWSER_VELOCITY_Y;
	_KingBowserALive = 6;														//set the number alive
	_Left = true;																//set the variable left
	_TimeStartBounce = GetTickCount();											//set time now
	_TimePerBounce = TIMES_TURN_BOUNCE;											//set time the turn bounce

	//Box
	_PositionX = positionX;
	_PositionY = positionY;
	int iPosition = _PositionX / SCREEN_WIDTH;
	iPosition *= SCREEN_WIDTH;								//lấy vị trí khung bắt đầu
	_WorldWidth = Camera::GetInstance()->GetWorldSize().x;	//chiều dài thế giới game
	_BoxWidthMin = iPosition + SCREEN_WIDTH / 4;
	_BoxWidthMax = iPosition + SCREEN_HEIGHT - SCREEN_WIDTH / 6 - 10;
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
	DWORD timeNow;
	int iMarioPositionX = Mario::GetInstance()->GetPosition().x;
	int iMarioPositionY = Mario::GetInstance()->GetPosition().y;
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
	if (_Velocity.y == 0.0f)
	{
		//mario vào vị trí này sẽ nhảy lên va chạm
		if (iMarioPositionX >= _Position.x - KINGBOWSER_WIDTH && iMarioPositionX <= _Position.x + KINGBOWSER_WIDTH && iMarioPositionY > _PositionY)
		{
			_MonsterVelocityY = -_MonsterVelocityY;
			_Velocity.y = _MonsterVelocityY;
		}
		else
		{
			timeNow = GetTickCount();
			//if (timeNow - _TimeStartBounce >= _TimePerBounce)						//time radom velocity and bounce
			{
				_TimeStartBounce = timeNow;

				//random Velocity x
				int minX = 1;
				int maxX = 5;
				int randomX = rand() % (maxX - minX + 1) + minX;
				_Velocity.x = _MonsterVelocityX / randomX;

				//random Velocity y
				int minY = 0;
				int maxY = 2;
				int randomY = rand() % (maxY - minY + 1) + minY;
				if (randomY == 0)
				{
					_MonsterVelocityY = -_MonsterVelocityY;//
					_Velocity.y = _MonsterVelocityY;
				}
			}
		}
	}
	else
	{
		//nhảy
		_Velocity.y -= KINGBOWSER_ACCELERATION;
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
	//đưa này vào súng
	DWORD timeNow = GetTickCount();
	if (timeNow - _TimeStartShoot >= _TimePerShoot)
	{
		_TimeStartShoot = timeNow;

		int iMarioPositionX = Mario::GetInstance()->GetPosition().x;

		/*int minX = 0;
		int maxX = 5;
		int randomX = rand() % (maxX - minX + 1) + minX;*/

		if (iMarioPositionX < _Position.x)
		{
			_KingBowserGun.GunShoot(D3DXVECTOR2(_Position.x - KINGBOWSER_WIDTH / 2, _Position.y), true, D3DXVECTOR2(_PositionX, _PositionY), 3);
		}
		else
		{
			if (iMarioPositionX > _Position.x)
			{
				_KingBowserGun.GunShoot(D3DXVECTOR2(_Position.x + KINGBOWSER_WIDTH / 2, _Position.y + KINGBOWSER_HEIGHT / 3), false, D3DXVECTOR2(_PositionX, _PositionY), 1);
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
			//_Position.x += _Velocity.x;
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