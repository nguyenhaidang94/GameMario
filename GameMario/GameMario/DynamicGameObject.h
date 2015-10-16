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
	Box GetBoundaryBox();
	virtual Box GetMovementRangeBox() = 0;
	//Set velocity for object
	void SetVelocity(D3DXVECTOR2 velocity);
};

