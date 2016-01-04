#pragma once
#include "GameScene.h"
#include "Unility.h"
#include "PlayMap.h"
#include "GameStatistics.h"
#include "SoundManager.h"

class PlayScene :
	public GameScene
{
private:
	eWorldID _WorldID;
	std::map<eWorldID, PlayMap*> _ListMap;

	//Handling collision of map object
	void HandlingCollision();

	bool _IsMusicPlay;	//check if world music is played

	//manage ingame time
	DWORD _FrameStart;
	int _currentLife; //Life of mario when time > 0
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

