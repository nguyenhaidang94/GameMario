#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "GameStatistics.h"

class Monster : public DynamicGameObject
{
protected:
	DWORD _FrameCurrent;
	//location
	DWORD _TimeStartFrame;
	DWORD _TimePerFrame;
	//velocity
	DWORD _TimeStartVelocity;
	DWORD _TimePerVelocity;
	//frame
	DWORD _FrameStart;
	DWORD _FrameEnd;
	//direction: left right
	FLOAT _MonsterVelocity;
	bool _MonsterAlive;
public:
	Monster();
	~Monster();
	//directions Collision
	void DirectionsCollision(GameObject *object, eCollisionDirection collisionDirection);
};