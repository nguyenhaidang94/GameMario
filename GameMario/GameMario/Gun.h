#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"
#include "Unility.h"
#include "Bullet.h"
#include "vector" 
#include "Camera.h"

using namespace std;

class Gun: public DynamicGameObject
{
private:
	vector<Bullet*> ListBullet;
	vector<Bullet*> PoolBullet;
	static Gun *Instance;
	Camera * _Camera;
	bool _IsShoot;
public:
	Gun(void);
	void Update();
	void Render();
	void Shoot(D3DXVECTOR2 MarioPosition, bool IsRight);
	void Release();
	bool GetStatus();
	bool SetStatus();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
	~Gun(void);

	static Gun *GetInstance();
};

