#pragma once
#include "Monster.h"
#define KOOPATROOPA_WIDTH 32
#define KOOPATROOPA_HEIGHT 48
#define KOOPATROOPASTOP_HEIGHT 32
#define KOOPATROOPA_VELOCITY_X 1.5f
#define KOOPATROOPA_VELOCITY_Y 6.0f
#define KOOPATROOPA_ACCELERATION 0.3f
#define TIMES_TURN 100
#define TIMES_REVIVED_VELOCITY 3000

class KoopaTroopa: public Monster
{
protected:
	bool _KoopaTroopaRevived;			//Hồi sinh: sống
	bool _KoopaTroopaStop;				//Đứng yên
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
	void MonsterDead(int MonsterTypeDead);

	//set start and end frame
	void SetFrame(int MonsterType);
};

