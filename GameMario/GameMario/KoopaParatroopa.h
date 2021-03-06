#pragma once
#include "KoopaTroopa.h"
#define KOOPAPARATROOPA_WIDTH 32
#define KOOPAPARATROOPA_HEIGHT 48
#define KOOPAPARATROOPA_VELOCITY_X 1.5f
#define KOOPAPARATROOPA_VELOCITY_Y 6.0f
#define KOOPAPARATROOPA31_VELOCITY_Y 2.4f
#define KOOPAPARATROOPA_ACCELERATION 0.3f
#define KOOPAPARATROOPA31_ACCELERATION 0.1f
#define TIMES_TURN 100
#define TIMES_REVIVED_VELOCITY 3000
#define TIMES_TURN_STOP 1000

class KoopaParatroopa: public KoopaTroopa
{
	bool _KoopaParatroopaRevived;
	FLOAT _PositionY;
	DWORD _TimeStartStop;
	DWORD _TimePerStop;
	bool _KoopaParatroopStop;
public:
	KoopaParatroopa();
	~KoopaParatroopa();

	//Contructor
	KoopaParatroopa(int ObjectTypeID, int PossitionX, int PossitionY);
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

