#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"
#include "SoundManager.h"

class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
	bool _IsCollide;	//check if collided with ground
	D3DXVECTOR2 _CollisionPoint; 
public:
	Mario(void);
	~Mario(void);
	//Inherited function
	void Update();
	void Render();
	void Release();
	void OnCollision(GameObject *object, eCollisionDirection collisionDirection);

	//New
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

