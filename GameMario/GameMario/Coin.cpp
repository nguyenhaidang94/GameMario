#include "Coin.h"

#define COIN_FRAME_RATE 8	//coin at top score swap 8 time per sec
#define COIN_SCORE 200		//200 score each coin
#define COIN_WIDTH 20
#define COIN_HEIGHT 28

Coin::Coin(void)
{
}

Coin::Coin(int x, int y)
{
	_Position = D3DXVECTOR2(x, y);
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eCoin);
	_Size = D3DXVECTOR2(COIN_WIDTH, COIN_HEIGHT);
	count_per_frame = 1000 / COIN_FRAME_RATE;
	frame_start = GetTickCount();
}

Coin::~Coin(void)
{
}

void Coin::Update()
{
	DWORD now = GetTickCount();
	if (now - frame_start >= count_per_frame) 
	{
		frame_start = now;
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 0, 3);
	}
}
void Coin::Render()
{
	_Sprite->RenderAtFrame(_Position.x, _Position.y, _CurrentFrame);
}

void Coin::Release()
{

}

void Coin::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	//case mario
	case eMario:
		_Tag = eGameTag::eDestroyed;
		GameStatistics::GetInstance()->ChangeScore(COIN_SCORE);		//inscrease score
		GameStatistics::GetInstance()->IncreaseCoin();		//inscrease score
		break;
	default:
		break;
	}
}
