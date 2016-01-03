#include "Axe.h"

#define AXE_FRAME_RATE 4	//coin at top score swap 8 time per sec

Axe::Axe(void)
{
}

Axe::Axe(int x, int y, int width, int height)
{
	SetPosition(D3DXVECTOR2(x, y));
	_Size.x = width - 12;
	_Size.y = height + 32;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eAxe);
	_IsPauseAlready = false;
	_CurrentFrame = 0;

	_CountPerFrame = 1000 / AXE_FRAME_RATE;
	_FrameStart = GetTickCount();
	SetObjectType(eAxeBoss);
}


Axe::~Axe(void)
{
}

void Axe::Update()
{
	DWORD now = GetTickCount();
	if (now - _FrameStart >= _CountPerFrame) 
	{
		_FrameStart = now;
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 2);
	}

	if((Camera::GetInstance()->GetBoundaryBox().fX +  Camera::GetInstance()->GetBoundaryBox().fWidth -48 > _Position.x) && !_IsPauseAlready)
	{
		Camera::GetInstance()->PauseCamera(true);
		_IsPauseAlready = true;
	}
}

void Axe::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Axe::Release()
{

}

void Axe::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	case eMario:
		if(GameStatistics::GetInstance()->IsBowserDead())	//if bowser already dead, unlock camera
		{
			Camera::GetInstance()->PauseCamera(false);	//stop pause camera
			Camera::GetInstance()->AutoMoveCamera(true);//auto move camera
		}
		GameStatistics::GetInstance()->MarioReachAxe();
		GameStatistics::GetInstance()->PauseTime(true);
		_Tag = eDestroyed;
		break;
	default:
		break;
	}
}