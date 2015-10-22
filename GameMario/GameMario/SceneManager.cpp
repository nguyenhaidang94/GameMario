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
	_CurrentSceneID = eSceneID::eMenu;
	_LisScene[eSceneID::eMenu] = new MenuScene();
	_LisScene[eSceneID::eStartMap] = new StartScene();
	_LisScene[eSceneID::ePlay] = new PlayScene();
	_LisScene[eSceneID::eGameOver] = new GameOverScene();
	_LisScene[_CurrentSceneID]->Load();
}

void SceneManager::SwitchScene(eSceneID sceneID)
{
	_CurrentSceneID = sceneID;
	GameStatistics::GetInstance()->PauseTime();
	_LisScene[_CurrentSceneID]->Load();
}

void SceneManager::Update()
{
	_LisScene[_CurrentSceneID]->Update();

	if(_CurrentSceneID != GameStatistics::GetInstance()->GetSceneID())
	{
		this->SwitchScene(GameStatistics::GetInstance()->GetSceneID());
	}
}

void SceneManager::Render()
{
	_LisScene[_CurrentSceneID]->Render();
}

void SceneManager::Release()
{
}