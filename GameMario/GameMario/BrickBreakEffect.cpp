#include "BrickBreakEffect.h"
#define DEFAULT_VELOCITY_LOW_X 2
#define DEFAULT_VELOCITY_HIGH_X 2.25
#define DEFAULT_VELOCITY_HIGH_Y 10
#define DEFAULT_VELOCITY_LOW_Y 6
#define FALLDOWN_VELOCITY_DECREASE 0.5
#define EFFECT_FRAME_RATE 8	//swap 8 time per sec

BrickBreakEffect::BrickBreakEffect(void)
{
}

BrickBreakEffect::BrickBreakEffect(D3DXVECTOR2 position, int type)
{
	//0 is top-left, 1 is top-right, 2 is bottom-left, 3 is bottom-right
	_IsAlive = true;
	for(int i = 0; i < 4; i++)
	{
		_DebrisPosition[i] = position;
	}
	_DebrisVelocity[0] = D3DXVECTOR2(- DEFAULT_VELOCITY_HIGH_X, DEFAULT_VELOCITY_HIGH_Y);
	_DebrisVelocity[1] = D3DXVECTOR2(- DEFAULT_VELOCITY_LOW_X, DEFAULT_VELOCITY_LOW_Y);
	_DebrisVelocity[2] = D3DXVECTOR2(DEFAULT_VELOCITY_HIGH_X, DEFAULT_VELOCITY_HIGH_Y);
	_DebrisVelocity[3] = D3DXVECTOR2(DEFAULT_VELOCITY_LOW_X, DEFAULT_VELOCITY_LOW_Y);
	_Type = type;
	_Sprite = SpriteManager::GetInstance()->GetSprite(eSpriteID::eBrickDebris);
	for(int i = 0; i < 4; i++)
	{
		_CurrentSprite[i] = i + _Type*4;	//brown brick from 0->3, blue from 4->7
	}
	_CountPerFrame = 1000 / EFFECT_FRAME_RATE;
	_FrameStart = GetTickCount();
}

BrickBreakEffect::~BrickBreakEffect(void)
{
	BrickBreakEffect::Release();
}


void BrickBreakEffect::Update()
{
	if(_IsAlive)
	{
		for(int i = 0; i < 4; i++)
		{
			_DebrisPosition[i].x += _DebrisVelocity[i].x;
			_DebrisPosition[i].y += _DebrisVelocity[i].y;
			_DebrisVelocity[i].y -= FALLDOWN_VELOCITY_DECREASE;
		}
		//check one of high debris, if it fall out of screen, kill effect 
		Box cameraBox = Camera::GetInstance()->GetBoundaryBox();
		if(_DebrisPosition[0].y < cameraBox.fY - cameraBox.fHeight)
		{
			_IsAlive = false;
		}
	}
}

void BrickBreakEffect::Render()
{
	if(_IsAlive)
	{
		for(int i = 0; i < 4; i++)
		{
			_Sprite->RenderAtFrame(_DebrisPosition[i].x, _DebrisPosition[i].y, _CurrentSprite[i]);
		}

		//manage frame rate
		DWORD now = GetTickCount();
		if (now - _FrameStart >= _CountPerFrame) 
		{
			_FrameStart = now;
			for(int i = 0; i < 4; i++)
			{
				_CurrentSprite[i] = SpriteManager::NextFrame(_CurrentSprite[i], _Type*4, _Type*4 + 3);
			}
		}
	}
}

void BrickBreakEffect::Release()
{
	
}