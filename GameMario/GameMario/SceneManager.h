#pragma once
#include <vector>
#include "GameScene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "StartScene.h"
#include "GameOverScene.h"
using namespace std;

class SceneManager
{
private:
	GameScene* _GameScene;
	static SceneManager *Instance;
public:
	SceneManager(void);
	~SceneManager(void);
	static SceneManager *GetInstance();
	void Initialize();
	void Update();
	void Render();
	void Release();
	void SwitchScene(eSceneID sceneID);
	//this function use for test collision
	//and show result to messagebox
	void Update(HWND hWnd);
};

