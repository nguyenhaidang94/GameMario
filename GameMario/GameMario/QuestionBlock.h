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

	//manage frame rate
	DWORD count_per_frame;
	DWORD frame_start;
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

