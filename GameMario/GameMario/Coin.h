#pragma once
#include "gameobject.h"
#include "GameStatistics.h"
#include "EffectManager.h"

class Coin :
	public GameObject
{
private:
	int _CurrentFrame;
	eColorID _Color;			//color of the coin
	//control rate
	DWORD count_per_frame;
	DWORD frame_start;

	bool _IsHittedByBrick;	//play animation when get hitted by brick
public:
	Coin(void);
	Coin(int x, int y);
	~Coin(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

