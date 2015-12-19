#pragma once
#include "Monster.h"
#include "vector" 
#include "BulletFire.h"
using namespace std;

class KingBowserGun: public Monster
{
protected:
	vector<BulletFire*> ListBullet;
	vector<BulletFire*> PoolBullet;
	static KingBowserGun *Instance;
public:
	KingBowserGun();
	~KingBowserGun();
	//Contructor
	KingBowserGun(int ObjectTypeID, int PossitionX, int PossitionY);

	static KingBowserGun *GetInstance();
	//Shoot bullet
	void GunShoot(D3DXVECTOR2 PositionBullet, bool IsLeft, D3DXVECTOR2 PositionKing, int BulletType);

	//Update object
	void Update();

	//Draw object to screen
	void Render();

	//Removes a gameobject, component or asset.
	void Release();

	//Handling object when colision happened
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	
};

