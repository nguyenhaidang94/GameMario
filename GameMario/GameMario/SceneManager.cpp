#include "SceneManager.h"

SceneManager *SceneManager::Instance = NULL;

SceneManager::SceneManager(void)
{
}


SceneManager::~SceneManager(void)
{
}

SceneManager *SceneManager::GetInstance()
{
	if(Instance == NULL)
	{
		Instance = new SceneManager();
	}
	return Instance;
}

void SceneManager::Initialize()
{
	PlayScene::GetInstance()->Initialize();
	MenuScene::GetInstance()->Initialize();
	StartScene::GetInstance()->Initialize();
	GameOverScene::GetInstance()->Initialize();
	_GameScene = MenuScene::GetInstance();		//start scene is menu
}

void SceneManager::SwitchScene(eSceneID sceneID)
{
	switch (sceneID)
	{
	case eMenu:
		_GameScene = MenuScene::GetInstance();
		break;
	case eStartMap:
		_GameScene = StartScene::GetInstance();
		break;
	case ePlay:
		_GameScene = PlayScene::GetInstance();
		break;
	case eGameOver:
		_GameScene = GameOverScene::GetInstance();
		break;
	default:
		break;
	}
	GameStatistics::GetInstance()->PauseTime();
	_GameScene->Load();
}

void SceneManager::Update()
{
	_GameScene->Update();
}

void SceneManager::Render()
{
	_GameScene->Render();
}

void SceneManager::Release()
{
	
}