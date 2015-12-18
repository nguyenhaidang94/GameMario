#include "SceneManager.h"

SceneManager *SceneManager::_Instance = NULL;

SceneManager::SceneManager(void)
{
}


SceneManager::~SceneManager(void)
{
}

SceneManager *SceneManager::GetInstance()
{
	if(_Instance == NULL)
	{
		_Instance = new SceneManager();
	}
	return _Instance;
}

void SceneManager::Initialize()
{
	_CurrentSceneID = eSceneID::ePlay;
	_ListScene[eSceneID::eMenu] = new MenuScene();
	_ListScene[eSceneID::eStartMap] = new StartScene();
	_ListScene[eSceneID::ePlay] = new PlayScene();
	_ListScene[eSceneID::eGameOver] = new GameOverScene();
	_ListScene[eSceneID::eTimeUp] = new TimeUpScene();
	_ListScene[_CurrentSceneID]->Load();
}

void SceneManager::SwitchScene(eSceneID sceneID)
{
	GameStatistics::GetInstance()->PauseTime(true);	//pause time for all scene, olny PlayScene stop this
	_CurrentSceneID = sceneID;
	_ListScene[_CurrentSceneID]->Load();
	Camera::GetInstance()->Reset();
}

void SceneManager::Update()
{
	_ListScene[_CurrentSceneID]->Update();

	if(_CurrentSceneID != GameStatistics::GetInstance()->GetSceneID())
	{
		this->SwitchScene(GameStatistics::GetInstance()->GetSceneID());
	}
}

void SceneManager::Render()
{
	_ListScene[_CurrentSceneID]->Render();
}

void SceneManager::Release()
{
	_ListScene[eSceneID::ePlay]->Release();
}