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
	eBlockTypeID _Type;

	DWORD count_per_frame;
	DWORD frame_start;
public:
	FireFlower(void);
	FireFlower(eBlockTypeID blockType, int x, int y);
	~FireFlower(void);

	//Inherited function
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

