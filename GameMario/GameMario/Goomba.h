#pragma once
#include "Monster.h"
#define GOOMBA_WIDTH 32
#define GOOMBA_HEIGHT 32
#define GOOMBA_VELOCITY_X 1.5f
#define GOOMBA_VELOCITY_Y 6.0f
#define GOOMBA_ACCELERATION 0.3f
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 15
#define TIMES_PER_DEAD 700


class Goomba: public Monster
{
	FLOAT positionx;
	//time Dead of Goomba
	DWORD _TimeStartDead;
	DWORD _TimePerDead;
public:
	Goomba();
	~Goomba();
	//Contructor
	Goomba(int ObjectTypeID, int PossitionX, int PossitionY);

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

