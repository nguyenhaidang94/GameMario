#pragma once
#include "Block.h"
#include "FireFlower.h"
#include "Mushroom.h"
#include "Starman.h"
#include "GameStatistics.h"

class ItemBrick :
	public Block
{
	bool _IsHitted;		//if item alreadt released, turn to hard block
	bool _IsInvisible;	//true block is invisible
	GameObject *_SpawmItem;
	eGameTag _SpawmItemTag;
	//attribute for coin block	
	int _CointLeft;		//store how many coint left
public:
	ItemBrick(void);
	ItemBrick(int objectID, int x, int y, string tag);
	~ItemBrick(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

