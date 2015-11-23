﻿#pragma once
#include "Monster.h"
#define PIRANHAPLANT_WIDTH 32
#define PIRANHAPLANT_HEIGHT 64
#define PIRANHAPLANT_VELOCITY_X 1.5f
#define PIRANHAPLANT_VELOCITY_Y 6.0f
#define PIRANHAPLANT_ACCELERATION 0.3f//chú ý: gia tốc được trừ ra, nhưng vẫn đảm bảo vật vẫn tới trên miệng ống
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 50
#define TIMES_TURN_STOP 3000

class PiranhaPlant : public Monster
{
protected:
	FLOAT _PositionY;
	DWORD _TimeStartStop;									
	DWORD _TimePerStop;
	bool _PiranhaPlantStop;
public:
	PiranhaPlant();
	~PiranhaPlant();
	//Contructor
	PiranhaPlant(int ObjectTypeID, int PossitionX, int PossitionY);

	//Update object
	void Update();

	//Draw object to screen
	void Render();

	//Removes a gameobject, component or asset.
	void Release();

	//Handling object when colision happened
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//Dead
	void PiranhaPlantDead();

	//set start and end frame
	void SetFrame(int PiranhaPlantType);
};
