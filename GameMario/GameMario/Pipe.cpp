#include "Pipe.h"
#define PIPE_WIDTH 64
#define HORIZONTAL_PIPE_WIDTH 64
#define SMALL_PIPE_HEIGHT 64
#define MEDIUM_PIPE_HEIGHT 96
#define BIG_PIPE_HEIGHT 128

Pipe::Pipe(void)
{
}

Pipe::Pipe(int objectID, int x, int y , std::string destination)
{
	_Position.x = x;
	_Position.y = y;
	_Tag = Unility::GetGameTag(destination);

	//set default value
	_ObjectTypeID = eObjectTypeID::ePipe;
	_Size.x = PIPE_WIDTH;		
	_Size.y = SMALL_PIPE_HEIGHT;
	//setup or each type of pipe
	switch (objectID)
	{
	case 9:	//small
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eSmallPipe);
		_Size.y = SMALL_PIPE_HEIGHT;
		break;
	case 10:	//medium
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eMediumPipe);
		_Size.y = MEDIUM_PIPE_HEIGHT;
		break;
	case 11:	//big
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBigPipe);
		_Size.y = BIG_PIPE_HEIGHT;
		break;
	case 12:	//horizontal
		_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eHorizontalPipe);
		_Size.x = HORIZONTAL_PIPE_WIDTH;
		break;
	default:
		break;
	}
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