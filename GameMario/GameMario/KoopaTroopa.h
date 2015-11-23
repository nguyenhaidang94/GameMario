#pragma once
#include "Monster.h"
#define KOOPATROOPA_WIDTH 32
#define KOOPATROOPA_HEIGHT 64
#define KOOPATROOPA_VELOCITY_X 3.0f
#define KOOPATROOPA_VELOCITY_Y 3.5f
#define TIMES_TURN 100
#define TIMES_REVIVED_VELOCITY 3000

class KoopaTroopa: public Monster
{
protected:
	bool _KoopaTroopaRevived;
	bool _KoopaTroopaStop;
	//frame type
	DWORD _FrameStartType;
	DWORD _FrameEndType;
public:
	KoopaTroopa();
	~KoopaTroopa();
	//Contructor
	KoopaTroopa(int ObjectTypeID, int PossitionX, int PossitionY);
	void SetKoopaTroopa(int objectTypeID, int positionX, int positionY);
	//Update object
	void Update();

	//Draw object to screen
	void Render();

	//Removes a gameobject, component or asset.
	void Release();
	
	//Handling object when colision happened
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//Dead
	void KoopaTroopaDead();
	
	//set start and end frame
	void SetFrame(int KoopaTroopaType);
};

