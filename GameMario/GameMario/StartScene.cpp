#include "StartScene.h"
#define WAIT_TIME 1000		//wait 1s

StartScene *StartScene::Instance = NULL;

StartScene::StartScene(void)
{
	_SceneID = eSceneID::eStartMap;
}


StartScene::~StartScene(void)
{
}

StartScene *StartScene::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new StartScene();
	}
	return Instance;
}

void StartScene::Initialize()
{
}

void StartScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME)
	{
		GameStatistics::GetInstance()->ChangeScene(eSceneID::ePlay);
	}
}

void StartScene::Render()
{
	TextManager::GetInstance()->FixedRender("world " + GameStatistics::GetInstance()->GetCurrentWorldName(), SCREEN_WIDTH/2, 160);
	TextManager::GetInstance()->FixedRender("x " + to_string(GameStatistics::GetInstance()->GetLife()), SCREEN_WIDTH/2, 196);
}

void StartScene::Release()
{
}

void StartScene::Load()
{
	_StartTime = GetTickCount();
}