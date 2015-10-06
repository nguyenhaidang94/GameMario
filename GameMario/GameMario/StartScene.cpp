#include "StartScene.h"
#define WAIT_TIME 2000		//wait 2s

StartScene *StartScene::Instance = NULL;

StartScene::StartScene(void)
{
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
	_StartTime = GetTickCount();
}

void StartScene::Update()
{
	if((GetTickCount() - _StartTime) > WAIT_TIME)
	{
		SceneManager::GetInstance()->SwitchScene(eSceneID::ePlay);
	}
}

void StartScene::Render()
{
	TextManager::GetInstance()->FixedRender("world " + GameStatistics::GetInstance()->GetCurrentWorldName(), 176, 160);
	TextManager::GetInstance()->FixedRender("x " + to_string(GameStatistics::GetInstance()->GetLife()), 240, 196);
}

void StartScene::Release()
{
}

void StartScene::Load()
{
	_StartTime = GetTickCount();
}