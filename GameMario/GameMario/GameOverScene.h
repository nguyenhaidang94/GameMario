#pragma once
#include "gamescene.h"
class GameOverScene :
	public GameScene
{
private:
	static GameOverScene *Instance;
public:
	GameOverScene(void);
	~GameOverScene(void);
	static GameOverScene *GetInstance();
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

