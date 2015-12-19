#pragma once
#include "Monster.h"
#include "Mario.h"
#include "KingBowserGun.h"
#define KINGBOWSER_WIDTH 64
#define KINGBOWSER_HEIGHT 64
#define KINGBOWSER_VELOCITY_X 1.5f
#define KINGBOWSER_VELOCITY_Y 6.0f
#define KINGBOWSER_ACCELERATION 0.3f
#define TIMES_TURN 100
#define TIMES_TURN_SHOOT 1500
#define KOOPAPARATROOPA_ACCELERATION 0.3f

class KingBowser : public Monster
{
protected:
	int _KingBowserALive;
	FLOAT _KingBowserBoxWidthMin;					//Khoảng di chuyển của Bowser
	FLOAT _KingBowserBoxWidthMax;
	FLOAT _PositionX;
	FLOAT _PositionY;
	KingBowserGun _KingBowserGun;
	bool _Left;
	//Box
	int _WorldWidth;
	int _BoxWidthMin;
	int _BoxWidthMax;
	//time bounce
	DWORD _TimeStartBounce;
	DWORD _TimePerBounce;
	//time shoot
	DWORD _TimeStartShoot;
	DWORD _TimePerShoot;
	
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
	void KingBowserGun();
};

