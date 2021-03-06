#pragma once
#include "GameObject.h"
#include "GameStatistics.h"
#include "EffectManager.h"
class FireFlower
	: public GameObject
{
private:
	int _CurrentFrame;
	bool _IsSpawnDone;	//Mushroom has finished spawn animation or not
	int _BeginningPositionY;
	eColorID _Color;			//color of the block


	DWORD _CounPerFrame;
	DWORD _FrameStart;
public:
	FireFlower(void);
	FireFlower(eColorID blockColor, int x, int y);
	~FireFlower(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

