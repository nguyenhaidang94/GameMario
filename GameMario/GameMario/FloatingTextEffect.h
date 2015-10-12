#pragma once
#include "effect.h"
#include "TextManager.h"
#include "Camera.h"
class FloatingTextEffect :
	public Effect
{
private:
	D3DXVECTOR2 _ScorePosition;
	D3DXVECTOR2 _ScoresVelocity;
	string _Score;
	int _BeginingY;		//Begining positon in y axis
	//convert position in world to a fixed top-left position
	D3DXVECTOR2 WorldPostionToFixedPostion(D3DXVECTOR2 position);
public:
	FloatingTextEffect(void);
	FloatingTextEffect(D3DXVECTOR2 position, string score);
	~FloatingTextEffect(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
};

