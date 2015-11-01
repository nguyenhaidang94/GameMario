#include "FloatingBar.h"

#define BAR_WIDTH 96
#define BAR_HEIGHT 16
#define DEFAULT_VELOCITY 2
#define MAX_VELOCITY 3
#define ACCELERARION_X 0.1
#define ACCELERARION_Y 0.035

FloatingBar::FloatingBar(void)
{
}

FloatingBar::FloatingBar(int x, int y, std::string tag)
{
	if(tag == "down")
	{
		_ObjectID = 0;
	}
	if(tag == "up")
	{
		_ObjectID = 1;
	}
	if(tag == "horizontal")
	{
		_ObjectID = 2;
	}
	if(tag == "vertical")
	{
		_ObjectID = 3;
	}
	_Position = D3DXVECTOR2(x, y);
	_Size = D3DXVECTOR2(BAR_WIDTH, BAR_HEIGHT);
	_Velocity = D3DXVECTOR2(0, 0);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBarSprite);
	_ObjectTypeID = eObjectTypeID::eFloatingBar;
	_Acceleration = 0;
	_Direction = true;
	//temporary case
	switch (_ObjectID)
	{
	case 0:	//go down
		_Velocity = D3DXVECTOR2(0, -DEFAULT_VELOCITY);
		break;
	case 1:	//go up
		_Velocity = D3DXVECTOR2(0, DEFAULT_VELOCITY);
		break;
	case 2:	//horizontal rotation
		_Acceleration = ACCELERARION_X;
		break;
	case 3:	//vertical rotation
		_Acceleration = ACCELERARION_Y;
		break;
	default:
		break;
	}
}


FloatingBar::~FloatingBar(void)
{
}

void FloatingBar::Update()
{
	Box cameraBound = Camera::GetInstance()->GetBoundaryBox();
	switch (_ObjectID)
	{
	//go down
	case 0:	
		_Position.y += _Velocity.y;
		if(_Position.y < cameraBound.fY - cameraBound.fHeight)	//below camera bound
		{
			_Position.y = cameraBound.fY;
		}
		break;

	//go up
	case 1:	
		_Position.y += _Velocity.y;
		if(_Position.y > cameraBound.fY)	//above camera bound
		{
			_Position.y = cameraBound.fY - cameraBound.fHeight;
		}
		break;

	//horizontal rotation
	case 2:	
		if(_Direction)
		{
			_Position.x += _Velocity.x;
		}
		else
		{
			_Position.x -= _Velocity.x;
		}
		_Velocity.x += _Acceleration;

		//if bar reach max velocity or velocity = 0, revert acceleration
		if(_Velocity.x >= MAX_VELOCITY || _Velocity.x <= 0)
		{
			_Acceleration = -_Acceleration;

			if( _Velocity.x <= 0)	//change direction if velociity reach 0
			{
				_Direction = !_Direction;
			}
		}
		break;

	//vertical rotation
	case 3:	
		if(_Direction)
		{
			_Position.y += _Velocity.y;
		}
		else
		{
			_Position.y -= _Velocity.y;
		}
		_Velocity.y += _Acceleration;

		//if bar reach max velocity or velocity = 0, revert acceleration
		if(_Velocity.y >= MAX_VELOCITY || _Velocity.y <= 0)
		{
			_Acceleration = -_Acceleration;

			if( _Velocity.y <= 0)	//change direction if velociity reach 0
			{
				_Direction = !_Direction;
			}
		}
		break;

	default:
		break;
	}
}

void FloatingBar::Render()
{
	_Sprite->RenderFirstFrame(_Position.x, _Position.y);
}

void FloatingBar::Release()
{

}

void FloatingBar::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{

}