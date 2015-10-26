#include "FireFlower.h"

#define FLOWER_SPAWM_VELOCITY_Y 0.5
#define FLOWER_WIDTH 32
#define FLOWER_HEIGHT 32
#define FRAME_RATE 8
#define FLOWER_SCORE 1000

FireFlower::FireFlower(void)
{
}

FireFlower::FireFlower(eColorID blockColor, int x, int y)
{
	_Position = D3DXVECTOR2(x, y);
	_BeginningPositionY = y;
	_Size = D3DXVECTOR2(FLOWER_WIDTH, FLOWER_HEIGHT);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eItems);
	_CurrentFrame = 0;
	_IsSpawnDone = false;
	_ObjectTypeID = eObjectTypeID::eFireFlower;
	_Color = blockColor;
	_Tag = eGameTag::eIgnoreCollision;	//ignore collision when on spawn animation

	_CounPerFrame = 1000 / FRAME_RATE;
	_FrameStart = GetTickCount();
}


FireFlower::~FireFlower(void)
{
}

void FireFlower::Update()
{
	if(!_IsSpawnDone)
	{
		_Position.y += FLOWER_SPAWM_VELOCITY_Y;
		if(_Position.y > _BeginningPositionY + TITLE_SIZE)
		{
			_Position.y = _BeginningPositionY + TITLE_SIZE;
			_IsSpawnDone = true;
			_Size = D3DXVECTOR2(FLOWER_WIDTH, FLOWER_HEIGHT);
		}
	}

	//control frame rate
	DWORD now = GetTickCount();
	if (now - _FrameStart >= _CounPerFrame) 
	{
		_FrameStart = now;
		if(_Color == eColorID::eBrown)
		{
			_CurrentFrame = SpriteManager::NextFrame(_CurrentFrame, 0, 3);
		}
		else
		{
			if(_Color == eColorID::eBlue)
			{
				_CurrentFrame = SpriteManager::NextFrame(_CurrentFrame, 4, 7);
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

void FireFlower::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void FireFlower::Release()
{

}

void FireFlower::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	//case mario
	case eMario:
		_Tag = eGameTag::eDestroyed;
		GameStatistics::GetInstance()->ChangeScore(FLOWER_SCORE);		//inscrease score
		EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eFloatingText, FLOWER_SCORE);
		break;
	default:
		break;
	}
}