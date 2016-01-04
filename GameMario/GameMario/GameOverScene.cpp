#include "GameOverScene.h"
#define WAIT_TIME 5000		//wait 5s

GameOverScene::GameOverScene(void)
{
	_SceneID = eSceneID::eGameOver;
}


GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Initialize()
{
	
}

void GameOverScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME || Keyboard::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		GameStatistics::GetInstance()->ChangeScene(eSceneID::eMenu);
	}
}

void GameOverScene::Render()
{
	TextManager::GetInstance()->FixedRender("Game Over", SCREEN_WIDTH/2, 160);
}

void GameOverScene::Release()
{
}

void GameOverScene::Load()
{
	_StartTime = GetTickCount();
}