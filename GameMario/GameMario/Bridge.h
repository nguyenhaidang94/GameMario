#pragma once
#include "gameobject.h"
#include "Keyboard.h"
class Bridge :
	public GameObject
{
private:
	int _PartLeft;				//each part of the bridge will be destroy one by one, this will store number left
	D3DXVECTOR2 _StartPosition;	//the 1st block on the left of the bridge
	bool _StartDestroyBridge;

	//manage destroy bridge speed
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	Bridge(void);
	Bridge(int x, int y,  int width, int height);
	~Bridge(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

