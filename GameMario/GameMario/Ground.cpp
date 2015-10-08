#include "Ground.h"
#define GROUND_HEIGHT 16		//because of map editor...

Ground::Ground(void)
{
}

Ground::Ground(int x, int y, int width)
{
	SetPosition(D3DXVECTOR2(x, y));
	_Size.x = width;
	_Size.y = GROUND_HEIGHT;
	_ObjectTypeID = eObjectTypeID::eGround;
}


Ground::~Ground(void)
{
}

void Ground::Update()
{

}

void Ground::Render()
{
	
}

void Ground::Release()
{

}

void Ground::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	default:
		break;
	}
}