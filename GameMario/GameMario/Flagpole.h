#pragma once
#include "gameobject.h"
#include "GameStatistics.h"
#include "EffectManager.h"
class Flagpole :
	public GameObject
{
private:
	Sprite *_FlagSprite;
	bool _IsHitted;
	bool _IsFlagHittedGround;
	D3DXVECTOR2 _FlagPosition;
public:
	Flagpole(void);
	Flagpole(int x, int y);
	~Flagpole(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};