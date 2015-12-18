#pragma once
#include "Block.h"
#include "EffectManager.h"
#include "Mushroom.h"
#include "FireFlower.h"
#include "GameStatistics.h"

class QuestionBlock :
	public Block
{
	bool _IsHitted;		//if item alreadt released, turn to hard block
	GameObject *_SpawmItem;
	eGameTag _SpawmItemTag;

	//manage frame rate
	DWORD _CountPerFrame;
	DWORD _FrameStart;
public:
	QuestionBlock(void);
	QuestionBlock(int objectID, int x, int y);
	~QuestionBlock(void);

	//Inherited funtion
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

