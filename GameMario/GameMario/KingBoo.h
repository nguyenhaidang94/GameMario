#pragma once
#include "Monster.h"
#include "Mario.h"
#define KINGBOO_WIDTH 32
#define KINGBOO_HEIGHT 32
#define KINGBOO_VELOCITY_X 1.5f
#define KINGBOO_VELOCITY_Y 6.0f
#define KINGBOO_ACCELERATION 0.3f
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 15

class KingBoo: public Monster
{
protected:
	int _KingBooALive;
public:
	KingBoo();
	~KingBoo();

	//Contructor
	KingBoo(int ObjectTypeID, int PossitionX, int PossitionY);

	//Update object
	void Update();

	//Draw object to screen
	void Render();

	//Removes a gameobject, component or asset.
	void Release();

	//Handling object when colision happened
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//Dead
	void MonsterDead(int MonsterTypeDead);

	//set start and end frame
	void SetFrame(int MonsterType);
};

