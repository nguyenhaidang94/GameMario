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

Box DynamicGameObject::GetBoundaryBox()
{
	return Box(_Position.x - _Size.x/2, _Position.y + _Size.y/2, _Size.x, _Size.y, _Velocity.x, _Velocity.y);
}