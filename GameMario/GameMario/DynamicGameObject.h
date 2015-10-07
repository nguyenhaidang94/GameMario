#pragma once
#include "gameobject.h"
class DynamicGameObject :
	public GameObject
{
protected:
	D3DXVECTOR2 _Velocity;
public:
	DynamicGameObject(void);
	~DynamicGameObject(void);
	//Get velocity
	D3DXVECTOR2 GetVelocity(){ return _Velocity; }
	//Set velocity for object
	void SetVelocity(D3DXVECTOR2 velocity);
};

