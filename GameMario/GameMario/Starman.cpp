#include "Starman.h"

#define DEFAULT_VELOCITY_X 1.5
#define STARMAN_SPAWM_VELOCITY_Y 0.5
#define STARMAN_WIDTH 32
#define STARMAN_HEIGHT 32
#define STARMAN_SCORE 1000
#define JUMP_VELOCITY_BOOST 5
#define FALLDOWN_VELOCITY_DECREASE 0.15
#define STARMAN_FRAME_RATE 4

Starman::Starman(void)
{
}

Starman::Starman(eColorID blockColor, int x, int y)
{
	_Position = D3DXVECTOR2(x, y);
	_Velocity = D3DXVECTOR2(DEFAULT_VELOCITY_X, 0);
	_Size = D3DXVECTOR2(STARMAN_WIDTH, STARMAN_HEIGHT);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eItems);
	_IsSpawnDone = false;
	_BeginningPositionY = y;
	_IsGoingRight = true;
	_Tag = eGameTag::eIgnoreCollision;	//ignore collision when on spawn animation
	_ObjectTypeID = eObjectTypeID::eStarMan;
	_Color = blockColor;
	_IsJump = false;
	_RenderPriority = 0.4;	//render behide brick when spawm

	_CounPerFrame = 1000 / STARMAN_FRAME_RATE;
	_FrameStart = GetTickCount();

}

Starman::~Starman(void)
{
}


void Starman::Update()
{
	if(_IsSpawnDone)
	{
		_Position.x += _Velocity.x;
		_Position.y += _Velocity.y;

		//destroy mushroom if it goes off screen
		Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
		if(_Position.x < cameraBox.fX - TITLE_SIZE|| _Position.x > cameraBox.fX + cameraBox.fWidth + TITLE_SIZE||
			_Position.y > cameraBox.fY + TITLE_SIZE|| _Position.y < cameraBox.fY - cameraBox.fHeight - TITLE_SIZE)
		{
			_Tag = eGameTag::eDestroyed;
		}

		//setup velocity again
		if(_IsJump)
		{
			_Velocity.y = JUMP_VELOCITY_BOOST;
			_IsJump = false;
		}
		else
		{
			_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
		}
		if(_IsGoingRight)
		{
			_Velocity.x = DEFAULT_VELOCITY_X;
		}
		else
		{
			_Velocity.x = -DEFAULT_VELOCITY_X;
		}
	}
	else
	{
		_Position.y += STARMAN_SPAWM_VELOCITY_Y;
		if(_Position.y > _BeginningPositionY + TITLE_SIZE)
		{
			_Position.y = _BeginningPositionY + TITLE_SIZE;
			_IsSpawnDone = true;
			_Tag = eGameTag::eEmpty;	//stop ignore collison
			_IsJump = true;
			_RenderPriority = 0.6;
		}
	}

	//control frame rate
	DWORD now = GetTickCount();
	if (now - _FrameStart >= _CounPerFrame) 
	{
		_FrameStart = now;
		if(_Color == eColorID::eBrown)
		{
			_CurrentFrame = SpriteManager::NextFrame(_CurrentFrame, 8, 11);
		}
		else
		{
			if(_Color == eColorID::eBlue)
			{
				_CurrentFrame = SpriteManager::NextFrame(_CurrentFrame, 12, 15);
			}
		}
	}

	//destroy flower if it goes off screen
	Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
	if(_Position.x < cameraBox.fX - TITLE_SIZE|| _Position.x > cameraBox.fX + cameraBox.fWidth + TITLE_SIZE||
			_Position.y > cameraBox.fY + TITLE_SIZE|| _Position.y < cameraBox.fY - cameraBox.fHeight - TITLE_SIZE)
	{
		_Tag = eGameTag::eDestroyed;
	}
}

void Starman::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame, _RenderPriority);
}

void Starman::Release()
{
}

void Starman::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	Box objectBox = object->GetBoundaryBox();
	switch (object->GetObjectTypeID())
	{
	case eHardBrick:
	case eGround:
	case ePipe:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = objectBox.fY + _Size.y/2 + 1;
			_Velocity.y = 0;
			_IsJump = true;
			break;
		case eLeft:
			_Position.x = objectBox.fX + objectBox.fWidth + _Size.y/2 + 1;
			_Velocity.x = 0;
			_IsGoingRight = true;
			break;
		case eRight:
			_Position.x = objectBox.fX - _Size.y/2 - 1;
			_Velocity.x = 0;
			_IsGoingRight = false;
			break;
		default:
			break;
		}
		break;

	//case brick, only collide on bottom(?)
	case eBrick:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = objectBox.fY + _Size.y/2 + 1;
			_Velocity.y = 0;
			_IsJump = true;
		}
		break;

	//case mario
	case eMario:
		_Tag = eGameTag::eDestroyed;
		GameStatistics::GetInstance()->ChangeScore(STARMAN_SCORE);		//inscrease score
		EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, STARMAN_SCORE);
		break;
	default:
		break;
	}
}
