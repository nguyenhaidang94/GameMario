#pragma once
#include "DynamicGameObject.h"
#include "GlobalVariables.h"
#include "SpriteManager.h"
#include "Keyboard.h"

class Mario : public DynamicGameObject
{
private:
	int _CurrentFrame;
	eMarioState _State;
public:
	Mario(void);
	~Mario(void);
	//Inherited funtion
	void Update();
	void Render();
	void Release();
	Box GetBox();

	//New
	//Handling user input
	void HandlingInput();
	//Initialize
	void Initialize();
};

