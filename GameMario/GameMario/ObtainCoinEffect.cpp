#include "ObtainCoinEffect.h"

#define DEFAULT_VELOCITY_Y 10
#define FALLDOWN_VELOCITY_DECREASE 0.5
#define COIN_FRAME_RATE 8	//coin spin at 8 time per sec

ObtainCoinEffect::ObtainCoinEffect(void)
{
}

ObtainCoinEffect::ObtainCoinEffect(D3DXVECTOR2 position, int scoreEarn)
{
	_CoinPosition = position;
	_CoinVelocity = D3DXVECTOR2(0, DEFAULT_VELOCITY_Y);
	_BeginingY = position.y;
	_CurrentFrame = 0;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eCoin);
	_ScoreEarn = scoreEarn;
	_IsAlive = true;
	_CountPerFrame = 1000 / COIN_FRAME_RATE;
	_FrameStart = GetTickCount();
}

ObtainCoinEffect::~ObtainCoinEffect(void)
{
}

void ObtainCoinEffect::Update()
{
	if(_IsAlive)
	{
		_CoinPosition.x += _CoinVelocity.x;
		_CoinPosition.y += _CoinVelocity.y;
		_CoinVelocity.y -= FALLDOWN_VELOCITY_DECREASE;
		//check one of high debris, if it fall out of screen, kill effect and show score 
		if(_CoinPosition.y < _BeginingY + 48 && _CoinVelocity.y < 0)	//belown begining position plus 48 and when coin goes down
		{
			_IsAlive = false;
			EffectManager::GetInstance()->ShowEffect(_CoinPosition, eEffectID::eFloatingText, _ScoreEarn);
		}
		//control coin rate
		DWORD now = GetTickCount();
		if (now - _FrameStart >= _CountPerFrame) 
		{
			_FrameStart = now;
			_CurrentFrame = SpriteManager::GetInstance()->NextFrame(_CurrentFrame, 4,8);
		}
	}
}

void ObtainCoinEffect::Render()
{
	if(_IsAlive)
	{
		_Sprite->RenderAtFrame(_CoinPosition.x, _CoinPosition.y, _CurrentFrame);
	}
}

void ObtainCoinEffect::Release()
{
	
}