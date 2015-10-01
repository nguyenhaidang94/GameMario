#include "GameOverScene.h"

GameOverScene *GameOverScene::Instance = NULL;

GameOverScene::GameOverScene(void)
{
}


GameOverScene::~GameOverScene(void)
{
}

GameOverScene *GameOverScene::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new GameOverScene();
	}
	return Instance;
}

void GameOverScene::Initialize()
{
	
}

void GameOverScene::Update()
{
	
}

void GameOverScene::Render()
{
	
}

void GameOverScene::Release()
{
}

void GameOverScene::Load()
{
	
}