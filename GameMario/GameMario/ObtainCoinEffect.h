#pragma once
#include "effect.h"
#include "EffectManager.h"
#include "SoundManager.h"

class ObtainCoinEffect :
	public Effect
{
private:
	D3DXVECTOR2 _CoinPosition;
	D3DXVECTOR2 _CoinVelocity;
	int _CurrentFrame;
	int _BeginingY;		//Begining positon in y axis
	int _ScoreEarn;
	//manage frame rate
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	ObtainCoinEffect(void);
	//position is position of the block gererate coin
	ObtainCoinEffect(D3DXVECTOR2 position, int scoreEarn);
	~ObtainCoinEffect(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
};

