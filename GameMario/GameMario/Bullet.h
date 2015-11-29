#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"
#include "Unility.h"

class Bullet: public DynamicGameObject
{
private:
	int _CurrentFrame;
	bool _IsCollide;
	static Bullet *Instance;
	int _TimeAlive;
	int _Time;
	bool _IsRight;

	bool _IsAlive;
	DWORD _Frame_start;	
	DWORD _Tick_per_frame;

public:
	Bullet(void);
	~Bullet(void);

	D3DXVECTOR2 VanTocNemXien(int time, float v, float alpha);
	Box GetMovementRangeBox();
	void Update();
	void Render();
	bool SetRight(bool IsRight);
	int GetTime();
	int SetTimeAlive(int time);
	int SetTime(int time);
	bool SetIsEF(bool ef);
	bool GetEFStatus();
	bool SetCollision(bool collision);
	D3DXVECTOR2 SetPosition(D3DXVECTOR2 Position);
	D3DXVECTOR2 SetVelocity(D3DXVECTOR2 Velocity);
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);
	static Bullet *GetInstance();
};

