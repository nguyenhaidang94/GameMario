#pragma once
#include "DynamicGameObject.h"
#include "GameStatistics.h"
#include "EffectManager.h"
class Mushroom
	: public DynamicGameObject
{
private:
	int _CurrentFrame;
	bool _IsSpawnDone;	//Mushroom has finished spawn animation or not
	int _BeginningPositionY;
	bool _IsGoingRight;	//to add velocity y when not stand on any object
public:
	Mushroom(void);
	Mushroom(int x, int y, eGameTag tag);
	~Mushroom(void);

	//Inherited function
	Box GetMovementRangeBox();
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

