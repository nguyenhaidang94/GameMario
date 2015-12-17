#pragma once
#include "Effect.h"

class BrickBreakEffect : public Effect
{
	int _Type;		//determine blue or brown brick, 0 if brown, 1 is blue
	D3DXVECTOR2 _DebrisVelocity[4];	//store 4 position of debris
	D3DXVECTOR2 _DebrisPosition[4];	//store 4 position of debris
	int _CurrentSprite[4];		//to rotate brick sprite

	//manage frame rate
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	BrickBreakEffect(void);
	BrickBreakEffect(D3DXVECTOR2 position, int type);
	~BrickBreakEffect(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
};

