#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"


class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
	bool _IsCollide;	//check if collided with ground
	D3DXVECTOR2 _CollisionPoint; 
	bool _IsOnVerticlePipe;
	eGameTag _PipeTag;	//if mario stand on pipe with tag can go to another world, store tag here
public:
	Mario(void);
	~Mario(void);
	//Inherited function
	Box GetMovementRangeBox();
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//New
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
	//if return gametag different eEmpty, switch scence
	eGameTag CheckSwitchWorld();
	//reset _PipeTag
	void ResetPipeTag();
};

