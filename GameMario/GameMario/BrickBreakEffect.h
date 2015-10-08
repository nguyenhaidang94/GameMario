#pragma once
#include "Effect.h"
#include <vector>

class BrickBreakEffect : public Effect
{
private:
	int _Type;		//determine blue or brown brick, 0 if brown, 1 is blue
	D3DXVECTOR2 _DebrisVelocity[4];	//store 4 position of debris
	D3DXVECTOR2 _DebrisPosition[4];	//store 4 position of debris
public:
	BrickBreakEffect(void);
	BrickBreakEffect(D3DXVECTOR2 position, int type);
	~BrickBreakEffect(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
};

