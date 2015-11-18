#pragma once
#include "SpriteManager.h"

class Effect
{
protected:
	bool _IsAlive;
	Sprite *_Sprite;
public:
	Effect(void);
	virtual ~Effect(void);
	//Check if effect is still alive
	bool CheckAlive() const;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};

