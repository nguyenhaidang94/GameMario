#pragma once
#include "Monster.h"
#define GOOMBA_WIDTH 32
#define GOOMBA_HEIGHT 32
#define GOOMBA_VELOCITY_X 1.4f
#define GOOMBA_VELOCITY_Y 3.4f
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 15


class Goomba: public Monster
{
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
	void GoombaDead();

	//set start and end frame
	void SetFrame(int GoombaType);
};

