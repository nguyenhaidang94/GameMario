#pragma once
#include "gamescene.h"
#include "Keyboard.h"
#include "TextManager.h"
class TimeUpScene :
	public GameScene
{
private:
	DWORD _StartTime;
public:
	TimeUpScene(void);
	~TimeUpScene(void);

	//Initialize scene
	void Initialize();
	//Free menory use
	void Release();
	//Render scence
	void Render();
	//Update scene
	void Update();
	//Load scene
	void Load();
};

