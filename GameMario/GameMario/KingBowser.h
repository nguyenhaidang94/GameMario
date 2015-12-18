#pragma once
#include "Monster.h"
#include "Mario.h"
#define KINGBOWSER_WIDTH 64
#define KINGBOWSER_HEIGHT 64
#define KINGBOWSER_VELOCITY_X 1.5f
#define KINGBOWSER_VELOCITY_Y 6.0f
#define KINGBOWSER_ACCELERATION 0.3f
#define TIMES_TURN 100
#define TIMES_TURN_VELOCITY 15
#define KOOPAPARATROOPA_ACCELERATION 0.3f

class KingBowser : public Monster
{
protected:
	int _KingBowserALive;
	FLOAT _KingBowserBoxWidthMin;					//Khoảng di chuyển của Bowser
	FLOAT _KingBowserBoxWidthMax;
	FLOAT _PositionX;
	//Box
	int _WorldWidth;
	int _BoxWidthMin;
	int _BoxWidthMax;
	//velocity
	DWORD _TimeStartBounce;
	DWORD _TimePerBounce;
	
public:
	KingBowser();
	~KingBowser();

	//Contructor
	KingBowser(int ObjectTypeID, int PossitionX, int PossitionY);

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

	void KingBowserMove();
};

