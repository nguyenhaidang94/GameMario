#include "Camera.h"

#define AUTO_MOVE_SPEED 4;

Camera *Camera::Instance = NULL;

Camera::Camera(void)
{
	_ViewPortX = 0;
	_ViewPortY = SCREEN_HEIGHT;
	_IsAllowBack = false;
	_IsPause = false;
	_IsAutoMove = false;
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

void Camera::SetWorldSize(D3DXVECTOR2 worldSize)
{
	_WorldWidth = worldSize.x;
	_WorldHeight = worldSize.y;
}

void Camera::Update(D3DXVECTOR2 characterPosition)
{
	if(!_IsPause)	//if camera not pause
	{
		//Update X axis
		//If character not go back and camera allow go back
		if(!_IsAllowBack)
		{
			if(characterPosition.x >= _OldX)
			{
				_OldX = characterPosition.x;
				if(!_IsAutoMove)
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
						
							_ViewPortX = LONG(characterPosition.x) - SCREEN_WIDTH / 2;
						}
					}
				}
				else
				{
					_ViewPortX += AUTO_MOVE_SPEED;
					if((_ViewPortX + SCREEN_WIDTH) >= _WorldWidth) 
					{
						_IsAutoMove = false;
						_ViewPortX = _WorldWidth - SCREEN_WIDTH;
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
					_ViewPortX = LONG(characterPosition.x) - SCREEN_WIDTH / 2;
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
}

D3DXVECTOR2 Camera::GetViewPort() const
{
	return D3DXVECTOR2(float(_ViewPortX), float(_ViewPortY));
}

D3DXVECTOR2 Camera::GetWorldSize() const
{
	return D3DXVECTOR2(float(_WorldWidth),float(_WorldHeight));
}

Box Camera::GetBoundaryBox() const
{
	return Box(_ViewPortX, _ViewPortY, SCREEN_WIDTH, SCREEN_HEIGHT);
}

Box Camera::GetActiveSite() const
{
	return Box(_ViewPortX - BUFFER_FOR_SCREEN, _ViewPortY + BUFFER_FOR_SCREEN, SCREEN_WIDTH + 2*BUFFER_FOR_SCREEN, SCREEN_HEIGHT + 2*BUFFER_FOR_SCREEN);
}

void Camera::PauseCamera(bool isPause)
{
	_IsPause = isPause;
}

void Camera::AutoMoveCamera(bool isAutoMove)
{
	_IsAutoMove = isAutoMove;
}

void Camera::Reset()
{
	_ViewPortX = 0;
	_ViewPortY = SCREEN_HEIGHT;
	_OldX = 0;
	_OldY = 0;
}