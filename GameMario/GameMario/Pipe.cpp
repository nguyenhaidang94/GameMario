#include "Pipe.h"

Pipe::Pipe(void)
{
}

Pipe::Pipe(int x, int y, int width, int height, eSpriteID spriteID, std::string destination)
{
	_Position.x = x;
	_Position.y = y;
	_Size.x = width;
	_Size.y = height;
	_Tag = destination;
	_ObjectTypeID = eObjectTypeID::ePipe;
	_Sprite = SpriteManager::GetInstance()->GetSprite(spriteID);
}


Pipe::~Pipe(void)
{
}

void Pipe::Update()
{

}

void Pipe::Render()
{
	_Sprite->RenderFirstFrame(_Position.x, _Position.y);
}

void Pipe::Release()
{

}

void Pipe::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{
	//Handling collision by object type here
	switch (object->GetObjectTypeID())
	{
	default:
		break;
	}
}