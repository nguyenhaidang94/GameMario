#pragma once
#include "Monster.h"
#define BULLETFIRE_WIDTH 48
#define BULLETFIRE_HEIGHT 16
#define BULLETFIRE_VELOCITY_X 6.0f
#define BULLETFIRE_VELOCITY_Y 6.0f
#define TIMES_TURN 100

class BulletFire: public Monster
{
protected:
	int _BulletType;
	FLOAT _PositionEndY;
public:
	BulletFire();
	~BulletFire();
	//Contructor
	BulletFire(int ObjectTypeID, int PossitionX, int PossitionY);
	//Bullet move to position new
	void BulletFireMoveY(FLOAT PositionEnd);
	void SetBullet(D3DXVECTOR2 BulletPosition, bool IsLeft, D3DXVECTOR2 PositionKing, int BulletType);
	
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

	void SetPosition(FLOAT PositionX, FLOAT PositionY);
	void SetVelocity(FLOAT VelocityX, FLOAT VelocityY);
	void SetBulletType(int BulletType);
};

