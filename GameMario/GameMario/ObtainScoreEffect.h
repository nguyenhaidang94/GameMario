#pragma once
#include "effect.h"
#include "TextManager.h"
#include "Camera.h"
class ObtainScoreEffect :
	public Effect
{
private:
	D3DXVECTOR2 _ScorePosition;
	D3DXVECTOR2 _ScoresVelocity;
	int _Score;
		int _BeginingY;		//Begining positon in y axis
	//convert position in world to a fixed top-left position
	D3DXVECTOR2 WorldPostionToFixedPostion(D3DXVECTOR2 position);
public:
	ObtainScoreEffect(void);
	ObtainScoreEffect(D3DXVECTOR2 position, int score);
	~ObtainScoreEffect(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
};

