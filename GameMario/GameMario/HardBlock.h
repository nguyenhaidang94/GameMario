#pragma once
#include "Block.h"
class HardBlock :
	public Block
{
public:
	HardBlock(void);
	HardBlock(int objectID, int x, int y);
	~HardBlock(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

