#pragma once
#include "GameObject.h"
class Ground : public GameObject
{
private:
	D3DXVECTOR2 _Size;	//Store object size
public:
	Ground(void);
	Ground(int x, int y, int width, int height);
	~Ground(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	Box GetBoundaryBox();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

