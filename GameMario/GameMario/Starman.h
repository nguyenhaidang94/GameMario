#pragma once
#include "DynamicGameObject.h"
#include "GameStatistics.h"
#include "EffectManager.h"

class Starman :
	public DynamicGameObject
{
private:
	int _CurrentFrame;
	bool _IsSpawnDone;	//Mushroom has finished spawn animation or not
	int _BeginningPositionY;
	bool _IsGoingRight;	//to add velocity y when not stand on any object
	eColorID _Color;
	bool _IsJump;
	float _RenderPriority;

	//control frame rate
	DWORD _CounPerFrame;
	DWORD _FrameStart;
public:
	Starman(void);
	Starman(eColorID blockColor, int x, int y);
	~Starman(void);

	//Inherited function
	Box GetMovementRangeBox();
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
};

