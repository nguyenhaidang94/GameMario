#pragma once
#include <vector>
#include "Effect.h"
#include "BrickBreakEffect.h"
#include "ObtainCoinEffect.h"
#include "FloatingTextEffect.h"

class EffectManager
{
private:
	std::vector<Effect*> _ListEffect;
	static EffectManager *_Instance;	
public:
	EffectManager(void);
	~EffectManager(void);
	//Get instance of sprite manager
	static EffectManager *GetInstance();

	//Show a effect with effectID at position, tag for more option(for coin effect: tag is score, for breakbrick: 0 is brown and 1 is blue, for floating text: -2 is tag for 1up text else is score)
	void ShowEffect(D3DXVECTOR2 position ,eEffectID effectID, int tag = -1);
	//Update all current effect
	void Update();
	//Render all current effect
	void Render();
	//Release all current effect
	void Release();
};

