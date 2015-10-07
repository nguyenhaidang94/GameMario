#include "Mario.h"


Mario::Mario(void)
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
	//Testing
	SetVelocity(D3DXVECTOR2(0,-2));
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
	SetPosition(D3DXVECTOR2(32,32));
	_IsCollide = false;
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
		_State = eMarioState::eRun;
	}
	if(Keyboard::GetInstance()->IsKeyDown(DIK_K))
	{
		_State = eMarioState::eJump;
		SoundManager::GetInstance()->GetSound(eSoundID::eJumpSmall)->Play();
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
	case eRun:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 8, 10);
		_Velocity.x = 2;
		break;
	case eJump:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 12);
		_Velocity.y += 2;
		break;
	default:
		break;
	}
	_Velocity.y -= 0.05;
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

Box Mario::GetBoundaryBox()
{
	//temporary
	return Box(_Position.x - 29, _Position.y + 32, 58, 64, _Velocity.x, _Velocity.y);
}

void Mario::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object goes here
	switch (object->GetObjectTypeID())
	{
	case eGround:
		switch (collisionDirection)
		{
		case eTop:
			_Position.y = object->GetBoundaryBox().fY + 30;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}