#include "DynamicGameObject.h"


DynamicGameObject::DynamicGameObject(void)
{
}


DynamicGameObject::~DynamicGameObject(void)
{
}

void DynamicGameObject::SetVelocity(D3DXVECTOR2 velocity)
{
	_Velocity = velocity;
}