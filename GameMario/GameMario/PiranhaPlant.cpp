﻿#include "PiranhaPlant.h"


PiranhaPlant::PiranhaPlant()
{
}


PiranhaPlant::~PiranhaPlant()
{
}

PiranhaPlant::PiranhaPlant(int objectTypeID, int positionX, int positionY)
{
	//Object											//set id
	_Position = D3DXVECTOR2(positionX, positionY - 1.4 * 32);						//set position: positionY - 1.4 * 32 mục đích cho đi từ trên xuống lúc bắt đầu
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::ePiranhaPlant);	//set sprite
	_Size = D3DXVECTOR2(PIRANHAPLANT_WIDTH, PIRANHAPLANT_HEIGHT);					//set size
	_Velocity = D3DXVECTOR2(0, PIRANHAPLANT_VELOCITY_Y);	//set position
	_TypeSpriteID = eSpriteID::ePiranhaPlant;										//set type spriteID
	_MonsterTypeID = objectTypeID;
	SetObjectType(eMonsterDead);													//trạng thái chết tạm thời: để không bị va chạm khi mới vào: do đang ở dưới

	// PiranhaPlant
	_TimeStartFrame = GetTickCount();												//set time now
	_TimePerFrame = TIMES_TURN;														//set time the turn
	_TimeStartVelocity = GetTickCount();											//set time now
	_TimePerVelocity = TIMES_TURN_VELOCITY;											//set time the turn position+velocity
	SetFrame(objectTypeID);
	_MonsterVelocityX = -PIRANHAPLANT_VELOCITY_X;
	_MonsterVelocityY = -PIRANHAPLANT_VELOCITY_Y;
	_PositionY = positionY;															//set position turn away
	_TimeStartStop = GetTickCount();
	_TimePerStop = TIMES_TURN_STOP;
	_PiranhaPlantStop = false;
	_PiranhaPlantDanger = false;
}

void PiranhaPlant::Update()
{
	DWORD timeNow = GetTickCount();
	if (timeNow - _TimeStartFrame >= _TimePerFrame)
	{
		_TimeStartFrame = timeNow;
		_FrameCurrent = SpriteManager::GetInstance()->NextFrame(_FrameCurrent, _FrameStart, _FrameEnd);
	}

	if (_Position.y >= _PositionY)//ở trên nguy hiểm
	{
		_Position.y = _PositionY;
		_MonsterVelocityY = -PIRANHAPLANT_VELOCITY_Y;
		_PiranhaPlantStop = true;
	}
	else
	{
		if (_Position.y <= _PositionY - 1.4 * 35)//_MonsterVelocityY<0: ở dưới
		{
			_Position.y = _PositionY - 1.4 * 35;
			_MonsterVelocityY = PIRANHAPLANT_VELOCITY_Y;
			_PiranhaPlantStop = true;
			_Size.x = 90;
			_Size.y = 58;
			_PiranhaPlantDanger = false;//hết nguy hiểm
			SetObjectType(eMonsterDead);//trạng thái chết tạm thời
		}
	}

	if (_PiranhaPlantStop)
	{
		if (timeNow - _TimeStartStop >= _TimePerStop)// dừng 1 khoảng tg sẽ hoạt động tiếp
		{
			_TimeStartStop = timeNow;
			_Velocity.y = _MonsterVelocityY;
			_Position.y += _Velocity.y;				//thoát khỏi nị trí đứng yên
			_PiranhaPlantStop = false;
			_Size = D3DXVECTOR2(PIRANHAPLANT_WIDTH, PIRANHAPLANT_HEIGHT);
			_PiranhaPlantDanger = true;
			SetObjectType(eMonster);//sống lại
		}
	}
	else
	{
		_Position.y += _Velocity.y;
	}
}

void PiranhaPlant::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _FrameCurrent);
}

void PiranhaPlant::Release()
{
}

void PiranhaPlant::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	#pragma region va chạm ngược
	case eGround:
		//DirectionsCollision(object, collisionDirection);
		break;
	case ePipe:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case ePipeHorizontal:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case eBrick:
	//	DirectionsCollision(object, collisionDirection);
		break;
	case eHardBrick:
	//	DirectionsCollision(object, collisionDirection);
		break;
	#pragma endregion
	#pragma region Monster
	case eMonster:
		switch (object->GetSpriteID())
		{
			case eKoopaTroopaDanger:
				MonsterDead(2);
				break;
		}
		break;
	#pragma endregion
	#pragma region Mario
	case eMario:
		if (object->GetTag() == eMarioIsSmall || object->GetTag() == eMarioIsBig)//bình thường
		{
			if (!_PiranhaPlantDanger)// k còn nguy hiểm--sẽ đứng yên
			{
				switch (collisionDirection)
				{
				case eTop://để các dòng giống nhau từng case mà k gom hoạt động chung ý nghĩa: Phát triển sau này, không gây lỗi khi quên thêm code dùng chung
					_PiranhaPlantStop = true;
					_TimeStartStop = GetTickCount();
					break;
				case eRight:
					_PiranhaPlantStop = true;
					_TimeStartStop = GetTickCount();
					break;
				case eLeft:
					_PiranhaPlantStop = true;
					_TimeStartStop = GetTickCount();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if (object->GetTag() == eMarioIsSmallInvincible || object->GetTag() == eMarioIsBigInvincible)//ngôi sao
			{
				if (_PiranhaPlantDanger)//ở trên có thể chết
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
					default:
						break;
					}
				}
			}
		}
		break;
	#pragma endregion
	#pragma region bullet
	case eBullet:
		if (_PiranhaPlantDanger)
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

void PiranhaPlant::SetFrame(int PiranhaPlantType)
{
	switch (PiranhaPlantType)
	{
	case 26:
		_FrameCurrent = 0;
		_FrameStart = 0;
		_FrameEnd= 1;
		break;
	case 27:
		_FrameCurrent = 2;
		_FrameStart = 2;
		_FrameEnd = 3;
		break;
	case 3:
		_FrameCurrent = 4;
		_FrameStart = 4;
		_FrameEnd = 5;
		break;
	case 4:
		_FrameCurrent = 6;
		_FrameStart = 6;
		_FrameEnd = 7;
		break;
	default:
		_FrameCurrent = 0;
		_FrameStart = 0;
		_FrameEnd = 1;
		break;
	};
}

void PiranhaPlant::MonsterDead(int MonsterTypeDead)
{
	SetObjectType(eMonsterDead);//k cần lắm do đã gán destroyed
	_Tag = eGameTag::eDestroyed;
	UpPoint(MONSTER_POINT);
}

bool PiranhaPlant::GetPiranhaPlantDanger()
{
	return _PiranhaPlantDanger;
}