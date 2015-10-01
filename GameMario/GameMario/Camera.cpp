#include "Camera.h"

Camera *Camera::Instance = NULL;

Camera::Camera(void)
{
	_ViewPortX = 0;
	_ViewPortY = SCREEN_HEIGHT;
	_IsAllowBack = true;
}

Camera::~Camera(void)
{	
}

Camera *Camera::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new Camera();
	}
	return Instance;
}

void Camera::SetWorldSize(int worldWidth, int worldHeight)
{
	_WorldHeight = worldHeight;
	_WorldWidth = worldWidth;
}

void Camera::Update(D3DXVECTOR2 characterPosition)
{
	//Update X axis
	//If character not go back and camera allow go back
	if(!_IsAllowBack)
	{
		if(characterPosition.x > _OldX)
		{
			_OldX = characterPosition.x;
			//If character in begin of the world
			if(characterPosition.x - SCREEN_WIDTH/2 < 0)
			{
				_ViewPortX = 0;
			}
			else
			{
				//If character in end of world
				if (characterPosition.x + SCREEN_WIDTH / 2 > _WorldWidth)
				{
					_ViewPortX = _WorldWidth - SCREEN_WIDTH;
				}
				//Normal case
				else
				{
					_ViewPortX = (LONG)characterPosition.x - SCREEN_WIDTH / 2;
				}
			}
		}
	}
	else
	{
		//If character in begin of the world
		if(characterPosition.x - SCREEN_WIDTH/2 < 0)
		{
			_ViewPortX = 0;
		}
		else
		{
			//If character in end of world
			if (characterPosition.x + SCREEN_WIDTH / 2 > _WorldWidth)
			{
				_ViewPortX = _WorldWidth - SCREEN_WIDTH;
			}
			//Normal case
			else
			{
				_ViewPortX = (LONG)characterPosition.x - SCREEN_WIDTH / 2;
			}
		}
	}
	////Update Y axis
	////If character in begin of the world
	//if(characterPosition.y - SCREEN_HEIGHT/2 < 0)
	//{
	//	ViewPortY = 0;
	//}
	//else
	//{
	//	//If character in end of world
	//	if(characterPosition.y + SCREEN_WIDTH/2 < WorldWidth)
	//	{
	//		ViewPortX = WorldWidth - SCREEN_WIDTH/2;
	//	}
	//	//Normal case
	//	else
	//	{
	//		ViewPortX = characterPosition.y - SCREEN_WIDTH/2;
	//	}
	//}
}

D3DXVECTOR2 Camera::GetViewPort()
{
	return D3DXVECTOR2((float)_ViewPortX, (float)_ViewPortY);
}

D3DXVECTOR2 Camera::GetWorldSize()
{
	return D3DXVECTOR2((float)_WorldWidth,(float) _WorldHeight);
}

Box Camera::GetBoundaryBox()
{
	return Box(_ViewPortX, _ViewPortY, SCREEN_WIDTH, SCREEN_HEIGHT);
}