#pragma once
#include "gameobject.h"
#include "GameStatistics.h"

class Coin :
	public GameObject
{
private:
	int _CurrentFrame;

	//control rate
	DWORD count_per_frame;
	DWORD frame_start;
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

