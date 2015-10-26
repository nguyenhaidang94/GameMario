#pragma once
#include "GameScene.h"
#include "Unility.h"
#include "PlayMap.h"
#include "GameStatistics.h"

class PlayScene :
	public GameScene
{
private:
	eWorldID _WorldID;
	std::map<eWorldID, PlayMap*> _ListMap;

	//Handling collision of map object
	void HandlingCollision();
public:
	PlayScene(void);
	~PlayScene(void);
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

