#pragma once
#include "gameobject.h"
#include "GameStatistics.h"
class Axe :
	public GameObject
{
private:
	int _CurrentFrame;
	bool _IsPauseAlready;
	//control frame rate
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	Axe(void);
	Axe(int x, int y, int width, int height);
	~Axe(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

