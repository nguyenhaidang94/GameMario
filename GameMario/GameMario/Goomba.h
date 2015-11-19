#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "GameStatistics.h"
#define GOOMBA_WIDTH 32
#define GOOMBA_HEIGHT 32
#define GOOMBA_VELOCITY_X 1.4f
#define GOOMBA_VELOCITY_Y 2.4f
#define GOOMBA_SPEED 1.4f
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 15


class Goomba: public DynamicGameObject
{
	DWORD _FrameCurrent;
	//location
	DWORD _TimeStartFrame;
	DWORD _TimePerFrame;
	//velocity
	DWORD _TimeStartVelocity;
	DWORD _TimePerVelocity;
	//frame
	DWORD _FrameStart;
	DWORD _FrameEnd;
	FLOAT _GoobaVelocity;
	bool _GoombaAlive;
public:
	Goomba();
	~Goomba();
	//Contructor
	Goomba(int ObjectTypeID, int PossitionX, int PossitionY);
	void GoombaDead();

	//set start and end frame
	void SetFrame(int GoombaType);
	//Update object
	void Update();

	//Draw object to screen
	void Render();

	//Removes a gameobject, component or asset.
	void Release();

	//Handling object when colision happened
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

