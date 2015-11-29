#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"
#include "Unility.h"
#include "Gun.h"

class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
	eMarioState _PreState;
	bool _IsCollide;	//check if collided with ground
	D3DXVECTOR2 _CollisionPoint; 
	eGameTag _PipeTag;	//if mario stand on pipe with tag can go to another world, store tag here
	eGameTag _BrickTag;

	static Mario *Instance;
	

	int _CountTimeJump;
	bool _IsRight;
	DWORD _Frame_start;	
	DWORD _Tick_per_frame;
	DWORD _Tick_per_frame_animation;
	bool _IsGetMushroom;
	bool _IsGetStar;
	bool _IsTranferToSmall;
	bool _IsGetFlowerToTranform;
	bool _IsFlower;
	int _CountStar;
	int _currentFrameBeforeTransformToFlower;
	bool _IsAnimationPipe;
	bool _IsAnimationFlag;
	bool _IsCollisionMonster;
	bool _IsDead;
	int _TimeBeforeTranferToSmall;

	//Get new position for mario in new world base on tag
	D3DXVECTOR2 GetNewMarioPosition(eGameTag tag);

public:
	Mario(void);
	~Mario(void);
	//Inherited function
	Box GetMovementRangeBox();
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//Mario state
	void Jump();
	void Fall();
	void Stand();
	void RunToRight();
	void RunToLeft();
	void PreStandRight();
	void PreStandLeft();
	void Sitting();
	void TranferSmallToBig();
	void TranferBigToSmall();
	void Dead();

	//state flower man
	void TranferBigToFlower();
	void SetSpriteBeforeTransfromFlower();
	void SetSpriteShoot();
	void AutoAnimationPipe();
	void AutoAnimationFlag();
	

	//New
	//Get an instance of class mario
	static Mario *GetInstance();
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

