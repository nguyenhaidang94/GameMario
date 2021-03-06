#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "gamescene.h"
#include "Keyboard.h"
#include "TextManager.h"


class GameOverScene :
	public GameScene
{
private:
	DWORD _StartTime;
public:
	GameOverScene(void);
	~GameOverScene(void);

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

