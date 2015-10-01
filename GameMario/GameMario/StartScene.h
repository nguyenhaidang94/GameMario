#pragma once
#include "GameScene.h"
#include "TextManager.h"
#include "SceneManager.h"

class StartScene :
	public GameScene
{
private:
	static StartScene *Instance;
	DWORD _StartTime;
public:
	StartScene(void);
	~StartScene(void);
	static StartScene *GetInstance();
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

