#pragma once
#include "GlobalVariables.h"
#include "GameStatistics.h"

class GameScene
{
protected:
	eSceneID _SceneID;
public:
	GameScene(void);
	GameScene(eSceneID sceneID);
	~GameScene(void);
	//Initialize scene
	virtual void Initialize() = 0;
	//Free menory use
	virtual void Release() = 0;
	//Render scence
	virtual void Render() = 0;
	//Update scene
	virtual void Update() = 0;
	//Load scene
	virtual void Load() = 0;
};

