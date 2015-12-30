#include "Coin.h"

#define COIN_FRAME_RATE 4	//coin fps
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
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eItems);
	_Size = D3DXVECTOR2(COIN_WIDTH, COIN_HEIGHT);
	_CountPerFrame = 1000 / COIN_FRAME_RATE;
	_FrameStart = GetTickCount();
	_Color = eColorID::eBrown;	//map editor only have brown coin atm
}

Coin::~Coin(void)
{
}

void Coin::Update()
{
	DWORD now = GetTickCount();
	if (now - _FrameStart >= _CountPerFrame) 
	{
		_FrameStart = now;
		_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 16, 19);
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
	case eBrick:
		_Tag = eGameTag::eDestroyed;
		GameStatistics::GetInstance()->ChangeScore(COIN_SCORE);		//inscrease score
		GameStatistics::GetInstance()->IncreaseCoin();		//inscrease score
		EffectManager::GetInstance()->ShowEffect(_Position, eEffectID::eObtainCoin, COIN_SCORE);
		break;
	default:
		break;
	}
}
