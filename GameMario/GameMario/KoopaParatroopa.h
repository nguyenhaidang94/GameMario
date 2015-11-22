#pragma once
#include "KoopaTroopa.h"
#define KOOPAPARATROOPA_WIDTH 32
#define KOOPAPARATROOPA_HEIGHT 64
#define KOOPAPARATROOPA_VELOCITY_X 1.5f
#define KOOPAPARATROOPA_VELOCITY_Y 6.0f
#define KOOPAPARATROOPA_ACCELERATION 0.3f
#define TIMES_TURN 50
#define TIMES_REVIVED_VELOCITY 3000

class KoopaParatroopa: public KoopaTroopa
{
	bool _KoopaParatroopaRevived;
	//frame type
	DWORD _FrameStartType;
	DWORD _FrameEndType;
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
	void KoopaParatroopaDead();
	
	//set start and end frame
	void SetFrame(int KoopaParatroopaType);
};

