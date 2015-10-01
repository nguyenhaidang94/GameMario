#pragma once
#include <vector>
#include "GameScene.h"
#include "PlayScene.h"
#include "MenuScene.h"
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
};

