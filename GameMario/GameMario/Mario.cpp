#include "Mario.h"


Mario::Mario(void)
{
	_State = eMarioState::eIdle;
	SetObjectType(eMario);
	//Testing
	SetVelocity(D3DXVECTOR2(2,2));
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigMario);
	SetPosition(D3DXVECTOR2(0,64));
	
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
	if(Keyboard::GetInstance()->IsKeyDown(DIK_D))
	{
		_State = eMarioState::eRun;
	}
	if(Keyboard::GetInstance()->IsKeyDown(DIK_K))
	{
		_State = eMarioState::eJump;
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
		break;
	case eRun:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 8, 10);
		_Position.x += _Velocity.x;
		break;
	case eJump:
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 12, 12);
		_Position.y += _Velocity.y;
		break;
	default:
		break;
	}
}

void Mario::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Mario::Release()
{

}

Box Mario::GetBox()
{
	return Box();
}