#include "Mario.h"

#define JUMP_VELOCITY_BOOST 2
#define FALLDOWN_VELOCITY_DECREASE 0.1
#define DEFAULT_VELOCITY -1

Mario::Mario(void)
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
	_PipeTag = eGameTag::eEmpty;
	_IsOnVerticlePipe = false;
	//temporary Testing
	_Tag = eGameTag::eMarioIsSmall;
	SetVelocity(D3DXVECTOR2(0, DEFAULT_VELOCITY));
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
	SetPosition(D3DXVECTOR2(32,32));
	_IsCollide = false;
	SetSize(D3DXVECTOR2(32, 64));
}


Mario::~Mario(void)
{
}

void Mario::Initialize()
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
}

void Mario::HandlingInput()
{
	//testing
	_State = eMarioState::eIdle;
	if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
	{
		_State = eMarioState::eRunLeft;
	}
	if(Keyboard::GetInstance()->IsKeyDown(DIK_A))
	{
		_State = eMarioState::eRunRight;
	}
	if(_State != eMarioState::eJump)
	{
		if(Keyboard::GetInstance()->IsKeyDown(DIK_K))
		{
			_State = eMarioState::eJump;
			SoundManager::GetInstance()->GetSound(eSoundID::eJumpSmall)->Play();
			_Velocity.y += JUMP_VELOCITY_BOOST;
		}
	}
	if(_PipeTag != eGameTag::eEmpty && _IsOnVerticlePipe)
	{
		if(!Keyboard::GetInstance()->IsKeyDown(DIK_S))
		{
			_PipeTag = eGameTag::eEmpty;	//if mario dont press down, reset _PipeTag
		}
	}
}

Box Mario::GetMovementRangeBox()
{
	return GetBoundaryBox();
}

void Mario::Update()
{
	//Just testing
	HandlingInput();
	switch (_State)
	{
	case eIdle:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 7, 7);
		_Velocity.x = 0;
		break;
	case eRunLeft:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 8, 10);
		_Velocity.x = 2;
		break;
	case eRunRight:
		_CurrentFrame = SpriteManager::GetInstance()->PreviousFrame(_CurrentFrame, 3, 5);
		_Velocity.x = -2;
		break;
	case eJump:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 12);
		_Velocity.y += 2;
		break;
	default:
		break;
	}
	_Position.x += _Velocity.x;
	_Position.y += _Velocity.y;
	if(_Velocity.y == 0)
	{
		_Velocity.y = DEFAULT_VELOCITY;
	}
	_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
	_IsOnVerticlePipe = false;
}

void Mario::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Mario::Release()
{

}

void Mario::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object goes here
	switch (object->GetObjectTypeID())
	{
	case eGround:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = DEFAULT_VELOCITY;
			break;
		default:
			break;
		}
		break;
	case ePipe:
		_IsOnVerticlePipe = true;
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = DEFAULT_VELOCITY;
			if(object->GetTag() != eGameTag::eEmpty)
			{
				_PipeTag = object->GetTag();
			}
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2;
			break;
		default:
			break;
		}
		break;
	case ePipeHorizontal:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = DEFAULT_VELOCITY;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2;
			if(object->GetTag() != eGameTag::eEmpty)
			{
				_PipeTag = object->GetTag();
			}
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2;
			break;
		default:
			break;
		}
		break;
	case eBrick:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = 0;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2 - 1;
			_Velocity.x = 0;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2 +1;
			_Velocity.x = 0;
			break;
		case eTop:
			_Velocity.y = -_Velocity.y;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

eGameTag Mario::CheckSwitchWorld()
{
	return _PipeTag;
}

void Mario::ResetPipeTag()
{
	_PipeTag = eGameTag::eEmpty;
}