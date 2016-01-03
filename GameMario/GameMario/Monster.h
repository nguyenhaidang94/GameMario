#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "GameStatistics.h"
#include "EffectManager.h"
#define MONSTER_POINT 200

class Monster : public DynamicGameObject
{
protected:
	//location
	DWORD _TimeStartFrame;
	DWORD _TimePerFrame;
	//velocity
	DWORD _TimeStartVelocity;
	DWORD _TimePerVelocity;
	//frame
	DWORD _FrameCurrent;
	DWORD _FrameStart;
	DWORD _FrameEnd;
	//direction: left right
	FLOAT _MonsterVelocityX;
	FLOAT _MonsterVelocityY;
	bool _MonsterAlive;
	//type monster
	int _MonsterTypeID;
public:
	Monster();
	~Monster();
	//directions Collision
	void DirectionsCollision(GameObject *object, eCollisionDirection collisionDirection);
	void DirectionsCollisionNoBox(GameObject *object, eCollisionDirection collisionDirection);
	void UpPoint(int Point);
};