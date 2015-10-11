#pragma once
#include "dynamicgameobject.h"
#include "EffectManager.h"
#include "Unility.h"

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32
#define BOUNCE_VELOCITY 4
#define FALLDOWN_VELOCITY_DECREASE 0.5

class Block :
	public DynamicGameObject
{
protected:
	int _CurrentFrame;	//manage brick frame in sprite
	int _DefaultY;		//store default brick's position to bring back after brick bounce
	eBlockTypeID _Type;			//color of the block
	bool _IsBounce;
public:
	Block(void);
	~Block(void);
	//Initialize block with basic attribute like velocity, positon, sprite, objectID
	void Initialize(int x, int y);
};

