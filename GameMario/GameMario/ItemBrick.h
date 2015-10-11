#pragma once
#include "Block.h"
#include "Unility.h"
#include "EffectManager.h"
class ItemBrick :
	public Block
{
	bool _IsHitted;		//if item alreadt released, turn to hard block

	//attribute for coin block	
	int _CointLeft;		//store how many coint left
public:
	ItemBrick(void);
	ItemBrick(int objectID, int x, int y);
	~ItemBrick(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

