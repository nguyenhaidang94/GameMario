#pragma once
#include "GameScene.h"
#include "Keyboard.h"
#include "SceneManager.h"

class MenuScene :
	public GameScene
{
private:
	static MenuScene *Instance;
public:
	MenuScene(void);
	~MenuScene(void);
	static MenuScene *GetInstance();
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
	//---New---//
	void HandlingInput();
};

