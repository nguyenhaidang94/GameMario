#pragma once
#include "GameObject.h"
class Ground : public GameObject
{
public:
	Ground(void);
	Ground(int x, int y, int width);
	~Ground(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

