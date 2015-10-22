#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "GameStatistics.h"
#include "Unility.h"

class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
	bool _IsCollide;	//check if collided with ground
	D3DXVECTOR2 _CollisionPoint; 
	eGameTag _PipeTag;	//if mario stand on pipe with tag can go to another world, store tag here

	static Mario *Instance;

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

	//New
	//Get an instance of class mario
	static Mario *GetInstance();
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

