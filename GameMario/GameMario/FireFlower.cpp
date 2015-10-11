#include "FireFlower.h"

#define FLOWER_SPAWM_VELOCITY_Y 0.5
#define FLOWER_WIDTH 32
#define FLOWER_HEIGHT 32
#define FRAME_RATE 8
#define FLOWER_SCORE 1000

FireFlower::FireFlower(void)
{
}

FireFlower::FireFlower(eBlockTypeID blockType, int x, int y)
{
	_Position = D3DXVECTOR2(x, y);
	_BeginningPositionY = y;
	_Size = D3DXVECTOR2(0, 0);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eItems);
	_CurrentFrame = 0;
	_IsSpawnDone = false;
	_ObjectTypeID = eObjectTypeID::eFireFlower;
	_Type = blockType;

	count_per_frame = 1000 / FRAME_RATE;
	frame_start = GetTickCount();
}


FireFlower::~FireFlower(void)
{
}

void FireFlower::Update()
{
	if(!_IsSpawnDone)
	{
		_Position.y += FLOWER_SPAWM_VELOCITY_Y;
		if(_Position.y > _BeginningPositionY + 32)
		{
			_IsSpawnDone = true;
			_Size = D3DXVECTOR2(FLOWER_WIDTH, FLOWER_HEIGHT);
		}
	}

	//control frame rate
	DWORD now = GetTickCount();
	if (now - frame_start >= count_per_frame) 
	{
		frame_start = now;
		if(_Type == eBlockTypeID::eBrownBlock)
		{
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 3);
		}
		else
		{
			if(_Type == eBlockTypeID::eBlueBlock)
			{
				_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 4, 7);
			}
		}
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
		EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eObtainScore, FLOWER_SCORE);
		break;
	default:
		break;
	}
}