#include "FloatingBar.h"

#define DEFAULT_VELOCITY 2
#define MAX_VELOCITY 3
#define ACCELERARION_X 0.1
#define ACCELERARION_Y 0.035

FloatingBar::FloatingBar(void)
{
}

FloatingBar::FloatingBar(int x, int y, int width, int height,std::string tag)
{
	_Velocity = D3DXVECTOR2(0, 0);
	_Acceleration = 0;
	_Position = D3DXVECTOR2(x, y);
	_LeftPosition = D3DXVECTOR2(x - width/2 + TITLE_SIZE/2, y);
	_Size = D3DXVECTOR2(width, height);
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBarSprite);
	_ObjectTypeID = eObjectTypeID::eFloatingBar;
	_Direction = true;
	_NumberOfBlock = width/TITLE_SIZE;

	//go down
	if(tag == "down")			
	{
		_ObjectID = 0;
		_Velocity = D3DXVECTOR2(0, -DEFAULT_VELOCITY);
	}
	//go up
	if(tag == "up")				
	{
		_ObjectID = 1;
		_Velocity = D3DXVECTOR2(0, DEFAULT_VELOCITY);
	}
	//horizontal rotation
	if(tag == "horizontal")		
	{
		_ObjectID = 2;
		_Acceleration = ACCELERARION_X;
	}
	//vertical rotation
	if(tag == "vertical")		
	{
		_ObjectID = 3;
		_Acceleration = ACCELERARION_Y;
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
		//check if in some edge case to update direction and acceleration
		if(_Direction)	//go right
		{
			if(_Velocity.x >= MAX_VELOCITY)	//if bar reach max velocity or velocity = 0, revert acceleration
			{
				_Acceleration = -_Acceleration;
			}
			else
			{
				if( _Velocity.x <= 0)	//change direction if velociity reach 0
				{
					_Direction = !_Direction;
				}
			}
		}
		else
		{
			if(_Velocity.x <= -MAX_VELOCITY)	//if bar reach max velocity or velocity = 0, revert acceleration
			{
				_Acceleration = -_Acceleration;
			}
			else
			{
				if( _Velocity.x >= 0)	//change direction if velociity reach 0
				{
					_Direction = !_Direction;
				}
			}
		}

		//then update velociry and position
		_Velocity.x += _Acceleration;
		_Position.x += _Velocity.x;	//update position
		break;
	//vertical rotation
	case 3:	
				//check if in some edge case to update direction and acceleration
		if(_Direction)	//go right
		{
			if(_Velocity.y >= MAX_VELOCITY)	//if bar reach max velocity or velocity = 0, revert acceleration
			{
				_Acceleration = -_Acceleration;
			}
			else
			{
				if( _Velocity.y <= 0)	//change direction if velociity reach 0
				{
					_Direction = !_Direction;
				}
			}
		}
		else
		{
			if(_Velocity.y <= -MAX_VELOCITY)	//if bar reach max velocity or velocity = 0, revert acceleration
			{
				_Acceleration = -_Acceleration;
			}
			else
			{
				if( _Velocity.y >= 0)	//change direction if velociity reach 0
				{
					_Direction = !_Direction;
				}
			}
		}

		//then update velociry and position
		_Velocity.y += _Acceleration;
		_Position.y += _Velocity.y;	//update position
		break;

	default:
		break;
	}

	//update left position for drawing
	_LeftPosition = D3DXVECTOR2(_Position.x - _Size.x/2 + TITLE_SIZE/2, _Position.y);
}

void FloatingBar::Render()
{
	for(int i = 0; i < _NumberOfBlock; i++)
	{
		_Sprite->RenderFirstFrame(_LeftPosition.x + i*TITLE_SIZE, _Position.y);
	}
}

void FloatingBar::Release()
{

}

void FloatingBar::OnCollision(GameObject *object, eCollisionDirection collisionDirection)
{

}