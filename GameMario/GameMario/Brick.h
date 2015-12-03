#pragma once
#include "Block.h"
#include "EffectManager.h"

class Brick : public Block
{
private:
	int _IsAboutToDestroy;	//0 is start, 1 is 1 tick has passed and destroy the birck
public:
	Brick(void);
	//Object ID is id of brick from map editor
	Brick(int objectID, int x, int y);
	~Brick(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

