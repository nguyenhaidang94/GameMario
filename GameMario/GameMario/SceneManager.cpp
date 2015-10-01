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
}

void SceneManager::SwitchScene(eSceneID sceneID)
{
	switch (sceneID)
	{
	case eMenu:
		_GameScene = MenuScene::GetInstance();
		break;
	case eStartMap:
		break;
	case ePlay:
		_GameScene = PlayScene::GetInstance();
		_GameScene->Load();
		break;
	case eGameOver:
		break;
	default:
		break;
	}
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