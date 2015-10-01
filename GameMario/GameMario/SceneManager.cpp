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
		_GameScene->Load();
		break;
	case eStartMap:
		_GameScene = StartScene::GetInstance();
		_GameScene->Load();
		break;
	case ePlay:
		_GameScene = PlayScene::GetInstance();
		_GameScene->Load();
		break;
	case eGameOver:
		_GameScene = GameOverScene::GetInstance();
		_GameScene->Load();
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