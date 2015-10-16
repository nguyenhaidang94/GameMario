#pragma once
#include "Block.h"
#include "EffectManager.h"
#include "Unility.h"

class Brick : public Block
{
public:
	Brick(void);
	//Object ID is id of brick from map editor
	Brick(int objectID, int x, int y);
	~Brick(void);

	Box GetMovementRangeBox();
	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

