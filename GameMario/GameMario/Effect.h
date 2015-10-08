#pragma once
#include "SpriteManager.h"
#include <d3dx9.h>
class Effect
{
protected:
	bool _IsAlive;
	Sprite *_Sprite;
public:
	Effect(void);
	~Effect(void);
	//Check if effect is still alive
	bool CheckAlive();
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

