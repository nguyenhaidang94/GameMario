#pragma once
#include <vector>
#include "PlayScene.h"
#include "MenuScene.h"
#include "StartScene.h"
#include "GameOverScene.h"

class SceneManager
{
private:
	std::map<eSceneID, GameScene*> _ListScene;
	static SceneManager *_Instance;
	eSceneID _CurrentSceneID;
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

