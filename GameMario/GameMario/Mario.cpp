#include "Mario.h"

#define JUMP_VELOCITY_BOOST 2
#define FALLDOWN_VELOCITY_DECREASE 0.1
#define DEFAULT_VELOCITY -1

Mario::Mario(void)
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
	//temporary Testing
	_Tag = eGameTag::eMarioIsBig;
	SetVelocity(D3DXVECTOR2(0, DEFAULT_VELOCITY));
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
	SetPosition(D3DXVECTOR2(32,32));
	_IsCollide = false;
	SetSize(D3DXVECTOR2(40, 64));
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
	_Velocity.y -= FALLDOWN_VELOCITY_DECREASE;
	_Position.x += _Velocity.x;
	_Position.y += _Velocity.y;
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
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = DEFAULT_VELOCITY;
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
	case eBrick:
		switch (collisionDirection)
		{
		case eBottom:
			_Position.y = object->GetBoundaryBox().fY + _Size.y/2;
			_Velocity.y = DEFAULT_VELOCITY;
			break;
		case eRight:
			_Position.x = object->GetBoundaryBox().fX - _Size.x/2;
			break;
		case eLeft:
			_Position.x = object->GetBoundaryBox().fX + object->GetBoundaryBox().fWidth + _Size.x/2;
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