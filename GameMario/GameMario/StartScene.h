#pragma once
#include "GameScene.h"
#include "TextManager.h"
#include "Mario.h"

class StartScene :
	public GameScene
{
private:
	DWORD _StartTime;

	//get position of mario when start world
	D3DXVECTOR2 GetMarioStartPosition();
public:
	StartScene(void);
	~StartScene(void);
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

