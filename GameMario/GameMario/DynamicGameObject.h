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
	//Overide get colision box of object
	virtual	Box GetBoundaryBox();
	//Set velocity for object
	void SetVelocity(D3DXVECTOR2 velocity);
	D3DXVECTOR2 GetVelocity(){ return _Velocity; }
};

